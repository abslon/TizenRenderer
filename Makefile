CXX		  := g++
CXX_FLAGS := -Wall -Wextra -std=c++17 -ggdb

# Your DALi projects directory
DALI := /home/medialab/DALi

INC_DALI	:= $(DALI)/dali-env/opt/include
INC_BULLET	:= /usr/local/include/bullet
LIB_DALI	:= $(DALI)/dali-env/opt/lib

LIBRARIES_STD := 
LIBRARIES_BULLET := -lBulletDynamics -lBulletCollision -lLinearMath
LIBRARIES_DALI := -ldali-core -ldali-adaptor -ldali-toolkit

BIN			:= bin
SRC			:= src
INCLUDE		:= -Iinclude -I$(INC_DALI) -I$(INC_BULLET)
LIB			:= -Llib -L$(LIB_DALI)

LIBRARIES	:= $(LIBRARIES_STD) $(LIBRARIES_DALI) $(LIBRARIES_BULLET)
EXECUTABLE	:= hello-bullet


all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) $(INCLUDE) $(LIB) $^ -o $@ $(LIBRARIES)

clean:
	-rm $(BIN)/*
