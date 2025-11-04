CC := gcc
CFLAGS := -std=c11 -Wall -Wextra -Werror -pedantic -O2 -MMD -MP -Iinclude
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
	ar rcs $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(BUILD_DIR)

install: $(TARGET)
	@echo "Installing $(LIB_NAME) to $(INSTALL_LIB_PATH)"
	install -d $(INSTALL_LIB_PATH)
	install -m 0755 $(TARGET) $(INSTALL_LIB_PATH)/$(LIB_NAME)
	@echo "Installing headers to $(INSTALL_INC_PATH)"
	install -d $(INSTALL_INC_PATH)
	install -m 0644 include/*.h $(INSTALL_INC_PATH)

uninstall:
	@echo "Removing $(LIB_NAME) from $(INSTALL_LIB_PATH)"
	rm -f $(INSTALL_LIB_PATH)/$(LIB_NAME)
	@echo "Removing headers from $(INSTALL_INC_PATH)"
	rm -f $(INSTALL_INC_PATH)/*.h
	rmdir --ignore-fail-on-non-empty $(INSTALL_INC_PATH)

help:
	@echo ""
	@echo "$(YELLOW)Available targets:$(RESET)"
	@echo "  $(GREEN)make$(RESET)           - Build the library"
	@echo "  $(GREEN)make install$(RESET)   - Install library and headers system-wide"
	@echo "  $(GREEN)make uninstall$(RESET) - Remove installed files"
	@echo "  $(GREEN)make clean$(RESET)     - Remove build artifacts"
	@echo "  $(GREEN)make help$(RESET)      - Show this help message"
	@echo ""
