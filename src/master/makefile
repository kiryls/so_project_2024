TARGET_EXEC := master

BUILD_DIR := ../../build/src/master
SRC_DIR := .
UTIL_DIR := ../../src/utils
BIN_DIR := $(BUILD_DIR)/bin
CONFIG_DIR := ../../config
UTIL_DIR2 := ./src/utils

SRCS := $(shell find $(SRC_DIR) $(UTIL_DIR) -name '*.c')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIR) -type d)
INC_FLAGS := $(addprefix -I, $(INC_DIRS))

CFLAGS := -Wvla -Wextra -Werror
CPPFLAGS := $(INC_FLAGS) -MMD -MP

RAYLIB := $(shell pkg-config --libs --cflags raylib)

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) $(RAYLIB) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

run: $(OBJS)
	$(BUILD_DIR)/$(TARGET_EXEC) $(CONFIG_DIR)/$(CONFIG_FILE)

.PHONY: clean
clean:
	rm -r $(BUILD_DIR)

-include $(DEPS)

