#include "tehtavalista.h"
#include <iostream>
#include <fstream>

#include <sstream>
#include <vector>

// alustetaan tyhj‰ teht‰v‰lista
Tehtavalista::Tehtavalista() {
	tehtavat.clear();
	viimeisinTunnus = 1;
}

void Tehtavalista::tyhjennaLista() {
	tehtavat.clear();
}

int Tehtavalista::getTehtavienLkm() {
	return tehtavat.size();
}

int Tehtavalista::getVikaTunnus() {
	return viimeisinTunnus;
}

void Tehtavalista::lisaaTehtava(std::string kuvaus) {
	Tehtava tehtava = Tehtava(kuvaus);

	tehtava.setTunnus(viimeisinTunnus);
	viimeisinTunnus++;

	tehtavat.push_back(tehtava);
}

void Tehtavalista::lisaaTehtava(std::string kuvaus, int prioriteetti) {
	Tehtava tehtava = Tehtava(kuvaus);

	tehtava.setTunnus(viimeisinTunnus);
	viimeisinTunnus++;

	tehtava.setPrioriteetti(prioriteetti);

	tehtavat.push_back(tehtava);
}

int Tehtavalista::haeIndeksi(int tunnus) {
	if (tehtavat.empty()) {
		return -1;
	}
	
	for (int i = 0; i < tehtavat.size(); i++) {
		if (tunnus == tehtavat[i].getTunnus()) {
			return i;
		}
	}
	return -1;
}

Tehtava& Tehtavalista::palautaTehtava(int tunnus) {
	int indeksi = haeIndeksi(tunnus);
	return tehtavat[indeksi];	
}

void Tehtavalista::vaihdaTila(int tunnus) {
	Tehtava* tehtava = &palautaTehtava(tunnus);

	if (tehtava->getValmis()) {
		tehtava->setValmis(false);
	} else {
		tehtava->setValmis(true);
	}
}

void Tehtavalista::poistaTehtava(int tunnus) {
	int indeksi = haeIndeksi(tunnus);
	tehtavat.erase(tehtavat.begin()+indeksi);
}

void Tehtavalista::tallennaTiedostoon(std::string tiedostonNimi) {
	// Object tiedostoon kirjoittamista varten
	std::ofstream tiedosto_obj;

	// Avataan tiedosto append-tilassa
	tiedosto_obj.open(tiedostonNimi, std::ios::out | std::ios::app);

	// tyhj‰ teht‰v‰-muuttuja
	Tehtava tehtava;

	// k‰yd‰‰n jokainen teht‰v‰listan teht‰v‰ l‰pi
	for (iteraattori = tehtavat.begin(); iteraattori != tehtavat.end(); iteraattori++) {
		// asetaan teht‰v‰-muuttujaan iteraattorin muistipaikassa oleva teht‰v‰
		tehtava = *iteraattori;

		// kirjoitetaan tehtavan tiedot tiedostoon
		tiedosto_obj << tehtava.getTunnus() << "|" << tehtava.getKuvaus() << "|" << tehtava.getPrioriteetti() << "|" << tehtava.getValmis() << std::endl;
	}

	tiedosto_obj.close();

}

void Tehtavalista::lueTiedostosta(std::string tiedostonNimi) {
	// Object tiedoston lukemista varten
	std::ifstream tiedosto_obj;
	// Avataan tiedosto input-tilassa
	tiedosto_obj.open(tiedostonNimi, std::ios::in);

	// tyhjennet‰‰n teht‰v‰lista tiedoston teht‰vi‰ varten
	tyhjennaLista();
	viimeisinTunnus = 0;

	// tyhj‰ teht‰v‰-muuttuja tietojen lukemista varten
	Tehtava tehtava;

	// tyhj‰ merkkijono rivien lukemista varten
	std::string rivi{};

	while (std::getline(tiedosto_obj, rivi)) {
		// alustetaan teht‰v‰-muuttujaan uusi teht‰v‰-olio
		tehtava = Tehtava();
		// luetaan kokonainen rivi std::string rivi -muuttujaan
	    // Asetaan se std::istringstreamiin, jotta se voidaan paloitella iostream funktioilla
		std::istringstream iss(rivi);

		std::string osamerkkijono{};
		// s‰ilˆt‰‰n osamerkkijonot vectoriin
		std::vector<std::string> osamerkkijonot{};

		// paloitellaan std::istringstream osamerkkijonoihin erotinmerkin | perusteella
		while (std::getline(iss, osamerkkijono, '|')) {

			// lis‰t‰‰n osamerkkijonot vectoriin talteen
			osamerkkijonot.push_back(osamerkkijono);
		}
		// asetaan osamerkkijonoissa olevat tiedot alustettuun teht‰v‰-olioon
		tehtava.setTunnus(std::stoul(osamerkkijonot[0]));

		// jos luetun teht‰v‰n tunnus on suurempi kuin viimeisin ylh‰‰ll‰ oleva, p‰ivitet‰‰n viimeisin uuteen arvoon
		if (tehtava.getTunnus() > viimeisinTunnus) {
			viimeisinTunnus = tehtava.getTunnus();
		}

		tehtava.setKuvaus(osamerkkijonot[1]);
		tehtava.setPrioriteetti(std::stoi(osamerkkijonot[2]));
		tehtava.setValmis(std::stoi(osamerkkijonot[3]));

		// lis‰t‰‰n teht‰v‰ teht‰v‰listalle talteen
		tehtavat.push_back(tehtava);
	}
	viimeisinTunnus++;

	tiedosto_obj.close();
}
