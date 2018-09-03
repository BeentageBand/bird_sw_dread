#define COBJECT_IMPLEMENTATION
#define Dbg_FID DATA_POST_FID, 3

#include "data_post_cbk.h"
#include "data_post_fsm.h"
#include "data_post_set.h"
#include "dbg_log.h"
#include "ipc.h"
#include "tmr.h"

#define DATA_POST_RETRY_SESSION_TOUT_MS (300000UL) // 5min
#define DATA_POST_PACKET_TOUT_MS        (30000UL)  // 30 sec
#define DATA_POST_SESSION_TOUT_MS       (30000UL)  // 30 sec

static void data_post_delete(struct Object * const obj);
static bool data_post_ready_guard(union State_Machine * const st_m, union St_Machine_State * const state);
static bool data_post_session_guard(union State_Machine * const st_m, union St_Machine_State * const state);
static bool data_packet_guard(union State_Machine * const st_m, union St_Machine_State * const state);
static void data_post_open_session(union State_Machine * const st_m);
static void data_post_start_packet(union State_Machine * const st_m);
static void data_post_close_session(union State_Machine * const st_m);
static void data_post_end(union State_Machine * const st_m);
static void data_post_packet(union State_Machine * const st_m);

FSM_Declare_Chart(DATA_POST_FSM, Data_Post_St_Chart)

static union Data_Post_FSM Data_Post_FSM = {NULL};
static union Data_Post_Cbk Data_Post_Cbk = {NULL};
static union St_Machine_State Data_Post_States[DATA_POST_MAX_STID] = {0};
static union Timer Data_Post_Timer[3] = {0};
static struct Data_Post_Session Data_Post_Session = {NULL, NULL};
static struct Data_Post_Packet Data_Post_Packet = {NULL, 0};

union Data_Post_FSM_Class Data_Post_FSM_Class =
{
        {data_post_delete, NULL}
};

void data_post_delete(struct Object * const obj){}

bool data_post_ready_guard(union State_Machine * const st_m, union St_Machine_State * const state)
{
    union Data_Post_FSM * const this = _cast(Data_Post_FSM, st_m);
    Isnt_Nullptr(this, false);
    Isnt_Nullptr(this->retry_session_tmr, false);
    bool rc = Data_Post_Cbk.vtbl->get_file_size(&Data_Post_Cbk) > 0 &&
            DATA_POST_CONN_OK == this->conn_status;
    union Timer * const tmr = this->retry_session_tmr;
    if(!rc)
    {
        tmr->vtbl->start(tmr);
    }
    return rc;
}

bool data_post_session_guard(union State_Machine * const st_m, union St_Machine_State * const state)
{
    return true; //TODO
}

bool data_packet_guard(union State_Machine * const st_m, union St_Machine_State * const state)
{
    return true; //TODO
}

void data_post_open_session(union State_Machine * const st_m)
{
    union Data_Post_FSM * const this = _cast(Data_Post_FSM, st_m);
    Isnt_Nullptr(this, );
    Isnt_Nullptr(this->retry_session_tmr, );
    Isnt_Nullptr(this->session, );
    union Timer * tmr = this->retry_session_tmr;

    tmr->vtbl->stop(tmr);
    this->session->filename = Data_Post_Cbk.vtbl->get_filename(&Data_Post_Cbk);
    this->session->https_url = DATA_POST_PACKET_SESSION_URL;
    this->session->https_passwd = DATA_POST_PACKET_SESSION_PASSWORD;
    Data_Post_Cbk.vtbl->open_session(&Data_Post_Cbk, this->session);

    tmr = this->session_res_tmr;
    tmr->vtbl->start(tmr);

}

static void data_post_start_packet(union State_Machine * const st_m)
{
    union Data_Post_FSM * const this = _cast(Data_Post_FSM, st_m);
    Isnt_Nullptr(this, false);
    Isnt_Nullptr(this->packet_res_tmr, false);


    this->packet->data_left = Data_Post_Cbk.vtbl->get_file_size(&Data_Post_Cbk);
    Data_Post_Cbk.vtbl->start_packet(&Data_Post_Cbk, this->packet);
    this->packet_res_tmr->vtbl->start(this->packet_res_tmr);
}

void data_post_close_session(union State_Machine * const st_m)
{
    Data_Post_Cbk.vtbl->close_session(&Data_Post_Cbk);
}

void data_post_end(union State_Machine * const st_m)
{
    union Data_Post_FSM * const this = _cast(Data_Post_FSM, st_m);
    Isnt_Nullptr(this, false);
    Isnt_Nullptr(this->packet_res_tmr, false);
    Isnt_Nullptr(this->retry_session_tmr, false);
    Isnt_Nullptr(this->session_res_tmr, false);
    union Timer * tmr = this->retry_session_tmr;

    tmr->vtbl->stop(tmr);
    tmr = this->session_res_tmr;
    tmr->vtbl->stop(tmr);
    tmr = this->retry_session_tmr;
    tmr->vtbl->start(tmr);
}

void data_post_packet(union State_Machine * const st_m)
{
    union Data_Post_FSM * const this = _cast(Data_Post_FSM, st_m);
    Isnt_Nullptr(this, );
    Isnt_Nullptr(this->packet_res_tmr, );
    Isnt_Nullptr(this->packet, );
    Data_Post_Cbk.vtbl->post_packet(&Data_Post_Cbk, this->packet);
}

void Populate_Data_Post_FSM(union Data_Post_FSM * const this)
{
    if(NULL == Data_Post_FSM.vtbl)
    {
        Populate_FSM(&Data_Post_FSM.FSM,
                Data_Post_St_Chart, Num_Elems(Data_Post_St_Chart),
                Data_Post_States, Num_Elems(Data_Post_States));
        Object_Init(&Data_Post_FSM.Object,
                &Data_Post_FSM_Class.Class,
                sizeof(Data_Post_FSM_Class.FSM));
        Populate_Data_Post_Cbk(&Data_Post_Cbk);
        Data_Post_FSM.packet_res_tmr = Data_Post_Timer;
        Data_Post_FSM.retry_session_tmr = Data_Post_Timer + 1;
        Data_Post_FSM.session_res_tmr = Data_Post_Timer + 2;
        Data_Post_FSM.session = &Data_Post_Session;
        Data_Post_FSM.conn_status = DATA_POST_CONN_MAX;
        Data_Post_FSM.packet = &Data_Post_Packet;
    }
    _clone(this, Data_Post_FSM);

    union Timer * tmr = this->retry_session_tmr;
    tmr->vtbl->set_time(tmr, DATA_POST_RETRY_SESSION_TOUT_MS, false);
    tmr = this->packet_res_tmr;
    tmr->vtbl->set_time(tmr, DATA_POST_PACKET_TOUT_MS, false);
    tmr->vtbl->set_time(tmr, DATA_POST_SESSION_TOUT_MS, false);
}
