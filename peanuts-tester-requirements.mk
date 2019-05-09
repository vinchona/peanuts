include utils.mk

this.peanuts-tester-requirements:=$(call get-my-dir)

PEANUTS_TESTER_SRCS:=\
	$(this.peanuts-tester-requirements)/srcs/tester.cpp\

PEANUTS_TESTER_INCLUDE_DIRECTORIES:=\
	$(this.peanuts-tester-requirements)/includes

PEANUTS_TESTER_INCLUDE_FILES:=\

PEANUTS_TESTER_CFLAGS:=\

PEANUTS_TESTER_LDFLAGS:=\
