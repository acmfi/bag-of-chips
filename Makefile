CFLAGS = -Wall -g

default: bagofchips

bagofchips: 
	gcc $(CFLAGS) src/bagofchips.c src/opcodes.c -o bagofchips

clean:
	rm -rf bagofchips

