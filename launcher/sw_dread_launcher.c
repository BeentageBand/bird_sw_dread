#define COBJECT_IMPLEMENTATION
#include "sw_dread_launcher_app_def.h"
#include "data_collector_wrkr.h"
int main(void)
{
   Data_Collector_Wrkr_T * t_dc = NULL;
   Allocate_Data_Collector_Wrkr(&t_dc);
   t_dc->vtbl->on_start(t_dc);
   return 0;
}
