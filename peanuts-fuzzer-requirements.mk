include utils.mk

this.peanuts-fuzzer-requirements:=$(call get-my-dir)

PEANUTS_FUZZER_SRCS:=\
	$(this.peanuts-fuzzer-requirements)/srcs/fuzzer.cpp\

PEANUTS_FUZZER_INCLUDE_DIRECTORIES:=\
	$(this.peanuts-fuzzer-requirements)/includes

PEANUTS_FUZZER_INCLUDE_FILES:=\

PEANUTS_FUZZER_CFLAGS:=\

PEANUTS_FUZZER_LDFLAGS:=\
