include utils.mk

this:=$(call get-my-dir)

all: true_all

BIN?=bin

include $(this)/build.mk

include $(this)/peanuts-tester-requirements.mk

PEANUTS_TESTER_APP_NAME:=tester.exe
PEANUTS_TESTER_APP_TARGET:=$(PEANUTS_TESTER_APP_NAME:%.exe=%)

PEANUTS_TESTER_APP_SRCS:=\
  $(PEANUTS_TESTER_SRCS)\
  $(this)/srcs/example.cpp\

PEANUTS_TESTER_APP_OBJS:=\
  $(PEANUTS_TESTER_APP_SRCS:%=$(BIN)/%.o)

PEANUTS_TESTER_APP_INCLUDE_DIRECTORIES:=\
  $(PEANUTS_TESTER_INCLUDE_DIRECTORIES:%=-I%)

PEANUTS_TESTER_APP_INCLUDE_FILES:=\
  $(PEANUTS_TESTER_INCLUDE_FILES:%=-include %)

PEANUTS_TESTER_APP_CFLAGS:=\
  $(PEANUTS_TESTER_CFLAGS)\
  -Wall\
  -Wextra\
  -Werror\
  -pedantic-errors\

PEANUTS_TESTER_APP_LDFLAGS:=\
  $(PEANUTS_TESTER_LDFLAGS)\

$(BIN)/$(PEANUTS_TESTER_APP_NAME):\
  $(PEANUTS_TESTER_APP_OBJS)

$(PEANUTS_TESTER_APP_TARGET): CFLAGS+=$(PEANUTS_TESTER_APP_CFLAGS)
$(PEANUTS_TESTER_APP_TARGET): LDFLAGS+=$(PEANUTS_TESTER_APP_LDFLAGS)
$(PEANUTS_TESTER_APP_TARGET): INCLUDE_DIRECTORIES+=$(PEANUTS_TESTER_APP_INCLUDE_DIRECTORIES)
$(PEANUTS_TESTER_APP_TARGET): INCLUDE_FILES+=$(PEANUTS_TESTER_APP_INCLUDE_FILES)
$(PEANUTS_TESTER_APP_TARGET): $(BIN)/$(PEANUTS_TESTER_APP_NAME)

.PHONY: $(PEANUTS_TESTER_APP_TARGET)
  TARGETS+=$(PEANUTS_TESTER_APP_TARGET)

include $(this)/peanuts-fuzzer-requirements.mk

PEANUTS_FUZZER_APP_NAME:=fuzzer.exe
PEANUTS_FUZZER_APP_TARGET:=$(PEANUTS_FUZZER_APP_NAME:%.exe=%)

PEANUTS_FUZZER_APP_SRCS:=\
  $(PEANUTS_FUZZER_SRCS)\
  $(this)/srcs/example.cpp\

PEANUTS_FUZZER_APP_OBJS:=\
  $(PEANUTS_FUZZER_APP_SRCS:%=$(BIN)/%.o)

PEANUTS_FUZZER_APP_INCLUDE_DIRECTORIES:=\
  $(PEANUTS_FUZZER_INCLUDE_DIRECTORIES:%=-I%)

PEANUTS_FUZZER_APP_INCLUDE_FILES:=\
  $(PEANUTS_FUZZER_INCLUDE_FILES:%=-include %)

PEANUTS_FUZZER_APP_CFLAGS:=\
  $(PEANUTS_FUZZER_CFLAGS)\
  -Wall\
  -Wextra\
  -Werror\
  -pedantic-errors\

PEANUTS_FUZZER_APP_LDFLAGS:=\
  $(PEANUTS_FUZZER_LDFLAGS)\

$(BIN)/$(PEANUTS_FUZZER_APP_NAME):\
  $(PEANUTS_FUZZER_APP_OBJS)\

$(PEANUTS_FUZZER_APP_TARGET): CFLAGS+=$(PEANUTS_FUZZER_APP_CFLAGS)
$(PEANUTS_FUZZER_APP_TARGET): LDFLAGS+=$(PEANUTS_FUZZER_APP_LDFLAGS)
$(PEANUTS_FUZZER_APP_TARGET): INCLUDE_DIRECTORIES+=$(PEANUTS_FUZZER_APP_INCLUDE_DIRECTORIES)
$(PEANUTS_FUZZER_APP_TARGET): INCLUDE_FILES+=$(PEANUTS_FUZZER_APP_INCLUDE_FILES)
$(PEANUTS_FUZZER_APP_TARGET): $(BIN)/$(PEANUTS_FUZZER_APP_NAME)

.PHONY: $(PEANUTS_FUZZER_APP_TARGET)
  TARGETS+=$(PEANUTS_FUZZER_APP_TARGET)


true_all: $(TARGETS)
