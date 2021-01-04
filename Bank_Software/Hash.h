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

#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

//HASH FUNCTION
string ToHex(unsigned long long int input)
{
	string hexHashedString;

	stringstream hexStream;
	hexStream << hex << input;
	hexHashedString = hexStream.str();
	transform(hexHashedString.begin(), hexHashedString.end(), hexHashedString.begin(), ::toupper);

	return hexHashedString;
}

string ToHash(string userInfo)
{
	unsigned long long int hash = 1;

	for (unsigned long long int i = 0; i < userInfo.size(); i++)
	{
		hash = hash * (unsigned long long int)userInfo[i] * (i + 1);
	}

	userInfo = ToHex(hash);

	return userInfo;
}