exec = mylang.out
sources = $(wildcard *.cpp)
objects = $(sources:.cpp=.o)
libs =
flags = -g -Wall ${libs}

$(exec): $(objects)
	g++ $(objects) $(flags) -o $(exec)

%.o: %.c %.h
	g++ -c $(flags) $< -o $@

clean:
	rm -f *.out *.o *.png

lint:
	clang-tidy *.c *.h
