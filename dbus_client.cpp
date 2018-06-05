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

/*!
*  \fn initDBus()
*  \brief Init the dbus client
*
*  \return 1 if init is ok, -1 if it is not.
*
*/
int initDBus()
{
  GError *error = NULL;
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
  std::string nomAgent = "org.agentTheseTifG."+nomAgentToSend;
  //We want to send a message, we must verify the integrity of the receiver first.
  //If we want to send a message to AMS or ACC, it's not necessary to indicate the complete AID of the agent.
  //It can be dangerous, AMS is not always on the same board of the agent.

  GDBusMessage *msg;
  std::string objectName = "/org/agentTheseTifG/SMAInterface";
  std::string interfaceToJoin = "org.agentTheseTifG.SMAInterface";


  msg = g_dbus_message_new_method_call (nomAgent.c_str(),
  objectName.c_str(), interfaceToJoin.c_str(), "Contact");

  g_dbus_message_set_body (msg, g_variant_new ("(s)", messageToSend.c_str()));
  std::cout<<g_dbus_connection_send_message(connClient,msg,G_DBUS_SEND_MESSAGE_FLAGS_NONE,-NULL,&error)<<std::endl;
  return 1;
}
