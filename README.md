# DBUS
An exemple of C++ DBUS client and server

# compile
server : g++ server_main.cpp dbus_server.cpp dbus_manager.cpp $(pkg-config  --cflags dbus-1 glib-2.0 --libs gio-2.0 glib-2.0 dbus-1) -std=c++11 -o server

client : g++ client_main.cpp dbus_client.cpp $(pkg-config  --cflags dbus-1 glib-2.0 --libs gio-2.0 glib-2.0 dbus-1) -o client
