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
  serv = new Server_DBUS("org.interfaceGit","interfaceGit.Alice","/interfaceGit/Contact","Contact");
  serv->setCV(&cond_var);
  serv->setNewMessage(&isDataAvailable);
  serv->init_server();
  threadManagerDBus = new std::thread(&DBUS_Manager::run,this);
}

DBUS_Manager::~DBUS_Manager()
{

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
      //Do whatever you want with your message here !


      serv->getListMessage()->pop_back();
    }
  }
}
