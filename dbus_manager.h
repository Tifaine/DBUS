/*
* dbus_manager.h
*
* Copyright (c) 2018 STMicroelectronics - All Rights Reserved
* Copyright (c) 2018 CREN - Action de Recherche Tifaifai
*
* Author: Guyot Tifaine <tifaine.guyot@st.com>
*/

#ifndef DBUS_MANAGER_H
#define DBUS_MANAGER_H
#include <vector>
#include <iterator> // std::ostream_iterator
#include "dbus_server.h"
#include "dbus_client.h"
#include "../Shared_Memory/sharedMemory.h"


/*!
* \file dbus_manager.h
* \brief DBUS_Manager class.
* \author GUYOT Tifaine
* \version 0.1
*/

/*! \class DBUS_Manager
* \brief Class which manage the incoming DBUS message.
*
*  This class manage all the incoming message and inform the MTPS when he received a message.
*/
class DBUS_Manager
{
public:
  /*!
  *  \brief builder
  *
  *  Builder of the DBUS_Manager class
  *
  */
  DBUS_Manager();
  DBUS_Manager(std::string _interfaceName, std::string _nameOnBus, std::string _nameObject,
     std::string _functionName, std::condition_variable* _cond_var, bool* _isDataAvailable,
    std::vector<std::string> *_listMessagesParent);
  ~DBUS_Manager();

  void envoiMessage_DBUS(std::string messageToSend, std::string nomAgentToSend,std::string interfaceToSend);

  bool* getParentWatcher(){return parentWatcher;}

  std::string getNameOnBus(){return serv->getNameOnBus();}

private:
  std::condition_variable cond_var;
  std::mutex mut;

  bool isDataAvailable;
  Server_DBUS* serv;
  DBUS_Client* client;

  void run();
  std::thread* threadManagerDBus;
  bool* parentWatcher;
  std::condition_variable* cond_var_Parent;
  std::vector<std::string> *listMessagesParent;
};

#endif //DBUS_MANAGER_H
