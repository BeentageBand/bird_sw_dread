/*
 * data_post_types.h
 *
 *  Created on: Sep 1, 2018
 *      Author: uids6144
 */

#ifndef DATA_POST_TYPES_H_
#define DATA_POST_TYPES_H_

#include "std_reuse.h"

enum DATA_POST_STID
{
    DATA_POST_IDLE_STID,
    DATA_POST_SESSION_STID,
    DATA_POST_PACKET_STID,
    DATA_POST_MAX_STID
};

enum DATA_POST_CONN
{
    DATA_POST_CONN_OK,
    DATA_POST_CONN_FAILED,
    DATA_POST_CONN_INVALID_PARAMS,
    DATA_POST_CONN_MAX
};

typedef uint8_t Data_Post_Conn_Stat_T;


typedef struct Data_Post_Session
{
        char const * https_url;
        char const * https_passwd;
        char const * filename;
}Data_Post_Session_T;

typedef struct Data_Post_Packet
{
        char const * filename;
        size_t data_left;
}Data_Post_Packet_T;

#endif /* DATA_POST_TYPES_H_ */
