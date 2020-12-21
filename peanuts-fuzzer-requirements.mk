include utils.mk

this.peanuts-fuzzer-requirements:=$(call get-my-dir)

include $(this.peanuts-fuzzer-requirements)/third-parties/carryall/carryall-requirements.mk

PEANUTS_FUZZER_SRCS:=\
	$(this.peanuts-fuzzer-requirements)/srcs/fuzzer.cpp\
	$(CARRYALL_SRCS:%=$(this.peanuts-fuzzer-requirements)/third-parties/carryall/%)\

PEANUTS_FUZZER_INCLUDE_DIRECTORIES:=\
	$(this.peanuts-fuzzer-requirements)/includes\
	$(CARRYALL_INCLUDE_DIRECTORIES:%=$(this.peanuts-fuzzer-requirements)/third-parties/carryall/%)\

PEANUTS_FUZZER_INCLUDE_FILES:=\
	$(CARRYALL_INCLUDE_FILES:%=$(this.peanuts-fuzzer-requirements)/third-parties/carryall/%)\

PEANUTS_FUZZER_CFLAGS:=\
	$(CARRYALL_CFLAGS)\

PEANUTS_FUZZER_LDFLAGS:=\
	$(CARRYALL_LDFLAGS)\
