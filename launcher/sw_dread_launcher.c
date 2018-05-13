#define COBJECT_IMPLEMENTATION
#include "sw_dread_launcher_app_def.h"
#include "data_collector_wrkr.h"
#include "dread_stdin_wrkr.h"
#include "ipc.h"
#include "ipc_posix.h"

int main(void)
{
  static IPC_POSIX_T posix;
  Data_Collector_Wrkr_T * t_dc = NULL;
  Dread_StdIn_Wrkr_T * t_ds = NULL;

  Populate_IPC_POSIX(&posix);
  IPC_Helper_Append(&posix);

  t_dc = Allocate_Data_Collector_Wrkr();
  t_ds = Allocate_Dread_StdIn_Wrkr();

  IPC_Run(DREAD_DC_TID);
  IPC_Run(DREAD_DS_TID);

  while(1){}
  return 0;
}
