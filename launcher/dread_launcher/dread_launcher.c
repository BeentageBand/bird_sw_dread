#include "dread_launcher.h"
#include "application.h"

int main(void)
{
    Dread_Init();
    static union Application dread_application = {NULL};
    Populate_Application(&dread_application, App_Factory_Method);
    App_Stat_T rc = dread_application.vtbl->startup(&dread_application);
    _delete(&dread_application);
    return rc;
}