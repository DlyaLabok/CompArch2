CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
AR = ar
ARFLAGS = rcs
LIB_NAME = libcalculator.a
EXEC_NAME = calculator_app
OBJ = calculator.o main.o

all: $(EXEC_NAME)

$(EXEC_NAME): main.o $(LIB_NAME)
	$(CXX) $(CXXFLAGS) -o $@ main.o -L. -lcalculator

$(LIB_NAME): calculator.o
	$(AR) $(ARFLAGS) $@ $<

calculator.o: calculator.cpp calculator.h
	$(CXX) $(CXXFLAGS) -c calculator.cpp

main.o: main.cpp calculator.h
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm -f *.o *.a $(EXEC_NAME)
