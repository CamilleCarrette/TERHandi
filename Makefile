##################
#ça c'est du make
##################

graphtest: graph.cpp
	g++ -Wpedantic $^ -o graphtest