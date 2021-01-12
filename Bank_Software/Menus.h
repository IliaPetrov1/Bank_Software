/**
*
* Solution to course project # 3
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2020/2021
*
* @author Ilia Petrov
* @idnumber 62520
* @compiler VC
*
* <file with helper function>
*
*/

#include <vector>
#include <map>
#include <string>
#include <iomanip>
#include "User.h"

using namespace std;

bool IsThisAccInUsers(vector<User> &Users, string username);
void LogIn(vector<User> &Users, map<string, double>& UsernamesAndFinance, string& clientUsername, string& clientPassword, double& clientFinance);
void Register(vector<User>& Users, map<string, double>& UsernamesAndFinance, string& clientUsername, string& clientPassword, double& clientFinance, string fileNameUsernamesPasswords, string fileNameUsernamesFinance);
void Quit(vector<User>& Users, map<string, double>& UsernamesAndFinance, string& clientUsername, string& clientPassword, double& clientFinance, string& fileNameUsernamesPasswords, string& fileNameUsernamesFinance);
void OptionsStartMenu(vector<User>& Users, map<string, double>& UsernamesAndFinance, string& clientUsername, string& clientPassword, double& clientFinance, string fileNameUsernamesPasswords, string fileNameUsernamesFinance);
void StartMenu(vector<User>& Users, map<string, double>& UsernamesAndFinance, string& clientUsername, string& clientPassword, double& clientFinance, string fileNameUsernamesPasswords, string fileNameUsernamesFinance);
void RemoveDigitsAfterSecondSymAfterComma(double& money);
bool CancelAcc(vector<User>& Users, map<string, double>& UsernamesAndFinance, string& clientUsername, string& clientPassword, double& clientFinance, string fileNameUsernamesPasswords, string fileNameUsernamesFinance);
void Deposit(map<string, double>& UsernamesAndFinance, string& clientUsername, double& clientFinance, string fileNameUsernamesFinance);
void Logout(vector<User>& Users, map<string, double>& UsernamesAndFinance, string& clientUsername, string& clientPassword, double& clientFinance, string fileNameUsernamesPasswords, string fileNameUsernamesFinance);
void Transfer(vector<User>& Users, map<string, double>& UsernamesAndFinance, string& clientUsername, double& clientFinance, string fileNameUsernamesFinance);
void Withdraw(map<string, double>& UsernamesAndFinance, string& clientUsername, double& clientFinance, string fileNameUsernamesFinance);
void OptionsUserMenu(vector<User>& Users, map<string, double>& UsernamesAndFinance, string& clientUsername, string& clientPassword, double& clientFinance, string fileNameUsernamesPasswords, string fileNameUsernamesFinance);
void UserMenu(vector<User>& Users, map<string, double>& UsernamesAndFinance, string& clientUsername, string& clientPassword, double& clientFinance, string fileNameUsernamesPasswords, string fileNameUsernamesFinance);


//START MENU
bool IsThisAccInUsers(vector<User> &Users, string username)
{
	bool answ = false;
	int usersSize = Users.size();
	for (int i = 0; i < usersSize; i++)
	{
		if (Users[i].get_username() == username)
		{
			answ = true;
			break;
		}
	}

	return answ;
}

void LogIn(vector<User> &Users, map<string, double>& UsernamesAndFinance, string& clientUsername, string& clientPassword, double& clientFinance)
{
	string username = "";
	string password = "";
	cout << "Enter your username: ";
	cin >> username;
	cout << "Enter your password: ";
	cin >> password;
	cout << endl;

	password = ToHash(password);

	User thisUser;
	int usersSize = Users.size();
	for (int i = 0; i < usersSize; i++)
	{
		if (Users[i].get_username() == username)
		{
			thisUser = Users[i];
			break;
		}
	}


	while (IsThisAccInUsers(Users, username) == false || thisUser.get_password() != password)
	{
		if (IsThisAccInUsers(Users, username) == false)
		{
			cout << "There is no such user with this username. Try again!" << endl;
			cout << "Enter your username: ";
			cin >> username;
			cout << "Enter your password: ";
			cin >> password;
			password = ToHash(password);
			cout << endl;
		}
		else if (IsThisAccInUsers(Users, username) == true && thisUser.get_password() != password)
		{
			cout << "Wrong password. Try again!" << endl;
			cout << "Enter your username: ";
			cin >> username;
			cout << "Enter your password: ";
			cin >> password;
			password = ToHash(password);
			cout << endl;
		}
	}

	clientUsername = username;
	clientPassword = password;
	clientFinance = UsernamesAndFinance[clientUsername];
}

