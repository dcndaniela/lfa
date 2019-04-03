#include<iostream>
#include<string.h>
#include<fstream>
using namespace std;

ifstream f("salut.txt");

void citire(int &nr,int &w,char&l1,char &l2,int v[20],int a[20][20],int* cod,int &y)
{
    //dati prima si ultima litera
    f>>l1>>l2;
    // dati numarul literelor din alfabet
    f>>y;
    char pp;
    //"dati literele: ";
    for(int i=0; i<y; i++)
    {
        f>>pp;
        cod[i]=pp-'a';
    }

    //dati numarul starilor finale:
    f>>w;
    //dati starile finale: ";

    int i,j,st;
    for(i=0; i<w; i++)//vectorul starilor finale
        f>>v[i];
    char lit;
  //dati numarul de stari: ";
    f>>nr;
    for(i=0; i<nr; i++)
    {
        int k;
        // dati numarul de litere pentru starea i
        f>>k;
        for(j=0; j<k; j++)
        {
            //dati litera si starea in care ajunge:
            f>>lit>>st;
            a[i][lit-l1]=st;// starea in care se ajunge plecand din starea st cu litera lit
        }
    }
}

//starea in care ajung cu litera x plecand din starea st
int find(int x,int a[20][20],int st)
{
    if(a[st][x]==-1)
        return -1;
    return a[st][x];
}

//verific daca x e stare finala
int st_finala(int x,int v[20],int w)
{
    for(int i=0; i<w; i++)
        if(x==v[i])
            return 1;
    return 0;
}

void verif(int w,char l1,char l2,int a[20][20],int v[20],int *cod,int y)
{
    int nrsiruri,j,i,st;
    //dati numarul de siruri pe care doriti sa le verificati: ";
    f>>nrsiruri;
    for(j=1; j<=nrsiruri; j++)
    {
        //"introduceti sirul j
        char s[100];
        f>>s;
        st=0;//starea initiala
        char vid='~';
        if(s[0]==vid&&st_finala(0,v,w)==1)
        {
            cout<<"acceptat"<<endl;
            return;
        }
       // else
         //   cout<<"neacceptat"<<endl;
        for(i=0; i<(int)strlen(s); i++)
        {
            if((find(s[i]-l1,a,st)==-1)||st_finala(s[i]-'a',cod,y)==0) //litera nu se afla in alfabet
            {
                st=-1;
                break;
            }
            else
                st=find(s[i]-l1,a,st); //starea curenta
        }
        if(s[0]!='~')
        {
            if(st_finala(st,v,w)==1)
                cout<<s<<" acceptat "<<endl;

        else
            cout<<s<<" neacceptat"<<endl;
        }
    }

}



int main()
{
    int a[20][20]= {-1}; //initializare matrice (presupun ca nu exista stari in care ajung)
    char l1,l2;
    int w,v[20],y,nr,cod[20];
    citire(nr,w,l1,l2,v,a,cod,y); //y=nr de litere ale alfabetului
    verif(w,l1,l2,a,v,cod,y);
    return 0;
}



