PROGRAM = capture.out
OBJECTS = capture.o
CFLAGS = -ggdb `pkg-config opencv --cflags --libs`

.PHONY: all
all: $(PROGRAM)
	./$(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	$(RM) *.out *.o
