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

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "User.h"

using namespace std;

//FUNCTIONS FOR GETTING INFORMATION AND WRITING IN .TXT FILES
void ReadFileUsernamesPasswords(vector<User>& Users, string fileName)
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

void ReadFileUsernamesFinance(map<string, double>& UsernamesAndFinance, string fileName)
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

void AddAllUserFileUsernamesPasswords(vector<User>& Users, string fileName)
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

void AddAllUserFileUsernamesFinance(map<string, double>& UsernamesAndFinance, string fileName)
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