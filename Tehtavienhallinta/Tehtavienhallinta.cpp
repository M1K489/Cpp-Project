// Tehtavienhallinta.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "tehtavalista.h"

void tulostaMenu();
void tulostaTehtavat(Tehtavalista& tehtavalista);
void lueTunnus(std::string& merkkijono, int& luku, Tehtavalista& tehtavalista);
void lueMerkkijono(std::string& merkkijono);
void tallennaListaNimella(std::string& merkkijono, Tehtavalista& tehtavalista);
void avaaListaNimella(std::string& merkkijono, Tehtavalista& tehtavalista);
bool voikoMuuttaaLuvuksi(std::string& merkkijono, int& lukuna);

int main()
{
    Tehtavalista tehtavalista = Tehtavalista();
    srand(time(NULL));

    char komento;
    std::string merkkijono;
    int luku;

    while (1) {
        system("cls");
        std::cout << "Tehtavienhallinta\n";

        std::cout << std::endl;

        tulostaTehtavat(tehtavalista);

        std::cout << std::endl << std::endl;

        tulostaMenu();

        std::cin >> komento;

        if (komento == '0') {
            break;
        }
        else if (komento == '1') {
            std::cout << "Anna tehtavan kuvaus: ";

            std::string kuvaus = "";

            lueMerkkijono(kuvaus);

            std::cout << "Anna tehtavan prioriteetti (1 - 5) ei-kiireellisesta (1) kiireelliseen (5): ";

            std::getline(std::cin, merkkijono);
            while (!voikoMuuttaaLuvuksi(merkkijono, luku) || !(1 <= luku && luku <=5))
            {
                std::cout << "Kelvoton prioriteetin arvo. Yrita uudelleen: ";
                getline(std::cin, merkkijono);
            }

            tehtavalista.lisaaTehtava(kuvaus, luku);
        }
        else if (komento == '2') {
            std::cout << "Anna tehtavan tunnus: ";

            lueTunnus(merkkijono, luku, tehtavalista);

            tehtavalista.vaihdaTila(luku);
            
        }
        else if (komento == '3') {
            std::cout << "Anna tehtavan tunnus: ";

            lueTunnus(merkkijono, luku, tehtavalista);

            tehtavalista.poistaTehtava(luku);
        }
        else if (komento == '4') {

            tallennaListaNimella(merkkijono, tehtavalista);
        }
        else if (komento == '5') {
            std::cout << "Toisen listan avaaminen nollaa nykyisen listan. Haluatko jatkaa (K/E): ";

            std::cin >> komento;

            if (komento != 'K') {
                continue;
            }
            avaaListaNimella(merkkijono, tehtavalista);
        }
    }

    return 0;
}

void avaaListaNimella(std::string& merkkijono, Tehtavalista& tehtavalista)
{
    std::cout << "Anna avattavan tiedoston nimi, esim. tehtavat.txt: ";

    lueMerkkijono(merkkijono);

    tehtavalista.lueTiedostosta(merkkijono);
}

void tallennaListaNimella(std::string& merkkijono, Tehtavalista& tehtavalista)
{
    std::cout << "Anna tiedoston nimi, esim. tehtavat.txt: ";

    lueMerkkijono(merkkijono);

    tehtavalista.tallennaTiedostoon(merkkijono);
}

void lueMerkkijono(std::string& merkkijono)
{
    std::cin.clear();
    std::cin.ignore();
    std::getline(std::cin, merkkijono);
}

void lueTunnus(std::string& merkkijono, int& luku, Tehtavalista& tehtavalista)
{
    std::cin.clear();
    std::cin.ignore();
    std::getline(std::cin, merkkijono);

    while (!voikoMuuttaaLuvuksi(merkkijono, luku) || tehtavalista.haeIndeksi(luku) == -1)
    {
        std::cout << "Kelvoton tunnuksen arvo. Yrita uudelleen: ";
        getline(std::cin, merkkijono);
    }
}

void tulostaMenu() {
    std::cout << "1) Lisaa uusi tehtava" << std::endl;
    std::cout << "2) Merkitse tehtava valmiiksi / kesken" << std::endl;
    std::cout << "3) Poista tehtava listalta" << std::endl;
    std::cout << "4) Tallenna tehtavalista tiedostoon" << std::endl;
    std::cout << "5) Avaa lista tiedostosta" << std::endl;
    std::cout << "0) Sulje ohjelma" << std::endl;

    std::cout << std::endl;

    std::cout << "Anna komento: ";
}


bool voikoMuuttaaLuvuksi(std::string& input, int& output) {
    try {
        output = std::stoi(input);
    }
    catch (std::invalid_argument) {
        return false;
    }
    return true;
}

void tulostaTehtavat(Tehtavalista& tehtavalista) {
    if (tehtavalista.getTehtavienLkm() == 0) {
        std::cout << "Tehtavalista on tyhja!" << std::endl;
        return;
    }
    std::cout << "Tunnus | Kuvaus | Prioriteetti | Status" << std::endl;

    for (int i = 0; i <= tehtavalista.getVikaTunnus(); i++) {
        if (tehtavalista.haeIndeksi(i) != -1) {
            std::cout << tehtavalista.palautaTehtava(i).naytaTiedot() << std::endl;
        }
    }
}

