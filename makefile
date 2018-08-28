PROJ_DIR=.
PROJ_MAK_DIR=$(PROJ_DIR)/project_make

#OUT_DIR=$(HOME)/projects/suite_object_out

include $(PROJ_MAK_DIR)/prolog.mk 

define Project_Make

PROJ_DIR=.
PROJ_MAK_DIR=$(PROJ_DIR)/project_make
#OUT_DIR=$(HOME)/projects/suite_object_out

FLAVOR_LIST=linux

#Flavor
host_build=linux
linux_build=linux

#MACRO
host_PROJ_INC=\
include \
include/host

linux_PROJ_INC=\
include \
include/linux

endef

include $(PROJ_MAK_DIR)/project.mk
