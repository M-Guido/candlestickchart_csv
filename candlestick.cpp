
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <cstring>

using namespace std;

const int WYSOKOSC = 50;
const int DLUGOSC = 200;
const int MAX_NAPIS = 100;
const int DLUGOSC_LINII = 1024;

struct swieczka {
    float open;
    float high;
    float low;
    float close;
};

void menu();
void wykres();

void wykres() {
    swieczka s[DLUGOSC];
    float skala;
    float max = 0;
    float min = 1000;
    float wartosc[WYSOKOSC];
    char wykres[DLUGOSC][WYSOKOSC];
    char danyplik[MAX_NAPIS];
    char linia[DLUGOSC_LINII];
    char *kolumna;

    fstream plikcsv, pliktxt;

    cout << "Podaj plik csv do odczytu: ";
    cin >> danyplik;
    system("CLS");

    plikcsv.open(danyplik, ios::in);
    pliktxt.open("chart.txt", ios::out);

    if (!plikcsv.is_open()) {
        cout << "Blad w odczytaniu pliku" << endl;
        return;
    }

    int ilosc_linii = 0;
    while (plikcsv.getline(linia, DLUGOSC_LINII)) {
        ilosc_linii++;
    }

    int poczatek = ilosc_linii > DLUGOSC ? ilosc_linii - DLUGOSC : 0;

    plikcsv.clear();
    plikcsv.seekg(0, ios::beg);

    for (int i = 0; i < poczatek && plikcsv.getline(linia, DLUGOSC_LINII); i++) {}

    for (int i = 0; i < DLUGOSC && plikcsv.getline(linia, DLUGOSC_LINII); i++) {
        kolumna = strtok(linia, ",");
        kolumna = strtok(NULL, ",");
        s[i].open = atof(kolumna);
        kolumna = strtok(NULL, ",");
        s[i].high = atof(kolumna);
        kolumna = strtok(NULL, ",");
        s[i].low = atof(kolumna);
        kolumna = strtok(NULL, ",");
        s[i].close = atof(kolumna);
    }
    for(int i = 0; i < DLUGOSC; i++){
        if(s[i].low < min) min = s[i].low;
        if(s[i].high > max) max = s[i].high;
    }
    skala = (max - min)/WYSOKOSC;
    wartosc[0] = max;
    for(int z = 1 ; z < WYSOKOSC ; z++){ wartosc[z] = wartosc[z-1]-skala;}
    for(int i = 0; i < DLUGOSC; i++){
        for(int j = 0 ; j < WYSOKOSC; j++){
            if(wartosc[j] > s[i].high  || wartosc[j] < s[i].low){wykres[i][j] = ' ';}
            if(wartosc[j] <= s[i].high && wartosc[j] >= s[i].low){wykres[i][j] = '|';}
            if(wartosc[j] <= s[i].open && wartosc[j] >= s[i].close){wykres[i][j] = '#';}
            if(wartosc[j] >= s[i].open && wartosc[j] <= s[i].close){wykres[i][j] = 'o';}
        }
    }

    for(int i = 0; i < WYSOKOSC; i++){
        pliktxt <<fixed;
        pliktxt << i+1 << "   " << setprecision(3) << wartosc[i]<<"  ";
        for(int j = 0 ; j < DLUGOSC; j++){
            pliktxt << setw(3) << wykres[j][i];
        }
        pliktxt << endl;
    }
    int decyzja;
    cout << "Czy chcialcbys zobaczyc wykres w kompilatorze? "<< endl;
    cout << "Tak - nacisnij 1 " << endl;
    cout << "Nie - nacisnij 0 " << endl;
    cout << "Decyzja???:  ";
    cin >> decyzja;
    if(decyzja == 1){
        system("CLS");
        for(int i = 0; i < WYSOKOSC; i++){
            cout <<fixed;
            cout << i+1 << " " << setprecision(3) << wartosc[i]<<" ";
            for(int j = 0 ; j < 100; j++){
                cout << wykres[j][i];
            }
            cout << endl;
        }
    }
    else if(decyzja == 0){
        system("CLS");
        menu();
    }

}

void menu() {
    while (true) {
         int co_chcesz;
         cout << "         Menu: " <<endl;
         cout << "   1. Generuj wykres do pliku - nacisnij 1" <<endl;
         cout << "   2. Wyjscie z programu - nacisnij 2" <<endl;
         cout << "   Co dusza pragnie: ";
         cin >> co_chcesz;

            switch (co_chcesz) {
            case 1:
                system("CLS");
                wykres();
                break;
            case 2:
                system("CLS");
               cout << R"(
            ____                      _                                    _
           |  _ \   ___    ____ ___  | |__    __ _   ___  ____ ___  _ __  (_)  __ _
           | | | | / _ \  |_  // _ \ | '_ \  / _` | / __||_  // _ \| '_ \ | | / _` |
           | |_| || (_) |  / /| (_) || |_) || (_| || (__  / /|  __/| | | || || (_| |
           |____/  \___/  /___|\___/ |_.__/  \__,_| \___|/___|\___||_| |_||_| \__,_|

           )"<< '/n';
                 exit(0);
             default:
                 cout << "Cos nie ten sie kliklo " << endl;
         }
     }
 }

int main() {
    menu();
    wykres();
    return 0;
}
