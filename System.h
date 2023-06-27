#pragma once
#include <iostream>

#include "Marketplace.h"
#include "Factory.h"



//inspired by: Georgy Terziev/ Sem. 15 / Design Patterns / Creational / Singleton/ Singleton.h

class System //Singleton
{
private:
	static System* instance;
	Vector<User *> users;
	Marketplace market;

	System();
	void free();

public:
	System(const System&) = delete;
	System& operator=(const System&) = delete;
	~System();

	static System* getInstance();
	
	int getUserIndex(const MyString& username) const;

	void addNewUser(unsigned typeNumber, const MyString& name, const MyString& surname, const MyString& userName, const MyString& email, const MyString& password);

	void addNewHero(const Superhero& hero);
	void addBoughtHero(const MyString& playerName, const MyString& heroName);
	void sellHeroToAPlayer(const MyString& heroName, const MyString& playerName);
	void deletePlayer(const MyString& playerName);   //used in case an admin intends to delete a player's profile 
													 // or when the latter wants to remove their own account

	void attackAnotherPlayer(const MyString& attackingPlayer, const MyString& attackedPlayer, const MyString& attackingHero, const MyString& attackedHero);
	void attackRandomHero(const MyString& attackingPlayerName, const MyString& attackedPlayerName, const MyString& attackingHero);
	void showUserInfo(const MyString& playerName);

	int findUserByName(const MyString& userName) const;	
	void incrementPlayersMoneyInAPeriod();

	void logIn(const MyString& username, const MyString& password);
	void signUp(unsigned typeNumber, const MyString& name, const MyString& surname, const MyString& userName, const MyString& email, const MyString& password);
	void logOut(const MyString& username);

	bool checkIfLoggedIn(const MyString& userName) const;
	bool isAPlayer(const MyString& userName) const;
	bool isAnAdministrator(const MyString& userName) const;

	void printPlayers() const;
	void printDetailedInfo() const;
	void getRankingPrinted(const MyString& username);   //this funcion is not const as it calls a non-const other function in its body

	void printPlayerSavedProgress(const MyString& user, const MyString& playerName) const;
	void printMarket(const MyString& username) const;
	void printUserInfo(const MyString& username) const;

	void changeHeroMode(const MyString& playerName, const MyString& heroName, Mode mode);
	void improveHero(const MyString& playerName, const MyString& heroName);

	unsigned playersCount() const;
	Vector<Player*> extractPlayers();
	void partOfSelectionSort(int index, int N, int minIndex, const unsigned int* playersMoney);
	void sortPlayersByScore(Vector<Player*> players, unsigned count);

	void saveRankingToFile(std::ofstream& ofs);
	void readRankingFromFile(std::ifstream& ifs);

};

