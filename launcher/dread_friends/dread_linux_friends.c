#include "dbg_log_ext.h"
#include "dread_launcher.h"
#include "hid_worker.h"
#include "sem.h"
#include "ipc_posix.h"

static union Semaphore Dbg_Semaphore = {NULL};

bool Dbg_Log_Available(void)
{
    return Dbg_Semaphore.vtbl->wait(&Dbg_Semaphore, 200U);
}

void Dbg_Log_Sync(void)
{
    Dbg_Semaphore.vtbl->post(&Dbg_Semaphore);
}

void Dread_Init(void)
{
    static union IPC_POSIX ipc_posix = {NULL};
    Populate_IPC_POSIX(&ipc_posix);
    IPC_Helper_Append(&ipc_posix.IPC_Helper);
    Populate_Semaphore(&Dbg_Semaphore, 1U);
}
