/*
* dbus_server.h
*
* Copyright (c) 2018 STMicroelectronics - All Rights Reserved
* Copyright (c) 2018 CREN - Action de Recherche Tifaifai
*
* Author: Guyot Tifaine <tifaine.guyot@st.com>
*/

#ifndef DBUS_SERVER_H
#define DBUS_SERVER_H
#include <string>
#include <thread>
#include <iostream>
#include <dbus/dbus.h>

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
class Server_DBUS
{
public:
  /*!
  *  \brief builder
  *
  *  Builder of the Server_DBUS class
  *
  *  \param _interfaceName : Name of the dbus interface to use
  *  \param _nameOnBus : Name of the agent. Use for the registration on the dbus.
  */
  Server_DBUS(std::string _interfaceName, std::string _nameOnBus, std::string _nameObject, std::string _functionName);

  /*!
  *  \brief Destructor
  *
  *  Destructor of the Server_DBUS class
  *
  */
  ~Server_DBUS();

  int init_server();

private:
  DBusConnection *conn;
  int run();

  std::string interfaceName;
  std::string nameOnBus;
  std::string nameObject;
  std::string functionName;

  std::thread* threadDBus;
  DBusObjectPathVTable server_vtable;

};
#endif //DBUS_SERVER_H
