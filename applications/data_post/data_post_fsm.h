/*
 * data_post_fsm.h
 *
 *  Created on: Sep 1, 2018
 *      Author: uids6144
 */

#ifndef DATA_POST_FSM_H_
#define DATA_POST_FSM_H_

#include "data_post_types.h"
#include "fsm.h"

#define DATA_POST_FSM(cb) \
FSM_STATE_DEF(cb, DATA_POST_IDLE_STID, \
    FSM_TRANSITION_DEF(cb, DATA_POST_INT_POST_REQ_MID,   DATA_POST_SESSION_STID, data_post_ready_guard,  data_post_open_session) \
) \
FSM_STATE_DEF(cb, DATA_POST_SESSION_STID, \
    FSM_TRANSITION_DEF(cb, DATA_POST_INT_SESSION_START_MID,     DATA_POST_PACKET_STID,  data_post_session_guard, data_post_start_packet) \
    FSM_TRANSITION_DEF(cb, DATA_POST_INT_SESSION_STOP_MID,      DATA_POST_SESSION_STID, NULL,                    data_post_close_session) \
    FSM_TRANSITION_DEF(cb, DATA_POST_INT_SESSION_TOUT_MID,      DATA_POST_IDLE_STID,    NULL,                    data_post_end) \
) \
FSM_STATE_DEF(cb, DATA_POST_PACKET_STID, \
    FSM_TRANSITION_DEF(cb, DATA_POST_INT_PACKET_START_MID,      DATA_POST_PACKET_STID,      data_packet_guard, data_post_packet) \
    FSM_TRANSITION_DEF(cb, DATA_POST_INT_PACKET_ACK_MID,        DATA_POST_PACKET_STID,      data_packet_guard, data_post_packet) \
    FSM_TRANSITION_DEF(cb, DATA_POST_INT_PACKET_STOP_MID,       DATA_POST_SESSION_STID,     NULL,              data_post_close_session) \
    FSM_TRANSITION_DEF(cb, DATA_POST_INT_PACKET_TOUT_MID,       DATA_POST_IDLE_STID,        NULL,              data_post_end) \
) \

typedef union Data_Post_FSM
{
        union Data_Post_FSM_Class _private * _private vtbl;
        struct Object Object;
        union State_Machine State_Machine;
        struct
        {
                union FSM FSM;
                Data_Post_Conn_Stat_T _private conn_status; //Connection status
                union Timer _private * _private retry_session_tmr; // 5 minutes to retry post
                union Timer _private * _private session_res_tmr; //30 sec for sessiong hangup
                union Timer _private * _private packet_res_tmr; //30 sec for packet post hangup
                struct Data_Post_Session _private * _private session;
                struct Data_Post_Packet _private * _private packet;
        };
}Data_Post_FSM_T;

typedef union Data_Post_FSM_Class
{
        struct Class Class;
        struct State_Machine_Class State_Machine;
        union FSM_Class FSM;
}Data_Post_FSM_Class_T;

extern union Data_Post_FSM_Class _private Data_Post_FSM_Class;

extern void Populate_Data_Post_FSM(union Data_Post_FSM * const data_post_fsm);

#endif /* DATA_POST_FSM_H_ */
