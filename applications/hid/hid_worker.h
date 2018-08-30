#ifndef HID_WORKER_H_
#define HID_WORKER_H_

#include "worker.h"

typedef union HID_Worker
{
    union HID_Worker_Class _private * _private vtbl;
    union Worker Worker;
    union Thread Thread;
    struct Object Object;
}HID_Worker_T;

typedef union HID_Worker_Class
{
    struct Class Class;
    union Worker_Class Worker;
    struct Thread_Class Thread;
}HID_Worker_Class_T;

extern union HID_Worker_Class _private HID_Worker_Class;

extern void Populate_HID_Worker(union HID_Worker * const hid_worker);

#endif /*HID_WORKER_H_*/