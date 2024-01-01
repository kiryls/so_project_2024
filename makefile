TARGET_EXEC := proj_exec_name

BUILD_DIR := ./build
SRC_DIR := ./src
BIN_DIR := $(BUILD_DIR)/bin

SRCS := $(shell find $(SRC_DIR) -name '*.c')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIR) -type d)
INC_FLAGS := $(addprefix -I, $(INC_DIRS))

CPPFLAGS := $(INC_FLAGS) -MMD -MP

RAYLIB := $(shell pkg-config --libs --cflags raylib)

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) $(RAYLIB) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

run: $(OBJS)
	$(BUILD_DIR)/$(TARGET_EXEC)

.PHONY: clean git
clean:
	rm -r $(BUILD_DIR)

f := .
git:
	git add $f 
	git commit -m "$(msg)" 
	git push origin master

master:
	$(MAKE) -C ./src/master

-include $(DEPS)

