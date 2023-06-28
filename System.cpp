#include "System.h"
#include <iostream>

System* System::instance = nullptr;

System::System()
{
	Administrator* initialAdmin = new Administrator("Default admin's name", "Default admin's surname", "Default admin", "default@gmail.com", "Password12");
	users.pushBack(initialAdmin);   //creates a default admin (by hand) in the beginning of the game
}

System* System::getInstance()
{
	if (instance == nullptr)
	{
		instance = new System();
	}
	return instance;
}

void System::free()
{	
	for (size_t i = 0; i < users.getSize(); i++)
	{
		delete users[i];
	}
	delete instance;	
}
int System::getUserIndex(const MyString& username) const
{
	for (unsigned i = 0; i < users.getSize(); i++)
	{
		if (users[i]->compareUsername(username))
		{
			return i;
		}
	}
	return -1;
}
System::~System()
{
	free();
}

void System::addNewUser(unsigned typeNumber, const MyString& name, const MyString& surname, const MyString& userName, const MyString& email, const MyString& password)
{
    users.pushBack(factory(typeNumber, name, surname, userName, email, password));	
}
void System::deletePlayer(const MyString& playerName)
{	
	if (!isAnAdministrator(playerName))
	{
		throw std::exception("Error! This is an administrator, not a player!");
	}
	int index = findUserByName(playerName);
	users.popAt(index);
}
void System::showUserInfo(const MyString& username)
{
	int index = findUserByName(username);
	if (index < 0)
	{
		throw std::exception("Error! There is no such user!");
	}
	users[index]->printInfo();
}
void System::addNewHero(const Superhero& hero)
{
	market.addNewHero(hero);
}
void System::addBoughtHero(const MyString& playerName, const MyString& heroName)
{
	int playerIndex = findUserByName(playerName);
	if (playerIndex == -1 || users[playerIndex]->getUserType()== UserType::administrator)
	{
		throw std::exception("Error! There is no such player");
	}
	Player* p = (Player*)users[playerIndex];
	market.addNewHero(*p->returnHeroByName(heroName));
}
void System::sellHeroToAPlayer(const MyString& heroName, const MyString& playerName)
{
	int playerIndex = findUserByName(playerName);

	if (playerIndex != -1 && users[playerIndex]->getUserType() == UserType::player)
	{
		Player* p = (Player*) users[playerIndex];   //an inevitable cast
		market.sellHeroToAPlayer(heroName, *p);
	}
	else
	{	
		throw std::exception("Error! There is no such player!");		
	}     	
}
void System::attackAnotherPlayer(const MyString& attackingPlayerName, const MyString& attackedPlayerName, const MyString& attackingHero, const MyString& attackedHero)
{
	int indexAttackingPlayer = findUserByName(attackingPlayerName);
	int indexAttackedPlayer = findUserByName(attackedPlayerName);

	if (indexAttackingPlayer < 0 || indexAttackedPlayer < 0)
	{
		throw std::exception("Error! There is no such user!");
	}

	if (users[indexAttackingPlayer]->getUserType() == UserType::administrator || users[indexAttackedPlayer]->getUserType() == UserType::administrator)
	{
		throw std::exception("Error! Only players (not administrators) could participate in an attack!");
	}
	Player* attackingPlayer = (Player*)users[indexAttackingPlayer];    //an inevitable cast
	Player* attackedPlayer = (Player*)users[indexAttackedPlayer];

	attackingPlayer->attackAnotherPlayer(attackedPlayer, attackingHero, attackedHero);	
}

void System::attackRandomHero(const MyString& attackingPlayerName, const MyString& attackedPlayerName, const MyString& attackingHero)
{
	int indexAttackingPlayer = findUserByName(attackingPlayerName);
	int indexAttackedPlayer = findUserByName(attackedPlayerName);

	if (indexAttackingPlayer < 0 || indexAttackedPlayer < 0)
	{
		throw std::exception("Error! There is no such user!");
	}
	Player* attackingPlayer = (Player*)users[indexAttackingPlayer];    //an inevitable cast
	Player* attackedPlayer = (Player*)users[indexAttackedPlayer];

	attackingPlayer->attackRandomHero(attackedPlayer, attackingHero);
}

