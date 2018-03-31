#define COBJECT_IMPLEMENTATION
#include "sw_dread_launcher_app_def.h"
#include "data_collector_wrkr.h"
#include "ipc.h"
#include "ipc_posix.h"

int main(void)
{
  static IPC_POSIX_T posix;
  Data_Collector_Wrkr_T * t_dc = NULL;

  Populate_IPC_POSIX(&posix);
  IPC_Helper_Append(&posix);

  Allocate_Data_Collector_Wrkr(&t_dc);
  IPC_Run(DREAD_DC_TID);
  while(1){}
  return 0;
}
