CC = clang++
CFLAGS = -std=c++98 -pedantic -Werror -O2 -g
LFLAGS = 
OBJS = sieve.o main.o
BIN = sieve

sieve: $(OBJS)
	$(CC) $^ -o $@ $(LFLAGS)

sieve.o: sieve.cpp sieve.hpp
	$(CC) -c $< $(CFLAGS) -o $@

main.o: main.cpp sieve.hpp
	$(CC) -c $< $(CFLAGS) -o $@

.PHONY : clean
clean:
	$(RM) $(BIN) $(OBJS) *~
