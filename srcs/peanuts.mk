this.peanuts:=$(call get-my-dir)

PEANUTS_NAME:=peanuts.exe

PEANUTS_TARGET:=$(PEANUTS_NAME:%.exe=%)

PEANUTS_SRCS:=\
	$(this.peanuts)/main.cpp\

PEANUTS_OBJS:=\
	$(PEANUTS_SRCS:%=$(BIN)/%.o)

INCLUDES+=-I$(INCLUDE)

$(BIN)/$(PEANUTS_NAME):\
	$(PEANUTS_OBJS)\

$(PEANUTS_TARGET): $(BIN)/$(PEANUTS_NAME)

.PHONY: $(PEANUTS_TARGET)
TARGETS+=$(PEANUTS_TARGET)


