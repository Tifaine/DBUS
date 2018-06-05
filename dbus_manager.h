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
#include "dbus_server.h"

/*!
* \file dbus_server.h
* \brief DBUS_Server class.
* \author GUYOT Tifaine
* \version 0.1
*/

/*! \class Server_DBUS
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

  ~DBUS_Manager();

private:
  std::condition_variable cond_var;
  std::mutex mut;
  bool isDataAvailable;
  Server_DBUS* serv;
  void run();
  std::thread* threadManagerDBus;
};

#endif //DBUS_MANAGER_H
