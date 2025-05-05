TARGET_EXEC := minimacs

CC := gcc
BUILD_DIR := build
SRC_DIRS := .
INC_DIRS := .
INC_FLAGS := $(addprefix -I,$(INC_DIRS))
SRCS := $(shell find $(SRC_DIRS) -name '*.c')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

CFLAGS := -MMD -MP -Wall -Wextra -Wpedantic -pedantic -std=c11 -O0 -ggdb

ifeq ($(OS),Windows_NT)
	LDFLAGS := -L. -lraylib -lgdi32 -lwinmm -Wl,--subsystem,windows
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Darwin)
		LDFLAGS := -lm -framework IOKit -framework Foundation -framework AppKit -framework OpenGL -framework CoreVideo
	endif
	ifeq ($(UNAME_S),Linux)
		LDFLAGS := -lXrandr -lX11 -lm -lGL -ldl -lpthread
	endif
endif

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)
	cp -f Hack-Regular.ttf build

$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(INC_FLAGS) $(CFLAGS) -c $< -o $@

run: $(BUILD_DIR)/$(TARGET_EXEC)
	@$(BUILD_DIR)/$(TARGET_EXEC)

.PHONY: clean run
clean:
	rm -r $(BUILD_DIR)

-include $(DEPS)
