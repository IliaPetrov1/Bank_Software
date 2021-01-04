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
#include <regex>

using namespace std;

//EXTRACTING USERNAMES, PASSWORDS AND FINANCE WITH REGEX
string GetUsernameRegexFileUsernamesPasswords(string userInfo)
{
	smatch match;
	const string REG_STRING = "(?=username:).+(?=_password:)";
	regex reg(REG_STRING);
	regex_search(userInfo, match, reg);

	string username = match.str().substr(9, match.size() - 9);
	return username;
}

string GetPasswordRegexFileUsernamesPasswords(string userInfo)
{
	smatch match;
	const string REG_STRING = "(?=_password:).+";
	regex reg(REG_STRING);
	regex_search(userInfo, match, reg);

	string password = match.str().substr(10, match.size() - 10);

	return password;
}

string GetUsernameRegexFileUsernamesFinance(string userInfo)
{
	smatch match;
	const string REG_STRING = "(?=username:).+(?=_finance:)";
	regex reg(REG_STRING);
	regex_search(userInfo, match, reg);

	string username = match.str().substr(9, match.size() - 9);
	return username;
}

double GetFinanceRegexFileUsernamesFinance(string userInfo)
{
	smatch match;
	const string REG_STRING = "(?=_finance:).+";
	regex reg(REG_STRING);
	regex_search(userInfo, match, reg);

	string financeStr = match.str().substr(9, match.size() - 10);
	double finance = stod(financeStr);

	return finance;
}