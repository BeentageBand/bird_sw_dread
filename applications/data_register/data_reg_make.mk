define $(_flavor_)_$(_feat_)_MAKE
$(_flavor_)_$(_feat_)_inc=data_reg_worker.h data_reg_cbk.h data_reg_mailist.h data_reg_types.h
$(_flavor_)_$(_feat_)_lib_objs=data_reg_fsm data_reg_process data_reg_worker
$(_flavor_)_$(_feat_)_lib=data_reg
endef

-include $(PROJ_MAK_DIR)/epilog.mk