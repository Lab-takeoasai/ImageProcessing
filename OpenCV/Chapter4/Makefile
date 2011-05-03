CFLAGS = -std=c99 -ggdb `pkg-config opencv --cflags --libs`

.PHONY: all
all: binarize.out histogram.out contours.out edge.out hough.out

edge.out: edge.o
	$(CC) $(CFLAGS) -o $@ $^

hough.out: hough.o
	$(CC) $(CFLAGS) -o $@ $^

binarize.out: binarize.o
	$(CC) $(CFLAGS) -o $@ $^

contours.out: contours.o
	$(CC) $(CFLAGS) -o $@ $^

histogram.out: histogram.o
	$(CC) $(CFLAGS) -o $@ $^

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	$(RM) *.out *.o *.bmp
