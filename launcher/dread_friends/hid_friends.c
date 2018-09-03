/*
 * hid_friends.c
 *
 *  Created on: Sep 1, 2018
 *      Author: uids6144
 */
#define COBJECT_IMPLEMENTATION
#define Dbg_FID DREAD_LAUNCHER_FID,1
#include "dbg_log.h"
#include "hid_cbk.h"

static void hid_cbk_delete(struct Object * const obj);
static void hid_cbk_on(union HID_Cbk * const, HID_Color_T const);
static void hid_cbk_off(union HID_Cbk * const);

static union HID_Cbk HID_Cbk = {NULL};
struct HID_Cbk_Class HID_Cbk_Class =
{
        {hid_cbk_delete, NULL},
        hid_cbk_on,
        hid_cbk_off
};

void hid_cbk_delete(struct Object * const obj)
{}

void hid_cbk_on(union HID_Cbk * const this, HID_Color_T const color)
{
    this->is_on = true;
    this->color = color;
    Dbg_Info("%s: ON new color %d", __func__, color);
}

void hid_cbk_off(union HID_Cbk * const this)
{
    this->is_on = false;
    Dbg_Info("%s: OFF new color", __func__);
}

void Populate_HID_Cbk(union HID_Cbk * const this)
{
    if(NULL == HID_Cbk.vtbl)
    {
        HID_Cbk.vtbl = &HID_Cbk_Class;
    }
    _clone(this, HID_Cbk);
}
