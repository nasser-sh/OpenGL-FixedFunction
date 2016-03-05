
TARGET_DIR = lib
TARGET     = $(TARGET_DIR)/libGLApp.a

CXX        = g++
CXX_FLAGS  = -std=c++1y -g -Wall
CXX_FILES  = $(wildcard *.cc)
OBJ_DIR    = obj
OBJECTS    = $(CXX_FILES:%cc=$(OBJ_DIR)/%o)


.PHONY: all clean
all : $(TARGET_DIR) $(OBJ_DIR) $(TARGET)

$(TARGET): $(OBJECTS)
	$(AR) -rcs $(TARGET) $(OBJECTS)

$(OBJ_DIR)/%.o : %.cc
	$(CXX) $(CXX_FLAGS) $^ -c -o $@

$(TARGET_DIR) :
	@echo Creating $(TARGET_DIR)
	mkdir -p $(TARGET_DIR)

$(OBJ_DIR) :
	@echo Creating $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)

clean : 
	rm -rf $(OBJ_DIR) $(TARGET_DIR)