void Register(vector<User>& Users, map<string, double>& UsernamesAndFinance, string& clientUsername, string& clientPassword, double& clientFinance, string fileNameUsernamesPasswords, string fileNameUsernamesFinance)
{
	string username = "";
	string password = "";

	cout << "Enter your username: ";
	cin >> username;
	ValidateUsername(username);

	while (IsThisAccInUsers(Users, username) == true)
	{
		cout << "Someone else has already used this username, try again." << endl;

		cout << "Enter your username: ";
		cin >> username;
		ValidateUsername(username);
	}

	cout << "Enter your password: ";
	cin >> password;
	ValidatePassword(password);

	string confirmedPassword;
	cout << "Confirm your password: ";
	cin >> confirmedPassword;

	while (password != confirmedPassword)
	{
		cout << "Confirmation of your password is not valid, enter your password again: " << endl;
		cout << "Enter your password: ";
		cin >> password;
		ValidatePassword(password);

		cout << "Confirm your password: ";
		cin >> confirmedPassword;
	}

	clientUsername = username;
	clientPassword = password;
	clientFinance = 0;

	clientPassword = ToHash(clientPassword);

	AddUserFileUsernamesPasswords(clientUsername, clientPassword, fileNameUsernamesPasswords);
	AddUserFileUsernamesFinance(clientUsername, clientFinance, fileNameUsernamesFinance);
}

void Quit(vector<User>& Users, map<string, double>& UsernamesAndFinance, string& clientUsername, string& clientPassword, double& clientFinance, string& fileNameUsernamesPasswords, string& fileNameUsernamesFinance)
{
	cout << "We at FMI Bank know you had many options to choose from, we thank you for choosing us!" << endl;
	exit(EXIT_FAILURE);
}

void OptionsStartMenu(vector<User>& Users, map<string, double>& UsernamesAndFinance, string& clientUsername, string& clientPassword, double& clientFinance, string fileNameUsernamesPasswords, string fileNameUsernamesFinance)
{
	ReadFileUsernamesPasswords(Users, fileNameUsernamesPasswords);
	ReadFileUsernamesFinance(UsernamesAndFinance, fileNameUsernamesFinance);

	string clientOption;
	cin >> clientOption;

	if (clientOption != "L" && clientOption != "R" && clientOption != "Q")
	{
		while (clientOption != "L" && clientOption != "R" && clientOption != "Q")
		{
			cout << "Sorry, but you have entered invalid input, please try again: ";
			cin >> clientOption;
		}
	}

	if (clientOption == "L")
	{
		if (Users.size() == 0)
		{
			cout << "You cannot log in, because there is no account in database, try again: ";
			OptionsStartMenu(Users, UsernamesAndFinance, clientUsername, clientPassword, clientFinance, fileNameUsernamesPasswords, fileNameUsernamesFinance);
		}
		LogIn(Users, UsernamesAndFinance, clientUsername, clientPassword, clientFinance);
		UserMenu(Users, UsernamesAndFinance, clientUsername, clientPassword, clientFinance, fileNameUsernamesPasswords, fileNameUsernamesFinance);
	}
	else if (clientOption == "R")
	{
		Register(Users, UsernamesAndFinance, clientUsername, clientPassword, clientFinance, fileNameUsernamesPasswords, fileNameUsernamesFinance);
		UserMenu(Users, UsernamesAndFinance, clientUsername, clientPassword, clientFinance, fileNameUsernamesPasswords, fileNameUsernamesFinance);
	}
	else if (clientOption == "Q")
	{
		Quit(Users, UsernamesAndFinance, clientUsername, clientPassword, clientFinance, fileNameUsernamesPasswords, fileNameUsernamesFinance);
	}
}

void StartMenu(vector<User>& Users, map<string, double>& UsernamesAndFinance, string& clientUsername, string& clientPassword, double& clientFinance, string fileNameUsernamesPasswords, string fileNameUsernamesFinance)
{

	cout << "Hello to FMI Bank!" << endl;
	cout << endl;
	cout << "Select one of 3 options:" << endl;
	cout << "L - log in" << endl;
	cout << "R - register" << endl;
	cout << "Q - quit" << endl;
	cout << "Type here: ";

	OptionsStartMenu(Users, UsernamesAndFinance, clientUsername, clientPassword, clientFinance, fileNameUsernamesPasswords, fileNameUsernamesFinance);
}

//USER MENU
void RemoveDigitsAfterSecondSymAfterComma(double& money)
{
	string moneyStr = to_string(money);

	int indexComma = 0;
	for (char symb : moneyStr)
	{
		if (symb == '.' || symb == ',')
		{
			break;
		}
		else
		{
			indexComma++;
		}
	}

	moneyStr = moneyStr.substr(0, indexComma + 3);
	money = stod(moneyStr);
}

