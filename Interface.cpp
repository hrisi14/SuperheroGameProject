#include "Interface.h"

//parts of the logIn, logOut and signUp functions are taken by :gihub/plamena-ilieva/Kindle

Interface::Interface()
{
    system = system->getInstance();
}
void Interface::logIn()
{
    std::cout << "Please, enter your username:" << std::endl;
    MyString username;
    std::cin >> username;

    std::cout << "Please, enter yout password:" << std::endl;
    MyString password;
    std::cin >> password;
    system->logIn(username, password);
}

void Interface::signUp()
{  
        std::cout << "Please, enter 1 if you would wish to sign in as an administrator, and 2 - as a player:" << std::endl;
        unsigned number;
        std::cin >> number;
        if (number != 1 && number!=2)
        {
            throw std::exception("Error! Invalid user type!");
        }
        std::cout << "Please, enter user's name:" << std::endl;
        MyString name;
        std::cin >> name;

        std::cout << "Please, enter user'surname:" << std::endl;
        MyString surname;
        std::cin >> surname;

        std::cout << "Please, enter user's nickname:" << std::endl;
        MyString userName;
        std::cin >> userName;

        std::cout << "Please, enter user's email:" << std::endl;
        MyString email;
        std::cin >> email;

        std::cout << "Please, enter user's password:" << std::endl;
        MyString password;
        std::cin >> password;

        system->signUp(number, name, surname, userName, email, password);
}

void Interface::logOut()
{
    std::cout << "Please, enter your username:" << std::endl;
    MyString username;
    std::cin >> username;

    system->logOut(username);
}
Superhero* Interface::getInitialHeroes()
{
    std::cout << "As an administrator, enter personal data of three heroes you want to add to the marketplace since it is empty:" << std::endl;

    Superhero* heroes = new Superhero[3];
    for (size_t i = 0; i < 3; i++)
    {
        heroes[i] = enterHeroesData();
    }
    return heroes;
}

void Interface::initialHeroes()
{
    Superhero* initialHeroes = getInitialHeroes();                //the admin adds three new heroes when 
    system->addNewHero(initialHeroes[0]);                        //logging in/ signing up in case the market is empty	
    system->addNewHero(initialHeroes[1]);
    system->addNewHero(initialHeroes[2]);
    delete[] initialHeroes;
}

