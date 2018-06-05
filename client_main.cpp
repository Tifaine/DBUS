#include "dbus_client.h"
#include <stdio.h>

int main()
{
  initDBus();
  sendMessageDBUS("Wololo","TitiFirst");
  
  return 0;
}
