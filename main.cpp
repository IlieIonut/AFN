#include <iostream>
#include <conio.h>
#include <string.h>
#include <fstream>

using namespace std;

struct automat
{
    int stare_init;
    int numar;
    int final;
    struct tranz
    {
        char litera[100][100];
        int stare_finala[100];
    } t;
};

struct nod
{
    int info;
    nod *next;
};

/**
 *
 * @param v reprezinta inceputul cozi
 * @param sf reprezinta sfarsitul cozi
 * @param x reprezinta informatia pe care o punem in coada
 */

void pune(nod* &v,nod* &sf,int x)
{
    nod *c;
    if(!v)
    {
        v=new nod;
        v->info=x;
        v->next=0;
        sf=v;
    }
    else
    {
        c=new nod;
        sf->next=c;
        c->info=x;
        sf=c;
        sf->next=0;
    }
}

/**
 *
 * @param v reprezinta coada
 * @return numarul de noduri din coada v
 */

int numar_noduri(nod *v)
{
    nod *c;
    int k=0;
    c=v;
    while(c)
    {
        k++;
        c=c->next;
    }
    return k;
}

/**
 *
 * @param v scoate din coada un element
 */

void scoate(nod* &v)
{
    nod* c;
    if(!v)
        cout<<"coada este vida si nu mai ai ce elimina!!!";
    else
    {
        c=v;
        v=v->next;
        delete c;
    }
}

/**
 *
 * @param v reprezinta coada
 * @param q reprezinta automatul
 * @return 1 daca un element din coada este stare finala altfel 0
 */

int verific_stare(nod *v,automat *q){
    nod *c;
    c=v;
    while(c)
    {
        if(q[c->info].final==1)
            return 1;
        c=c->next;
    }
    return 0;
}

int main()
{
    nod *varf=0,*ultim=0;
    int i,j,k,f,n;
    char l[100],cuvant[100];
    ifstream fin("automat.txt");
    ifstream fc("cuvant.txt");
    fc>>cuvant;
    fin>>n;
    automat *q=new automat[n];
    for(i=0; i<n; i++)
    {
        q[i].stare_init=i;
        fin>>q[i].numar;
        fin>>q[i].final;
        k=q[i].numar;
        while(k>0)
        {
            fin>>f;
            q[i].t.stare_finala[q[i].numar-k]=f;
            fin>>l;
            strcpy(q[i].t.litera[q[i].numar-k],l);
            k--;
        }
    }
    cout<<"cuvantul care trebuie verificat :"<<cuvant<<endl;
    cout<<"nr de stari:"<<n<<endl;
    for(i=0; i<n; i++)
    {
        if(q[i].final==0)
            cout<<"nu e stare finala"<<endl;
        else if(q[i].final==1)
            cout<<"e stare finala"<<endl;
        cout<<"starea q"<<q[i].stare_init<<" are "<<q[i].numar<<" tranzitii"<<endl;
        for(j=0; j<q[i].numar; j++)
            cout<<"catre "<<q[i].t.stare_finala[j]<<" cu literele "<<q[i].t.litera[j]<<endl;
    }
    if(fc.eof())
        if(q[0].final==1){
            cout<<"Cuvantul este acceptat";
            return 0;
        }else{
            cout<<"Cuvantul nu este acceptat";
            return 0;
        }
    i=0;
    j=0;
    k=0;
    int x=1,y,z;
    pune(varf,ultim,q[0].stare_init);
    while(j<strlen(cuvant))
    {
        z=x;
        x=0;
        for(y=0; y<z; y++)
        {
            i=varf->info;
            for(int k=0; k<q[i].numar; k++)
                if(strchr(q[i].t.litera[k],cuvant[j]))
                {
                    pune(varf,ultim,q[i].t.stare_finala[k]);
                    x++;
                }
            scoate(varf);
        }
        j++;
    }
    if(numar_noduri(varf)!=0 && verific_stare(varf,q)==1)
        cout<<"Cuvant acceptat";
    else
        cout<<"Cuvantul nu este acceptat";
    return 0;
}
