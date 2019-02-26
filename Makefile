define get-my-dir
$(patsubst %/,%,$(dir $(lastword $(MAKEFILE_LIST))))
endef

this:=$(call get-my-dir)

all: true_all

BIN?=bin

SRCS:=$(this)/srcs
INCLUDE:=$(this)/include

include $(this)/build.mk
-include $(this)/$(SRCS)/peanuts.mk

CFLAGS+=-Wall
CFLAGS+=-Wextra
CFLAGS+=-Werror
CFLAGS+=-pedantic-errors

.PHONY: clean
clean:
	$(QUIET)rm -rf $(BIN)
	@echo "Cleaning $(BIN)"

true_all: $(TARGETS)
