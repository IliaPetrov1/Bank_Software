#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <regex>
#include <sstream>

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

	ShowUsersInfo(Users);
	AddAllUsersFile(Users, fileName);

	file.close();
	return 0;
}
