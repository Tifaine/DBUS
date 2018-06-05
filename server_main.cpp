#include "dbus_server.h"
#include <stdio.h>
#include <unistd.h>
int main()
{
  Server_DBUS serv("ContactSMA","TitiFirst");
  serv.init_server();

  while(1)
  {
    sleep(1);
  };
  return 0;
}
