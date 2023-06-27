#pragma once
#include <iostream>
#include "System.h"
//inspired by github/Plamena-Ilieva/ OOP-Tasks-2022/Kindle/ Vector.hpp

const unsigned MAX_POWER_STR = 6;
class Interface
{
	System* system;
	
public:
	Interface();
	
	void logIn();
	void signUp();
	void logOut();
	
	Superhero* getInitialHeroes();
	void initialHeroes();  //in case the market is empty at the beginning, the admin has to add three brand new heroes to it
	
	void commandAddNewUser();
	void commandAddNewHero();
	void commandAddBoughtHero();
	void commandSellHeroToAPlayer();
	void commandAttackAnotherPlayer();
	void commandDeleteYourProfile();        //only for a player in case he/she intends to delete his/her own profile
	void commandDeleteAPlayer();           //this command can be performed only be administrators
	void commandChangeHeroesMode();       // for players only
	void commandBonusImproveHero();       //  bonus command for players

	void commandPrintPlayersGeneralInformation() const;   //can be accessed by both admins and players
	void commandPrintPlayersDetailedInformation() const;  //for admins only
	void commandPrintPlayersRanking();
	void commandPrintUserInfoByName() const;
	void commandPrintMarketInformation() const;
	void commandPrintPlayerSavedProgress() const;

	Superhero enterHeroesData() const;
	bool isAnAdministrator(const MyString& userName) const;
	bool isAPlayer(const MyString& userName) const;
	bool checkIfLoggedIn(const MyString& userName) const;

	void printOpeningMessage() const;
	bool validCommand(int commandNumber) const;
	void getUsersInput();
	void programExecution();
	void clearConsole() const;              // By: Nikola Svetoslavov's github
};


