CXX = cl.exe
CFLAGS = /Za /EHsc /O2
LFLAGS =
 
sieve.exe: main.obj sieve.obj
	$(CXX) /Fe$@ main.obj sieve.obj $(LFLAGS)
 
sieve.obj: sieve.cpp sieve.hpp
	$(CXX) /c sieve.cpp $(CFLAGS) 
 
main.obj: main.cpp sieve.hpp
	$(CXX) /c main.cpp $(CFLAGS)
 
.PHONY : clean
clean:
	del *.exe *.obj