int System::findUserByName(const MyString& userName) const
{
	if (users.empty() || users.getSize()==1)
	{
		return -1;
	}
	for (unsigned int i = 0; i < users.getSize(); i++)
	{
		if ((*users[i]).compareUsername(userName))
		{
			return i;
		}
	}
	return -1;
}

void System::logIn(const MyString& username, const MyString& password)
{
    for (size_t i = 0; i < users.getSize(); i++)
    {
        if (users[i]->compareUsername(username))
        {
            if (users[i]->loggedIn)
            {
                throw std::invalid_argument("Error! User has already logged in!");
            }
            if (users[i]->comparePassword(password))
            {
                users[i]->loggedIn = true;
                if (users[i]->getUserType() == UserType::player)
                {
                    Player* player = (Player*)users[i];
                    player->incrementNumberOfMoves();
					if (player->getNumberOfMoves() > 3)
					{
						std::cout << "Error! No more than three moves allowed!" << std::endl;
						break;
					}
                    if (player->getNumberOfMoves() % 2 == 0)
                    {
                        incrementPlayersMoneyInAPeriod();
                    }
                }
				return;
            }
			else
			{
				throw std::invalid_argument("Error! Incorrect password!");
			}
        }
    }
	throw std::invalid_argument("Error! Incorrect username!");

}


void System::signUp(unsigned typeNumber, const MyString& name, const MyString& surname, const MyString& userName, const MyString& email, const MyString& password)
{
	if (findUserByName(userName)!=-1)
	{
		std::cout << "Unfortunately, this username has already been taken! Please, try with another one instead.";		
	}
	else
	{
		User* addedUser = factory(typeNumber, name, surname, userName, email, password);
		users.pushBack(addedUser);
		addedUser->saveToBinaryFile(name);
	}
}

void System::logOut(const MyString& username)
{
	int userIndex = findUserByName(username);
    if (userIndex == -1)
    {
        throw std::invalid_argument("Error! There is no such user!");
    }
    users[userIndex]->saveToBinaryFile(username);        //saves all the updated information about the user in a file 	
    users[userIndex]->loggedIn = false;
	users[userIndex]->incrementMoves();
}


void System::incrementPlayersMoneyInAPeriod()
{
    for (size_t i = 0; i < users.getSize(); i++)
    {
        if (users[i]->getUserType() == UserType::player && users[i]->getNumberOfMoves() % 2 > 0)
        {
            Player* p = (Player*)users[i];
            p->incrementMoney(j);            
        }
    }
}


bool System::isAnAdministrator(const MyString& userName) const
{
	int userIndex =  findUserByName(userName);
	if (userIndex == -1)
	{
		throw std::exception("Error! There is no such user!");
	}
	return users[userIndex]->getUserType() == UserType::administrator;
}
bool System::isAPlayer(const MyString& userName) const
{
	int userIndex = findUserByName(userName);
	if (userIndex == -1)
	{
		throw std::exception("Error! There is no such user!");
	}
	return users[userIndex]->getUserType() == UserType::player;
}

bool System::checkIfLoggedIn(const MyString& userName) const
{
	int userIndex = findUserByName(userName);
	if (userIndex == -1)
	{
		throw std::exception("Error! There is no such user!");
	}
	return users[userIndex]->loggedIn;	
}

void System::printPlayers() const
{
	for (size_t i = 0; i < users.getSize(); i++)
	{
		if (users[i]->getUserType() == UserType::player)
		{
			users[i]->generalInfo();
		}
	}
}

void System::getRankingPrinted(const MyString& username) 
{
	if (checkIfLoggedIn(username))
	{
		Vector<Player*> players = extractPlayers();
		unsigned count = playersCount();

		sortPlayersByScore(players, count);

		for (size_t i = 0; i < count; i++)
		{
			(*players[i]).printInfo();
		}
	}
}

