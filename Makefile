CXXFLAGS += -O3 -std=c++11 -Wall -Wextra -pedantic-errors

all: build/k-server

build/k-server: build/main.o build/environment.o build/trainer.o build/greeder.o build/net.o build/neuron.o build/util.o
	$(CXX) $(CXXFLAGS) -o build/k-server build/*.o

build/neuron.o: src/neuron.cpp
	$(CXX) $(CXXFLAGS) -c src/neuron.cpp -o build/neuron.o

build/net.o: src/net.cpp
	$(CXX) $(CXXFLAGS) -c src/net.cpp -o build/net.o

build/util.o: src/util.cpp
	$(CXX) $(CXXFLAGS) -c src/util.cpp -o build/util.o

build/environment.o: src/environment.cpp
	$(CXX) $(CXXFLAGS) -c src/environment.cpp -o build/environment.o

build/trainer.o: src/trainer.cpp
	$(CXX) $(CXXFLAGS) -c src/trainer.cpp -o build/trainer.o

build/greeder.o: src/greeder.cpp
	$(CXX) $(CXXFLAGS) -c src/greeder.cpp -o build/greeder.o

build/main.o: src/main.cpp
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o build/main.o

clean:
	$(RM) build/*.o build/k-server