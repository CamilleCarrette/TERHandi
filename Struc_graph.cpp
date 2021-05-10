#include <iostream>
#include <set>

using namespace std;

//------------------------//
//     Graphe simple      //
//------------------------//

//Structure
struct sGraph
{
    //Attributs
    int nbV; //nbr de sommets
    int **M; //matrice d'adjacence

    //Constructeur 
    sGraph(int n); 

    //Methodes
    void addEdge(int v1, int v2, int c);
    void afficheMatrice();

    //Destructeur
    void destructor();
};

//Crée un graphe sans arête
//n : nombre de sommet(s) 
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

//Ajout d'une arête 
//v1 : sommet 1 ; v2 : sommet 2 ; c couleur de l'arête;
void sGraph::addEdge(int v1, int v2, int c)
{
    this->M[v1][v2] = c;
}


//Affichage de matrice 
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
    cout<<endl;
}

//Libère l'espace mémoire  
void sGraph::destructor()
{
    for (int i = 0; i < this->nbV; i++)
    {
        delete[] this->M[i];
    }
    delete[] this->M;
}


//------------------------//
//     Graphe Binaire     //
//------------------------//

//Structure
struct binMat
{
    //Atributs
    int n; //nbr de sommet(s)
    bool **M; //matrice binaire (sans couleurs)

    //Constructeur
    binMat(int n);

    //Methodes
    void afficheMatrice();

    //Destructeur
    void destructor();
};

//Crée une matrice binaire sans aucune arête (tout a faux)
//n : nbr de sommet(s)
binMat::binMat(int n)
{
    this->n = n;
    this->M = new bool*[this->n];
    for (int i = 0; i < this->n; i++)
    {
        this->M[i] = new bool[this->n];
        for (int j = 0; j < this->n; j++)
        {
            this->M[i][j]=false;
        }
    }
}

//Affichage de la matrice binaire
void binMat::afficheMatrice()
{
    for (int i = 0; i < this->n; i++)
    {
        for (int j = 0; j < this->n; j++)
        {
            cout<<M[i][j];
        }
        cout<<endl;
    }
    cout<<endl;
}

//Libère l'espace mémoire
void binMat::destructor()
{
    for (int i = 0; i < this->n; i++)
    {       
        delete[] this->M[i];
    }
    delete[] this->M;
}

//-----------------------//
//  Multi-colored Graph  //
//-----------------------//

//Structure
struct mcGraph
{
    //Attributs
    int nbV; //nbr de sommet(s)
    int nbC; //nbr de couleur(s)
    set<int> **M; //matrice d'adjacence, chaque valeur contient un liste de couleur(s)

    //Constructeur
    mcGraph(int n, int c);

    //Methodes
    void addEdge(int v1, int v2, int c);
    
    //Destructeur
    void destructor(); 
};

//Crée une matrice à n sommet(s) et c couleur(s)
mcGraph::mcGraph(int n, int c)
{
    this->nbV = n;
    this->nbC = c;
    this->M = new set<int>*[n];
    for (int i = 0; i < n; i++)
    {
        this->M[i] = new set<int>[n];
    }
}

//Ajout d'une arête 
//v1 : sommet 1 ; v2 : sommet 2 ; c couleur de l'arête;
void mcGraph::addEdge(int v1, int v2, int c)
{
    this->M[v1][v2].insert(c);
}


//Libère l'espace mémoire
void mcGraph::destructor()
{
    for (int i = 0; i < this->nbV; i++)
    {       
        delete[] this->M[i];
    }
    delete[] this->M;
}