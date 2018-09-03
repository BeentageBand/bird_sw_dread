/*
 * data_reg_types.h
 *
 *  Created on: Sep 1, 2018
 *      Author: uids6144
 */

#ifndef DATA_REG_TYPES_H_
#define DATA_REG_TYPES_H_

#define DATA_REG_DATE_MMDDYYYY_HHMM_LENGTH (17U) // dd/mm/yyyy hh:mm
#define DATA_REG_ID_LENGTH (16U)

enum
{
    DATA_REG_IDLE_STID,
    DATA_REG_VALIDATION_STID,
    DATA_REG_RESPONSE_STID,
    DATA_REG_SAVED_STID,
    DATA_REG_MAX_STID
};

typedef struct Data_Register_Token
{
        char date[DATA_REG_DATE_MMDDYYYY_HHMM_LENGTH];
        char id[DATA_REG_ID_LENGTH];
}Data_Register_Token_T;

#endif /* DATA_REG_TYPES_H_ */
