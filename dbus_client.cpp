/*
* dbus_client.cpp
*
* Copyright (c) 2018 STMicroelectronics - All Rights Reserved
* Copyright (c) 2018 CREN - Action de Recherche Tifaifai
*
* Author: Guyot Tifaine <tifaine.guyot@st.com>
*/


#include "dbus_client.h"
#include <iostream>

GDBusConnection *connClient;
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
int initDBus(std::string _interfaceName, std::string _objectName, std::string _functionName)
{
  GError *error = NULL;
  interfaceName = _interfaceName;
  objectName = _objectName;
  functionName = _functionName;

  connClient = g_bus_get_sync(G_BUS_TYPE_SESSION, NULL, &error);
  if(!connClient)
  {
    fprintf(stderr, "Failed to get a session DBus connection: %s\n", error->message);
    return -1;
  }

  return 1;
}

/*!
*  \fn sendMessageDBUS(std::string messageToSend)
*  \brief Send a dbus message
*
*
*  \param messageToSend : The message that has to be sent
*
*  \return true if the message is sent, -1 if not;
*
*/
int sendMessageDBUS(std::string messageToSend, std::string nomAgentToSend)
{
  GError *error = NULL;
  GDBusMessage *msg;
  msg = g_dbus_message_new_method_call (nomAgentToSend.c_str(),
  objectName.c_str(), interfaceName.c_str(), functionName.c_str());

  g_dbus_message_set_body (msg, g_variant_new ("(s)", messageToSend.c_str()));
  g_dbus_connection_send_message(connClient,msg,G_DBUS_SEND_MESSAGE_FLAGS_NONE,-NULL,&error);
  return 1;
}
