#define COBJECT_IMPLEMENTATION
#include "hid_process.h"
#include "ipc.h"

#define CHash_Map_Params IPC_MID, HID_Process
#include "chash_map.c"
#undef CHash_Map_Params 

#define HID_PROCESS_MAILIST(X) \
HID_SUBSCRIPTION_MAILIST(X) \
X(HID_INT_BLINK_TOUT_MID,  hid_blink_tout) \
X(HID_INT_START_BLINK_MID, hid_start_blink) \
X(HID_INT_STOP_BLINK_MID,  hid_stop_blink) \
X(HID_INT_BUZZ_SUCESS_MID, hid_buzz_success) \
X(HID_INT_BUZZ_ERROR_MID,  hid_buzz_error) \
X(HID_INT_BUZZ_INIT_MID,   hid_buzz_init) \

#define HID_PROCESS(mid, proc) {mid, proc},

static void hid_blink_times(IPC_Clock_T const time_ms, uint8_t times, HID_Color_T const color);
static void hid_blink_tout(union HID_Worker * const this, union Mail * const mail);
static void hid_start_blink(union HID_Worker * const this, union Mail * const mail);
static void hid_stop_blink(union HID_Worker * const this, union Mail * const mail);
static void hid_buzz_success(union HID_Worker * const this, union Mail * const mail);
static void hid_buzz_error(union HID_Worker * const this, union Mail * const mail);
static void hid_buzz_init(union HID_Worker * const this, union Mail * const mail);

static HID_Process_MID_T HID_Dispatcher_Mailist[] =
{
    HID_PROCESS_MAILIST(HID_PROCESS)
};

HID_Color_T HID_Blink_Color = HID_MAX_COLOR;

void hid_blink_times(IPC_Clock_T const time_ms, uint8_t times, HID_Color_T const color)
{
    while(times--)
    {
        HID_LED.vtbl->on(&HID_LED, color);
        IPC_Sleep(time_ms);
        HID_LED.vtbl->off(&HID_LED);
    }
}

void hid_blink_tout(union HID_Worker * const this, union Mail * const mail)
{
    static bool blink_st = false;
    if(blink_st)
    {
        HID_LED.vtbl->on(&HID_LED, HID_Blink_Color);
    }
    else
    {
        HID_LED.vtbl->off(&HID_LED);
    }
}
void hid_start_blink(union HID_Worker * const this, union Mail * const mail)
{
    HID_Blink_Color = *(HID_Color_T *)mail->payload;
    this->blink_timer->start(this->blink_timer);
}

void hid_stop_blink(union HID_Worker * const this, union Mail * const mail)
{
    this->blink_timer->stop(this->blink_timer);
}

void hid_buzz_success(union HID_Worker * const this, union Mail * const mail)
{
    HID_Color_T * const color = (HID_Color_T *)mail->payload;
    Isnt_Nullptr(color, );

    hid_beep_times(HID_LONG_TIME_MS, 1, *color);
}

void hid_buzz_error(union HID_Worker * const this, union Mail * const mail)
{
    HID_Color_T * const color = (HID_Color_T *)mail->payload;
    Isnt_Nullptr(color, );

    hid_beep_times(HID_LONG_TIME_MS, 1, *color);

}

void hid_buzz_init(union HID_Worker * const this, union Mail * const mail)
{
    HID_Color_T * const color = (HID_Color_T *)mail->payload;
    Isnt_Nullptr(color, );

    hid_beep_times(HID_SHORT_TIME_MS > 1U, 2, *color);

}

void Populate_HID_Dispatcher(HID_Dispatcher_T * const dispatcher)
{
    if(NULL == dispatcher->vtbl)
    {
        Populate_CHash_Map_IPC_MID_HID_Process(dispatcher,
        HID_Dispatcher_Mailist, Num_Elems(HID_Dispatcher_Mailist));
    }
}
