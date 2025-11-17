CC := gcc
CFLAGS := -std=gnu11 -Wall -Wextra -Werror -pedantic -O2 -MMD -MP -Iinclude
LDFLAGS :=

SRC_DIR := src
BUILD_DIR := build

INSTALL_INC_PATH := /usr/local/include
INSTALL_LIB_PATH := /usr/local/lib

SOURCES := $(wildcard $(SRC_DIR)/*.c)
OBJECTS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCES))

LIB_NAME := libslog.a
TARGET := $(BUILD_DIR)/$(LIB_NAME)

GREEN  := \033[1;32m
RED    := \033[1;31m
YELLOW := \033[1;33m
BLUE   := \033[1;34m
RESET  := \033[0m


PREFIX := /usr/local
LIB_DIR := $(PREFIX)/lib
INCLUDE_DIR := $(PREFIX)/include

.PHONY: all clean install uninstall help

all: $(TARGET)

$(BUILD_DIR):
	@mkdir -p $@

$(TARGET): $(OBJECTS)
	@printf "$(BLUE)>>>$(RESET) Archiving $(LIB_NAME)...\n"
	@ar rcs $@ $^ && printf "$(GREEN)Build successful!$(RESET)\n" || (printf "$(RED)Build failed!$(RESET)\n" && exit 1)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	@printf "$(BLUE)>>>$(RESET) Compiling $<...\n"
	@$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@printf "$(BLUE)>>>$(RESET) Cleaning build artifacts...\n"
	@rm -rf $(BUILD_DIR)

install: $(TARGET)
	@printf "$(BLUE)>>>$(RESET) Installing $(LIB_NAME) to $(INSTALL_LIB_PATH)\n"
	@install -d $(INSTALL_LIB_PATH)
	@install -m 0755 $(TARGET) $(INSTALL_LIB_PATH)/$(LIB_NAME)
	@printf "$(BLUE)>>>$(RESET) Installing headers to $(INSTALL_INC_PATH)\n"
	@install -d $(INSTALL_INC_PATH)
	@install -m 0644 include/slog.h $(INSTALL_INC_PATH)
	@printf "$(GREEN)Installation complete!$(RESET)\n"

uninstall:
	@printf "$(BLUE)>>>$(RESET) Removing $(LIB_NAME) from $(INSTALL_LIB_PATH)\n"
	@rm -f $(INSTALL_LIB_PATH)/$(LIB_NAME)
	@printf "$(BLUE)>>>$(RESET) Removing headers from $(INSTALL_INC_PATH)\n"
	@rm -f $(INSTALL_INC_PATH)/slog.h
	@rmdir --ignore-fail-on-non-empty $(INSTALL_INC_PATH)
	@printf "$(GREEN)Uninstallation complete!$(RESET)\n"

help:
	@printf "\n"
	@printf "$(YELLOW)Available targets:$(RESET)\n"
	@printf "  $(GREEN)make$(RESET)           - Build the library\n"
	@printf "  $(GREEN)make install$(RESET)   - Install library and headers system-wide\n"
	@printf "  $(GREEN)make uninstall$(RESET) - Remove installed files\n"
	@printf "  $(GREEN)make clean$(RESET)     - Remove build artifacts\n"
	@printf "  $(GREEN)make help$(RESET)      - Show this help message\n"
	@printf "\n"
