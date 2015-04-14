PPFLAGS = -O2 -std=c++11 -Wall

all: hw2.cpp
	g++ $(CPPFLAGS) hw2.cpp -o demo
		                        
clean:
	rm -rf demo
