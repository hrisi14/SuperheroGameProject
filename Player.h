#pragma once
#include <iostream>

#include "User.h"
#include "Superhero.h"
#include "MyVector.hpp"


const unsigned int MAX_MONEY = 500;

class Player : public User
{
	Vector <Superhero> heroes;

	unsigned int money;

	unsigned heroesCounter; //this variable is needed when reading from file

public:
	Player();
	Player(const MyString& name, const MyString& surname, const MyString& userName, const MyString& email, const MyString& password);

	void incrementMoney(unsigned int sumToAdd);
	void decrementMoney(unsigned int sumToRemove);
	void incrementNumberOfMoves();

	unsigned int getMoney() const;
	
	const Superhero& getHeroByName(const MyString& heroName) const;
	User* clone() const override;

	void addNewHeroToCollection(const Superhero& hero);

	void changeHeroMode(const MyString& heroName, Mode newMode);

	void readFromBinaryFile(const MyString& fileName) override;
	void saveToBinaryFile(const MyString& fileName) override;

	void readFromStream(std::ifstream&) override;
	void saveToStream(std::ofstream&) override;

	void printInfo() const override;
	void generalInfo() const override;

	void bonusImproveHero(const MyString& heroName);

	int findHeroByName(const MyString& heroName) const;
	Superhero* returnHeroByName(const MyString& heroName);

	void attackAnotherPlayer(Player* attackedPlayer, const MyString& attackingHero, const MyString& attackedHero);	
	void attackRandomHero(Player* attackedPlayer, const MyString& attackingHeroName);
	void attackPlayerWithoutHeroes(Player* attackedPlayer, unsigned indexAttackingHero);
	void compareHeroesPower(unsigned indexAttackingHero, unsigned indexAttackedHero, Player* attackedPlayer);
	void comparePowerSize(unsigned indexAttackingHero, unsigned indexAttackedHero, Player* attackedPlayer);
};

