define $(_flavor_)_$(_feat_)_MAKE
$(_flavor_)_$(_feat_)_inc=data_post_worker.h data_post_cbk.h data_post_mailist.h data_post_types.h
$(_flavor_)_$(_feat_)_lib_objs=data_post_fsm data_post_process data_post_worker
$(_flavor_)_$(_feat_)_lib=data_post
endef

-include $(PROJ_MAK_DIR)/epilog.mk