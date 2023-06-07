#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;

// Struktura za ocjene jednog predmeta
struct Ocjene {
    string ucenik;
    string predmet;
    int ocjena;
};

// Klasa za admin privilegije
class Admin {
private:
    string username;
    string password;

public:
    Admin(const string& user, const string& pass) {
        username = user;
        password = pass;
    }

    bool authenticate(const string& user, const string& pass) {
        return (username == user && password == pass);
    }
};

// Klasa za E-Dnevnik
class EDnevnik {
private:
    vector<string> ucenici;
    vector<Ocjene> ocjene;

public:
    EDnevnik() {
        // Uneseni ucenici
        ucenici.push_back("John Doe1");
        ucenici.push_back("John Doe2");
        ucenici.push_back("John Doe3");

        ucitajOcjeneIzDatoteke();
    }

    void prikaziUcenike() {
        cout << "Popis ucenika:" << endl;
        for (int i = 0; i < ucenici.size(); i++) {
            cout << i + 1 << ". " << ucenici[i] << endl;
        }
    }

    bool provjeriUcenika(int indeks) {
        return (indeks >= 1 && indeks <= ucenici.size());
    }

    string getUcenik(int indeks) {
        return ucenici[indeks - 1];
    }

    void ispisiOcjene(const string& imeUcenika) {
        cout << "Ocjene za ucenika " << imeUcenika << ":" << endl;
        bool found = false;
        for (const auto& ocjena : ocjene) {
            if (ocjena.ucenik == imeUcenika) {
                cout << "Predmet: " << ocjena.predmet << ", Ocjena: " << ocjena.ocjena << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "Nema unesenih ocjena za ucenika " << imeUcenika << endl;
        }
    }

    void dodajOcjenu(const string& imeUcenika, const string& predmet, int ocjena) {
        ocjene.push_back({ imeUcenika, predmet, ocjena });
        cout << "Ocjena " << ocjena << " za predmet " << predmet << " dodana za ucenika " << imeUcenika << endl;
        spremiOcjeneUDatoteku();
    }

    void spremiOcjeneUDatoteku() {
        ofstream file;
        file.open("C:\\Users\\luka\\Desktop\\Dnevnik.txt");

        if (!file) {
            cerr << "Greska prilikom otvaranja datoteke." << endl;
            return;
        }

        for (const auto& ocjena : ocjene) {
            file << ocjena.ucenik << "," << ocjena.predmet << "," << ocjena.ocjena << endl;
        }

        file.close();
        cout << "Ocjene su uspjesno spremljene u datoteku." << endl;
    }

    void ucitajOcjeneIzDatoteke() {
        ifstream file;
        file.open("C:\\Users\\luka\\Desktop\\Dnevnik.txt");

        if (!file) {
            cerr << "Greska prilikom otvaranja datoteke." << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            string ucenik, predmet, ocjenaStr;
            size_t delimiterPos1 = line.find(',');
            size_t delimiterPos2 = line.find(',', delimiterPos1 + 1);

            if (delimiterPos1 != string::npos && delimiterPos2 != string::npos) {
                ucenik = line.substr(0, delimiterPos1);
                predmet = line.substr(delimiterPos1 + 1, delimiterPos2 - delimiterPos1 - 1);
                ocjenaStr = line.substr(delimiterPos2 + 1);

                int ocjena = stoi(ocjenaStr);
                ocjene.push_back({ ucenik, predmet, ocjena });
            }
        }

        file.close();
    }
};

int main() {
    string adminUser, adminPass;
    cout << "Unesite korisnicko ime admina: ";
    cin >> adminUser;
    cout << "Unesite lozinku admina: ";
    cin >> adminPass;

    Admin admin("admin", "password"); // User i password

    if (!admin.authenticate(adminUser, adminPass)) {
        cout << "Pogresno korisnicko ime ili lozinka. Izlazak iz programa." << endl;
        return 1;
    }

    EDnevnik eDnevnik;

    eDnevnik.prikaziUcenike();

    int izborUcenika;
    cout << "Odaberite ucenika (unesite broj): ";
    cin >> izborUcenika;

    if (!eDnevnik.provjeriUcenika(izborUcenika)) {
        cout << "Nepoznat ucenik. Izlazak iz programa." << endl;
        return 1;
    }

    string imeUcenika = eDnevnik.getUcenik(izborUcenika);

    cout << "Izaberite opciju:" << endl;
    cout << "1. Ispisi ocjene" << endl;
    cout << "2. Dodaj ocjenu" << endl;
    int opcija;
    cin >> opcija;

    if (opcija == 1) {
        eDnevnik.ispisiOcjene(imeUcenika);
    }
    else if (opcija == 2) {
        string predmet;
        int ocjena;
        cout << "Unesite naziv predmeta: ";
        cin >> predmet;
        cout << "Unesite ocjenu: ";
        cin >> ocjena;
        eDnevnik.dodajOcjenu(imeUcenika, predmet, ocjena);
        eDnevnik.spremiOcjeneUDatoteku();
    }
    else {
        cout << "Nepoznata opcija. Izlazak iz programa." << endl;
        return 1;
    }

    return 0;
}
