// Spacecraft.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Planet
{
	std::string namePlanet;
	std::string nameSpaceship;
	Planet(const std::string& namePlanet, const std::string nameSpaceship):namePlanet(namePlanet), nameSpaceship(nameSpaceship){}

public:

	std::string getNamePlanet()
	{
		return namePlanet;
	}

	std::string getNameSpaceship()
	{
		return nameSpaceship;
	}

	static Planet* sharedPlanet(const std::string& namePlanet, const std::string nameSpaceship)
	{
		static Planet* planet = new Planet(namePlanet, nameSpaceship);
		return planet;
	}
};

class IAstronauts
{
public:
	virtual void sitOnTheSpaceship(Planet* planet) = 0;
	virtual void comeOffFromTheSpaceship(Planet* planet) = 0;
};

class Astronauts : public IAstronauts
{
public:
	virtual void sitOnTheSpaceship(Planet* planet) override
	{
		std::cout << "Sit on the Planet " <<  planet->getNamePlanet() << " on the spaceship " << planet->getNameSpaceship() << std::endl;
	}
	virtual void comeOffFromTheSpaceship(Planet* planet) override
	{
		std::cout << "Come off on the Planet " << planet->getNamePlanet() << " on the spaceship " << planet->getNameSpaceship() << std::endl;
	}
};

class Spaceship
{
	std::vector <IAstronauts*> m_astronauts;
public:

	void take(IAstronauts* _astronauts)
	{
		m_astronauts.push_back(_astronauts);
	}

	void goDown(IAstronauts* _astronauts)
	{
		auto it = std::find(m_astronauts.begin(), m_astronauts.end(), _astronauts);
		if (it != m_astronauts.end())
		{
			m_astronauts.erase(it);
		}
	}

	void plateShutdown(Planet* planet)
	{
		for (IAstronauts* astronauts : m_astronauts)
		{
			astronauts->comeOffFromTheSpaceship(planet);
		}
	}

	void placingBord(Planet* planet)
	{
		for (IAstronauts* astronauts : m_astronauts)
		{
			astronauts->sitOnTheSpaceship(planet);
		}
	}
};



int main()
{
	//Planet::sharedPlanet("Earth", "Spaceship");
	Spaceship sp;
	IAstronauts* a1 = new Astronauts;

	sp.take(a1);
	sp.placingBord(Planet::sharedPlanet("Earth", "Spaceship"));

	system("pause");
    return 0;
}

