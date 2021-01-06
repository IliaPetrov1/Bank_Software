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
#include "User.h"

using namespace std;

//ADD AND DELETE USER INFORMATION 
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
	int usersSize = Users.size();
	for (int i = 0; i < usersSize; i++)
	{
		if (Users[i].get_username() == newUser.get_username())
		{
			indexUser = i;
			break;
		}
	}

	Users.erase(Users.begin() + indexUser);
}

void CreateBankFinance(map<string, double>& UsernamesAndFinance, string username, double finance)
{
	UsernamesAndFinance.insert(pair<string, double>(username, finance));
}

void DeleteBankFinance(map<string, double>& UsernamesAndFinance, string username)
{
	map<string, double>::iterator element;
	element = UsernamesAndFinance.find(username);
	UsernamesAndFinance.erase(element);
}
