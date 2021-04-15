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

//--------------------------//
//       Algos-outils       //           
//--------------------------//

// Fermeture transitive

void Warshall(mcGraph* G, // la matrice d'adjacence non binaire de G
              binMat* wG) // la matrice d'adjacence binaire de G*
{
    for (int i = 0; i < G->nbV; i++)
    {
        for (int j = 0; j < G->nbV; j++)
        {
            wG->M[i][j] = !(G->M[i][j].empty());
        }
    }
    for (int k = 0; k < G->nbV; k++)
    {
        for (int i = 0; i < G->nbV; i++)
        {
            for (int j = 0; j < G->nbV; j++)
            {
                wG->M[i][j] = (wG->M[i][j] || (wG->M[i][k] && wG->M[k][j]));
            }
        }
    }  
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



//-------------------------//
// K-colored paths problem //
//-------------------------//

// 1ere approche naïve du problème en cherchant tout les chemins entre S0 et T0, et en regardant le nb de couleur pour chaque chemin

// Algo de rechreche du plus court chemin entre S0 et T0

// En construction...






//------------------------//
//          Main          //
//------------------------//

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
    mcGraph* g2;
    switch(choice)
    {
        case 1: 
            g1=graphDense(n);
            g1->afficheMatrice();
            g1->destructor();
            break;

        case 2: 
            //J'utilise la 2eme structure de graphe pour cette partie, elle m'a servi de test, et tout marche, 
            //j'ai aussi adapté la construction 1, mais j'ai pas fait d'affichage pour les mcGraphs
            int nbC,nbE;
            sGraph* g_tmp;
            cout << "Indiquez le nombre d'aretes du graph aleatoire : "<<endl;
            cin>>nbE;
            cout << "Indiquez le nombre de couleurs du graph aleatoire : "<<endl;
            cin>>nbC;
            g2=mcgraphAleatoire(n,nbE,nbC);
            for (int i = 0; i < nbC; i++)
            {
                cout <<endl << "La matrice construite par la couleur " << i <<endl;
                g_tmp = construction1mc(g2, i);
                g_tmp->afficheMatrice();
            }
            g_tmp->destructor();
            break;
    }
    cout << "Matrice d'adjacence de G : "<<endl;
    binMat* bM = new binMat(g2->nbV);
    for (int i = 0; i < g2->nbV; i++)
    {
        for (int j = 0; j < g2->nbV; j++)
        {
            bM->M[i][j] = !(g2->M[i][j].empty());
        }
    }
    bM->afficheMatrice();
    cout << "Matrice d'adjacence de G* : "<<endl;
    Warshall(g2,bM);
    bM->afficheMatrice();
    bM->destructor();
    g2->destructor();
    return 0;
}