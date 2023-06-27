#include "Player.h"

Player::Player() :User()
{
	money = m;    //every new player starts with m as a sum of money
	setUserType(UserType::player);
	heroesCounter = 0;
}

Player::Player(const MyString& name, const MyString& surname, const MyString& userName, const MyString& email, const MyString& password) :
	User(name, surname, userName, email, password, UserType::player)
{
	setUserType(UserType::player);
	money = m;
	heroesCounter = 0;
}

User* Player::clone() const
{
	return new Player(*this);
}

unsigned int Player::getMoney() const
{
	return money;
}

void Player::addNewHeroToCollection(const Superhero& hero)
{
	heroes.pushBack(hero);
}

void Player::incrementMoney(unsigned int sumToAdd)
{
	money += sumToAdd;
	if (money >= MAX_MONEY)
	{
		money = MAX_MONEY;
	}
}

void Player::decrementMoney(unsigned int sumToRemove)
{
	if (money < sumToRemove)
	{
		money = 0;
	}
	else
	{
		money -= sumToRemove;
	}
}

void Player::incrementNumberOfMoves()
{
	numberOfMoves++;
}

void Player::readFromBinaryFile(const MyString& fileName)
{
	std::ifstream ifs(fileName.c_str(), std::ios::in | std::ios::binary);

	if (!ifs.is_open())
	{
		throw std::exception("Error! File failed to open!");
	}

	name << ifs;
	surname << ifs;
	username << ifs;
	email << ifs;
	password << ifs;

	ifs.read((char*)&money, sizeof(money));
	ifs.read((char*)&heroesCounter, sizeof(heroesCounter));

	Superhero* readHeroes = new Superhero[heroesCounter];
	for (size_t i = 0; i < heroesCounter; i++)
	{
		readHeroes[i].readFromBinaryFile(ifs);
		heroes.pushBack(readHeroes[i]);
	}
	delete[] readHeroes;

	ifs.close();
}
void Player::saveToBinaryFile(const MyString& fileName)
{
	std::ofstream ofs(fileName.c_str(), std::ios::out | std::ios::binary);
	if (!ofs.is_open())
	{
		throw std::exception("Error! File failed to open!");
	}
	ofs.clear();    //clears file's content and saves all thå updated information again 

	name >> ofs;
	surname >> ofs;
	username >> ofs;
	email >> ofs;
	password >> ofs;

	heroesCounter = heroes.getSize();
	ofs.write((const char*)&money, sizeof(money));
	ofs.write((const char*)&heroesCounter, sizeof(heroesCounter));

	for (size_t i = 0; i < heroesCounter; i++)
	{
		heroes[i].saveToBinaryFile(ofs);
	}

	ofs.close();
}
void Player::printInfo() const     //that is all the information about a single player that only an administrator can access
{
	std::cout << name << std::endl;
	std::cout << surname << std::endl;
	std::cout << username << std::endl;
	std::cout << email << std::endl;
	std::cout << password << std::endl;
	std::cout << money << '$' << std::endl;
	for (size_t i = 0; i < heroes.getSize(); i++)
	{
		heroes[i].printAll();
	}
}

const Superhero& Player::getHeroByName(const MyString& heroName) const
{
	for (size_t i = 0; i < heroes.getSize(); i++)
	{
		if (heroes[i].compareNickname(heroName))
		{
			return heroes[i];
		}
	}
}


void Player::generalInfo() const
{
	std::cout << username << std::endl;
	std::cout << money << '$' << std::endl;
	for (size_t i = 0; i < heroes.getSize(); i++)
	{
		heroes[i].printGeneralInfo();
	}
}

void Player::changeHeroMode(const MyString& heroName, Mode newMode)
{
	int index = findHeroByName(heroName);
	if (index < 0)
	{
		throw std::exception("Error! There is no such hero in this player's collection!");
	}
	heroes[index].setMode(newMode);
}

void Player::bonusImproveHero(const MyString& heroName)
{
	int index = findHeroByName(heroName);
	if (index < 0)
	{
		throw std::exception("Error! There is no such hero in this player's collection!");
	}
	decrementMoney(money / 4);
	heroes[index].upgrade();
}

