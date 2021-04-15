#include <iostream>
#include <ctime>
#include "Struc_graph.cpp"

using namespace std;

//------------------------------------------//
// Création de graphes simples particuliers //
//------------------------------------------//

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

//-----------------------------------------------//
// Création de graphes multicolorés particuliers //
//-----------------------------------------------//

mcGraph* mcgraphAleatoire(int nbV, int nbE, int nbC) //nbV nombre de sommets, nbE nombre d'arêtes, nbC nombres de couleurs
{
    int c,x,y;
    srand(time(NULL));
    mcGraph* graph = new mcGraph(nbV);
    for (int i = 0; i < nbE; i++)
    {
        x = rand()%nbV;
        do 
        {
        y = rand()%nbV;
        } while (x==y);
        c = rand()%nbC;
        cout << x<<","<< y<<","<<c<<endl;
        graph->addEdge(x,y,c);  
    }
    return graph;
}





//-------------------------//
// Constructions du papier //
//-------------------------//


sGraph* construction1(sGraph* g, int c)
{
    sGraph* result = new sGraph(g->nbV);
    for (int i = 0; i < g->nbV; i++)
    {
        for (int j = 0; j < g->nbV; j++)
        {
            if(g->M[i][j] == c) result->addEdge(i, j, 1);
        }
    }
    return result;
}

sGraph* construction1mc(mcGraph* g, int c)
{
    sGraph* result = new sGraph(g->nbV);
    for (int i = 0; i < g->nbV; i++)
    {
        for (int j = 0; j < g->nbV; j++)
        {
            if(g->M[i][j].find(c)!=g->M[i][j].end()) 
            result->addEdge(i, j, 1);
        }
    }
    return result;
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
    switch(choice)
    {
        case 1: 
            sGraph* g1;
            g1=graphDense(n);
            g1->afficheMatrice();
            g1->destructor();
            break;

        case 2: 
            //J'utilise la 2eme structure de graphe pour cette partie, elle m'a servi de test, et tout marche, 
            //j'ai aussi adapté la construction 1, mais j'ai pas fait d'affichage pour les mcGraphs
            mcGraph* g2;
            int nbC,nbE;
            sGraph* g_tmp;
            cout << "Indiquez le nombre d'arêtes du graph aléatoire : "<<endl;
            cin>>nbE;
            cout << "Indiquez le nombre de couleurs du graph aléatoire : "<<endl;
            cin>>nbC;
            g2=mcgraphAleatoire(n,nbE,nbC);
            //g1->afficheMatrice();
            for (int i = 0; i < nbC; i++)
            {
                cout <<endl << "La matrice construite par la couleur " << i <<endl;
                g_tmp = construction1mc(g2, i);
                g_tmp->afficheMatrice();
            }
            g_tmp->destructor();
            g2->destructor();
            break;
    }
}