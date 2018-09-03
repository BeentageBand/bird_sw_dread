/*
 * data_reg_mailist.h
 *
 *  Created on: Sep 1, 2018
 *      Author: uids6144
 */

#ifndef DATA_REG_MAILIST_H_
#define DATA_REG_MAILIST_H_

#define DATA_REG_INT_MAILIST(X) \
    X(DATA_REG_INT_INCOMING_MSG_MID, " ") \
    X(DATA_REG_INT_VALID_DATA_MID  , " ") \
    X(DATA_REG_INT_INVALID_DATA_MID, " ") \
    X(DATA_REG_INT_STATUS_REQ_MID  , " ") \
    X(DATA_REG_INT_STATUS_RES_MID  , " ") \
    X(DATA_REG_INT_RES_TOUT_MID    , " ") \
    X(DATA_REG_INT_NOTIFY_SAVED_MID, " ") \
    X(DATA_REG_INT_SAVED_TOUT_MID  , " ") \

#define DATA_REG_PBC_MAILIST(X) \
    X(DATA_REG_PBC_NOTIFY_FAILURE_MID, " ") \


#endif /* DATA_REG_MAILIST_H_ */