void Player::readFromStream(std::ifstream& ifs)
{
	name << ifs;
	surname << ifs;
	username << ifs;
	email << ifs;
	password << ifs;

	ifs.read((char*)&money, sizeof(money));
	ifs.read((char*)&heroesCounter, sizeof(heroesCounter));

	Superhero* readHeroes = new Superhero[heroesCounter];
	for (size_t i = 0; i < heroesCounter; i++)
	{
		readHeroes[i].readFromBinaryFile(ifs);
		heroes.pushBack(readHeroes[i]);
	}
	delete[] readHeroes;
}
void Player::saveToStream(std::ofstream& ofs)
{
	name >> ofs;
	surname >> ofs;
	username >> ofs;
	email >> ofs;
	password >> ofs;

	heroesCounter = heroes.getSize();
	ofs.write((const char*)&money, sizeof(money));
	ofs.write((const char*)&heroesCounter, sizeof(heroesCounter));

	for (size_t i = 0; i < heroesCounter; i++)
	{
		heroes[i].saveToBinaryFile(ofs);
	}
}

int Player::findHeroByName(const MyString& heroName) const
{
	for (unsigned int i = 0; i < heroes.getSize(); i++)
	{
		if (heroes[i].compareNickname(heroName))
		{
			return i;
		}
	}
	return -1;
}

Superhero* Player::returnHeroByName(const MyString& heroName)
{
	int index = findHeroByName(heroName);
	if (index >= 0)
	{
		return &heroes[index];
	}
	return nullptr;
}

void Player::attackAnotherPlayer(Player* attackedPlayer, const MyString& attackingHero, const MyString& attackedHero)
{	
	int indexAttackingHero = findHeroByName(attackingHero);
	int indexAttackedHero =  attackedPlayer->findHeroByName(attackedHero);

	if (indexAttackingHero < 0 || indexAttackedHero < 0)
	{
		throw std::exception("Error! There is no such hero in the collection of this player!");
	}

	heroes[indexAttackingHero].setMode(Mode::attack);
	
	if (attackedPlayer->heroes.empty())
	{
		attackPlayerWithoutHeroes(attackedPlayer, indexAttackingHero);
		return;
	}
	compareHeroesPower(indexAttackingHero, indexAttackedHero, attackedPlayer);
}
void Player::attackRandomHero(Player* attackedPlayer, const MyString& attackingHeroName)
{
	unsigned indexAttackingHero = findHeroByName(attackingHeroName);
	if (attackedPlayer->heroes.empty())
	{
		attackPlayerWithoutHeroes(attackedPlayer, indexAttackingHero);
		return;
	}
	heroes[indexAttackingHero].setMode(Mode::attack);
	int attackedHeroIndex = rand() % (attackedPlayer->heroes.getSize()) + 1;
	
	compareHeroesPower(indexAttackingHero, attackedHeroIndex, attackedPlayer);
}
void Player::attackPlayerWithoutHeroes(Player* attackedPlayer, unsigned indexAttackingHero)
{
    attackedPlayer->decrementMoney(heroes[indexAttackingHero].getPowerSize());
	this->incrementMoney(x);
}
void Player::compareHeroesPower(unsigned indexAttackingHero, unsigned indexAttackedHero, Player* attackedPlayer)
{
	Superhero attacked = attackedPlayer->heroes[indexAttackedHero];
	int cmpPower = heroes[indexAttackingHero].comparePowerTypes(heroes[indexAttackingHero].getPower(), attacked.getPower());

	if (cmpPower == 1)
	{
		heroes[indexAttackingHero].setPowerSize(heroes[indexAttackingHero].getPowerSize() * 2);
		comparePowerSize(indexAttackingHero, indexAttackedHero, attackedPlayer);
	}
	else if (cmpPower == -1)
	{
		attacked.setPowerSize(attacked.getPowerSize() * 2);
	    comparePowerSize(indexAttackingHero, indexAttackedHero, attackedPlayer);
	}
	else
	{
		comparePowerSize(indexAttackingHero, indexAttackedHero, attackedPlayer);
	}
}

void Player::comparePowerSize(unsigned indexAttackingHero, unsigned indexAttackedHero, Player* attackedPlayer)
{
	Superhero attacked = attackedPlayer->heroes[indexAttackedHero];

	bool isDefensive = (attacked.getMode() == Mode::defense);

	if (heroes[indexAttackingHero].getPowerSize() > attacked.getPowerSize())
	{
		unsigned int difference = heroes[indexAttackingHero].getPowerSize() - attacked.getPowerSize();
		this->incrementMoney(difference);
		attackedPlayer->heroes.popAt(indexAttackedHero);
		if (!isDefensive)
		{
			attackedPlayer->decrementMoney(difference);
		}
	}
	else if (heroes[indexAttackingHero].getPowerSize() < attacked.getPowerSize())
	{
		unsigned int difference = attackedPlayer->heroes[indexAttackedHero].getPowerSize() - attacked.getPowerSize();
		attackedPlayer->incrementMoney(z);
		this->decrementMoney(2 * difference);
		heroes.popAt(indexAttackingHero);
	}
	else
	{
		this->decrementMoney(k);
	}
}


