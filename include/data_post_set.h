/*
 * data_post_set.h
 *
 *  Created on: Sep 2, 2018
 *      Author: uids6144
 */

#ifndef DATA_POST_SET_H_
#define DATA_POST_SET_H_

#define DATA_POST_PACKET_SESSION_URL "https://thisurl.com/data/"
#define DATA_POST_PACKET_SESSION_PASSWORD "xxxxx"

#define DATA_POST_SUBSCRIPTION_MAILIST(X) \
    X(DATA_REG_PBC_NOTIFY_FAILURE_MID, data_post_on_data_reg_failure)

#endif /* DATA_POST_SET_H_ */
