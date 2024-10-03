CXX = g++

CXXFLAGS = -std=c++20

SOURCES = $(shell find $(SRC_DIR) -name '*.cpp')
# SRC_DIR = src
# SRC = $(shell find $(SRC_DIR) -name '*.cpp')

OBJECTS = $(SOURCES:.cpp=.o)

TARGET = main

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)