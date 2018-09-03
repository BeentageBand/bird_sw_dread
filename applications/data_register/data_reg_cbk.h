#ifndef DATA_REG_CBK_H_
#define DATA_REG_CBK_H_

#include "data_reg_types.h"
#include "cobject.h"

typedef union Data_Reg_Cbk
{
       struct Data_Reg_Cbk_Class _private * _private vtbl;
       struct Object Object;
}Data_Reg_Cbk_T;

typedef struct Data_Reg_Cbk_Class
{
        struct Class Class;
        void (* _private notify_success)(union Data_Reg_Cbk * const);
        void (* _private notify_failure)(union Data_Reg_Cbk * const );
        void (* _private req_status)(union Data_Reg_Cbk * const );
        void (* _private backup)(union Data_Reg_Cbk * const, struct Data_Register_Token * const);
}Data_Reg_Cbk_Class_T;

extern struct Data_Reg_Cbk_Class _private Data_Reg_Cbk_Class;

extern void Populate_Data_Reg_Cbk(union Data_Reg_Cbk * const cbk);

#endif /* DATA_REG_CBK_H_ */
