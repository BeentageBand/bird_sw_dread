#ifndef HID_CBK_H_
#define HID_CBK_H_

#include "hid_types.h"
#include "cobject.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef union HID_Cbk
{
    struct HID_Cbk_Class _private * _private vtbl;
    struct
    {
        struct Object Object;
        HID_Color_T _private color;
        bool _private is_on;
    };
}HID_Cbk_T;

typedef struct HID_Cbk_Class
{
    struct Class Class;
    void (*_private on)(union HID_Cbk * const, HID_Color_T const);
    void (*_private off)(union HID_Cbk * const);
}HID_Cbk_Class_T;

extern struct HID_Cbk_Class _private HID_Cbk_Class;

extern void Populate_HID_Cbk(union HID_Cbk * const cbk);

#ifdef __cplusplus
}
#endif
#endif /*HID_CBK_H_*/
