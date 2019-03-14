this.tester:=$(call get-my-dir)

TESTER_NAME:=tester.exe

TESTER_TARGET:=$(TESTER_NAME:%.exe=%)

TESTER_SRCS:=\
	$(this.tester)/tester.cpp\
	$(this.tester)/peanuts.cpp\
	$(this.tester)/example.cpp\

TESTER_OBJS:=\
	$(TESTER_SRCS:%=$(BIN)/%.o)

INCLUDES+=-I$(INCLUDE)

$(BIN)/$(TESTER_NAME):\
	$(TESTER_OBJS)\

$(TESTER_TARGET): $(BIN)/$(TESTER_NAME)

.PHONY: $(TESTER_TARGET)
TARGETS+=$(TESTER_TARGET)


