#-----------------------------------------------------------------------#
#---------------------------- Begin MakeFile ---------------------------#
#-----------------------------------------------------------------------#

# OBJS Specifies which files to compile as part of the project
OBJS = Src/main.c Src/utils.c Src/getter.c Src/generator.c

# CC specifies which compiler we're using (gcc for c and g++ for c++)
CC = gcc

# COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w

# LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = Inc/main.h Inc/utils.h Inc/getter.h Inc/generator.h

# OBJ_NAME specifies the name of our executable
OBJ_NAME = main

# The compilation commands to form executable
all:$(OBJS)
	$(CC) $(OBJS) $(LINKER_FLAGS) -o $(OBJ_NAME)
