CXX = g++
FLAGS = -std=c++20 -O2 -Wall -Wextra -pedantic

default:
	$(CXX) $(FLAGS) -I . -c Examples/Binomial.cpp
	$(CXX) $(FLAGS) -I . -c main.cpp
	$(CXX) -o main *.o
	rm -f *.o
