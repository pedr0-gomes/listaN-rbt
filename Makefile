CC = gcc
CFLAGS = -Wall

%.exe: %.c rbt.c
	$(CC) $(CFLAGS) $< rbt.c -o $@

clean:
	del *.exe *.o