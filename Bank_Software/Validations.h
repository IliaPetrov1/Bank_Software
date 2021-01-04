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
#include <string>
#include <regex>

using namespace std;

//VALIDATION
bool DoesNumberHasMoreThanTwoDigitsAfterComma(double number)
{
	bool ans = false;

	if (number * 100 - (int)(number * 100) == 0)
	{
		ans = true;
	}

	return ans;
}

bool IsNumberPositive(double number)
{
	bool ans = (number > 0) ? true : false;
	return ans;
}

bool CanThisMoneyBeRemovedFromBankBalance(double ownedMoney, double removedMoney, double overdraft)
{
	bool ans = (ownedMoney - removedMoney >= -1 * overdraft) ? true : false;
	return ans;
}

//Validation username
bool DoesUsernameContainsRightSymbs(string userInfo)
{
	bool answ = true;

	for (char symb : userInfo)
	{
		if (symb >= 48 && symb <= 57)
		{
			answ = false;
			break;
		}
	}

	return answ;
}

void ValidateUsername(string userInfo)
{
	bool doesUsernameContainsRightSymbs = DoesUsernameContainsRightSymbs(userInfo);

	while (doesUsernameContainsRightSymbs == false)
	{
		//Writing if I have to add extra criteria for username
		if (doesUsernameContainsRightSymbs == false)
		{
			cout << "Your username must contain only latin letters and symbols, try again: " << endl;
		}

		cin >> userInfo;
		doesUsernameContainsRightSymbs = DoesUsernameContainsRightSymbs(userInfo);
	}

}

//Validation password
bool DoesPasswordContainsRightSymbs(string userInfo)
{
	bool ans = false;

	smatch match;
	const string REG_STRING = "^[a-zA-Z0-9!@#$%^&*]+$";
	regex reg(REG_STRING);
	regex_search(userInfo, match, reg);

	if (match.str() != "")
	{
		ans = true;
	}

	return ans;
}

bool DoesPasswordContainsOneSmallLetter(string userInfo)
{
	bool ans = false;

	for (char symb : userInfo)
	{
		if (symb >= 'a' && symb <= 'z')
		{
			ans = true;
			break;
		}
	}

	return ans;
}

bool DoesPasswordContainsOneBigLetter(string userInfo)
{
	bool ans = false;

	for (char symb : userInfo)
	{
		if (symb >= 'A' && symb <= 'Z')
		{
			ans = true;
			break;
		}
	}

	return ans;
}

bool DoesPasswordContainsSpecSymb(string userInfo)
{
	bool ans = false;

	for (char symb : userInfo)
	{
		if (symb == '!' || symb == '@' || symb == '#' || symb == '$' || symb == '%' || symb == '^' || symb == '&' || symb == '*')
		{
			ans = true;
			break;
		}
	}

	return ans;
}

void ValidatePassword(string userInfo)
{
	int lenUserInfo = userInfo.length();
	bool doesPasswordContainsRightSymbs = DoesPasswordContainsRightSymbs(userInfo);
	bool doesPasswordContainsOneSmallLetter = DoesPasswordContainsOneSmallLetter(userInfo);
	bool doesPasswordContainsOneBigLetter = DoesPasswordContainsOneBigLetter(userInfo);
	bool doesPasswordContainsSpecSymb = DoesPasswordContainsSpecSymb(userInfo);

	while (lenUserInfo < 5 || doesPasswordContainsRightSymbs == false || doesPasswordContainsOneSmallLetter == false || doesPasswordContainsOneBigLetter == false || doesPasswordContainsSpecSymb == false)
	{
		if (lenUserInfo < 5)
		{
			cout << "Your password must be at least 5 symbols, try again: ";
		}
		if (doesPasswordContainsRightSymbs == false)
		{
			cout << "Your password must contain only small and big latin letters, digits and symbols (!@#$%^&*), try again: ";
		}
		if (doesPasswordContainsOneSmallLetter == false)
		{
			cout << "Your password must contain at least 1 small letter, try again: ";
		}
		if (doesPasswordContainsOneBigLetter == false)
		{
			cout << "Your password must contain at least 1 big letter, try again: ";
		}
		if (doesPasswordContainsSpecSymb == false)
		{
			cout << "Your password must contain at least 1 symbol (!@#$%^&*) letter, try again: ";
		}

		cin >> userInfo;

		lenUserInfo = userInfo.length();
		doesPasswordContainsRightSymbs = DoesPasswordContainsRightSymbs(userInfo);
		doesPasswordContainsOneSmallLetter = DoesPasswordContainsOneSmallLetter(userInfo);
		doesPasswordContainsOneBigLetter = DoesPasswordContainsOneBigLetter(userInfo);
		doesPasswordContainsSpecSymb = DoesPasswordContainsSpecSymb(userInfo);
	}
}
