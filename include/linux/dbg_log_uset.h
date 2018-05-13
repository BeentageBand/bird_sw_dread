#ifndef DBG_LOG_USET_H_
#define DBG_LOG_USET_H_

#define DBG_FID_LIST(FID) \
   /*  Feature ID,        Dbg Level,    Description */ \
   FID(COBJECT_FID,        DBG_INFO_LVL, "Cobject Implementation") \
   FID(DREAD_DC_FID,       DBG_INFO_LVL, "Dread Data Collector") \
   FID(FSM_FID,            DBG_INFO_LVL, "Finite State Machine") \
   FID(GTEST_FID,          DBG_INFO_LVL, "Gtest Framework") \
   FID(IPC_FID,            DBG_INFO_LVL, "IPC FrameWork") \

#define Dbg_Log_Print(feat_id, lvl, line, ...) \
    Dbg_Log(lvl, IFF_1(__VA_ARGS__), feat_id, \
    IF(NOT(CHECK(__VA_ARGS__)))(line, line, IFF_0(__VA_ARGS__)))
 
#endif /*DBG_LOG_USET_H_*/
