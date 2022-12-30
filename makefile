OBJ_DIR=objectFiles
INC_DIR=include
SRC_DIR=src
LIB_DIR=lib
BIN_DIR=bin

all : directory libUtils libSharedMemory libSemaphore libUserStorage server libClient client

reset : cleanUserStorage

directory :
	mkdir -p $(OBJ_DIR) $(BIN_DIR)
clean : cleanUserStorage
	rm -f $(OBJ_DIR)/*.o
	rm -f $(BIN_DIR)/*

libUtils.o : $(LIB_DIR)/libUtils.c
	gcc -c $(LIB_DIR)/libUtils.c -o $(OBJ_DIR)/libUtils.o 
libUtils : libUtils.o
	ar rcs  $(BIN_DIR)/libUtils.a $(OBJ_DIR)/libUtils.o

libSharedMemory.o : $(LIB_DIR)/libSharedMemory.c
	gcc -c $(LIB_DIR)/libSharedMemory.c -o $(OBJ_DIR)/libSharedMemory.o
libSharedMemory : libSharedMemory.o
	ar rcs $(BIN_DIR)/libSharedMemory.a $(OBJ_DIR)/libSharedMemory.o

libSemaphore.o : $(LIB_DIR)/libSemaphore.c
	gcc -c $(LIB_DIR)/libSemaphore.c  -o $(OBJ_DIR)/libSemaphore.o
libSemaphore : libSemaphore.o
	ar rcs $(BIN_DIR)/libSemaphore.a -o $(OBJ_DIR)/libSemaphore.o

libUserStorage.o : $(LIB_DIR)/libUserStorage.c
	gcc -c $(LIB_DIR)/libUserStorage.c  -o $(OBJ_DIR)/libUserStorage.o
libUserStorage : libUserStorage.o
	ar rcs $(BIN_DIR)/libUserStorage.a -o $(OBJ_DIR)/libUserStorage.o

libClient.o : $(LIB_DIR)/libClient.c
	gcc -c $(LIB_DIR)/libClient.c  -o $(OBJ_DIR)/libClient.o
libClient : libClient.o
	ar rcs $(BIN_DIR)/libClient.a -o $(OBJ_DIR)/libClient.o

server.o : $(SRC_DIR)/server.c
	gcc -c $(SRC_DIR)/server.c -o $(OBJ_DIR)/server.o
server : server.o 
	gcc $(OBJ_DIR)/server.o -o $(BIN_DIR)/server -L$(BIN_DIR) -lUtils -lSharedMemory -lSemaphore -lpthread

client.o : $(SRC_DIR)/client.c
	gcc -c $(SRC_DIR)/client.c -o $(OBJ_DIR)/client.o
client : client.o userStorage
	gcc $(OBJ_DIR)/client.o -o $(BIN_DIR)/client -L$(BIN_DIR) -lUserStorage -lUtils -lSharedMemory -lSemaphore -lpthread -lClient

cleanUserStorage :
	rm -f userStorage
userStorage : cleanUserStorage
	touch userStorage

	