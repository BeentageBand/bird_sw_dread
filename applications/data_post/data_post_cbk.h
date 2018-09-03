/*
 * data_post_cbk.h
 *
 *  Created on: Sep 1, 2018
 *      Author: uids6144
 */

#ifndef DATA_POST_CBK_H_
#define DATA_POST_CBK_H_

#include "data_post_types.h"
#include "cobject.h"

typedef union Data_Post_Cbk
{
       struct Data_Post_Cbk_Class _private * _private vtbl;
       struct Object Object;
}Data_Post_Cbk_T;

typedef struct Data_Post_Cbk_Class
{
        struct Class Class;
        void (* _private open_session)(union Data_Post_Cbk * const, struct Data_Post_Session * const);
        void (* _private close_session)(union Data_Post_Cbk * const, struct Data_Post_Session * const);
        void (* _private start_packet)(union Data_Post_Cbk * const, struct Data_Post_Packet * const);
        void (* _private post_packet)(union Data_Post_Cbk * const, struct Data_Post_Packet * const);
        size_t (* _private get_file_size)(union Data_Post_Cbk * const);
        char const * (* _private get_filename)(union Data_Post_Cbk * const);
}Data_Post_Cbk_Class_T;

extern struct Data_Post_Cbk_Class _private Data_Post_Cbk_Class;

extern void Populate_Data_Post_Cbk(union Data_Post_Cbk * const cbk);


#endif /* DATA_POST_CBK_H_ */