bool CancelAcc(vector<User> &Users, map<string, double>& UsernamesAndFinance, string& clientUsername, string& clientPassword, double& clientFinance, string fileNameUsernamesPasswords, string fileNameUsernamesFinance)
{
	bool isAccCanceled = true;
	cout << "Enter password: ";
	string password;
	cin >> password;
	password = ToHash(password);

	if (password != clientPassword)
	{
		while (password != clientPassword)
		{
			cout << "You entered wrong password, try again: ";
			cin >> password;
			password = ToHash(password);
		}
	}

	if (clientFinance > 0)
	{
		//Account has deposit and cannot be deleted
		isAccCanceled = false;
		return isAccCanceled;
	}
	else
	{
		DeleteUser(Users, clientUsername, clientPassword);
		DeleteBankFinance(UsernamesAndFinance, clientUsername);

		AddAllUserFileUsernamesPasswords(Users, fileNameUsernamesPasswords);
		AddAllUserFileUsernamesFinance(UsernamesAndFinance, fileNameUsernamesFinance);

		return isAccCanceled;
	}
}

void Deposit(map<string, double>& UsernamesAndFinance, string& clientUsername, double& clientFinance, string fileNameUsernamesFinance)
{
	cout << "How much money do you want to deposit: ";
	double deposit;

	cin >> deposit;

	while (IsNumberPositive(deposit) == false)
	{
		if (IsNumberPositive(deposit) == false)
		{
			cout << "Deposit should be positive number, try again: ";
		}

		cin >> deposit;
	}
	if (DoesNumberHasMoreThanTwoDigitsAfterComma(deposit) == false)
	{
		RemoveDigitsAfterSecondSymAfterComma(deposit);
	}

	clientFinance += deposit;

	UsernamesAndFinance[clientUsername] = clientFinance;
	AddAllUserFileUsernamesFinance(UsernamesAndFinance, fileNameUsernamesFinance);
	ReadFileUsernamesFinance(UsernamesAndFinance, fileNameUsernamesFinance);
}

void Logout(vector<User>& Users, map<string, double>& UsernamesAndFinance, string& clientUsername, string& clientPassword, double& clientFinance, string fileNameUsernamesPasswords, string fileNameUsernamesFinance)
{
	StartMenu(Users, UsernamesAndFinance, clientUsername, clientPassword, clientFinance, fileNameUsernamesPasswords, fileNameUsernamesFinance);
}

void Transfer(vector<User> &Users, map<string, double>& UsernamesAndFinance, string& clientUsername, double& clientFinance, string fileNameUsernamesFinance)
{
	double overdraft = 10000;
	cout << "How much money do you want to transfer: ";
	double transferedMoney;
	cin >> transferedMoney;
	while (IsNumberPositive(transferedMoney) == false || CanThisMoneyBeRemovedFromBankBalance(clientFinance, transferedMoney, overdraft) == false)
	{
		if (IsNumberPositive(transferedMoney) == false)
		{
			cout << "Transfered money should be positive number, try again: ";
		}
		else if (CanThisMoneyBeRemovedFromBankBalance(clientFinance, transferedMoney, overdraft) == false)
		{
			cout << "You cannot transfer, because you will go over your overdraft limit: ";
		}
		cin >> transferedMoney;
	}
	if (DoesNumberHasMoreThanTwoDigitsAfterComma(transferedMoney) == false)
	{
		RemoveDigitsAfterSecondSymAfterComma(transferedMoney);
	}
	cout << "Transfered money to (enter the username of account you want transfer to): ";
	string strangersUsername;
	cin >> strangersUsername;
	while (IsThisAccInUsers(Users, strangersUsername) == false)
	{
		cout << "You entered invalid username, try again: ";
		cin >> strangersUsername;
	}
	//Adding to stranger acc
	UsernamesAndFinance[strangersUsername] += transferedMoney;
	AddAllUserFileUsernamesFinance(UsernamesAndFinance, fileNameUsernamesFinance);
	ReadFileUsernamesFinance(UsernamesAndFinance, fileNameUsernamesFinance);
	//Removing from user acc
	clientFinance -= transferedMoney;
	UsernamesAndFinance[clientUsername] = clientFinance;
	AddAllUserFileUsernamesFinance(UsernamesAndFinance, fileNameUsernamesFinance);
	ReadFileUsernamesFinance(UsernamesAndFinance, fileNameUsernamesFinance);
}

