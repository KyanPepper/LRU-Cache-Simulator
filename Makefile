CC = gcc
CFLAGS = -g -Wall -Werror -std=c99

all: csim

csim: cachesim.c 
	$(CC) $(CFLAGS) -o cachesim cachesim.c cacheio.c -lm 

#
# cleanup
#
clean:
	rm -rf *.o
	rm -rf *.tmp
	rm -f cachesim
	rm -r cachesim.dSYM
	rm -f trace.all trace.f*

