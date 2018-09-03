#include "dread_launcher.h"
#include "hid_worker.h"
#include "ipc_posix.h"

void Dread_Init(void)
{
    static union IPC_POSIX ipc_posix = {NULL};
    Populate_IPC_POSIX(&ipc_posix);
    IPC_Helper_Append(&ipc_posix.IPC_Helper);
}
