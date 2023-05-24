#include <iostream>
#include <string>

using namespace std;

struct Datum{
    int dd,mm,gg;
};

struct Predmeti{
    struct Bosanski{
        int ocjene[100];
    };
    struct Matematika{
        int ocjene[100];
    };
    struct Engleski{
        int ocjene[100];
    };
    struct Informatika{
        int ocjene[100];
    };
};

struct Osoba{
    string ime,prezime;
    int razred;
    char odjeljenje;
    Datum d;
};


int main()
{
    struct Osoba uc[50];
    int br;
    cout<<"Unesi broj ucenika (max.50): ";
    cin>>br;
    
    if(br>50){
        cout<<"Maksimalan broj ucenika je 50!";
        return 0;
    }
    
    for(int i=0;i<br;i++){
        cout<<"Ucenik"<<i+1<<endl;
        cout<<"Ime: ";
        cin>>uc[i].ime;
        cout<<"Prezime: ";
        cin>>uc[i].prezime;
        cout<<"Razred: ";
        cin>>uc[i].razred;
        cout<<"Odjeljenje: ";
        cin>>uc[i].odjeljenje;
        cout<<"Dan rodjenja: ";
        cin>>uc[i].d.dd;
        cout<<"Mjesec rodjenja: ";
        cin>>uc[i].d.mm;
        cout<<"Godina rodjenja: ";
        cin>>uc[i].d.gg;
        
    }

    return 0;
}
