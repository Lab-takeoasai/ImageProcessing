PROJECT = a.out
CXXFLAGS = -g -Wall
HEADER = $(shell ls *.hpp)
SOURCE = $(shell ls *.cpp)

.PHONY: all
all: $(PROJECT)

$(PROJECT): $(SOURCE) $(HEADER)
	$(CXX) $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	$(RM) $(PROJECT) *.o *.dSYM
