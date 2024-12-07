CXX = g++
CXXFLAGS = -std=c++11

TARGET = do-command

all: $(TARGET)

$(TARGET): do-command.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) do-command.o

do-command.o: do-command.cpp
	$(CXX) $(CXXFLAGS) -c do-command.cpp

clean:
	rm -f do-command.o do-command