void Interface::commandAddNewUser()
{
    std::cout << "Please, enter your username before trying to add another user:" << std::endl;
    MyString username;
    std::cin >> username;
    if (isAnAdministrator(username) && checkIfLoggedIn(username))
    {
        std::cout << "Please, enter the data of the user you want to add:" << std::endl;
        std::cout << "Please, enter 1 for the registration of an administrator, and 2- for a player:" << std::endl;
        unsigned typeNumber;
        std::cin >> typeNumber;
        if (typeNumber != 1 && typeNumber != 2)
        {
            throw std::exception("Error! Invalid data!");
        }

        std::cout << "Please, enter user's name:" << std::endl;
        MyString name;
        std::cin >> name;

        std::cout << "Please, enter user'surname:" << std::endl;
        MyString surname;
        std::cin >> surname;

        std::cout << "Please, enter user's nickname:" << std::endl;
        MyString userName;
        std::cin >> userName;

        std::cout << "Please, enter user's email:" << std::endl;
        MyString email;
        std::cin >> email;

        std::cout << "Please, enter user's password:" << std::endl;
        MyString password;
        std::cin >> password;

        system->addNewUser(typeNumber, name, surname, userName, email, password);
    }
    /*else
    {
        throw std::exception("Error! Only for administrators!");
    }*/
}
void Interface::commandAddNewHero()
{
    std::cout << "Please, enter your username first:";
    MyString username;
    std::cin >> username;
    if (isAnAdministrator(username) && checkIfLoggedIn(username))
    {
        Superhero newHero = enterHeroesData();
        system->addNewHero(newHero);
        std::cout << "Hero successfully added!" << std::endl;
    }
    else
    {
        throw std::exception("Error! Only for administrators!");
    }
}
void Interface::commandAddBoughtHero()
{
    std::cout << "Please, enter your username first:";
    MyString username;
    std::cin >> username;

    if (isAnAdministrator(username) && checkIfLoggedIn(username))
    {
        std::cout << "Choose between one of the players' heroes:" << std::endl;
        commandPrintPlayersRanking();
        
        std::cout << "Please, enter the name of the player whose hero you want to add:" << std::endl;
        MyString playerName;
        std::cin >> playerName;

        std::cout << "Please, enter the name of the hero you'd to add:" << std::endl;
        MyString heroName;
        std::cin >> heroName;

        system->addBoughtHero(playerName, heroName);
        std::cout << "Hero successfully added!" << std::endl;
    }
    else
    {
        throw std::exception("Error! Only for administrators!");
    }
}
void Interface::commandSellHeroToAPlayer()
{
    std::cout << "Please, enter your username:" << std::endl;
    MyString username;
    std::cin >> username;

    if (isAPlayer(username) && checkIfLoggedIn(username))
    {
        std::cout << "Please, choose between the following heroes:" << std::endl;
        commandPrintMarketInformation();

        std::cout << "Please, enter hero's name" << std::endl;
        MyString heroName;
        std::cin >> heroName;

        system->sellHeroToAPlayer(heroName, username);
        std::cout << "Hero successfully bought!" << std::endl;
    }
    else
    {
        throw std::exception("Error! Only for players!");
    }
}
void Interface::commandAttackAnotherPlayer()
{
    std::cout << "Please, enter your username first:";
    MyString username;
    std::cin >> username;

    if (isAPlayer(username) && checkIfLoggedIn(username))
    {
        commandPrintPlayersRanking();
        std::cout << "Please, enter the name of the player you want to attack:";
        MyString playerName;
        std::cin >> playerName;

        std::cout << "Please, enter the name of the hero you want to attack with:";
        MyString heroName;
        std::cin >> heroName;

        std::cout << "Please, type 1 if you'd wish to initiate a battle with a random hero of the attacked player, and 2 if you want a particular one:" << std::endl;
        unsigned number;
        std::cin >> number;
        if (number == 1)
        {
            std::cout << "Please, enter the name of the hero you intend to attack:" << std::endl;
            MyString attackedHeroName;
            std::cin >> attackedHeroName;
            system->attackAnotherPlayer(username, playerName, heroName, attackedHeroName);
        }
        else
        {
            system->attackRandomHero(username, playerName, heroName);
        }
    }
    else
    {
        throw std::exception("Error! Only for players!");
    }
}
Superhero Interface::enterHeroesData() const
{
    Superhero hero;
    std::cout << "Enter hero's name:" << std::endl;
    MyString name;
    std::cin >> name;
    hero.setName(name);

    std::cout << "Enter hero's surname:" << std::endl;
    MyString surname;
    std::cin >> surname;
    hero.setSurname(surname);

    std::cout << "Enter hero's nickname:" << std::endl;
    MyString nickname;
    std::cin >> nickname;
    hero.setNickname(nickname);

    std::cout << "Enter hero's powertype ('fire', 'water' or 'earth':" << std::endl;
    char powerStr[MAX_POWER_STR];
    std::cin >> powerStr;
    hero.setPower(powerStr);

    std::cout << "Enter hero's powerSize (1-10):" << std::endl;
    size_t powerSize;
    std::cin >> powerSize;
    hero.setPowerSize(powerSize);

    std::cout << "Enter hero's price (1-50):" << std::endl;
    unsigned int price;
    std::cin >> price;
    hero.setPrice(price);

    return hero;
}
void Interface::commandPrintPlayersGeneralInformation() const
{
    std::cout << "Please, enter your username" << std::endl;
    MyString username;
    std::cin >> username;

    if (checkIfLoggedIn(username))
    {
        system->printPlayers();
    }
}

void Interface::commandPrintPlayersDetailedInformation() const
{
    std::cout << "Please, enter your username" << std::endl;
    MyString username;
    std::cin >> username;

    if (isAnAdministrator(username) && checkIfLoggedIn(username))
    {
        system->printDetailedInfo();
    }
}
void Interface::commandPrintPlayersRanking() 
{
    std::cout << "Please, enter your username" << std::endl;
    MyString username;
    std::cin >> username;

    system->getRankingPrinted(username);
}
void Interface::commandPrintPlayerSavedProgress() const
{
    std::cout << "Please, enter your username" << std::endl;
    MyString username;
    std::cin >> username;
   
    std::cout << "Please, enter a valid player's name:" << std::endl;
    MyString playerName;
    std::cin >> playerName;      
    system->printPlayerSavedProgress(username, playerName);    
}
void Interface::commandPrintMarketInformation() const
{
    std::cout << "Please, enter your username" << std::endl;
    MyString username;
    std::cin >> username;

    system->printMarket(username);
}

void  Interface::commandDeleteYourProfile()
{
    std::cout << "Note: only a player can delete their own profile!" << std::endl;
    std::cout << "Please, enter your username" << std::endl;
    MyString username;
    std::cin >> username;
   
    if (!checkIfLoggedIn(username))
    {
        throw std::exception("Error! You must first log in!");
    }
    system->deletePlayer(username);
     std::cout << "Your profile has been deleted successfully." << std::endl;
}

void Interface::commandDeleteAPlayer()
{
    std::cout << "Note: only an administrator can delete another player's profile!" << std::endl;
    std::cout << "Please, enter your username" << std::endl;
    MyString username;
    std::cin >> username;

    if (isAnAdministrator(username) && checkIfLoggedIn(username))
    {
        std::cout << "Please, enter the name of the player you want to delete:" << std::endl;
        MyString playerName;
        std::cin >> playerName;
        system->deletePlayer(playerName);
        std::cout << playerName << " 's profile has been deleted successfully." << std::endl;
    }
}

