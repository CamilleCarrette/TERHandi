#include <iostream>
#include <ctime>
#include <fstream>
#include "graph.cpp"

int main()
{
    // Création de tableaux pour faciliter la boucle des tests sur les instances
    int vertices[4] = {500,1000,5000,10000}; 
    int edges[4] = {1,2,5,10}; //multiplicateur du nb de sommets
    int colors[4] = {5,10,15,20};

    //Variables de temps
    time_t start,end;
    double seconds;


    //Boucle de tests
    int s0,t0;
    mcGraph* G;
    ofstream myfile;
    myfile.open ("temps_graph.txt");
    myfile<<"temps : "<<endl;
    for (int nbv : vertices)
    {
        for (int nbem : edges)
        {
            for (int nbc : colors)
            {
                for (int k = 1; k <= 3; k++)
                {
                    G = mcgraphAleatoire(nbv,nbv*nbem,nbc);
                    s0 = rand()%nbv;
                    t0 = rand()%nbv;
                    start = time(NULL);
                    KColored(G,s0,t0,k);
                    end = time(NULL);
                    seconds = difftime(end,start);
                    G->destructor();
                    myfile<<"{nbv,nbem,nbc,k} : {"<<nbv<<","<<nbem<<","<<nbc<<","<<k<<"} ; Temps : "<<seconds<<" sec"<<endl;
                    cout<<"{nbv,nbem,nbc,k} : {"<<nbv<<","<<nbem<<","<<nbc<<","<<k<<"} ; Temps : "<<seconds<<" sec"<<endl;
                }
            }
        }
    }
}
