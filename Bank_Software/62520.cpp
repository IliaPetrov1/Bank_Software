#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <regex>

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

//Debug Tools
//Showing username, password and finance of all users
void ShowUsersUsernamePassword(vector<User> Users)
{
	for (auto user : Users)
	{
		cout << user.get_username() << " " << user.get_password() << endl;
	}
}
void ShowUsersUsernameFinance(map<string, double> UsernamesAndFinance)
{
	for (auto user : UsernamesAndFinance)
	{
		cout << user.first << " " << user.second << endl;
	}
}

//Add and delete user info 
void CreateUser(vector<User> &Users, string username, string password)
{
	User newUser;
	newUser.set_username(username);
	newUser.set_password(password);
	Users.push_back(newUser);
}
void DeleteUser(vector<User> &Users, string username, string password)
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
void CreateBankFinance(map<string, double> &UsernamesAndFinance, string username, double finance)
{
	UsernamesAndFinance.insert(pair<string, double>(username, finance));
}
void DeleteBankFinance(map<string, double> &UsernamesAndFinance, string username)
{
	map<string, double>::iterator element;
	element = UsernamesAndFinance.find(username);
	UsernamesAndFinance.erase(element);
}

//Extracting usernames, passwords and finance with regexs
string GetUsernameRegexFileUsernamesPasswords(string userInfo)
{
	smatch match;
	const string REG_STRING = "(?=username:).+(?=_password:)";
	regex reg(REG_STRING);
	regex_search(userInfo, match, reg);

	string username = match.str().substr(9, match.size() - 9);
	return username;
}
string GetPasswordRegexFileUsernamesPasswords(string userInfo)
{
	smatch match;
	const string REG_STRING = "(?=_password:).+";
	regex reg(REG_STRING);
	regex_search(userInfo, match, reg);

	string password = match.str().substr(10, match.size() - 10);

	return password;
}
string GetUsernameRegexFileUsernamesFinance(string userInfo)
{
	smatch match;
	const string REG_STRING = "(?=username:).+(?=_finance:)";
	regex reg(REG_STRING);
	regex_search(userInfo, match, reg);

	string username = match.str().substr(9, match.size() - 9);
	return username;
}
double GetFinanceRegexFileUsernamesFinance(string userInfo)
{
	smatch match;
	const string REG_STRING = "(?=_finance:).+";
	regex reg(REG_STRING);
	regex_search(userInfo, match, reg);

	string financeStr = match.str().substr(9, match.size() - 10);
	double finance = stod(financeStr);

	return finance;
}

//Functions for getting information and writing in .txt files
void ReadFileUsernamesPasswords(vector<User> &Users, string fileName)
{
	ifstream file(fileName);
	if (file.is_open())
	{
		Users.clear();
		string infoLine;

		while (getline(file, infoLine))
		{
			string userUsername = GetUsernameRegexFileUsernamesPasswords(infoLine);
			string userPassword = GetPasswordRegexFileUsernamesPasswords(infoLine);
			CreateUser(Users, userUsername, userPassword);
		}
	}
	else
	{
		cout << "Error with open of file " + fileName + "! (function ReadFileUsernamesPasswords)";
	}

	file.close();
}
void ReadFileUsernamesFinance(map<string, double> &UsernamesAndFinance, string fileName)
{
	ifstream file(fileName);
	if (file.is_open())
	{
		UsernamesAndFinance.clear();
		string infoLine;

		while (getline(file, infoLine))
		{
			string userUsername = GetUsernameRegexFileUsernamesFinance(infoLine);
			double userFinance = GetFinanceRegexFileUsernamesFinance(infoLine);
			CreateBankFinance(UsernamesAndFinance, userUsername, userFinance);
		}
	}
	else
	{
		cout << "Error with open of file " + fileName + "! (function ReadFileUsernamesPasswords)";
	}

	file.close();
}
void AddUserFileUsernamesPasswords(string username, string password, string fileName)
{
	ofstream file(fileName, ios::app);

	if (file.is_open())
	{
		file << "username:" + username + "_password:" + password << endl;
	}
	else
	{
		cout << "Error with open of file " + fileName + "! (function AddUserFileUsernamesPasswords)";
	}

	file.close();
}
void AddUserFileUsernamesFinance(string username, double finance, string fileName)
{
	ofstream file(fileName, ios::app);

	if (file.is_open())
	{
		file << "username:" + username + "_finance:" << finance << endl;
	}
	else
	{
		cout << "Error with open of file " + fileName + "! (function AddUserFileUsernamesFinance)";
	}

	file.close();
}
void AddAllUserFileUsernamesPasswords(vector<User> Users, string fileName)
{
	ofstream file(fileName, ios::trunc);

	if (file.is_open())
	{
		for (auto user : Users)
		{
			file << "username:" + user.get_username() + "_password:" + user.get_password() << endl;
		}
		
	}
	else
	{
		cout << "Error with open of file " + fileName + "! (function AddAllUserFileUsernamesPasswords)";
	}

	file.close();
}
void AddAllUserFileUsernamesFinance(map<string, double> UsernamesAndFinance, string fileName)
{
	ofstream file(fileName, ios::trunc);

	if (file.is_open())
	{
		for (auto user : UsernamesAndFinance)
		{
			file << "username:" + user.first + "_finance:" << user.second << endl;
		}
	}
	else
	{
		cout << "Error with open of file " + fileName + "! (function AddAllUserFileUsernamesPasswords)";
	}

	file.close();
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
void LogIn(vector<User> Users, map<string, double>& UsernamesAndFinance, string &clientUsername, string &clientPassword, double &clientFinance)
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
	clientFinance = UsernamesAndFinance[clientUsername];

	//system("cls");
	cout << "You have successfully logged in!" << endl;
}
void Register(vector<User> Users, map<string, double>& UsernamesAndFinance, string &clientUsername, string &clientPassword, double& clientFinance, string fileNameUsernamesPasswords, string fileNameUsernamesFinance)
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
	clientFinance = 0;

	thisUser.set_username(clientUsername);
	thisUser.set_password(clientPassword);

	AddUserFileUsernamesPasswords(clientUsername, clientPassword, fileNameUsernamesPasswords);
	AddUserFileUsernamesFinance(clientUsername, clientFinance, fileNameUsernamesFinance);

	//system("cls");
	cout << "You have successfully registered!" << endl;
}
void Quit(vector<User> Users, string fileName)
{
	system("cls");
	cout << "We at FMI Bank know you had many options to choose from, we thank you for choosing us!" << endl;
	exit(EXIT_FAILURE);
}
void StartMenu(vector<User> Users, map<string, double>& UsernamesAndFinance, string &clientUsername, string &clientPassword, double &clientFinance,string fileNameUsernamesPasswords, string fileNameUsernamesFinance)
{
	//system("cls");

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
		LogIn(Users, UsernamesAndFinance, clientUsername, clientPassword, clientFinance);
	}
	else if (clientOption == "R")
	{
		Register(Users, UsernamesAndFinance, clientUsername, clientPassword, clientFinance, fileNameUsernamesPasswords, fileNameUsernamesFinance);
	}
	else if (clientOption == "Q")
	{
		Quit(Users, fileNameUsernamesPasswords);
	}
}

