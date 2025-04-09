CXX = g++
CXXFLAGS = -Igeometry/include -Iapplication/include -Wall -Wextra -std=c++17
LDFLAGS = -lboost_iostreams

SRC_DIRS = geometry/src application/src
BUILD_DIR = build
BIN_DIR = bin

SOURCES := $(wildcard $(addsuffix /*.cpp, $(SRC_DIRS)))
OBJECTS := $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(SOURCES))

TARGET = $(BIN_DIR)/main

all: $(TARGET)

$(TARGET): $(OBJECTS)
	mkdir -p $(BIN_DIR)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS) 

$(BUILD_DIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

run: $(TARGET)
	@./$(TARGET)

.PHONY: set-display
set-display:
	export DISPLAY=:0

MESSAGE =? automated push
push:
	git add .
	git commit -m "$(MESSAGE)"
	git push origin main

pull:
	git pull origin main