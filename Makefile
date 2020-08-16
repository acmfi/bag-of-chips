CFLAGS = -Wall -g -lSDL2 -lSDL2main -std=c99 

default: bagofchips

bagofchips: 
	gcc $(CFLAGS) src/*.c -o bagofchips

clean:
	rm -rf bagofchips

