/*=====================================================================================*/
/**
 * dread_stdin_set.h
 * author : puch
 * date : Oct 22 2015
 *
 * description : Any comments
 *
 */
/*=====================================================================================*/
#ifndef DREAD_STDIN_SET_H_
#define DREAD_STDIN_SET_H_
/*=====================================================================================*
 * Project Includes
 *=====================================================================================*/

/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Define Macros
 *=====================================================================================*/
#ifdef __cplusplus
extern "C" {
#endif

#define DREAD_STDIN_INFO_SIZE (4U)  /*Saved info is for rfid card at uint32_t (4 bytes)*/
#define DREAD_STDIN_STR_INFO_SIZE (10U) /*Saved info in strings is 10 digits long)*/
#define DR_STDIN_TOTAL_REGISTERS (40U)
#define DR_STDIN_REGISTER_SIZE (20U)
/*=====================================================================================* 
 * Exported Type Declarations
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Object Declarations
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Function Prototypes
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Function Like Macros
 *=====================================================================================*/
#ifdef __cplusplus
}
#endif
/*=====================================================================================* 
 * dread_stdin_set.h
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
#endif /*DREAD_STDIN_SET_H_*/
