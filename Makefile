define get-my-dir
$(patsubst %/,%,$(dir $(lastword $(MAKEFILE_LIST))))
endef

this:=$(call get-my-dir)

all: true_all

BIN?=bin

INCLUDE:=$(this)/include

include $(this)/build.mk
include $(this)/tester.mk
include $(this)/fuzzer.mk

CFLAGS+=-Wall
CFLAGS+=-Wextra
CFLAGS+=-Werror
CFLAGS+=-pedantic-errors

true_all: $(TARGETS)
