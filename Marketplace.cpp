#include "Marketplace.h"

Marketplace::Marketplace() {}



void Marketplace::addNewHero(const Superhero& hero)
{
	superheroes.pushBack(hero);
}
void Marketplace::removeSuperhero(const Superhero& hero)
{
	int index = findHeroByName(hero.getNickname());
	superheroes.popAt(index);
}

void Marketplace::printHeroes() const
{
	for (size_t i = 0; i < superheroes.getSize(); i++)
	{
		std::cout << i << ". ";
		superheroes[i].printGeneralInfo();
	}
}

int Marketplace::findHeroByName(const MyString& heroName) const
{
	for (unsigned int i = 0; i < superheroes.getSize(); i++)
	{
		if (superheroes[i].compareNickname(heroName))
		{
			return i;
		}
	}
	return -1;
}

void Marketplace::sellHeroToAPlayer(const MyString& heroName, Player& p)
{
	int index = findHeroByName(heroName);
	if (index != -1 && !superheroes[index].getIsBought())
	{
		p.addNewHeroToCollection(superheroes[index]);
		superheroes.popAt(index);
	}
	else
	{
		throw std::exception("Error! There is no such hero or it has already been bought!");
	}
}