define $(_flavor_)_$(_feat_)_MAKE

$(_flavor_)_$(_feat_)_inc=data_collector_wrkr.h

$(_flavor_)_$(_feat_)_lib_objs=data_collector_wrkr data_collector

$(_flavor_)_$(_feat_)_lib=data_collector

endef

include $(PROJ_MAK_DIR)/epilog.mk
