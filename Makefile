CFLAGS = -Wall -g -lSDL2 -lSDL2main

default: bagofchips

bagofchips: 
	clang $(CFLAGS) src/*.c -o bagofchips

clean:
	rm -rf bagofchips

