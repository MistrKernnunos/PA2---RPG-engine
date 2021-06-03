LD=g++
CXX=g++
CXXFLAGS=-Wall -pedantic -std=c++14
DEBUG_FLAGS=-DDEBUG -g -fsanitize=address

SOURCE_DIR= src
BUILD_DIR= build

# wildcard creates
SOURCES = $(wildcard $(SOURCE_DIR)/*.cpp)
HEADERS = $(wildcard $(SOURCE_DIR)/*.h)

OBJECTS = $(SOURCES:$(SOURCE_DIR)/%.cpp=$(BUILD_DIR)/%.o)
.PHONY: all
all: compile


.PHONY: run
run: compile
	./username

.PHONY: compile
compile: username

username: $(BUILD_DIR)/main
	cp $< $@

$(BUILD_DIR)/main: $(OBJECTS)
	mkdir -p $(@D)
	$(LD) $^ -o $@ `xml2-config --cflags --libs` -fsanitize=address

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS)  -c -o $@ $<  -llibxml2 `xml2-config --cflags --libs` $(DEBUG_FLAGS)

clean:
	rm -rf ./$(BUILD_DIR)

deps:
	$(CXX) -MM $(SOURCE_DIR)/*cpp >Makefile.d

-include Makefile.d