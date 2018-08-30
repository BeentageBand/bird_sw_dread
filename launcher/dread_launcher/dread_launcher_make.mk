define $(_flavor_)_$(_feat_)_MAKE
$(_flavor_)_$(_feat_)_inc=dread_launcher.h
$(_flavor_)_$(_feat_)_bin_objs=dread_launcher
$(_flavor_)_$(_feat_)_bin_libs=\
dread_slave_friends \
ipc_posix \
hid \
application \
ipc \
cobject \
dbg_log \
state_machine
$(_flavor_)_$(_feat_)_bin=dread_launcher
endef

-include $(PROJ_MAK_DIR)/epilog.mk