void Withdraw(map<string, double>& UsernamesAndFinance, string& clientUsername, double& clientFinance, string fileNameUsernamesFinance)
{
	double overdraft = 10000;

	cout << "How much money do you want to withdraw: ";
	double withdrawal;

	cin >> withdrawal;

	while (IsNumberPositive(withdrawal) == false || CanThisMoneyBeRemovedFromBankBalance(clientFinance, withdrawal, overdraft) == false)
	{
		if (IsNumberPositive(withdrawal) == false)
		{
			cout << "Withdrawal should be positive number, try again: ";
		}
		else if (CanThisMoneyBeRemovedFromBankBalance(clientFinance, withdrawal, overdraft) == false)
		{
			cout << "You cannot withdraw, because you will go over your overdraft limit: " << endl;
			cout << "How much money do you want to withdraw: ";
		}

		cin >> withdrawal;
	}
	if (DoesNumberHasMoreThanTwoDigitsAfterComma(withdrawal) == false)
	{
		RemoveDigitsAfterSecondSymAfterComma(withdrawal);
	}

	clientFinance -= withdrawal;

	UsernamesAndFinance[clientUsername] = clientFinance;
	AddAllUserFileUsernamesFinance(UsernamesAndFinance, fileNameUsernamesFinance);
	ReadFileUsernamesFinance(UsernamesAndFinance, fileNameUsernamesFinance);
}

void OptionsUserMenu(vector<User>& Users, map<string, double>& UsernamesAndFinance, string& clientUsername, string& clientPassword, double& clientFinance, string fileNameUsernamesPasswords, string fileNameUsernamesFinance)
{
	ReadFileUsernamesPasswords(Users, fileNameUsernamesPasswords);
	ReadFileUsernamesFinance(UsernamesAndFinance, fileNameUsernamesFinance);

	string clientOption;
	cin >> clientOption;

	if (clientOption != "C" && clientOption != "D" && clientOption != "L" && clientOption != "T" && clientOption != "W")
	{
		while (clientOption != "C" && clientOption != "D" && clientOption != "L" && clientOption != "T" && clientOption != "W")
		{
			cout << "Sorry, but you have entered invalid input, please try again: ";
			cin >> clientOption;
		}
	}

	if (clientOption == "C")
	{
		bool isAccCanceled = CancelAcc(Users, UsernamesAndFinance, clientUsername, clientPassword, clientFinance, fileNameUsernamesPasswords, fileNameUsernamesFinance);

		if (isAccCanceled == true)
		{
			StartMenu(Users, UsernamesAndFinance, clientUsername, clientPassword, clientFinance, fileNameUsernamesPasswords, fileNameUsernamesFinance);
		}
		else
		{
			UserMenu(Users, UsernamesAndFinance, clientUsername, clientPassword, clientFinance, fileNameUsernamesPasswords, fileNameUsernamesFinance);
		}
	}
	else if (clientOption == "D")
	{
		Deposit(UsernamesAndFinance, clientUsername, clientFinance, fileNameUsernamesFinance);
		UserMenu(Users, UsernamesAndFinance, clientUsername, clientPassword, clientFinance, fileNameUsernamesPasswords, fileNameUsernamesFinance);
	}
	else if (clientOption == "L")
	{
		Logout(Users, UsernamesAndFinance, clientUsername, clientPassword, clientFinance, fileNameUsernamesPasswords, fileNameUsernamesFinance);
	}
	else if (clientOption == "T")
	{
		Transfer(Users, UsernamesAndFinance, clientUsername, clientFinance, fileNameUsernamesFinance);
		UserMenu(Users, UsernamesAndFinance, clientUsername, clientPassword, clientFinance, fileNameUsernamesPasswords, fileNameUsernamesFinance);
	}
	else if (clientOption == "W")
	{
		if (clientFinance == -10000)
		{
			//Cannot withdrow, because user will go over his overdraft limit
			UserMenu(Users, UsernamesAndFinance, clientUsername, clientPassword, clientFinance, fileNameUsernamesPasswords, fileNameUsernamesFinance);
		}
		else
		{
			Withdraw(UsernamesAndFinance, clientUsername, clientFinance, fileNameUsernamesFinance);
			UserMenu(Users, UsernamesAndFinance, clientUsername, clientPassword, clientFinance, fileNameUsernamesPasswords, fileNameUsernamesFinance);
		}
	}

	AddAllUserFileUsernamesPasswords(Users, fileNameUsernamesPasswords);
	AddAllUserFileUsernamesFinance(UsernamesAndFinance, fileNameUsernamesFinance);
}

void UserMenu(vector<User>& Users, map<string, double>& UsernamesAndFinance, string& clientUsername, string& clientPassword, double& clientFinance, string fileNameUsernamesPasswords, string fileNameUsernamesFinance)
{
	cout << "You have " << fixed << setprecision(2) << UsernamesAndFinance[clientUsername] << " BGN. Choose one of the following options:" << endl;
	cout << "C - cancel account" << endl;
	cout << "D - deposit" << endl;
	cout << "L - logout" << endl;
	cout << "T - transfer" << endl;
	cout << "W - withdraw" << endl;
	cout << "Type here: ";

	OptionsUserMenu(Users, UsernamesAndFinance, clientUsername, clientPassword, clientFinance, fileNameUsernamesPasswords, fileNameUsernamesFinance);
}