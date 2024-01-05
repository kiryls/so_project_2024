TARGET_EXEC := master

CONFIG_FILE := custom.txt

BUILD_DIR := ./build
SRC_DIR := ./src/utils
BIN_DIR := $(BUILD_DIR)/src/master
CONFIG_DIR := ./config

SRCS := $(shell find $(SRC_DIR) -name '*.c')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIR) -type d)
INC_FLAGS := $(addprefix -I, $(INC_DIRS))

CFLAGS := -Wvla -Wextra -Werror -pthread
CPPFLAGS := $(INC_FLAGS) -MMD -MP

$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

all: $(OBJS) master atom

run: $(OBJS)
	$(MAKE) -C ./src/master run CONFIG_FILE=$(CONFIG_FILE)

.PHONY: clean git master atom
clean:
	rm -r $(BUILD_DIR)

f := .
git:
	git add $f 
	git commit -m "$(msg)" 
	git push origin master

master: $(shell find ./src/master -name '*.c')
	$(MAKE) -C ./src/master

atom: $(shell find ./src/atom -name '*.c')
	$(MAKE) -C ./src/atom

# run_master:
# 	$(MAKE) -C ./src/master run CONFIG_FILE=$(CONFIG_FILE)

-include $(DEPS)

