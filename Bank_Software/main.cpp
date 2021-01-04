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
* <main file>
*
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "User.h"
#include "DebugTools.h"
#include "Hash.h"
#include "Validations.h"
#include "AddDeleteUserInfo.h"
#include "ExtractingUserInfoRegex.h"
#include "GetUserInfoFile.h"
#include "Menus.h"

using namespace std;

int main()
{
	vector<User> Users;
	map<string, double> UsernamesAndFinance;

	string fileInfo;
	string const fileNameUsernamesPasswords = "users.txt";
	string const fileNameUsernamesFinance = "users_finance.txt";

	string clientUsername = "";
	string clientPassword = "";
	double clientFinance = 0;

	StartMenu(Users, UsernamesAndFinance, clientUsername, clientPassword, clientFinance, fileNameUsernamesPasswords, fileNameUsernamesFinance);

	return 0;
}