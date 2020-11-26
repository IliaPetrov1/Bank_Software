#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <regex>
#include <cmath>

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

//Create a user
void CreateUser(vector<User> &Users, string username, string password)
{
	User newUser;
	newUser.set_username(username);
	newUser.set_password(password);
	Users.push_back(newUser);
}
//Getting username and password from .txt info
string GetUsernameTxtInfo(string userInfo)
{
	smatch match;
	const string REG_STRING = "(?=username:).+(?=_password:)";
	regex reg(REG_STRING);
	regex_search(userInfo,match,reg);

	string username = match.str().substr(9, match.str().size() - 9);
	return username;
}
string GetPasswordTxtInfo(string userInfo)
{
	smatch match;
	const string REG_STRING = "(?=_password:).+";
	regex reg(REG_STRING);
	regex_search(userInfo, match, reg);

	string password = match.str().substr(10, match.str().size() - 10);

	string password = match.str();
	return password;
}
//Add username and password to .txt file
void AddUserToTxtFile(User user, string txtFileName)
{
	fstream txtFile(txtFileName);
	if (txtFile.is_open())
	{
		txtFile << "username:" + user.get_username() + "_password:" + user.get_password() << endl;
	}
	txtFile.close();
}
//Showing username and password of all users(debug)
void ShowUsersInfo(vector<User> Users)
{
	for (auto user : Users)
	{
		cout << user.get_username() << " " << user.get_password() << endl;
	}
}

int main()
{
	vector<User> Users;

	string txtInfo;
	string txtName = "users.txt";
	fstream txtFile(txtName);
	if (txtFile.is_open())
	{
		while (getline(txtFile, txtInfo))
		{
			CreateUser(Users, GetUsernameTxtInfo(txtInfo), GetPasswordTxtInfo(txtInfo));
		}
	}
	else
	{
		cout << "File doesn't open." << endl;
	}

	ShowUsersInfo(Users);
	txtFile.close();
	return 0;
}
