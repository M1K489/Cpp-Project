#include "tehtava.h"
#include <iostream>

Tehtava::Tehtava() {
	// arvotaan tehtavalle tunnus satunnaislukuna
	this->tunnus = rand() % 100 + 1;

	kuvaus = "";
	prioriteetti = 3;
	onkoValmis = false;
}

Tehtava::Tehtava(std::string kuvaus): Tehtava() {
	this->setKuvaus(kuvaus);
}

Tehtava::Tehtava(std::string kuvaus, int tunnus): Tehtava() {
	this->setKuvaus(kuvaus);
	this->setTunnus(tunnus);
}

int Tehtava::getTunnus() {
	return tunnus;
}

void Tehtava::setTunnus(int tunnus) {
	this->tunnus = tunnus;
}

std::string Tehtava::getKuvaus() {
	return kuvaus;
}

void Tehtava::setKuvaus(std::string kuvaus) {
	this->kuvaus = kuvaus;
}

int Tehtava::getPrioriteetti() {
	return prioriteetti;
}

void Tehtava::setPrioriteetti(int prioriteetti) {
	this->prioriteetti = prioriteetti;
}

bool Tehtava::getValmis() {
	return onkoValmis;
}

void Tehtava::setValmis(bool status) {
	this->onkoValmis = status;
}

std::string Tehtava::naytaTiedot() {
	// muutetaan tehtavan muuttujan valmis (0/1) arvo luettavampaan muotoon
	std::string status = this->onkoValmis ? "Tehty" : "Kesken";

	// palautetaan merkkijonoesitys tehtavan tilasta
	return std::to_string(this->tunnus) + " | " + this->kuvaus + " | " + std::to_string(this->prioriteetti) + " | " + status;
}

// toteutaan yhtäsuuruusvertailuoperaattori tehtavien välille. Jokaisella tehtävällä on yksilöllinen tunnus
bool Tehtava::operator==(const Tehtava& t) const {
	return tunnus == t.tunnus;
};
