#include <iostream>
#include "graph.cpp"

//------------------------//
//          Main          //
//------------------------//

int main(){
    //Choix du type de graphe 
    int choice = 0,n=0;
    while((choice != 1) && (choice != 2)){
        cout<<endl
            <<"Indiquez le type de graphe de votre choix :"<<endl
            <<"1- graphe dense"<<endl
            <<"2- graphe aleatoire" << endl;
        cin>>choice;
    }
    cout << "Indiquez le nombre de sommets du graphe : ";
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
            binMat* g_tmp;
            cout << "Indiquez le nombre d'aretes du graph aleatoire : ";
            cin>>nbE;
            cout << "Indiquez le nombre de couleurs du graph aleatoire : ";
            cin>>nbC;
            g2=mcgraphAleatoire(n,nbE,nbC);
            for (int i = 1; i <= nbC; i++)
            {
                cout <<endl << "La matrice construite par la couleur " << i <<endl;
                g_tmp = construction1mc(g2, i);
                g_tmp->afficheMatrice();
            }
            g_tmp->destructor();


            int k,s0,t0,sortie;

            cout << "Matrice d'adjacence de G :"<<endl;
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
            warshall(g2,bM);
            bM->afficheMatrice();
            bM->destructor();


            while(1)
            {
                cout<<"KColored : "<<endl;          
                
                cout<<endl<<"exite-t-il un chemin entre s0 et t0 en k couleurs ?"<<endl
                    <<"entrez k : ";
                cin>>k;
                cout<<"entrez s0 : ";
                cin>>s0;
                cout<<"entrez t0 : ";
                cin>>t0;
                cout<<"nbc : "<<g2->nbC<<"nbv : "<<g2->nbV<<endl;
                if (k > g2->nbC || s0 >= g2->nbV || t0 >= g2->nbV)
                    cout<<"erreur dans les entrees"<<endl;
                else    
                    cout<<"Reponse : "<<KColored(g2,s0,t0,k)<<endl<<endl;

                cout<<"voulez vous tester d'autre chemin ? 1 : oui ; 2 : non";
                cin>>sortie;
                if (sortie==0)
                    break;
            }
            g2->destructor();
            break;
    }
    return 0;
}