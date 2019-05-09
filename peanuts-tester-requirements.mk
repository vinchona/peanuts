include utils.mk

this.peanuts-tester-requirements:=$(call get-my-dir)

PEANUTS_TESTER_SRCS:=\
	$(this.peanuts-tester-requirements)/srcs/tester.cpp\

PEANUTS_TESTER_INCLUDES:=\
	-I$(this.peanuts-tester-requirements)/includes
