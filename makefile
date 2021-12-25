INCLUDE	=-I./include
FLAG	=-Wall -g
CC	=gcc
LIBS	=-lSDL2main -lSDL2 -lm
OUT	=-o RCengine
OBJ	=*.o
SRC	=src/main.c 	\
	 src/player.c	\
	 src/screen.c	\
	 src/ray.c		\
	 src/wall.c		\
	 src/mathRadian.c	\
	 src/map.c			\
	 src/renderer.c

compile :
	$(CC) -c $(SRC)

link :
	$(CC) $(FLAG) $(OBJ) $(INCLUDE) $(LIBS) $(OUT)

clear :
	rm -rf *.o
