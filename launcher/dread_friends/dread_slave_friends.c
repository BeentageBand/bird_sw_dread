#define COBJECT_IMPLEMENTATION
#define Dbg_FID DREAD_LAUNCHER_FID,1
#include "dbg_log.h"
#include "dread_launcher.h"
#include "dread_console_worker.h"
#include "data_reg_worker.h"
#include "data_post_worker.h"
#include "hid_worker.h"

union Worker * App_Factory_Method(IPC_TID_T const tid)
{
        static union HID_Worker hid = {NULL};
        static union Data_Post_Worker data_post = {NULL};
        static union Data_Reg_Worker data_reg = {NULL};
        static union Dread_Console_Worker dread_console = {NULL};

        union Worker * wrkr = NULL;
        switch(tid)
        {
        case HID_WORKER_TID:
            Populate_HID_Worker(&hid);
            wrkr = &hid.Worker;
            Dbg_Info("%s: creating HID_Worker",__func__);
            break;
        case DATA_POST_WORKER_TID:
            Populate_Data_Post_Worker(&data_post);
            wrkr = &data_post.Worker;
            Dbg_Info("%s: creating Data_Post_Worker",__func__);
            break;
        case DATA_REG_WORKER_TID:
            Populate_Data_Reg_Worker(&data_reg);
            Dbg_Info("%s: creating Data_Reg_Worker",__func__);
            wrkr = &data_reg.Worker;
            break;
        case DREAD_CONSOLE_WORKER_TID:
            Populate_Dread_Console_Worker(&dread_console);
            Dbg_Info("%s: creating Dread_Console_Worker", __func__);
            wrkr = &dread_console.Worker;
            break;
        default: break;
        }
        return wrkr;
}

