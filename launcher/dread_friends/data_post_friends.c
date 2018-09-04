#define COBJECT_IMPLEMENTATION

#include "data_post_cbk.h"
#include "ipc.h"

static void data_post_cbk_delete(struct Object * const obj);
static void data_post_cbk_open_session(union Data_Post_Cbk * const, struct Data_Post_Session * const);
static void data_post_cbk_close_session(union Data_Post_Cbk * const, struct Data_Post_Session * const);
static void data_post_cbk_start_packet(union Data_Post_Cbk * const, struct Data_Post_Packet * const);
static void data_post_cbk_post_packet(union Data_Post_Cbk * const, struct Data_Post_Packet * const);
static size_t data_post_cbk_get_file_size(union Data_Post_Cbk * const);
static char const * data_post_cbk_get_filename(union Data_Post_Cbk * const);

static union Data_Post_Cbk Data_Post_Cbk = {NULL};
struct Data_Post_Cbk_Class Data_Post_Cbk_Class =
{
        {data_post_cbk_delete, NULL},
        data_post_cbk_open_session,
        data_post_cbk_close_session,
        data_post_cbk_start_packet,
        data_post_cbk_post_packet,
        data_post_cbk_get_file_size,
        data_post_cbk_get_filename
};

void data_post_cbk_delete(struct Object * const obj)
{}

void data_post_cbk_open_session(union Data_Post_Cbk * const this, struct Data_Post_Session * const session)
{}

void data_post_cbk_close_session(union Data_Post_Cbk * const this, struct Data_Post_Session * const session)
{}

void data_post_cbk_start_packet(union Data_Post_Cbk * const this, struct Data_Post_Packet * const packet)
{}

void data_post_cbk_post_packet(union Data_Post_Cbk * const this, struct Data_Post_Packet * const packet)
{}

size_t data_post_cbk_get_file_size(union Data_Post_Cbk * const this)
{
    return 90500UL; //TODO
}

char const * data_post_cbk_get_filename(union Data_Post_Cbk * const this)
{
    return "this-name.txt"; //TODO
}


void Populate_Data_Post_Cbk(union Data_Post_Cbk * const this)
{
    if(NULL == Data_Post_Cbk.vtbl)
    {
        Data_Post_Cbk.vtbl = & Data_Post_Cbk_Class;
    }
    _clone(this, Data_Post_Cbk);
}

void data_post_on_data_reg_failure(union Data_Post_Worker * const this, union Mail * const mail)
{}