//UserMenu
void CancelAcc(vector<User> Users, map<string, double>& UsernamesAndFinance, string& clientUsername, string& clientPassword, double& clientFinance, string fileNameUsernamesPasswords, string fileNameUsernamesFinance)
{
	cout << "Enter password: ";
	string password;
	cin >> password;

	if (password != clientPassword)
	{
		while (password != clientPassword)
		{
			cout << "You entered wrong password, try again: ";
			cin >> password;
		}
	}

	DeleteUser(Users, clientUsername, clientPassword);
	DeleteBankFinance(UsernamesAndFinance, clientUsername);

	AddAllUserFileUsernamesPasswords(Users, fileNameUsernamesPasswords);
	AddAllUserFileUsernamesFinance(UsernamesAndFinance, fileNameUsernamesFinance);

	StartMenu(Users, UsernamesAndFinance, clientUsername, clientPassword, clientFinance, fileNameUsernamesPasswords, fileNameUsernamesFinance);
}
void Deposit()
{

}
void Logout()
{

}
void Transfer()
{

}
void Withdraw()
{

}
void UserMenu(vector<User> Users, map<string, double> UsernamesAndFinance, string& clientUsername, string& clientPassword, double& clientFinance, string fileNameUsernamesPasswords, string fileNameUsernamesFinance)
{
	//system("cls");
	ReadFileUsernamesPasswords(Users, fileNameUsernamesPasswords);
	ReadFileUsernamesFinance(UsernamesAndFinance, fileNameUsernamesFinance);

	cout << "You have " + to_string(UsernamesAndFinance[clientUsername]) + "BGN. Choose one of the following options:" << endl;
	cout << "C - cancel account" << endl;
	cout << "D - deposit" << endl;
	cout << "L - logout" << endl;
	cout << "T - transfer" << endl;
	cout << "W - withdraw" << endl;

	string clientOption;
	cout << "Type here: ";
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
		CancelAcc(Users, UsernamesAndFinance, clientUsername, clientPassword, clientFinance, fileNameUsernamesPasswords, fileNameUsernamesFinance);
	}
	else if (clientOption == "D")
	{
		Deposit();
	}
	else if (clientOption == "L")
	{
		Logout();
	}
	else if (clientOption == "T")
	{
		Transfer();
	}
	else if (clientOption == "W")
	{
		Withdraw();
	}

	AddAllUserFileUsernamesPasswords(Users, fileNameUsernamesPasswords);
	AddAllUserFileUsernamesFinance(UsernamesAndFinance, fileNameUsernamesFinance);
}

int main()
{
	vector<User> Users;
	map<string, double> UsernamesAndFinance;

	string fileInfo;
	string const fileNameUsernamesPasswords = "users.txt";
	string const fileNameUsernamesFinance = "users_finance.txt";

	ReadFileUsernamesPasswords(Users, fileNameUsernamesPasswords);
	ReadFileUsernamesFinance(UsernamesAndFinance, fileNameUsernamesFinance);

	string clientUsername = "";
	string clientPassword = "";
	double clientFinance = 0;

	StartMenu(Users, UsernamesAndFinance, clientUsername, clientPassword, clientFinance, fileNameUsernamesPasswords, fileNameUsernamesFinance);
	UserMenu(Users, UsernamesAndFinance, clientUsername, clientPassword, clientFinance, fileNameUsernamesPasswords, fileNameUsernamesFinance);

	return 0;
}