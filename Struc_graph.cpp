#include <iostream>
#include <set>

using namespace std;

//Simple graphs

struct sGraph
{
    int nbV;
    int **M;

    sGraph(int n);

    void addEdge(int v1, int v2, int c);
    void afficheMatrice();
    void destructor();
};

sGraph::sGraph(int n)
{
    this->nbV = n;
    this->M = new int*[n];
    for (int i = 0; i < n; i++)
    {
        this->M[i] = new int[n];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            this->M[i][j] = 0;
        }
    }
}

void sGraph::addEdge(int v1, int v2, int c)
{
    this->M[v1][v2] = c;
}



void sGraph::afficheMatrice()
{
    for (int i = 0; i < this->nbV; i++)
    {
        for (int j = 0; j < this->nbV; j++)
        {
            cout<<M[i][j];
        }
        cout<<endl;
    }
}

void sGraph::destructor()
{
    for (int i = 0; i < this->nbV; i++)
    {
        delete[] this->M[i];
    }
    delete[] this->M;
}



//Multi colored graphs

struct mcGraph
{
    int nbV;
    int nbC;
    set<int> **M;

    mcGraph(int n);

    void addEdge(int v1, int v2, int c);
    void destructor(); 
};

mcGraph::mcGraph(int n)
{
    this->nbV = n;
    this->M = new set<int>*[n];
    for (int i = 0; i < n; i++)
    {
        this->M[i] = new set<int>[n];
    }
    /*
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            this->M[i][j] = NULL;
        }
    }
    */
}

void mcGraph::addEdge(int v1, int v2, int c)
{
    this->M[v1][v2].insert(c);
}



void mcGraph::destructor()
{
    for (int i = 0; i < this->nbV; i++)
    {       
        delete[] this->M[i];
    }
    delete[] this->M;
}