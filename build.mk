VERBOSE?=0
BIN?=bin
VERSION?=0.0.0
MAJOR?=0

ifeq ($(VERBOSE),0)
	QUIET=@
	ECHO_OUTPUT=
else
	QUIET=
	ECHO_OUTPUT="> /dev/null"
endif

$(BIN)/%.cpp.o: %.cpp
	@mkdir -p $(dir $@)
	$(QUIET)$(CXX) $(CFLAGS) $(INCLUDE_DIRECTORIES) $(INCLUDE_FILES) -std=c++14 -o $@ -c $<
	@$(CXX) -MM "$<" -MT "$@" -o "$(BIN)/$*_cpp.deps" $(INCLUDE_DIRECTORIES) $(INCLUDE_FILES) $(CFLAGS) -std=c++14
	@echo "CXX $< $(ECHO_OUTPUT)"

$(BIN)/%.c.o: %.c
	@mkdir -p $(dir $@)
	$(QUIET)$(CC) $(CFLAGS) $(INCLUDE_DIRECTORIES) $(INCLUDE_FILES) -std=gnu99 -o $@ -c $<
	@$(CC) -MM "$<" -MT "$@" -o "$(BIN)/$*_c.deps" $(INCLUDE_DIRECTORIES) $(INCLUDE_FILES) $(CFLAGS)
	@echo "CC $< $(ECHO_OUTPUT)"

$(BIN)/%.a:
	@mkdir -p $(dir $@)
	$(QUIET)$(AR) cr $@ $^
	@echo "AR $@ $(ECHO_OUTPUT)"

$(BIN)/%.exe:
	@mkdir -p $(dir $@)
	$(QUIET)$(CXX) -o $@ $^ $(LDFLAGS)
	@echo "CXX $@ $(ECHO_OUTPUT)"

$(BIN)/%.so:
	$(QUIET)$(CXX) $(CFLAGS) -shared -Wl,-soname,$(notdir $@).$(MAJOR) -o "$@.$(VERSION)" $^ $(LDFLAGS)
	@echo "LD $@ $(ECHO_OUTPUT)"
	@ln -fs "$(@:$(BIN)/%=%).$(VERSION)" $@.$(MAJOR)
	@ln -fs "$(@:$(BIN)/%=%).$(VERSION)" $@

# Dependency generation
include $(shell test -d $(BIN) && find $(BIN) -name "*.deps")

.PHONY: clean
clean:
	$(QUIET)rm -rf $(BIN)
	@echo "Cleaning $(BIN)"
