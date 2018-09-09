#ifndef DBG_LOG_USET_H_
#define DBG_LOG_USET_H_

#define DBG_FID_LIST(FID) \
   /*  Feature ID,        Dbg Level,    Description */ \
   FID(APP_FID,            DBG_INFO_LVL, "Application") \
   FID(COBJECT_FID,        DBG_INFO_LVL, "Cobject Implementation") \
   FID(CONSOLE_FID,        DBG_INFO_LVL, "Console Implementation") \
   FID(DATA_REG_FID,       DBG_INFO_LVL, "Data Register") \
   FID(DATA_POST_FID,      DBG_INFO_LVL, "Data Posting") \
   FID(DREAD_LAUNCHER_FID, DBG_INFO_LVL, "Dread launcher") \
   FID(IPC_FID,            DBG_INFO_LVL, "IPC FrameWork") \
   FID(HID_FID,            DBG_INFO_LVL, "HID ") \
   FID(STATE_MACHINE_FID,  DBG_INFO_LVL, "Finite State Machine") \


#define Dbg_Log_Print(feat_id, lvl, line, ...) \
    Dbg_Log(lvl, IFF_1(__VA_ARGS__), feat_id, \
    IF(NOT(CHECK(__VA_ARGS__)))(line, line, IFF_0(__VA_ARGS__)))
 
#endif /*DBG_LOG_USET_H_*/
