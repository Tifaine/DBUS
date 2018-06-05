#include "dbus_server.h"
#include <stdio.h>
#include <unistd.h>
int main()
{
  Server_DBUS serv("org.interfaceGit","interfaceGit.Alice","/interfaceGit/Contact","Contact");
  serv.init_server();

  while(1)
  {
    sleep(1);
  };
  return 0;
}
