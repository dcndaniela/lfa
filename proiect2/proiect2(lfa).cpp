#include <iostream>
#include<vector>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<math.h>
#include<fstream>
using namespace std;

// ex 1) transformare NFA in DFA

struct matr
{
    string vv;//pentru memorarea tranzitiilor matricea nfa-ului
};

struct matr1
{
    vector<string>vv;
};

string s;//retine starile
int nrf,nr,nr_tr;
string q0;
vector<string> t;//tranzitiile
matr dfa[20][20];
matr1 nfa[20][20];

int cauta_poz(char c)
{
    int contor;
    for(contor=0; contor<(int)s.size(); contor++)
        if(c==s[contor])
            return contor;
    return -1;
}

string ee;
vector<string>temp;//coloana -1 a dfa-ului (tranzitiile  dfa-ului )

void completeaza_dfa()  //initial, ee=q0
{
    int i,z;
    temp.push_back(q0);
    for(z=0; z<(int)temp.size(); z++) //pt fiecare multime noua de stari gasita
    {
        ee=temp[z];

        int q,k;
        for(k=0; k<nr_tr; k++) //parcurg tranzitiile
        {
            string th;
            for(i=0; i<(int)ee.size(); i++) //pentru fiecare tranz din multimea de tranzitii respectiva verific
                for( q=0; q<nr; q++) // starile din nfa(coloanele)
                    if(nfa[cauta_poz(ee[i])][q].vv.size()!=0)
                        if((find(nfa[cauta_poz(ee[i])][q].vv.begin(), nfa[cauta_poz(ee[i])][q].vv.end(), t[k]))!=nfa[cauta_poz(ee[i])][q].vv.end()) //exista tranzitia
                            if(th.find(s[q])==th.size()+1) {th=th+s[q];cout<<th<<endl;}

            dfa[z][k].vv=th;//adaug in dfa multimea de stari obtinuta specifica tranzitiei k
            if(((find(temp.begin(),temp.end(),th))==temp.end())&&(th.size()!=0))
                temp.push_back(th); //adaug in vectorul de stari pentru dfa, noile tranzitii
        }
    }
}


vector<char>s_f;//vectorul starilor finale din nfa


int cauta_tr1(string p)//determina coloana coresp tranzitiei st
{
    int i;
    for(i=0;i<(int)t.size();i++)
        if(t[i]==p)
        return i;
  return -1;

}

int cauta_st_fin(string st)
{
    int i,j;
    for(i=0; i<(int)st.size(); i++)
    {
        j=0;
        while(j<nrf)
        {
            if(st[i]==s_f[j])
                return 1;
            j++;
        }
    }
    return -1;
}

int cauta_st_dfa(string st) //cauta pozitia tranzitiei st in vectorul de tranz al dfa-ului
{
    int i;
    for(i=0; i<(int)temp.size(); i++)
        if(temp[i]==st)
            return i;
    return i;
}

int verif1(string c,string stare)//tranzitia e caracter
{
    if(cauta_tr1(c)==-1)//tranzitia cu ss[i] nu exista in graf
        return 0;
    if(dfa[cauta_st_dfa(stare)][cauta_tr1(c)].vv.size()==0)//nu exista o stare in care sa ajunga cu tranzitia ss
        return 0;
    return 1;

}



int main()
{
    ifstream f("dfa.txt");

    char c;
    f>>q0;//starea initiala
    f>>nr;//nr total de stari
    f>>nrf;//nr stari finale
    for(int i=0; i<nrf; i++)//citeste starile finale
    {
        f>>c;
        s_f.push_back(c);
    }
    f>>nr_tr;//numarul de tranzitii diferite din nfa

    char y;
    string x;

    int tr;
int j,i;
    f>>s;//toate starile
    sort(s.begin(),s.end());//sortez starile in ordine crescatoare
    for(i=0; i<nr; i++)
    {
        f>>c;//starea curenta
        f>>tr; //numarul de tranzitii pentru starea c
        for(j=0; j<tr; j++)
        {
            f>>y;//starea in care se ajunge
            f>>x;//cu tranzitia
            //adauga tranzitia y in vector daca nu a mai fost adaugata anterior
            if(find(t.begin(),t.end(),x)==t.end())
                t.push_back(x);//adaug tranzitia x daca aceasta nu se afla deja in vectorul starilor
            nfa[s.find(c)][s.find(y)].vv.push_back(x);//adaug tranzitia in matrice pe pozitia coresp in nfa
        }
    }
    sort(t.begin(),t.end());

    //transform nfa in dfa

    completeaza_dfa();

    int nr_siruri,ok;
    f>>nr_siruri;//citeste nr sirurilor pe care sa le verifice
    string sir;
    string stare;
    string landa="@";
    for(int j=0; j<nr_siruri; j++)
    {
        f>>sir;
        stare=q0;
        ok=1;//presupun ca sir se afla in limbaj
        if(sir==landa&&(cauta_st_fin(stare)==-1))//se citeste landa si q0 nu e stare finala
            ok=0;
        i=0;
        while(i<(int)sir.size()&&ok==1&&sir!=landa)
        {

string p;
p+=sir[i];
            ok=verif1(p,stare);

if(find(t.begin(),t.end(),p)!=t.end())
stare=dfa[cauta_st_dfa(stare)][cauta_tr1(p)].vv;
else
    ok=0;

 if((i==(int)sir.size()-1)&&(cauta_st_fin(stare)==-1))
            ok=0;//nu ajung intr-o stare finala la sfarsitul cuv

   i++;
         }

         if(ok==1)
            cout<<sir<<" apartine limbajului"<<endl;
        else
            cout<<sir<<" nu apartine limbajului"<<endl;
    }



//afiseaza nfa

/*
 for(int i=0; i<nr; i++)
            for(j=0; j<nr; j++)
            {
                cout<<"nfa["<<i<<"]["<<j<<"]: ";
                for(int k=0; k<(int)nfa[i][j].vv.size(); k++)
                    cout<<nfa[i][j].vv[k]<<" ";
                cout<<endl;
            }
//afiseaza dfa

      for(int i=0; i<(int)temp.size(); i++)
            {for(j=0; j<nr_tr; j++)
                cout<<"dfa["<<i<<"]["<<j<<"]: "<<dfa[i][j].vv<<" ";
                cout<<endl;}

*/



    return 0;
}
