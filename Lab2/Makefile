CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

LIB = libcalculator.a
OBJ = calculator.o
APP = app

all: $(LIB) $(APP)

$(LIB): $(OBJ)
	ar rcs $(LIB) $(OBJ)

$(APP): main.o $(LIB)
	$(CXX) main.o -L. -lcalculator -o $(APP)

calculator.o: calculator.cpp calculator.h
	$(CXX) $(CXXFLAGS) -c calculator.cpp

main.o: main.cpp calculator.h
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm -f *.o *.a $(APP)
