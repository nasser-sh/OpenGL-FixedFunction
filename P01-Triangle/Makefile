
CXX = g++
CXX_FLAGS = -std=c++1y -Wall
INCLUDES = -I../GLApp
LD_FLAGS = -L../GLApp/lib
LIBS = -lGLApp -lSDL2 -lGLEW -lGL

CXX_FILES = $(wildcard *.cc)
OBJ_DIR = obj
OBJ_FILES = $(CXX_FILES:%cc=$(OBJ_DIR)/%o)

TARGET = P01-Triangle

.PHONY : all clean
all : $(OBJ_DIR) $(TARGET)

$(TARGET) : $(OBJ_FILES)
	$(CXX) $^ $(LD_FLAGS) $(LIBS) -o $@

$(OBJ_DIR)/%.o : %.cc
	$(CXX) $(CXX_FLAGS) $(INCLUDES) -c $^ -o $@

$(OBJ_DIR) : 
	@echo Creating $@
	mkdir -p $@

clean : 
	rm -rf $(OBJ_DIR) $(TARGET)
