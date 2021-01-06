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

#include "User.h"

//CONSTRUCTOR AND FUNCTIONS OF USER
void User::set_username(string text)
{
	_username = text;
}

string User::get_username(void)
{
	return _username;
}

void User::set_password(string text)
{
	_password = text;
}

string User::get_password(void)
{
	return _password;
}

