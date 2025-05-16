EXEC = programa

CXX = g++

CXXFLAGS = -Wall -std=c++11

SRC = main.cpp

all: $(EXEC)

$(EXEC): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(SRC)

clean:
	@if exist $(EXEC).exe del $(EXEC).exe

.PHONY: all clean
