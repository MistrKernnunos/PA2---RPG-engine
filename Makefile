#Makefile inspired by @David Bernahauer at https://gitlab.fit.cvut.cz/bernhdav/pa2-minesweeper/blob/master/Makefile
LD=g++
CXX=g++
CXXFLAGS=-Wall -pedantic -std=c++14

TARGET=machavi4

SOURCE_DIR= src
BUILD_DIR= build

# wildcard creates
SOURCES = $(wildcard $(SOURCE_DIR)/*.cpp)
HEADERS = $(wildcard $(SOURCE_DIR)/*.h)

OBJECTS = $(SOURCES:$(SOURCE_DIR)/%.cpp=$(BUILD_DIR)/%.o)
.PHONY: all
all: compile

buildClean: clean compile

.PHONY: run
run: compile
	./$(TARGET)

.PHONY: compile
compile: $(TARGET)

$(TARGET): $(BUILD_DIR)/main
	cp $< $@

$(BUILD_DIR)/main: $(OBJECTS)
	mkdir -p $(@D)
	$(LD) $^ -o $@ `xml2-config --cflags --libs` -lasan -fsanitize=address

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS)  -c -o $@ $<  -llibxml2 `xml2-config --cflags --libs` -fsanitize=address -lasan

clean:
	rm -rf ./$(BUILD_DIR)
	rm -rf ./doc
	rm -rf $(TARGET)

deps:
	$(CXX) -MM $(SOURCE_DIR)/*cpp >Makefile.d

doc: Doxyfile  $(HEADERS)
	doxygen Doxyfile

-include Makefile.d