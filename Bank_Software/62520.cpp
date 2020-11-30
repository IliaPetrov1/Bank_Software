#include <iostream>
#include <string>
#include <vector>
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
//Convert to Hex
string ToHex(unsigned int input)
{
	string hexHashedString;

	stringstream hexStream;
	hexStream << hex << input;
	hexHashedString = hexStream.str();
	transform(hexHashedString.begin(), hexHashedString.end(), hexHashedString.begin(), ::toupper);

	return hexHashedString;
}
//Hashing password
string ToHash(string input)
{
	string hasedPassword;
	unsigned int specNumber = 421312;
	unsigned int hash = 0;

	for (int i = 0; i < input.size(); i++)
	{
		hash = hash ^ (input[i]);
		hash = hash * specNumber;
	}
	hasedPassword = ToHex(hash);

	return hasedPassword;
}
//Create a user
void CreateUser(vector<User>& Users, string username, string password)
{
	User newUser;
	newUser.set_username(username);
	newUser.set_password(password);
	Users.push_back(newUser);
}
//Getting username and password from fileInfo
string GetUsernameFile(string userInfo)
{
	smatch match;
	const string REG_STRING = "(?=username:).+(?=_password:)";
	regex reg(REG_STRING);
	regex_search(userInfo, match, reg);

	string username = match.str().substr(9, match.size() - 9);
	return username;
}
string GetPasswordFile(string userInfo)
{
	smatch match;
	const string REG_STRING = "(?=_password:).+";
	regex reg(REG_STRING);
	regex_search(userInfo, match, reg);

	string password = match.str().substr(10, match.size() - 10);

	return password;
}
//Is username valid
bool IsUsernameValid(string userInfo)
{
	bool answ = true;
	return answ;
}
//Is password valid
bool IsPasswordValid(string userInfo)
{
	bool answ = true;
	return answ;
}
//Add username and password to file
void AddUserFile(User user, string fileName)
{
	fstream file(fileName);
	if (file.is_open())
	{
		file << "username:" + user.get_username() + "_password:" + user.get_password() << endl;
	}
}
//Add all usernames and passwords to file
void AddAllUsersFile(vector<User> Users, string fileName)
{
	fstream file(fileName);
	if (file.is_open())
	{
		if (file.is_open())
		{
			for (int i = 0; i < Users.size(); i++)
			{
				file << "username:" + Users[i].get_username() + "_password:" + Users[i].get_password() << endl;
			}
		}
	}
}
//Showing username and password of all users(debug)
void ShowUsersInfo(vector<User> Users)
{
	for (auto user : Users)
	{
		cout << user.get_username() << " " << user.get_password() << endl;
	}
}

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
void LogIn(vector<User> Users, string &clientUsername, string &clientPassword)
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
		if (IsThisAccInUsers(Users, username) == false && thisUser.get_password() == password)
		{
			cout << "There is no such user with this username. Try again!" << endl;
			cout << "Enter your username: ";
			//getline(cin, username);
			cin >> username;
			cout << "Enter your password: ";
			//getline(cin, password);
			cin >> password;
		}
		else if (IsThisAccInUsers(Users, username) == true && thisUser.get_password() != password)
		{
			cout << "Wrong password. Try again!" << endl;
			cout << "Enter your username: ";
			//getline(cin, username);
			cin >> username;
			cout << "Enter your password: ";
			//getline(cin, password);
			cin >> password;
		}
	}

	clientUsername = username;
	clientPassword = password;

	system("cls");
	cout << "You have successfully logged in!" << endl;
	cout << endl;
}
void Register(vector<User> Users, string& clientUsername, string& clientPassword)
{
	string username = "";
	string password = "";

	cout << "Enter your username: ";
	cin >> username;
	cout << "Enter your password: ";
	cin >> password;
	cout << endl;

	while (IsThisAccInUsers(Users, username) == true)
	{
		cout << "Someone else has already used this username, try again." << endl;
		cout << "Enter your username: ";
		//getline(cin, username);
		cin >> username;
		cout << "Enter your password: ";
		//getline(cin, password);
		cin >> password;
	}

	clientUsername = username;
	clientPassword = password;

	system("cls");
	cout << "You have successfully registered!" << endl;
	cout << endl;
}
void Quit(vector<User> Users, string fileName)
{
	AddAllUsersFile(Users, fileName);
	system("cls");
	cout << "We at FMI Bank know you had many options to choose from, we thank you for choosing us!" << endl;
	exit(EXIT_FAILURE);
}
void StartMenu(vector<User> Users, string &clientUsername, string &clientPassword, string fileName)
{
	system("cls");

	cout << "Hello to FMI Bank!" << endl;
	cout << endl;
	cout << "Select one of 3 options:" << endl;
	cout << "-type L to log in in your account" << endl;
	cout << "-type R to register in our bank" << endl;
	cout << "-type Q to quit" << endl;
	cout << "Type here: ";
	cout << endl;

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
		Register(Users, clientUsername, clientPassword);
	}
	else if (clientOption == "Q")
	{
		Quit(Users, fileName);
	}
}

int main()
{
	vector<User> Users;

	string fileInfo;
	string fileName = "users.txt";
	fstream file(fileName);

	//Get info from file
	if (file.is_open())
	{
		while (getline(file, fileInfo))
		{
			CreateUser(Users, GetUsernameFile(fileInfo), GetPasswordFile(fileInfo));
		}
	}
	else
	{
		cout << "File doesn't open." << endl;
	}

	string clientUsername = "";
	string clientPassword = "";

	StartMenu(Users, clientUsername, clientPassword, fileName);

	file.close();
	return 0;
}
