all:		main

main:
	 			g++ main.cpp -o main
				./main

clean:
				rm -rf *.o main
