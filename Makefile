CXX = clang++
CXXFLAGS = -Iinclude -Isrc -std=c++20 -Wall -Wextra -Wpedantic -MMD -MP
LDFLAGS  = -LC:/SDL2/lib

CXXFLAGS += $(shell sdl2-config --cflags)
LDFLAGS  += $(shell sdl2-config --libs)
LDLIBS   += -lSDL2_image -lSDL2_mixer -lSDL2_ttf

SRC_DIR   = src
BIN_DIR   = bin

DEBUG_MODE ?=1

ifeq ($(DEBUG_MODE), 1)
	BUILD_DIR = build/debug
	TARGET    = $(BIN_DIR)/SpaceRush_Debug.exe
	CXXFLAGS += -g -O0 -fsanitize=address -DDEBUG_MODE
	LDFLAGS  += -fsanitize=address
else
	BUILD_DIR = build/release
	TARGET    = $(BIN_DIR)/SpaceRush.exe  
	CXXFLAGS += -O2
endif

SRCS = $(shell find $(SRC_DIR) -type f -name "*.cpp")
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS) $(LDLIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf build 
	rm -f $(BIN_DIR)/*.exe

-include $(OBJS:.o=.d)