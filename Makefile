all:
	g++ *.cpp -c
	g++ *.o -o game

omp:
	g++ *.cpp -c -D USE_OMP
	g++ *.o -o game_omp -fopenmp

clear:
	rm *.o game game_omp 
