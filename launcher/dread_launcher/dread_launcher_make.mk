define $(_flavor_)_$(_feat_)_MAKE
$(_flavor_)_$(_feat_)_inc=dread_launcher.h
$(_flavor_)_$(_feat_)_bin_objs=dread_launcher
$(_flavor_)_$(_feat_)_bin_libs=\
application \
cobject \
console \
data_reg \
data_post \
dbg_log \
dread_slave_friends \
hid \
ipc \
ipc_posix \
state_machine
$(_flavor_)_$(_feat_)_bin=dread_launcher
endef

-include $(PROJ_MAK_DIR)/epilog.mk
