CXX = g++
CXXFLAGS = -I C:/SDL2/include/SDL2
LDFLAGS = -L C:/SDL2/lib
LDLIBS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

SRC_DIR = src
BUILD_DIR = build

TARGET = $(BUILD_DIR)/SpaceRush.exe
SRCS = $(SRC_DIR)/main.cpp
OBJS = $(BUILD_DIR)/main.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS) $(LDLIBS)

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(BUILD_DIR)/*.o $(TARGET)
