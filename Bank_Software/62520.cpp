#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <regex>
#include <sstream>
#include <cstdlib>

using namespace std;

//Class User with its functions get/set for username/password
class User
{
public:
	void set_username(string text);
	string get_username(void);

	void set_password(string text);
	string get_password(void);

private:
	string username;
	string password;
};
void User::set_username(string text)
{
	username = text;
}
string User::get_username(void)
{
	return username;
}
void User::set_password(string text)
{
	password = text;
}
string User::get_password(void)
{
	return password;
}

//Add and delete user info to vector Users or to map UsernamesAndSums
void CreateUser(vector<User>& Users, string username, string password)
{
	User newUser;
	newUser.set_username(username);
	newUser.set_password(password);
	Users.push_back(newUser);
}
void DeleteUser(vector<User>& Users, string username, string password)
{
	User newUser;
	newUser.set_username(username);
	newUser.set_password(password);

	int indexUser = 0;
	for (int i = 0; i < Users.size(); i++)
	{
		if (Users[i].get_username() == newUser.get_username())
		{
			indexUser = i;
			break;
		}
	}

	Users.erase(Users.begin() + indexUser);
}

//Extracting usernames and passwords with regexs
string GetUsernameRegex(string userInfo)
{
	smatch match;
	const string REG_STRING = "(?=username:).+(?=_password:)";
	regex reg(REG_STRING);
	regex_search(userInfo, match, reg);

	string username = match.str().substr(9, match.size() - 9);
	return username;
}
string GetPasswordRegex(string userInfo)
{
	smatch match;
	const string REG_STRING = "(?=_password:).+";
	regex reg(REG_STRING);
	regex_search(userInfo, match, reg);

	string password = match.str().substr(10, match.size() - 10);

	return password;
}

//Functions for getting information and writing in .txt files
void ReadFileUsernamesPasswords(vector<User>& Users, string fileName)
{
	ifstream file(fileName);

	if (file.is_open())
	{
		string infoLine;

		while (getline(file, infoLine))
		{
			string userUsername = GetUsernameRegex(infoLine);
			string userPassword = GetPasswordRegex(infoLine);
			CreateUser(Users, userUsername, userPassword);
		}
	}
	else
	{
		cout << "Error with open of file " + fileName + "! (function ReadFileUsernamesPasswords)";
	}

	file.close();
}
void AddUserFileUsernamesPasswords(User user, string fileName)
{
	ofstream file(fileName, ios::app);

	if (file.is_open())
	{
		string username = user.get_username();
		string password = user.get_password();
		file << "username:" + username + "_password:" + password << endl;
	}
	else
	{
		cout << "Error with open of file " + fileName + "! (function AddUserFileUsernamesPasswords)";
	}

	file.close();
}
void AddUserFileUsernamesFinance(string username, string fileName)
{
	ofstream file(fileName, ios::app);

	if (file.is_open())
	{
		file << username + " 0" << endl;
	}
	else
	{
		cout << "Error with open of file " + fileName + "! (function AddUserFileUsernamesFinance)";
	}

	file.close();
}

//Showing username and password of all users(debug)
void ShowUsersUsernamePassword(vector<User> Users)
{
	for (auto user : Users)
	{
		cout << user.get_username() << " " << user.get_password() << endl;
	}
}

//Start Menu
bool IsThisAccInUsers(vector<User> Users, string username)
{
	bool answ = false;

	for (int i = 0; i < Users.size(); i++)
	{
		if (Users[i].get_username() == username)
		{
			answ = true;
			break;
		}
	}

	return answ;
}
void LogIn(vector<User> Users, string& clientUsername, string& clientPassword)
{
	string username = "";
	string password = "";
	cout << "Enter your username: ";
	cin >> username;
	cout << "Enter your password: ";
	cin >> password;
	cout << endl;

	User thisUser;
	for (int i = 0; i < Users.size(); i++)
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
			cout << endl;
		}
		else if (IsThisAccInUsers(Users, username) == true && thisUser.get_password() != password)
		{
			cout << "Wrong password. Try again!" << endl;
			cout << "Enter your username: ";
			cin >> username;
			cout << "Enter your password: ";
			cin >> password;
			cout << endl;
		}
	}

	clientUsername = username;
	clientPassword = password;

	system("cls");
	cout << "You have successfully logged in!" << endl;
	cout << endl;
}
void Register(vector<User> Users, string& clientUsername, string& clientPassword, string fileNameUsernamesPasswords)
{
	string username = "";
	string password = "";

	cout << "Enter your username: ";
	cin >> username;
	cout << "Enter your password: ";
	cin >> password;
	cout << endl;

	User thisUser;

	while (IsThisAccInUsers(Users, username) == true)
	{
		cout << "Someone else has already used this username, try again." << endl;
		cout << "Enter your username: ";
		cin >> username;
		cout << "Enter your password: ";
		cin >> password;
		cout << endl;
	}

	clientUsername = username;
	clientPassword = password;

	thisUser.set_username(clientUsername);
	thisUser.set_password(clientPassword);

	AddUserFileUsernamesPasswords(thisUser, fileNameUsernamesPasswords);
	CreateUser(Users, thisUser.get_username(), thisUser.get_password());

	system("cls");
	cout << "You have successfully registered!" << endl;
	cout << endl;
}
void Quit(vector<User> Users, string fileName)
{
	system("cls");
	cout << "We at FMI Bank know you had many options to choose from, we thank you for choosing us!" << endl;
	exit(EXIT_FAILURE);
}
void StartMenu(vector<User> Users, string& clientUsername, string& clientPassword, string fileNameUsernamesPasswords)
{
	system("cls");

	cout << "Hello to FMI Bank!" << endl;
	cout << endl;
	cout << "Select one of 3 options:" << endl;
	cout << "L - log in" << endl;
	cout << "R - register" << endl;
	cout << "Q - quit" << endl;
	cout << "Type here: ";

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
		LogIn(Users, clientUsername, clientPassword);
	}
	else if (clientOption == "R")
	{
		Register(Users, clientUsername, clientPassword, fileNameUsernamesPasswords);
	}
	else if (clientOption == "Q")
	{
		Quit(Users, fileNameUsernamesPasswords);
	}
}

//UserMenu

int main()
{
	vector<User> Users;
	map<string, double> UsernamesAndFinance;

	string fileInfo;
	string fileNameUsernamesPasswords = "users.txt";
	string fileNameUsernamesFinance = "users_finance.txt";

	ReadFileUsernamesPasswords(Users, fileNameUsernamesPasswords);

	string clientUsername = "";
	string clientPassword = "";
	StartMenu(Users, clientUsername, clientPassword, fileNameUsernamesPasswords);
	

	return 0;
}
