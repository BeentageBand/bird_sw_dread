/*
 * data_post_mailist.h
 *
 *  Created on: Sep 1, 2018
 *      Author: uids6144
 */

#ifndef DATA_POST_MAILIST_H_
#define DATA_POST_MAILIST_H_


#define DATA_POST_INT_MAILIST(X) \
    X(DATA_POST_INT_POST_REQ_MID, "" ) \
    X(DATA_POST_INT_SESSION_START_MID, "" ) \
    X(DATA_POST_INT_SESSION_STOP_MID, "" ) \
    X(DATA_POST_INT_SESSION_TOUT_MID, "" ) \
    X(DATA_POST_INT_PACKET_START_MID, "" ) \
    X(DATA_POST_INT_PACKET_ACK_MID, "" ) \
    X(DATA_POST_INT_PACKET_STOP_MID, "" ) \
    X(DATA_POST_INT_PACKET_TOUT_MID, "" ) \

#define DATA_POST_PBC_MAILIST(X) \
    X(DATA_POST_PBC_POST_ERROR_MID, "") \

#endif /* DATA_POST_MAILIST_H_ */
