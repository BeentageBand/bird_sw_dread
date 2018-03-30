define $(_flavor_)_$(_feat_)_MAKE
$(_flavor_)_$(_feat_)_inc=\
sw_dread_launcher.h \
sw_dread_launcher_app_def.h

$(_flavor_)_$(_feat_)_bin_libs=\
dbg_log \
data_collector \
ipc \
cobject \
fsm \

$(_flavor_)_$(_feat_)_bin_objs=sw_dread_launcher
$(_flavor_)_$(_feat_)_bin=sw_dread_launcher

endef

include $(PROJ_MAK_DIR)/epilog.mk
