include utils.mk

this:=$(call get-my-dir)

all: true_all

BIN?=bin

INCLUDE:=$(this)/includes

include $(this)/build.mk
include $(this)/tester.mk
include $(this)/fuzzer.mk

CFLAGS+=-Wall
CFLAGS+=-Wextra
CFLAGS+=-Werror
CFLAGS+=-pedantic-errors

true_all: $(TARGETS)
