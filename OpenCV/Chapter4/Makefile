CFLAGS = -std=c99 -ggdb `pkg-config opencv --cflags --libs`
CXXFLAGS = -ggdb `pkg-config opencv --cflags --libs`

.PHONY: all
all: binarize.out histogram.out contours.out edge.out hough.out template.out rock.out closing.out


closing.out: closing.opp
	$(CXX) $(CXXFLAGS) -o $@ $^

rock.out: rock.opp
	$(CXX) $(CXXFLAGS) -o $@ $^

edge.out: edge.o
	$(CC) $(CFLAGS) -o $@ $^

template.out: template.o
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
.SUFFIXES: .cpp .opp
.c.o:
	$(CC) $(CFLAGS) -c $<
.cpp.opp:
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	$(RM) *.out *.o *.dSYM *.opp
