#include <iostream>
#include <ctime>
#include <list>
#include "Struc_graph.cpp"

using namespace std;

//------------------------------------------//
// Création de graphes simples particuliers // (obsolete)
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
    mcGraph* graph = new mcGraph(nbV,nbC);
    for (int i = 0; i < nbE; i++)
    {
        x = rand()%nbV;
        do 
        {
        y = rand()%nbV;
        } while (x==y);
        c = (rand()%nbC)+1;
        // cout <<"x,y: {"<< x<<","<< y<<"}, c: "<<c<<endl;
        graph->addEdge(x,y,c);  
    }
    return graph;
}

//--------------------------//
//       Algos-outils       //           
//--------------------------//

// Fermeture transitive

void warshall(mcGraph* G, // la matrice d'adjacence non binaire de G
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

bool chemin(binMat* g, int s0, int t0)
{
    if (s0==t0) 
        return true;

    bool visite[g->n];
    for (int i = 0; i < g->n; i++)
        visite[i] = false;

    list<int> liste;
    visite[s0] = true;
    liste.push_back(s0);
    while(!liste.empty())
    {
        s0 = liste.front();
        liste.pop_front();
        for (int i = 0; i < g->n; i++)
        {
            if (g->M[s0][i])
            {
                if (i == t0)
                    return true;

                if (!visite[i])
                {
                    visite[i] = true;
                    liste.push_back(i);
                }
            }
        }
    }
    return false;
}

int binomialCoeff(int n, int k)
{
    if (k > n)
        return 0;
    if (k == 0 || k == n)
        return 1;

    return binomialCoeff(n - 1, k - 1) + binomialCoeff(n - 1, k);
}
struct comb
{
    int count;
    list<int> F;
    list<int>* tab;
    comb(int n, int k);
};

comb::comb(int n, int k)
{
    this->count = 0;
    this->tab = new list<int>[binomialCoeff(n,k)];
    for (int i = 1; i <= n; i++)
    {
        this->F.push_back(i);
    }
    
}

void combinaison(comb* Cb, list<int> L, list<int> F, int k)
{
    if (k==0)
    {
        Cb->tab[Cb->count] = L;
        Cb->count++;
        return;
    }
    for (int x : F)
    {
        list<int> G = F;
        while (G.front()!=x)
        {
            G.pop_front();
        }
        G.pop_front();
        list<int> L2 = L;
        L2.push_back(x);
        combinaison(Cb,L2,G,k-1);       
    }
}

//-------------------------//
// Constructions du papier //
//-------------------------//


sGraph* construction1(sGraph* g, int c) // !!! obsolete !!!
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

binMat* construction1mc(mcGraph* g, int c)
{
    binMat* result = new binMat(g->nbV);
    for (int i = 0; i < g->nbV; i++)
    {
        for (int j = 0; j < g->nbV; j++)
        {
            if(g->M[i][j].find(c)!=g->M[i][j].end()) 
            result->M[i][j] = true;
        }
    }
    return result;
}

binMat* construction1KC(mcGraph* g, binMat* mat, int c)
{
    for (int i = 0; i < g->nbV; i++)
    {
        for (int j = 0; j < g->nbV; j++)
        {
            if(g->M[i][j].find(c)!=g->M[i][j].end()) 
            mat->M[i][j] = true;
        }
    }
    return mat;
}



//-------------------------//
// K-colored paths problem //
//-------------------------//

bool KColored(mcGraph* G, int s0, int t0, int k)
{
    comb* Cb = new comb(G->nbC,k);
    list<int> L; 
    bool res;
    int i = 0;
    int c;
    combinaison(Cb,L,Cb->F,k);
    binMat* mat = new binMat(G->nbV);
    while (i < Cb->count && !res)
    {
        for (int j = 0; j < G->nbV; j++)
        {
            for (int k = 0; k < G->nbV; k++)
            {
                mat->M[j][k]=false;
            }
        }
        for (int j = 0; j < k; j++)
        {
            c = Cb->tab[i].front();
            //cout<<"cb tab : "<<Cb->tab[i].front()<<endl;
            Cb->tab[i].pop_front();
            mat = construction1KC(G,mat,c);
        }
        res = chemin(mat,s0,t0);
        //cout<<"res : "<<res<<endl;
        i++;
    }
    mat->destructor();
    delete Cb->tab;
    return res;
}
