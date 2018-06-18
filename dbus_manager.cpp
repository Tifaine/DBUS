/*
* dbus_manager.cpp
*
* Copyright (c) 2018 STMicroelectronics - All Rights Reserved
* Copyright (c) 2018 CREN - Action de Recherche Tifaifai
*
* Author: Guyot Tifaine <tifaine.guyot@st.com>
*/

#include "dbus_manager.h"

DBUS_Manager::DBUS_Manager()
{
  //initDBus("org.interfaceGit","/interfaceGit/Contact","Contact");
  client = new DBUS_Client("org.interfaceGit","/org/interfaceGit/Contact","Contact");
  serv = new Server_DBUS("org.interfaceGit","org.interfaceGit.Alice","/org/interfaceGit/Contact","Contact");
  serv->setCV(&cond_var);
  serv->setNewMessage(&isDataAvailable);
  serv->init_server();

  parentWatcher = new bool;
  cond_var_Parent = new std::condition_variable();
  threadManagerDBus = new std::thread(&DBUS_Manager::run,this);
  listMessagesParent = new std::vector<std::string>;
}

DBUS_Manager::DBUS_Manager(std::string _interfaceName, std::string _nameOnBus,
  std::string _nameObject, std::string _functionName,
  std::condition_variable* _cond_var, bool* _isDataAvailable,
  std::vector<std::string> *_listMessagesParent)
  {
    client = new DBUS_Client(_interfaceName,_nameObject,_functionName);

    serv = new Server_DBUS(_interfaceName,_nameOnBus,_nameObject,_functionName);

    cond_var_Parent = _cond_var;
    parentWatcher = _isDataAvailable;
    listMessagesParent = _listMessagesParent;

    serv->setCV(&cond_var);
    serv->setNewMessage(&isDataAvailable);
    serv->init_server();
    threadManagerDBus = new std::thread(&DBUS_Manager::run,this);
    threadManagerDBus->detach();
  }

  DBUS_Manager::~DBUS_Manager()
  {

  }

  void DBUS_Manager::envoiMessage_DBUS(std::string messageToSend, std::string nomAgentToSend, std::string interfaceToSend)
  {

    Shared_Memory sh;
    srand (time(NULL));
    sh.setKey(rand()%2048);
    sh.setSize(messageToSend.size());
    uint8_t* buffer;
    buffer = sh.getSharedDatas();

    for(int i=0;i<messageToSend.size();i++)
    {
      buffer[i]=messageToSend.at(i);
    }

    std::string toSend;
    toSend+=(std::to_string(sh.getKey()));
    toSend+="|";
    toSend+=(std::to_string(messageToSend.size()));

    client->sendMessageDBUS(toSend,nomAgentToSend,interfaceToSend);
  }

  void DBUS_Manager::run()
  {
    
    while(1)
    {
      std::unique_lock<std::mutex> lk(mut);
      cond_var.wait(lk, [this]{return isDataAvailable;});
      isDataAvailable = false;
      while (!serv->getListMessage()->empty())
      {
        *parentWatcher = true;
        std::string newMessage = serv->getListMessage()->back();
        int clef=-1;
        int taille;
        int indice = 0;
        while((newMessage.at(indice)!= '|') && indice<newMessage.size())
        {
          indice++;
        }

        if(indice != newMessage.size())
        {
          std::string keyString = newMessage.substr(0,indice);
          std::string sizeString = newMessage.substr(indice+1,newMessage.size());

          clef = std::stoi(keyString);
          taille = std::stoi(sizeString);
        }
        Shared_Memory sh;
        sh.setKey(clef);
        sh.setSize(taille);
        uint8_t* buffer;
        buffer = (uint8_t*)malloc(sizeof(uint8_t)*taille);
        buffer = sh.getSharedDatas();
        std::vector<uint8_t> v(buffer, buffer+taille);
        std::string str(v.begin(), v.end());
        listMessagesParent->push_back(str);
        cond_var_Parent->notify_one();
        //Do whatever you want with your message here !
        serv->getListMessage()->pop_back();
      }
    }
  }
