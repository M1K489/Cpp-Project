#pragma once
#include <string>

class Tehtava {
private:
	int tunnus;
	std::string kuvaus;
	int prioriteetti;
	bool onkoValmis;

public:
	Tehtava();
	Tehtava(std::string kuvaus);
	Tehtava(std::string kuvaus, int tunnus);

	int getTunnus();
	void setTunnus(int tunnus);

	std::string getKuvaus();
	void setKuvaus(std::string kuvaus);

	int getPrioriteetti();
	void setPrioriteetti(int prioriteetti);

	bool getValmis();
	void setValmis(bool status);
	
	std::string naytaTiedot();

	bool operator==(const Tehtava& t) const;
};
