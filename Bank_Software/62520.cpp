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

//Getting username and password from .txt info
string GetUsernameTxtInfo(string userInfo)
{
	smatch match;
	const string REG_STRING = "(?=username:).+(?=_password:)";
	regex reg(REG_STRING);
	regex_search(userInfo,match,reg);

	string username = match.str().substr(9, match.str().size()-9);

	return username;
}

string GetPasswordTxtInfo(string userInfo)
{
	smatch match;
	const string REG_STRING = "(?=_password:).+";
	regex reg(REG_STRING);
	regex_search(userInfo, match, reg);

	string password = match.str().substr(10, match.str().size() - 9);

	return password;
}

int main()
{
	vector<string> Users;

	string txtInfo;
	ifstream txtFile("users.txt");
	if (txtFile.is_open())
	{
		while (getline(txtFile, txtInfo))
		{
			cout << GetUsernameTxtInfo(txtInfo) << endl;
			cout << GetPasswordTxtInfo(txtInfo) << endl;
		}
	}
	else
	{
		cout << "File doesn't open." << endl;
	}

	txtFile.close();

	return 0;
}
