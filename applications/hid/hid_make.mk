define $(_flavor_)_$(_feat_)_MAKE
$(_flavor_)_$(_feat_)_inc=hid_mailist.h hid.h hid_types.h hid_worker.h
$(_flavor_)_$(_feat_)_lib_objs=hid hid_fsm hid_process hid_worker
$(_flavor_)_$(_feat_)_lib=hid
endef

-include $(PROJ_MAK_DIR)/epilog.mk