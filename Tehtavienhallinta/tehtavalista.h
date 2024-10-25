#pragma once
#include <vector>
#include "tehtava.h"

class Tehtavalista {
private:
	std::vector<Tehtava> tehtavat;
	std::vector<Tehtava>::iterator iteraattori;

	int viimeisinTunnus;

	void tyhjennaLista();

public:
	Tehtavalista();

	int getTehtavienLkm();
	int getVikaTunnus();

	Tehtava& palautaTehtava(int tunnus);

	int haeIndeksi(int tunnus);

	void lisaaTehtava(std::string kuvaus);
	void lisaaTehtava(std::string kuvaus, int prioriteetti);

	void vaihdaTila(int tunnus);

	void poistaTehtava(int tunnus);

	void lueTiedostosta(std::string tiedostonNimi);
	void tallennaTiedostoon(std::string tiedostonNimi);
};