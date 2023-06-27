#pragma once
#include "Superhero.h"
#include "Player.h"
#include "MyVector.hpp"

class Marketplace  
{
	Vector <Superhero> superheroes;

public:
	Marketplace();
	
	void addNewHero(const Superhero& hero);
	void removeSuperhero(const Superhero& hero);

	void printHeroes() const;

	int findHeroByName(const MyString& heroName) const;
	void sellHeroToAPlayer(const MyString& heroName, Player& p);
};


