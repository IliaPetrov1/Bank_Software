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
* <file with class>
*
*/

#ifndef DATE_H
#define DATE_H

#include <string>

using namespace std;

//CLASS USER WITH ITS CONSTRUCTOR FUNCTIONS (GET/SET FOR USERNAME/PASSWORD)
class User
{
public:
	void set_username(string text);
	string get_username(void);

	void set_password(string text);
	string get_password(void);

private:
	string _username;
	string _password;
};

#endif