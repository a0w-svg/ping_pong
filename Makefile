CC = gcc

CFLAGS = -lm -lglut -lGL -lGLU
GAME_NAME = pingpong

all: src/main.o src/Window.o 
	$(CC) src/main.o src/Window.o  $(CFLAGS) -o pingpong

main.o:
	$(CC) -c src/main.c $(CFLAGS) 
Window.o:
	$(CC) -c src/Window.c $(CFLAGS)

clean:
	rm -f *.o $(APP_NAME)