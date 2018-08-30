define $(_flavor_)_$(_feat_)_MAKE
<<<<<<< HEAD
$(_flavor_)_$(_feat_)_inc=hid_mailist.h hid_types.h hid_worker.h hid_cbk.h
$(_flavor_)_$(_feat_)_lib_objs=hid_process hid_worker
=======
$(_flavor_)_$(_feat_)_inc=hid_mailist.h hid_types.h hid_worker.h
$(_flavor_)_$(_feat_)_lib_objs=hid_fsm hid_process hid_worker
>>>>>>> 2d7b02e8ea834592222b4e1acca5662538afffac
$(_flavor_)_$(_feat_)_lib=hid
endef

-include $(PROJ_MAK_DIR)/epilog.mk
