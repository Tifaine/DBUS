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

#include <glib.h>
#include <string>
#include <glib-object.h>
#include <glib/gprintf.h>
#include <gio/gio.h>
#include <dbus/dbus-glib-lowlevel.h>

/*!
* \file dbus_client.h
* \brief DBus client, allow agent to send DBUS message.
* \author GUYOT Tifaine
* \version 0.1
*/


/*!
*  \fn initDBus()
*  \brief Init the dbus client
*
*  \return 1 if init is ok, -1 if it is not.
*
*/
int initDBus(std::string _interfaceName, std::string _objectName, std::string _functionName);

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

#endif //DBUS_CLIENT_H
