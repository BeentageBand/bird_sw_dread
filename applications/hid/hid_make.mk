define $(_flavor_)_$(_feat_)_MAKE
$(_flavor_)_$(_feat_)_inc=hid_mailist.h hid_types.h hid_worker.h hid_cbk.h
$(_flavor_)_$(_feat_)_lib_objs=hid_process hid_worker
$(_flavor_)_$(_feat_)_lib=hid
endef

-include $(PROJ_MAK_DIR)/epilog.mk
