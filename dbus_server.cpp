/*
* dbus_server.cpp
*
* Copyright (c) 2018 STMicroelectronics - All Rights Reserved
* Copyright (c) 2018 CREN - Action de Recherche Tifaifai
*
* Author: Guyot Tifaine <tifaine.guyot@st.com>
*/
#include "dbus_server.h"

Server_DBUS::Server_DBUS(std::string _interfaceName, std::string _nameOnBus, std::string _nameObject, std::string _functionName)
{
  listMessages = new std::vector<std::string>();
  nameOnBus = _nameOnBus;
  interfaceName = _interfaceName;
  nameObject = _nameObject;
  functionName = _functionName;
}

Server_DBUS::~Server_DBUS()
{

}

int Server_DBUS::init_server()
{
  DBusError err;
  int rv;
  dbus_error_init(&err);
  /* connect to the daemon bus */
  conn = dbus_bus_get(DBUS_BUS_SESSION, &err);
  if (!conn) {
    fprintf(stderr, "Failed to get a session DBus connection: %s\n", err.message);
    dbus_error_free(&err);
    return EXIT_FAILURE;
  }
  std::string firstNomAgent = nameOnBus;
  int indiceName = 0;
  rv = dbus_bus_request_name(conn, nameOnBus.c_str(), DBUS_NAME_FLAG_DO_NOT_QUEUE  , &err);
  while (rv != DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER) {
    dbus_error_free(&err);
    indiceName++;
    nameOnBus = firstNomAgent + std::to_string(indiceName);
    rv = dbus_bus_request_name(conn, (nameOnBus).c_str(), DBUS_NAME_FLAG_DO_NOT_QUEUE  , &err);
  }
  threadDBus = new std::thread(&Server_DBUS::run,this);
  threadDBus->detach();
}

int Server_DBUS::run()
{
  DBusMessage *message;
  DBusError err;
  while(1)
  {
    dbus_connection_read_write(conn, -1);
    message = dbus_connection_pop_message(conn);
    while(message!=NULL)
    {
      if(dbus_message_is_method_call(message, interfaceName.c_str(), functionName.c_str()))
      {
        const char *msg;
        DBusMessageIter args;
        char* param = "";
        // read the arguments
        if (!dbus_message_iter_init(message, &args))
        {
          fprintf(stderr, "Message has no arguments!\n");
        }
        else if (DBUS_TYPE_STRING != dbus_message_iter_get_arg_type(&args))
        {
          fprintf(stderr, "Argument is not string!\n");
        }
        else
        {
          dbus_message_iter_get_basic(&args, &param);
        }

        *newMessage = true;
        listMessages->push_back(param);
        cv->notify_one();
      }else if(dbus_message_is_method_call(message, "org.freedesktop.DBus.Properties", "GetAll"))
      {
        dbus_message_unref(dbus_message_new_method_return(message));

        std::cout<<"Pas voulu"<<std::endl;
      }
      message = dbus_connection_pop_message(conn);
    }
  }
  return 0;
}
