include utils.mk

this.peanuts-tester-requirements:=$(call get-my-dir)

include $(this.peanuts-tester-requirements)/third-parties/carryall/carryall-requirements.mk

PEANUTS_TESTER_SRCS:=\
	$(this.peanuts-tester-requirements)/srcs/tester.cpp\
	$(CARRYALL_SRCS:%=$(this.peanuts-tester-requirements)/third-parties/carryall/%)\

PEANUTS_TESTER_INCLUDE_DIRECTORIES:=\
	$(this.peanuts-tester-requirements)/includes\
	$(CARRYALL_INCLUDE_DIRECTORIES:%=$(this.peanuts-tester-requirements)/third-parties/carryall/%)\

PEANUTS_TESTER_INCLUDE_FILES:=\
	$(CARRYALL_INCLUDE_FILES:%=$(this.peanuts-tester-requirements)/third-parties/carryall/%)\

PEANUTS_TESTER_CFLAGS:=\
	$(CARRYALL_CFLAGS)\

PEANUTS_TESTER_LDFLAGS:=\
	$(CARRYALL_LDFLAGS)\
