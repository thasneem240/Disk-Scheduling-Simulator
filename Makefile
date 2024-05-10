###
 # File: Makefile
 # File Created: 05, May 2022
 # Author: A.S.M. Thasneem
 # -----
 # Last Modified: 13, May 2022
 # Modified By: A.S.M. Thasneem
 # -----
 # Purpose: A make file to compile multiple files and get an Execute file
##


# Makefile Variables
CC		 = gcc
EXEC	 = OUTPUT
CFLAGS = -g
LDFLAGS= -pthread -lpthread
OBJ 	 = simulator.o scheduler.o


$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LDFLAGS)

simulator.o : simulator.c simulator.h scheduler.h
	$(CC) -c simulator.c $(CFLAGS)
	
scheduler.o : scheduler.c scheduler.h
	$(CC) -c scheduler.c $(CFLAGS)
clean :
	rm -f $(EXEC) $(OBJ)