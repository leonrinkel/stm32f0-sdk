TARGET_NAME = stm32f030xc

TARGET_ASFLAGS =
TARGET_CFLAGS = -DSTM32F030xC
TARGET_LDFLAGS = -Tstm32f030xc.ld

TARGET_SRC_ROOT = $(shell pwd)/src
TARGET_SRC_FILES = \
	$(TARGET_SRC_ROOT)/startup_stm32f030xc.s

include ../../Makefile.common
