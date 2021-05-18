CXX = g++
CXXFLAGS = -std=c++20 -Wall -I h -c 
LXXFLAGS = -std=c++20 -Ih -pthread
OBJECTS =  ./obj/main.o ./obj/ansi.o ./obj/cell.o ./obj/maze.o ./obj/graph.o

TARGET = main


$(TARGET): $(OBJECTS)
	$(CXX) $(LXXFLAGS) -o $(TARGET) $(OBJECTS) 
./obj/cell.o: ./cpp/cell.cpp
	$(CXX) $(CXXFLAGS) ./cpp/cell.cpp -o ./obj/cell.o
./obj/maze.o: ./cpp/maze.cpp ./h/cell.h
	$(CXX) $(CXXFLAGS) ./cpp/maze.cpp -o ./obj/maze.o
./obj/graph.o: ./cpp/graph.cpp
	$(CXX) $(CXXFLAGS) ./cpp/graph.cpp -o ./obj/graph.o
./obj/ansi.o: ./cpp/ansi.cpp 
	$(CXX) $(CXXFLAGS) ./cpp/ansi.cpp -o ./obj/ansi.o
./obj/main.o: ./cpp/main.cpp ./h/ansi.h ./h/cell.h ./h/maze.h ./h/graph.h
	$(CXX) $(CXXFLAGS) ./cpp/main.cpp -o ./obj/main.o
clean:
	rm -fv $(TARGET) $(OBJECTS)
