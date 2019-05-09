include utils.mk

this.peanuts-fuzzer-requirements:=$(call get-my-dir)

PEANUTS_FUZZER_SRCS:=\
	$(this.peanuts-fuzzer-requirements)/srcs/fuzzer.cpp\

PEANUTS_FUZZER_INCLUDES:=\
	$(this.peanuts-fuzzer-requirements)/includes
