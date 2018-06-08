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
  client = new DBUS_Client("org.interfaceGit","/interfaceGit/Contact","Contact");
  serv = new Server_DBUS("org.interfaceGit","interfaceGit.Alice","/interfaceGit/Contact","Contact");
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
}

DBUS_Manager::~DBUS_Manager()
{

}

void DBUS_Manager::envoiMessage_DBUS(std::string messageToSend, std::string nomAgentToSend)
{
  //client->sendMessageDBUS(messageToSend,nomAgentToSend);
  client->sendMessageDBUS("Bonjour",nomAgentToSend);
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
      std::cout<<(serv->getListMessage()->back())<<std::endl;
      *parentWatcher = true;
      listMessagesParent->push_back(serv->getListMessage()->back());
      cond_var_Parent->notify_one();
      //Do whatever you want with your message here !
      serv->getListMessage()->pop_back();
    }
  }
}
