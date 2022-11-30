OBJ_DIR=objectFiles
INC_DIR=include
SRC_DIR=src
LIB_DIR=lib
BIN_DIR=bin

all : directory libUtils libSharedMemory server

directory :
	mkdir -p $(OBJ_DIR) $(BIN_DIR)
clean :
	rm -f $(OBJ_DIR)/*.o
	rm -f $(BIN_DIR)/*

libUtils.o : $(LIB_DIR)/libUtils.c
	gcc -c $(LIB_DIR)/libUtils.c -o $(OBJ_DIR)/libUtils.o 
libUtils : libUtils.o
	ar rcs  $(BIN_DIR)/libUtils.a $(OBJ_DIR)/libUtils.o
libSharedMemory.o : $(LIB_DIR)/libSharedMemory.c
	gcc -c $(LIB_DIR)/libSharedMemory.c -o $(OBJ_DIR)/libSharedMemory.o
libSharedMemory : libSharedMemory.o
	ar rcs $(BIN_DIR)/libSharedMemory.a -o $(OBJ_DIR)/libSharedMemory.o
server.o : $(SRC_DIR)/server.c
	gcc -c $(SRC_DIR)/server.c -o $(OBJ_DIR)/server.o
server : server.o 
	gcc $(OBJ_DIR)/server.o -o $(BIN_DIR)/server -L$(BIN_DIR) -lUtils -lSharedMemory
