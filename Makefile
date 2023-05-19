CXXFLAGS= -std=c++17 -Wc++17-extensions -O3
program: funkcijos.o v3.0.o mylib.h funkcijos.h vector.h
	g++  -o program funkcijos.o v3.0.o 

funkcijos.o: funkcijos.cpp funkcijos.h mylib.h vector.h
	g++ -c $(CXXFLAGS) funkcijos.cpp 

v1.0.o: v3.0.cpp funkcijos.h mylib.h vector.h
	g++ -c $(CXXFLAGS) v3.0.cpp 
   
clean:
	rm -f funkcijos.o v3.0.o program
   



    