#include <iostream>
#include <string.h>
#include <stdio.h>
#include <windows.h>
#include <fstream>

using namespace std;

ifstream f("teatru.in");

class Actor
{
private:
    char *nume_actor;
    int varsta;
public:
    Actor(char *nume=NULL, int var=0)                              //constructor initializare
    {
        if(nume!=NULL)
        {
            this->nume_actor=new char[strlen(nume)+1];
            strcpy(this->nume_actor, nume);
        }
        else
            this->nume_actor=NULL;
        this->varsta=var;
    }
    Actor(Actor &a)                                               //constructor copiere
    {
        this->nume_actor=new char[strlen(a.nume_actor) + 1];
        strcpy(this->nume_actor, a.nume_actor);
        this->varsta = a.varsta;
    }
    ~Actor()                                                      //destructor
    {
        delete[] nume_actor;
        varsta=0;
    }
    void set_nume (char* nume)                                    //setter nume
    {
        delete[] this->nume_actor;
        this->nume_actor = new char[strlen(nume) + 1];
        strcpy(this->nume_actor, nume);
    }
    void set_varsta (int x)                                       //setter varsta
    {
        varsta=x;
    }
    char *get_nume()                                              //getter nume
    {
        return nume_actor;
    }
    int get_varsta()                                              //getter varsta
    {
        return varsta;
    }

    void citire(istream &in)
    {
        char memo[255];
        cout<<"     Cititi numele actorului: ";
        in.getline(memo, 256);
        if(strlen(memo)==0)
            in.getline(memo, 256);
        this->nume_actor = new char[strlen(memo) + 1];
        strcpy(this->nume_actor, memo);
        cout<<"     Cititi varsta actorului: ";
        in>>varsta;
        if (varsta<0||varsta>100)
        {
            while(varsta<0||varsta>100)
            {
                cout<<"Alege o varsta intre 0 si 100: ";
                in>>varsta;
            }
        }

    }
    friend istream& operator>>(istream &in, Actor&a)             //supraincarcare pe >>
    {
        a.citire(in);
        return in;
    }

    void afisare(ostream &out)
    {
        out<<"     Nume actor: "<<nume_actor<<endl;
        out<<"     Varsta: "<<varsta;
    }
    friend ostream& operator<<(ostream &out, Actor& a)          //supraincarcare pe <<
    {
        a.afisare(out);
        return out;
    }
    Actor& operator=(Actor &a)                                  //supraincarcare pe =
    {
        nume_actor=a.nume_actor;
        varsta=a.varsta;
    }


    friend class Teatru;
};



class Teatru
{
private:
    char *denumire_piesa;
    int numar_actori;
    Actor *actori;
    float rating;
public:
    Teatru(char *denumire_piesa=NULL, int nr_actr=0, Actor *actori=NULL, float rating=0)       //constructor initializare
    {
        set_denumire_piesa(denumire_piesa);
        this->rating = rating;
        if(actori != NULL)
            this->actori = actori;
        else
            this->actori = NULL;
        this->numar_actori = 0;
    }
    Teatru(Teatru &t)                                                                           //constructor copiere
    {
        set_denumire_piesa(t.denumire_piesa);
        this->numar_actori = t.numar_actori;
        if(actori != NULL)
        {
            this->actori = new Actor[t.numar_actori];
            for(int i=0; i<t.numar_actori; i++)
                this->actori[i]=t.actori[i];
        }
        else
            this->actori = NULL;
        this->rating = t.rating;
    }

    ~Teatru()                                                                   //destructor
    {
        delete[] denumire_piesa;
        delete[] actori;
        numar_actori=0;
        rating=0;
    }

    void set_denumire_piesa(char *denumire_piesa)                               //setter denumire piesa
    {
        if(denumire_piesa == NULL)
        {
            this->denumire_piesa = new char[1];
        }
        else
        {
            delete[] this->denumire_piesa;
            this->denumire_piesa = new char[strlen(denumire_piesa) + 1];
            strcpy(this->denumire_piesa, denumire_piesa);
        }

    }

    void set_numar_actori(int nr)                                               //setter numar de actori
    {
        numar_actori=nr;
    }

    void set_actori(Actor *a)                                                   //setter actori
    {
        delete[] this->actori;
        this->actori=new Actor[numar_actori+1];
        this->actori=a;
    }

    void set_rating(float nota)                                                  //setter rating
    {
        rating=nota;
    }

