CXX := g++
CXXFLAGS := -std=c++17 -Wall -Iinclude

SRC_DIR := src
BUILD_DIR := build
TARGET := $(BUILD_DIR)/proyecto

SRCS := $(wildcard $(SRC_DIR)/*.cpp $(SRC_DIR)/modelos/*.cpp $(SRC_DIR)/gestores/*.cpp $(SRC_DIR)/utilidades/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

LIB_SRCS := $(wildcard $(SRC_DIR)/modelos/*.cpp $(SRC_DIR)/gestores/*.cpp $(SRC_DIR)/utilidades/*.cpp)

TEST_DIR := tests
TESTS := $(wildcard $(TEST_DIR)/*.cpp)
TEST_BINS := $(patsubst $(TEST_DIR)/%.cpp,$(BUILD_DIR)/tests/%,$(TESTS))

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(TEST_BINS)
	@for bin in $(TEST_BINS); do ./$$bin || exit 1; done

$(BUILD_DIR)/tests/%: $(TEST_DIR)/%.cpp $(LIB_SRCS)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $< $(LIB_SRCS) -o $@

clean:
	rm -rf $(BUILD_DIR)
