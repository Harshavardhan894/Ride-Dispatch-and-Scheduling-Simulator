
all:
	g++ -std=c++17 main.cpp scheduler.cpp -o simulator.out

run:
	./simulator.out

clean:
	rm -f simulator.out
