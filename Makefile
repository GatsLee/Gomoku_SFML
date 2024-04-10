TARGET		= Gomoku_SFML

CXX			= c++
CXXFLAGS	= -I./lib/sfml/2.6.1/include -I./src -Wsilent

LDFLAGS		= -L./lib/sfml/2.6.1/lib -lsfml-graphics -lsfml-window -lsfml-system -Wl,-rpath,./lib/sfml/2.6.1/lib

SRC_DIR		= ./src
OBJ_DIR		= ./obj

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

CLANGD_GEN = ./clangd_gen.sh

all : $(TARGET)

$(TARGET) : $(OBJ_FILES)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	mkdir -p $(dir $@) //
	$(CXX) -c -o $@  $(CXXFLAGS) $<

clean :
	rm -rf $(OBJ_DIR) $(TARGET)

clangd :
	/bin/bash $(CLANGD_GEN)

.PHONY : all clean
