CFLAGS = -std=c99 -ggdb `pkg-config opencv --cflags --libs`

.PHONY: all
all: sepia.out scope.out mask.out affine.out perspective.out

sepia.out: sepia.o
	$(CC) $(CFLAGS) -o $@ $^

perspective.out: perspective.o
	$(CC) $(CFLAGS) -o $@ $^

affine.out: affine.o
	$(CC) $(CFLAGS) -o $@ $^

scope.out: scope.o
	$(CC) $(CFLAGS) -o $@ $^

mask.out: mask.o
	$(CC) $(CFLAGS) -o $@ $^

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	$(RM) *.out *.o *.bmp
