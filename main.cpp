#include <iostream>
#include <cstdlib>
#include <ctime>

//defiinicja struktury
struct struktura
{
    int i;
    char c;
    float f;
};

struct struktura** losowanie(int liczba_struktur)//konieczna poprawka
{
        int los;
        bool tabl_losowych[10000]{};            //tablica do spkrawdzania powtarzalnosci
        srand(time(0));

// alokacja taablicy wskaznikow do struktur
    auto **tablica_struktur=new struct struktura*[liczba_struktur] ;  //pierwszy wymiar- tworzenie
    for(int k=0; k<liczba_struktur; k++)
    {
        tablica_struktur[k]=new struct struktura;                     //drugi wymiar-tworzenie

        do          //losowanie unikalnej liczby i wpisanie jej do zmiennej i w strukturze
        {
            los=(rand()%10000);
        }
        while(tabl_losowych[los]);
        tabl_losowych[los]=true;                   //zapamietanie wylosowania danej liczby
        tablica_struktur[k]->i=los-1000;         //inicjalizacja pola int struktury

        //losowanie liter B-X i przypisanie do amiennej c w strukturze
        tablica_struktur[k]->c=char(rand()%23+66);//musi byc jednak 23, a nie 22

        tablica_struktur[k]->f=1000+k+1;    //inicjalizacja pola foat struktury

    }
return tablica_struktur;
}

void kasowanie(struct struktura** tablica, int n)   //skonczona funkcja
{
    for(int i=0; i<n; i++)
    {
        delete(tablica[i]);
    }
    delete []tablica;
}

struct struktura** sortowanie(struct struktura**tablica, int n)//zrobione
{
    //sortowwanie babelkowe inteligentne
    for(int k=n-1; k>0; k--)            //mozna i tak: for(int k=0; k<=n-1; k++)
    {
        int flag=1;
        for(int m =0; m<k; m++)         //wtedy tutaj: for(int m=0; m<n-i-1; m++)
        {
            if(((tablica[m])->i)>((tablica[m+1])->i))
            {
                //std::swap(tablica[m], tablica[m+1]);
                struct struktura *temp=tablica[m];
                tablica[m]=tablica[m+1];
                tablica[m+1]=temp;
                flag=0;
            }
        }
        if(flag) break;
    }
return tablica;
}

int zliczanie(struct struktura** tablica, int n, char znak)//powinno byc dobrze
{
    int licznik=0;
    for(int i=0; i<n; i++)
    {
        ((tablica[i]->c)==znak)?licznik++:licznik;
    }
return licznik;
}

int main()
{
    int rozmiar, liczba_znakow;
    char znak;
//***************************************************************************************
//wczytanie z pliku
    FILE* fp=fopen("lab1.txt", "r");
    if(fp==NULL)
        return -1;
    fscanf(fp, "%d %c", &rozmiar, &znak);
    fclose(fp);
//to tutaj nie jest potrzebne:
    std::cout<<"rozmiar tablicy: "<<rozmiar<<"  "<<std::endl;
    std::cout<<"szukany znak    :"<<znak<<std::endl;
//***************************************************************************************
    //Czas start!!!
    clock_t begin, end;
    double time_spent;
    begin = clock();
//****************************************************************************************
    //    losowanie N elementow;
struct struktura** p=losowanie(rozmiar);  //(rozmiar)

//****************************************************************************************
    //    sortowanie;
p=sortowanie(p,rozmiar); //na starym wskazniku (p, rozmiar)

//****************************************************************************************
    //    zliczanie znakow X;
liczba_znakow=zliczanie(p, rozmiar, znak);  //tu nic chyba nie trza poprawiać

//****************************************************************************************
    //  wypisanie
for(int m=0; m<20; m++)
{
    std::cout<<p[m]->f<<"     "<<p[m]->i<<"      "<<p[m]->c<<std::endl;
}
std::cout<<"Liczba wystapien znaku "<<znak<<" : "<<liczba_znakow<<std::endl;
//************************************************************************************
    // kasowanie
kasowanie(p, rozmiar);
//****************************************************************************************
    //  czas stop.
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
std::cout<<"Czas pracy programu: "<<time_spent<<std::endl;

//*****************************************************************************************
    return 0;
}
