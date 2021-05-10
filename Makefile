##################
#Makefile TERhandi
##################

graph: graph.cpp
	g++ main.cpp -o graph
	g++ data_to_excel.cpp -o graphtest

clean : 
	rm -f main graph temps_graph.txt graphtest 