void Interface::commandChangeHeroesMode()
{
    std::cout << "Note: only a player can delete their own profile!" << std::endl;
    std::cout << "Please, enter your username" << std::endl;
    MyString username;
    std::cin >> username;
   
        std::cout << "Please, enter hero's nickname: " << std::endl;
        MyString heroName;
        std::cin >> heroName;

        std::cout << "Please, enter 1 to set your hero in an attack mode, and 2- for a defense mode:" << std::endl;
        unsigned number;
        std::cin >> number;
        if (number == 1)
        {
            system->changeHeroMode(username, heroName, Mode::attack);
        }
        else if (number == 2)
        {
            system->changeHeroMode(username, heroName, Mode::defense);
        }
        else
        {
            throw std::exception("Error! Invalid data!");
        }    
}

void Interface::commandBonusImproveHero()
{
    std::cout << "Please, enter your username" << std::endl;
    MyString username;
    std::cin >> username;  
       
    std::cout << "Please, enter the nickname of the hero you'd wish to upgrade: " << std::endl;
    MyString heroName;
    std::cin >> heroName;

    std::cout << "Note: to improve your hero, you have to pay a quater of your money" << std::endl;
    system->improveHero(username, heroName);   
}



void Interface::printOpeningMessage() const
{
    clearConsole();
    std::cout << "Welcome to Superheroes' game!" << std::endl;
    std::cout << std::endl;
    std::cout << "Please, choose an operation from the following ones in order to start the game:" << std::endl;

    std::cout << "1) Sign up (if you do not have an account already)." << std::endl;
    std::cout << "2) Log in." << std::endl;
    std::cout << "3) Log out." << std::endl;
    std::cout << "4) Add a new user (only for administrators)." << std::endl;
    std::cout << "5) Add a new hero to the marketplace (only for administrators)." << std::endl;
    std::cout << "6) Add an already bought hero to the marketplace." << std::endl;
    std::cout << "7) Buy a new hero from the marketplace (only for players)." << std::endl;
    std::cout << "8) Attack another player (only for players)." << std::endl;
    std::cout << "9) Delete your own account (only for players)." << std::endl;
    std::cout << "10) Delete a player (only for administrators)." << std::endl;
    std::cout << "11) Change a hero's mode (only for players)." << std::endl;
    std::cout << "12) Improve your hero (only for players)." << std::endl;
    std::cout << "13) See all players' general information." << std::endl;
    std::cout << "14) See players' personal infromation (can be accessed only by administrators)." << std::endl;
    std::cout << "15) See players' score up to now." << std::endl;
    std::cout << "16) Print a particular user's information by name." << std::endl;
    std::cout << "17) Print superheroes marketplace's information." << std::endl;
    std::cout << "18) Print a player's progress." << std::endl;
}

bool Interface::validCommand(int commandNumber) const
{
    return (commandNumber >= 1 && commandNumber <= 18);
}

void Interface::getUsersInput()
{
    int command;
    printOpeningMessage();
    do
    {
        std::cin >> command;
        if (!validCommand(command))
        {
            std::cout << "Invalid input! Please, enter a valid number of a command.";
        }
    } while (!validCommand(command));

    switch (command)
    {
    case 1: signUp(); break;
    case 2: logIn(); break;
    case 3: logOut(); break;
    case 4: commandAddNewUser(); break;
    case 5:  commandAddNewHero(); break;
    case 6:  commandAddBoughtHero(); break;
    case 7:  commandSellHeroToAPlayer(); break;
    case 8: commandAttackAnotherPlayer(); break;
    case 9: commandDeleteYourProfile(); break;
    case 10:  commandDeleteAPlayer(); break;
    case 11:  commandChangeHeroesMode(); break;
    case 12:  commandBonusImproveHero(); break;
    case 13: commandPrintPlayersGeneralInformation(); break;
    case 14: commandPrintPlayersDetailedInformation(); break;
    case 15: commandPrintPlayersRanking(); break;
    case 16: commandPrintUserInfoByName(); break;
    case 17: commandPrintMarketInformation(); break;
    case 18: commandPrintPlayerSavedProgress(); break;
    }
}
void Interface::programExecution()
{   
    do
    {
        getUsersInput();       
        
    } while (1);
}

void Interface::clearConsole() const
{
    std::cout << "\033[;H"; // Moves cursor to the top left
    std::cout << "\033[J"; // Clears the console
}

bool Interface::checkIfLoggedIn(const MyString& userName) const
{
    return system->checkIfLoggedIn(userName);
}
bool Interface::isAPlayer(const MyString& userName) const
{
    return system->isAPlayer(userName);
}
bool Interface::isAnAdministrator(const MyString& userName) const
{
    return system->isAnAdministrator(userName);
}

void Interface::commandPrintUserInfoByName() const
{
    std::cout << "Please, enter your username" << std::endl;
    MyString username;
    std::cin >> username;

    if (checkIfLoggedIn(username))
    {
        std::cout << "Please, enter the name of the user whose information you wish to access:" << std::endl;
        MyString otherName;
        std::cin >> otherName;

        system->printUserInfo(otherName);
    }
}