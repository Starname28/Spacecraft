// Spacecraft.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>

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

	static std::shared_ptr<Planet> sharedPlanet(const std::string& namePlanet, const std::string& nameSpaceship)
	{
		static std::shared_ptr<Planet> planet(new Planet(namePlanet, nameSpaceship));
		return planet;
	}
};

class IAstronaut
{
public:
	virtual void sitOnTheSpaceship(std::shared_ptr<Planet> planet) = 0;
	virtual void comeOffFromTheSpaceship(std::shared_ptr<Planet> planet) = 0;
};

class Astronaut : public IAstronaut
{
public:
	virtual void sitOnTheSpaceship(std::shared_ptr<Planet> planet) override
	{
		std::cout << "Sit on the Planet " <<  planet->getNamePlanet() << " on the spaceship " << planet->getNameSpaceship() << std::endl;
	}
	virtual void comeOffFromTheSpaceship(std::shared_ptr<Planet> planet) override
	{
		std::cout << "Come off on the Planet " << planet->getNamePlanet() << " on the spaceship " << planet->getNameSpaceship() << std::endl;
	}
};

class Spaceship
{
	std::vector <std::shared_ptr<IAstronaut>> m_astronauts;
public:

	void take(std::shared_ptr<IAstronaut> _astronaut)
	{
		m_astronauts.push_back(_astronaut);
	}

	void goDown(std::shared_ptr<IAstronaut> _astronauts)
	{
		auto it = std::find(m_astronauts.begin(), m_astronauts.end(), _astronauts);
		if (it != m_astronauts.end())
		{
			m_astronauts.erase(it);
		}
	}

	void plateShutdown(std::shared_ptr<Planet> planet)
	{
		for (std::shared_ptr<IAstronaut> astronauts : m_astronauts)
		{
			astronauts->comeOffFromTheSpaceship(planet);
		}
	}

	void placingBord(std::shared_ptr<Planet> planet)
	{
		for (std::shared_ptr<IAstronaut> astronauts : m_astronauts)
		{
			astronauts->sitOnTheSpaceship(planet);
		}
	}
};



int main()
{
	//Planet::sharedPlanet("Earth", "Spaceship");
	Spaceship sp;
	std::shared_ptr<IAstronaut> a1(new Astronaut);

	sp.take(a1);
	sp.placingBord(Planet::sharedPlanet("Earth", "Spaceship"));

	system("pause");
    return 0;
}

