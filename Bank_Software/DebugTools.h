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
#include <vector>
#include <map>
#include "User.h"

using namespace std;

//DEBUG TOOLS
//Showing username, password and finance of all users
void ShowUsersUsernamePassword(vector<User>& Users)
{
	for (auto user : Users)
	{
		cout << user.get_username() << " " << user.get_password() << endl;
	}
}

void ShowUsersUsernameFinance(map<string, double>& UsernamesAndFinance)
{
	for (auto user : UsernamesAndFinance)
	{
		cout << user.first << " " << user.second << endl;
	}
}