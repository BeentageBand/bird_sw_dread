define $(_flavor_)_$(_feat_)_MAKE

$(_flavor_)_$(_feat_)_inc=dread_stdin.h dread_stdin_evs.h dread_stdin_wrkr.h
$(_flavor_)_$(_feat_)_lib_objs=dread_stdin_wrkr
$(_flavor_)_$(_feat_)_lib=dread_stdin

endef

include $(PROJ_MAK_DIR)/epilog.mk
