##################
#Makefile TERhandi
##################

graph: main.cpp 
	g++ -Wpedantic $^ -o graph

graphtest: data_to-excel.cpp 
	g++ -Wpedantic $^ -o graphtest

clean : 
	rm -f main graph temps_graph.txt graphtest 