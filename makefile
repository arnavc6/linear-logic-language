all:
	g++ -c -std=c++20 scanner.cpp 
	g++ -o scanner scanner.o 
	./scanner
	
clean:
	rm *.o
	rm scanner