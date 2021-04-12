#include <iostream>
#include <ctime>
#include "Struc_graph.cpp"

using namespace std;

//--------------------------------
// Création de graphes particuliers
//--------------------------------

sGraph* graphDense(int n)//n nombre de sommets
{
    sGraph* graph = new sGraph(n);
    
    for (int i = 0; i < graph->nbV; i++)
    {
        for (int j = 0; j < graph->nbV; j++)
        {
            if(i!=j) graph->addEdge(i,j,1);
        }
    }
    
    return graph;
}

sGraph* graphAleatoire(int n,int nbC) //n nombre de sommets, nbC nombres de couleurs
{
    int c=0;
    srand(time(NULL));
    sGraph* graph = new sGraph(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            c= rand()%(nbC+1);
            if(i!=j) graph->addEdge(i,j,c);
        }  
    }
    return graph;
}

int main(){
    //Choix du type de graphe 
    int choice = 0,n=0;
    while((choice != 1) && (choice != 2)){
        cout << "Indiquez le type de graphe de votre choix  1 : graphe dense 2 : graphe aleatoire" << endl;
        cin>>choice;
    }
    cout << "Indiquez le nombre de sommets du graphe : "<<endl;
    cin>>n;
    sGraph* g1;
    switch(choice)
    {
        case 1: 

            g1=graphDense(n);
    
        break;

        case 2: 

            int nbC=0;
            cout << "Indiquez le nombre de couleurs du graph aléatoire : "<<endl;
            cin>>nbC;
            g1=graphAleatoire(n,nbC);
    
        break;
    }
    g1->afficheMatrice();
}