void System:: printPlayerSavedProgress(const MyString& user, const MyString& playerName) const
{
	if (isAnAdministrator(user) && checkIfLoggedIn(user))
	{
		int index = findUserByName(playerName);
		if (index == -1)
		{
			throw std::exception("Error! There is no such user!");
		}
		users[index]->readFromBinaryFile(playerName);
		users[index]->printInfo();
	}
}

void System::printMarket(const MyString& username) const
{
	int index = findUserByName(username);
	if (index==-1)
	{
		throw std::exception("Error! There is no such user!");
	}
	if (checkIfLoggedIn(username))
	{
		market.printHeroes();
	}
}

void System::changeHeroMode(const MyString& playerName, const MyString& heroName, Mode mode)
{
	int index = findUserByName(playerName);
	if (index == -1  || !checkIfLoggedIn(playerName) || !isAPlayer(playerName))
	{
		throw std::exception("Error! Invalid input!");
	}
	Player* p = (Player*)users[index];
	p->changeHeroMode(heroName, mode);
}

void System::improveHero(const MyString& playerName, const MyString& heroName)
{
	int index = findUserByName(playerName);
	if (index == -1 || !checkIfLoggedIn(playerName) || !isAPlayer(playerName))
	{
		throw std::exception("Error! Invalid input!");
	}
	Player* p = (Player*)users[index];
	p->bonusImproveHero(heroName);
}

unsigned System::playersCount() const
{
	unsigned counter = 0;
	for (size_t i = 0; i < users.getSize(); i++)
	{
		if (users[i]->getUserType() == UserType::player)
		{
			counter++;
		}
	}
	return counter;
}

Vector<Player*> System::extractPlayers()
{
	Vector<Player*> players;
	for (size_t i = 0; i < users.getSize(); i++)
	{
		if (users[i]->getUserType() == UserType::player)
		{
			Player* p = (Player*)users[i];      //an inevitable cast
			players.pushBack(p);
		}
	}
	return players;
}

void System::partOfSelectionSort(int index, int N, int minIndex, const unsigned int* playersMoney)
{
	for (int j = index; j < N; j++)
	{
		if (playersMoney[j] < playersMoney[minIndex])
		{
			minIndex = j;
		}
	}
}
void System::sortPlayersByScore(Vector<Player*> players, unsigned count)
{	
	unsigned int* playersMoney = new unsigned int[count];

	for (unsigned i = 0; i < count; i++)
	{
		playersMoney[i] = (*players[i]).getMoney();
	}

	for (unsigned i = 0; i < count - 1; i++)
	{
		int minMoneyIndex = i;

		partOfSelectionSort(i, count, minMoneyIndex, playersMoney);

		if (minMoneyIndex != i)
		{
			Player temp = (*players[i]);
			players[i] = players[minMoneyIndex];
			players[minMoneyIndex] = &temp;

			unsigned int tempMoney = playersMoney[i];
			playersMoney[i] = playersMoney[minMoneyIndex];
			playersMoney[minMoneyIndex] = tempMoney;
		}
	}
	delete[] playersMoney;
}

void System::saveRankingToFile(std::ofstream& ofs)
{
	Vector <Player*> players = extractPlayers();
	unsigned count = playersCount();

	sortPlayersByScore(players, count);
	ofs.write((const char*)count, sizeof(count));

	for (size_t i = 0; i < count; i++)
	{
		(*players[i]).saveToStream(ofs);
	}	

	for (size_t i = 0; i < count; i++)
	{
		delete players[i];
	}
}

void System::readRankingFromFile(std::ifstream& ifs)
{
	unsigned count = 0;
	ifs.read((char*)&count, sizeof(count));

	Player* players = new Player [count];

	for (size_t i = 0; i < count; i++)
	{
		players[i].readFromStream(ifs);
	}

	for (size_t i = 0; i < count; i++)
	{
		players[i].printInfo();
	}
	delete[] players;
}

void System::printDetailedInfo() const
{
	for (size_t i = 0; i < users.getSize(); i++)
	{
		if (users[i]->getUserType() == UserType::player)
		{
			users[i]->printInfo();
		}
	}
}

void System::printUserInfo(const MyString& username) const
{
	int index = findUserByName(username);
	if (index != -1)
	{
		users[index]->printInfo();
	}
}