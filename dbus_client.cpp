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
  interfaceName = _interfaceName;
  objectName = _objectName;
  functionName = _functionName;

  connClient = g_bus_get_sync(G_BUS_TYPE_SESSION, NULL, &error);



  return 1;
}

/*!
*  \fn sendMessageDBUS(std::string messageToSend)
*  \brief Send a dbus message
*
*  \param messageToSend : The message that has to be sent
*
*  \return true if the message is sent, -1 if not;
*
*/
int DBUS_Client::sendMessageDBUS(std::string messageToSend, std::string nomAgentToSend,std::string interfaceToSend)
{
  proxy = g_dbus_proxy_new_sync(connClient,
    G_DBUS_PROXY_FLAGS_DO_NOT_LOAD_PROPERTIES ,
    NULL,				/* GDBusInterfaceInfo */
    nomAgentToSend.c_str(),		/* name */
    interfaceToSend.c_str(),	/* object path */
    interfaceName.c_str(),	/* interface */
    NULL,				/* GCancellable */
    &error);
    g_assert_no_error(error);

    g_dbus_proxy_call(proxy,"Contact",g_variant_new ("(s)",messageToSend.c_str()),G_DBUS_CALL_FLAGS_NONE,-1,NULL,NULL, NULL);

  return 1;
}