    char *get_denumire_piesa()                                                   //gettere
    {
        return denumire_piesa;
    }
    int get_numar_actori()
    {
        return numar_actori;
    }
    Actor *get_actori()
    {
        return actori;
    }
    float get_rating()
    {
        return rating;
    }

    void citire(istream &in)
    {
        char memo[255];
        cout<<"- Cititi denumirea piesei: ";
        in.getline(memo, 256);
        if(strlen(memo)==0)
            in.getline(memo, 256);
        this->denumire_piesa = new char[strlen(memo) + 1];
        strcpy(this->denumire_piesa, memo);

        cout<<"- Cititi numarul de actori: ";
        in>>numar_actori;

        cout<<"- Cititi actorii: "<<endl;
        this->actori = new Actor[numar_actori];
        for(int i=0; i<numar_actori; i++)
        {
            cout<<"  "<<i+1<<":"<<endl;
            in>>actori[i];
        }

        cout<<"- Cititi ratingul piesei: ";
        in>>rating;
        if (rating<1||rating>10)
        {
            while(rating<1||rating>10)
            {
                cout<<"Alege un rating intre 1 si 10: ";
                in>>rating;
            }
        }

    }
    friend istream& operator>>(istream &in, Teatru&t)                                  //supraincarcare pe >>
    {
        t.citire(in);
        return in;
    }

    void afisare(ostream &out)
    {
        out<<"- Denumire piesa: "<<denumire_piesa<<endl;
        out<<"- Numar actori: "<<numar_actori<<endl;
        out<<"- Actori: ";
        for(int i=0; i<numar_actori; i++)
            out<<endl<<"  "<<i+1<<":"<<endl<<actori[i];
        out<<endl<<"- Rating: "<<rating<<endl;
    }
    friend ostream& operator<<(ostream &out, Teatru &t)                                //supraincarcare pe <<
    {
        t.afisare(out);
        return out;
    }
    Teatru& operator=(Teatru &t)                                                         //supraincarcare pe =
    {
        denumire_piesa=t.denumire_piesa;
        numar_actori=t.numar_actori;
        actori=t.actori;
        rating=t.rating;
    }
    bool operator<(Teatru &t)                                                 //supraincarcare pe <
    {
        if(this->rating<t.rating)
            return true;
        else
            return false;
    }
    bool operator>(Teatru &t)                                                  //supraincarcare pe >
    {
        if(this->rating>t.rating)
            return true;
        else
            return false;
    }

};



void menu_output()
{
    printf("\n Bazdragan Maria Grupa 212 - Proiect 19 - Nume proiect: Clasa teatru \n");
    printf("\n\t MENIU:");
    printf("\n===========================================\n");
    printf("\n");
    printf("1. Cititi lista cu piese de teatru");
    printf("\n");
    printf("2. Afisati lista cu piese de teatru");
    printf("\n");
    printf("3. Modificati informatiile despre o piesa de teatru");
    printf("\n");
    printf("4. Comparati doua piese de teatru");
    printf("\n");
    printf("5. Adaugati o noua piesa de teatru");
    printf("\n");
    printf("0. Iesire.");
    printf("\n");
}



