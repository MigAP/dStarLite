cdf: mapGeneration.o dStarLite.o main.o  
	g++ -O3 -o cdf mapGeneration.o dStarLite.o main.o -Wall  

mapGeneration.o: mapGeneration.cpp 
	g++ -O3 -o mapGeneration.o -c mapGeneration.cpp -Wall 

dStarLite.o: dStarLite.cpp 
	g++ -I ./boost_1_68_0/ -O3 -o dStarLite.o -c dStarLite.cpp -Wall 

main.o: main.cpp  mapGeneration.h dStarLite.h 
	g++ -I ./boost_1_68_0/ -O3 -o main.o -c main.cpp -Wall  

clean:
	rm -f main.o dStarLite.o mapGeneration.o cdf
