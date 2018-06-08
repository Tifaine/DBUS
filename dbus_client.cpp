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

DBUS_Client::DBUS_Client(std::string _interfaceName, std::string _objectName, std::string _functionName)
{
  initDBus(_interfaceName,_objectName,_functionName);
}

DBUS_Client::~DBUS_Client()
{

}

/*!
*  \fn initDBus()
*  \brief Init the dbus client
*
*  \return 1 if init is ok, -1 if it is not.
*
*/
int DBUS_Client::initDBus(std::string _interfaceName, std::string _objectName, std::string _functionName)
{
  DBusError err;
  interfaceName = _interfaceName;
  objectName = _objectName;
  functionName = _functionName;
  dbus_error_init(&err);


  /* connect to the daemon bus */
  connClient = dbus_bus_get(DBUS_BUS_SESSION, &err);
  if (!connClient) {
    fprintf(stderr, "Failed to get a session DBus connection: %s\n", err.message);
    dbus_error_free(&err);

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
int DBUS_Client::sendMessageDBUS(std::string messageToSend, std::string nomAgentToSend)
{
  DBusMessage *msg;
  msg = dbus_message_new_method_call (nomAgentToSend.c_str(),
  objectName.c_str(), interfaceName.c_str(), functionName.c_str());
  const char *v_STRING = messageToSend.c_str();
  dbus_message_append_args(msg,DBUS_TYPE_STRING,&v_STRING);
  std::cout<<dbus_connection_send(connClient,msg,NULL)<<std::endl;
  return 1;
}