void menu()
{
    int option;///optiunea aleasa din meniu
    option=0;
    Teatru *t = new Teatru[100];
    int i, x=0, nr;
    do
    {
        menu_output();

        printf("\nIntroduceti numarul actiunii: ");
        scanf("%d", &option);

        if (option==1)
        {
            cout<<endl<<"Numarul pieselor de teatru care vor fi citite este: ";
            cin>>nr;
            if(nr>0)
            {
                x=nr;
                cout<<endl;
                for(i=0; i<nr; i++)
                {
                    cin.get();
                    cout<<"Piesa nr. "<<i+1<<":"<<endl;
                    cin>>t[i];
                    cout<<endl;
                }

                cout<<endl;
            }
            else
                cout<<"Cititi un numar mai mare decat 0";
        }
        if (option==2)
        {
            if (x>0)
            {
                if(x==1)
                {
                    cout<<endl<<"Exista o singura piesa de teatru:"<<endl<<endl;
                    cout<<t[0];
                }
                else
                {
                    cout<<endl<<"Sunt "<<x<<" piese de teatru:"<<endl<<endl;
                    for(i=0; i<x; i++)
                        cout<<"Piesa nr. "<<i+1<<":"<<endl<<t[i]<<endl;
                }
            }
            else
                cout<<"Nu exista nicio piesa de teatru citita :(";
            cout<<endl;
        }
        if (option==3)
        {
            if(x>0)
            {
                cout<<endl<<"Alege numarul piesei de teatru care va fi modificata: ";
                cin>>nr;
                cout<<endl;

                if(nr>x||nr<1)
                    cout<<"Piesa de teatru nu exista"<<endl;
                else
                {
                    int ok;
                    cin.get();
                    cout<<"Alege 1 pentru da si 0 pentru nu"<<endl<<endl;
                    cout<<"Vrei sa modifici denumirea piesei?  ";
                    cin>>ok;
                    if(ok==1)
                    {
                        char denumire[255];
                        cout<<"     Introdu noua denumire a piesei: ";
                        cin.get();
                        cin.get(denumire, 255);
                        t[nr-1].set_denumire_piesa(denumire);
                    }

                    cout<<"Vrei sa modifici numarul de actori?  ";
                    cin>>ok;
                    if(ok==1)
                    {
                        int nr_nou;
                        cout<<"     Introdu noul numar de actori: ";
                        cin>>nr_nou;
                        t[nr-1].set_numar_actori(nr_nou);
                        cout<<"     Introduceti cei "<<nr_nou<<" actori"<<endl;
                        Actor *a = new Actor [100];
                        for(i=0; i<nr_nou; i++)
                            cin>>a[i];
                        t[nr-1].set_actori(a);
                    }

                    cout<<"Vrei sa modifici actorii?  ";
                    cin>>ok;
                    if(ok==1)
                    {
                        int nr_act, v;
                        char nume[255];
                        cout<<"     Alege numarul actorului pe care vrei sa-l modifici: ";
                        cin>>nr_act;
                        if(nr_act<=t[nr-1].get_numar_actori()&&nr_act>0)
                        {
                            Actor *a = new Actor[100];
                            a=t[nr-1].get_actori();
                            cout<<"          Introdu noul nume: ";
                            cin.get();
                            cin.get(nume, 255);
                            cout<<"          Introdu noua varsta: ";
                            cin>>v;
                            while(v<0||v>100)
                            {
                                cout<<"Alege o varsta intre 0 si 100: ";
                                cin>>v;
                            }
                            a[nr_act-1].set_nume(nume);
                            a[nr_act-1].set_varsta(v);
                        }
                        else
                            cout<<"     Nu exista acest actor"<<endl;
                    }

                    cout<<"Vrei sa modifici ratingul?  ";
                    cin>>ok;
                    if(ok==1)
                    {
                        int rat;
                        cout<<"     Introdu noul rating: ";
                        cin>>rat;
                        while(rat < 1 || rat > 10)
                        {
                            cout<<"Alege un rating intre 1 si 10: ";
                            cin>>rat;
                        }
                        t[nr-1].set_rating(rat);
                    }

                }
            }
            else
                cout<<endl<<"Nu exista nicio piesa de teatru citita"<<endl;
        }
        if (option==4)
        {
            if(x==0)
                cout<<endl<<"Nu exista piese"<<endl;
            else
            {
                int a, b;
                cout<<"Alege numerele celor doua piese de teatru"<<endl<<endl;
                cout<<"Comparam piesa: ";
                cin>>a;
                cout<<"Cu piesa: ";
                cin>>b;
                cout<<endl;
                if(a>0&&a<=x&&b>0&&b<=x)
                {
                    if(t[a-1]>t[b-1])
                        cout<<"Piesa "<<a<<" este mai apreciata.";
                    else if (t[a-1]<t[b-1])
                        cout<<"Piesa "<<b<<" este mai apreciata.";
                    else
                        cout<<"Piesele au fost apreciate la fel.";
                    cout<<endl;
                }
                else
                    cout<<"Cel putin unul dintre numerele alese este invalid.";

            }
        }
        if (option==5)
        {
            if(x == 0)
                cout<<endl<<"Nu exista piese de teatru"<<endl;
            else
            {
                cout<<endl;
                cin.get();
                cin>>t[x];
                x++;
                cout<<endl;
            }
        }
        if (option==0)
        {
            printf("\nEXIT!\n");
        }
        if (option<0||option>5)
        {
            printf("\nSelectie invalida\n");
        }
        printf("\n");
        system("pause"); ///Pauza - Press any key to continue...
        system("cls");   ///Sterge continutul curent al consolei
    }
    while(option!=0);
}



int main()
{

    menu();
    return 0;
}
