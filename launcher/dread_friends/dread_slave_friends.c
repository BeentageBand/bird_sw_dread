#include "dread_launcher.h"
#include "ipc_posix.h"

void Dread_Init(void)
{
    static union IPC_POSIX ipc_posix = {NULL};
    Populate_IPC_POSIX(&ipc_posix);
    IPC_Helper_Append(&ipc_posix.IPC_Helper);
}
union Worker * App_Factory_Method(IPC_TID_T const tid) {return NULL;}