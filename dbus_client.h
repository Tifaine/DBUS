/*
* dbus_client.h
*
* Copyright (c) 2018 STMicroelectronics - All Rights Reserved
* Copyright (c) 2018 CREN - Action de Recherche Tifaifai
*
* Author: Guyot Tifaine <tifaine.guyot@st.com>
*/

#ifndef DBUS_CLIENT_H
#define DBUS_CLIENT_H

#include <string>
#include <stdio.h>
#include <dbus/dbus.h>

/*!
* \file dbus_client.h
* \brief DBus client, allow agent to send DBUS message.
* \author GUYOT Tifaine
* \version 0.1
*/

class DBUS_Client
{
public:
  /*!
  *  \brief builder
  *
  *  Builder of the DBUS_Client class
  *
  */
  DBUS_Client(std::string _interfaceName, std::string _objectName, std::string _functionName);
  ~DBUS_Client();

  /*!
  *  \fn sendMessageDBUS(std::string messageToSend)
  *  \brief Send a dbus message
  *
  *
  *  \param messageToSend : The message that has to be sent
  *  \param nomAgentToSend : The name of the agent the message has to be sent
  *  \return true if the message is sent, -1 if not;
  *
  */
  int sendMessageDBUS(std::string messageToSend, std::string nomAgentToSend);

private:
  DBusConnection *connClient;
  std::string interfaceName;
  std::string objectName;
  std::string functionName;

  /*!
  *  \fn initDBus()
  *  \brief Init the dbus client
  *
  *  \return 1 if init is ok, -1 if it is not.
  *
  */
  int initDBus(std::string _interfaceName, std::string _objectName, std::string _functionName);


};
#endif //DBUS_CLIENT_H
