define $(_flavor_)_$(_feat_)_MAKE
$(_flavor_)_$(_feat_)_inc=
$(_flavor_)_$(_feat_)_lib_objs=\
	dread_$($(_flavor_)_build)_friends \
	dread_slave_friends \
	data_reg_friends \
	hid_friends
$(_flavor_)_$(_feat_)_lib=dread_slave_friends
endef

-include $(PROJ_MAK_DIR)/epilog.mk
