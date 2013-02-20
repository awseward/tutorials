OBJS = LUtil.cpp main.cpp
CC = g++
COMPILER_FLAGS = -w
LINKER_FLAGS = -lGL -lGLU -lglut
OBJ_NAME = 01_hello_freeglut

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

clean : $(OBJ_NAME)
	rm $(OBJ_NAME)
