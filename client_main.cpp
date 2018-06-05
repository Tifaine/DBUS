#include "dbus_client.h"
#include <stdio.h>

int main()
{
  initDBus("org.interfaceGit","/interfaceGit/Contact","Contact");
  sendMessageDBUS("Wololo","interfaceGit.Alice");

  return 0;
}
