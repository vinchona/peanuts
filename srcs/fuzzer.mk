this.fuzzer:=$(call get-my-dir)

FUZZER_NAME:=fuzzer.exe

FUZZER_TARGET:=$(FUZZER_NAME:%.exe=%)

FUZZER_SRCS:=\
	$(this.fuzzer)/fuzzer.cpp\
	$(this.fuzzer)/peanuts.cpp\
	$(this.fuzzer)/example.cpp\

FUZZER_OBJS:=\
	$(FUZZER_SRCS:%=$(BIN)/%.o)

INCLUDES+=-I$(INCLUDE)

$(BIN)/$(FUZZER_NAME):\
	$(FUZZER_OBJS)\

$(FUZZER_TARGET): $(BIN)/$(FUZZER_NAME)

.PHONY: $(FUZZER_TARGET)
TARGETS+=$(FUZZER_TARGET)


