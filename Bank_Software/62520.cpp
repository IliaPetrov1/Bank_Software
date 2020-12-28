#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <regex>
#include <iomanip>
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
	string _username;
	string _password;
};
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

//DEBUG TOOLS
//Showing username, password and finance of all users
void ShowUsersUsernamePassword(vector<User> Users)
{
	for (auto user : Users)
	{
		cout << user.get_username() << " " << user.get_password() << endl;
	}
}
void ShowUsersUsernameFinance(map<string, double> UsernamesAndFinance)
{
	for (auto user : UsernamesAndFinance)
	{
		cout << user.first << " " << user.second << endl;
	}
}

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
void ValidateUsername(string &userInfo)
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
void ValidatePassword(string &userInfo)
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
			cout << "Your password must contain at least 1 symbol (!@#$%^&*) letter, try again: " ;
		}

		cin >> userInfo;

		lenUserInfo = userInfo.length();
		doesPasswordContainsRightSymbs = DoesPasswordContainsRightSymbs(userInfo);
		doesPasswordContainsOneSmallLetter = DoesPasswordContainsOneSmallLetter(userInfo);
		doesPasswordContainsOneBigLetter = DoesPasswordContainsOneBigLetter(userInfo);
		doesPasswordContainsSpecSymb = DoesPasswordContainsSpecSymb(userInfo);
	}
}

//ADD AND DELETE USER INFORMATION 
void CreateUser(vector<User> &Users, string username, string password)
{
	User newUser;
	newUser.set_username(username);
	newUser.set_password(password);
	Users.push_back(newUser);
}
void DeleteUser(vector<User> &Users, string username, string password)
{
	User newUser;
	newUser.set_username(username);
	newUser.set_password(password);

	int indexUser = 0;
	for (int i = 0; i < Users.size(); i++)
	{
		if (Users[i].get_username() == newUser.get_username())
		{
			indexUser = i;
			break;
		}
	}

	Users.erase(Users.begin() + indexUser);
}
void CreateBankFinance(map<string, double> &UsernamesAndFinance, string username, double finance)
{
	UsernamesAndFinance.insert(pair<string, double>(username, finance));
}
void DeleteBankFinance(map<string, double> &UsernamesAndFinance, string username)
{
	map<string, double>::iterator element;
	element = UsernamesAndFinance.find(username);
	UsernamesAndFinance.erase(element);
}

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

//FUNCTIONS FOR GETTING INFORMATION AND WRITING IN .TXT FILES
void ReadFileUsernamesPasswords(vector<User> &Users, string fileName)
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
void ReadFileUsernamesFinance(map<string, double> &UsernamesAndFinance, string fileName)
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
void AddAllUserFileUsernamesPasswords(vector<User> Users, string fileName)
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
void AddAllUserFileUsernamesFinance(map<string, double> UsernamesAndFinance, string fileName)
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

//START MENU
bool IsThisAccInUsers(vector<User> Users, string username)
{
	bool answ = false;

	for (int i = 0; i < Users.size(); i++)
	{
		if (Users[i].get_username() == username)
		{
			answ = true;
			break;
		}
	}

	return answ;
}
void LogIn(vector<User> Users, map<string, double>& UsernamesAndFinance, string &clientUsername, string &clientPassword, double &clientFinance)
{
	string username = "";
	string password = "";
	cout << "Enter your username: ";
	cin >> username;
	cout << "Enter your password: ";
	cin >> password;
	cout << endl;

	User thisUser;
	for (int i = 0; i < Users.size(); i++)
	{
		if (Users[i].get_username() == username)
		{
			thisUser = Users[i];
			break;
		}
	}

	/*cout << "User username: " << thisUser.get_username() << endl;
	cout << "User password: " << thisUser.get_password() << endl;*/

	while (IsThisAccInUsers(Users, username) == false || thisUser.get_password() != password)
	{
		if (IsThisAccInUsers(Users, username) == false)
		{
			cout << "There is no such user with this username. Try again!" << endl;
			cout << "Enter your username: ";
			cin >> username;
			cout << "Enter your password: ";
			cin >> password;
			cout << endl;
		}
		else if (IsThisAccInUsers(Users, username) == true && thisUser.get_password() != password)
		{
			cout << "Wrong password. Try again!" << endl;
			cout << "Enter your username: ";
			cin >> username;
			cout << "Enter your password: ";
			cin >> password;
			cout << endl;
		}
	}

	clientUsername = username;
	clientPassword = password;
	clientFinance = UsernamesAndFinance[clientUsername];

	system("cls");
}
void Register(vector<User> Users, map<string, double>& UsernamesAndFinance, string &clientUsername, string &clientPassword, double& clientFinance, string fileNameUsernamesPasswords, string fileNameUsernamesFinance)
{
	string username = "";
	string password = "";

	cout << "Enter your username: ";
	cin >> username;
	ValidateUsername(username);

	if (IsThisAccInUsers(Users, username) == true)
	{
		while (IsThisAccInUsers(Users, username) == true)
		{
			cout << "Someone else has already used this username, try again." << endl;

			cout << "Enter your username: ";
			cin >> username;
			ValidateUsername(username);
		}

		cout << "Enter your password: ";
		cin >> password;
		ValidatePassword(password);

		string confirmedPassword;
		cout << "Confirm your password: ";
		cin >> confirmedPassword;

		if (password != confirmedPassword)
		{
			cout << "Confirmation of your password is not valid, enter your password again: " << endl;

			while (password != confirmedPassword)
			{
				cout << "Enter your password: ";
				cin >> password;
				ValidatePassword(password);

				string confirmedPassword;
				cout << "Confirm your password: ";
				cin >> confirmedPassword;

				if (password == confirmedPassword)
				{
					break;
				}
			}
		}
	}
	else
	{
		cout << "Enter your password: ";
		cin >> password;
		ValidatePassword(password);

		string confirmedPassword;
		cout << "Confirm your password: ";
		cin >> confirmedPassword;

		if (password != confirmedPassword)
		{
			cout << "Confirmation of your password is not valid, enter your password again: " << endl;

			while (password != confirmedPassword)
			{
				cout << "Enter your password: ";
				cin >> password;
				ValidatePassword(password);

				string confirmedPassword;
				cout << "Confirm your password: ";
				cin >> confirmedPassword;

				if (password == confirmedPassword)
				{
					clientUsername = username;
					clientPassword = password;
					clientFinance = 0;

					AddUserFileUsernamesPasswords(clientUsername, clientPassword, fileNameUsernamesPasswords);
					AddUserFileUsernamesFinance(clientUsername, clientFinance, fileNameUsernamesFinance);

					break;
				}
			}
		}
		else
		{
			clientUsername = username;
			clientPassword = password;
			clientFinance = 0;

			AddUserFileUsernamesPasswords(clientUsername, clientPassword, fileNameUsernamesPasswords);
			AddUserFileUsernamesFinance(clientUsername, clientFinance, fileNameUsernamesFinance);
		}
	}
}
void Quit(vector<User> Users, string fileName)
{
	system("cls");
	cout << "We at FMI Bank know you had many options to choose from, we thank you for choosing us!" << endl;
	exit(EXIT_FAILURE);
}
void OptionsStartMenu(vector<User> Users, map<string, double>& UsernamesAndFinance, string& clientUsername, string& clientPassword, double& clientFinance, string fileNameUsernamesPasswords, string fileNameUsernamesFinance)
{
	string clientOption;
	cin >> clientOption;

	if (clientOption != "L" && clientOption != "R" && clientOption != "Q")
	{
		while (clientOption != "L" && clientOption != "R" && clientOption != "Q")
		{
			cout << "Sorry, but you have entered invalid input, please try again: ";
			cin >> clientOption;
		}
	}

	if (clientOption == "L")
	{
		if (Users.size() == 0)
		{
			cout << "You cannot log in, because there is no account in database, try again: ";
			OptionsStartMenu(Users, UsernamesAndFinance, clientUsername, clientPassword, clientFinance, fileNameUsernamesPasswords, fileNameUsernamesFinance);
		}
		LogIn(Users, UsernamesAndFinance, clientUsername, clientPassword, clientFinance);
	}
	else if (clientOption == "R")
	{
		Register(Users, UsernamesAndFinance, clientUsername, clientPassword, clientFinance, fileNameUsernamesPasswords, fileNameUsernamesFinance);
	}
	else if (clientOption == "Q")
	{
		Quit(Users, fileNameUsernamesPasswords);
	}
}
void StartMenu(vector<User> Users, map<string, double>& UsernamesAndFinance, string &clientUsername, string &clientPassword, double &clientFinance,string fileNameUsernamesPasswords, string fileNameUsernamesFinance)
{
	system("cls");

	cout << "Hello to FMI Bank!" << endl;
	cout << endl;
	cout << "Select one of 3 options:" << endl;
	cout << "L - log in" << endl;
	cout << "R - register" << endl;
	cout << "Q - quit" << endl;
	cout << "Type here: ";

	OptionsStartMenu(Users, UsernamesAndFinance, clientUsername, clientPassword, clientFinance, fileNameUsernamesPasswords, fileNameUsernamesFinance);
}

//USER MENU
void RemoveDigitsAfterSecondSymAfterComma(double& money)
{
	string moneyStr = to_string(money);

	int indexComma = 0;
	for (char symb : moneyStr)
	{
		if (symb == '.' || symb == ',')
		{
			break;
		}
		else
		{
			indexComma++;
		}
	}

	moneyStr = moneyStr.substr(0, indexComma + 3);
	money = stod(moneyStr);
}
bool CancelAcc(vector<User> Users, map<string, double>& UsernamesAndFinance, string& clientUsername, string& clientPassword, double& clientFinance, string fileNameUsernamesPasswords, string fileNameUsernamesFinance)
{
	bool isAccCanceled = true;
	cout << "Enter password: ";
	string password;
	cin >> password;

	if (password != clientPassword)
	{
		while (password != clientPassword)
		{
			cout << "You entered wrong password, try again: ";
			cin >> password;
		}
	}

	if (clientFinance > 0)
	{
		cout << "This account has deposit and cannot be deleted!" << endl;
		isAccCanceled = false;
		return isAccCanceled;
	}
	else
	{
		DeleteUser(Users, clientUsername, clientPassword);
		DeleteBankFinance(UsernamesAndFinance, clientUsername);

		AddAllUserFileUsernamesPasswords(Users, fileNameUsernamesPasswords);
		AddAllUserFileUsernamesFinance(UsernamesAndFinance, fileNameUsernamesFinance);

		return isAccCanceled;
	}
}
void Deposit(map<string, double>& UsernamesAndFinance, string& clientUsername, double& clientFinance, string fileNameUsernamesFinance)
{
	cout << "How much money do you want to deposit: ";
	double deposit;

	cin >> deposit;

	while (IsNumberPositive(deposit) == false)
	{
		if (IsNumberPositive(deposit) == false)
		{
			cout << "Deposit should be positive number, try again: ";
		}

		cin >> deposit;
	}
	if (DoesNumberHasMoreThanTwoDigitsAfterComma(deposit) == false)
	{
		RemoveDigitsAfterSecondSymAfterComma(deposit);
		cout << "dep:" << deposit << endl;
	}

	clientFinance += deposit;

	UsernamesAndFinance[clientUsername] = clientFinance;
	AddAllUserFileUsernamesFinance(UsernamesAndFinance, fileNameUsernamesFinance);
	ReadFileUsernamesFinance(UsernamesAndFinance, fileNameUsernamesFinance);
}
void Logout(vector<User> Users, map<string, double>& UsernamesAndFinance, string& clientUsername, string& clientPassword, double& clientFinance, string fileNameUsernamesPasswords, string fileNameUsernamesFinance)
{
	StartMenu(Users, UsernamesAndFinance, clientUsername, clientPassword, clientFinance, fileNameUsernamesPasswords, fileNameUsernamesFinance);
}
void Transfer(vector<User> Users, map<string, double>& UsernamesAndFinance, string& clientUsername, double& clientFinance, string fileNameUsernamesFinance)
{
	double overdraft = 10000;

	cout << "How much money do you want to transfer: ";
	double transferedMoney;

	cin >> transferedMoney;

	while (IsNumberPositive(transferedMoney) == false || CanThisMoneyBeRemovedFromBankBalance(clientFinance, transferedMoney, overdraft) == false)
	{
		if (IsNumberPositive(transferedMoney) == false)
		{
			cout << "Transfered money should be positive number, try again: ";
		}

		else if (CanThisMoneyBeRemovedFromBankBalance(clientFinance, transferedMoney, overdraft) == false)
		{
			cout << "You cannot transfer, because you will go over your overdraft limit: ";
		}

		cin >> transferedMoney;
	}
	if (DoesNumberHasMoreThanTwoDigitsAfterComma(transferedMoney) == false)
	{
		RemoveDigitsAfterSecondSymAfterComma(transferedMoney);
	}

	cout << "Transfered money to (enter the username of account you want transfer to): ";
	string strangersUsername;

	cin >> strangersUsername;

	while (IsThisAccInUsers(Users, strangersUsername) == false)
	{
		cout << "You entered invalid username, try again: ";
		cin >> strangersUsername;
	}

	//Adding to stranger acc
	UsernamesAndFinance[strangersUsername] += transferedMoney;
	AddAllUserFileUsernamesFinance(UsernamesAndFinance, fileNameUsernamesFinance);
	ReadFileUsernamesFinance(UsernamesAndFinance, fileNameUsernamesFinance);

	//Removing from user acc
	clientFinance -= transferedMoney;
	UsernamesAndFinance[clientUsername] = clientFinance;
	AddAllUserFileUsernamesFinance(UsernamesAndFinance, fileNameUsernamesFinance);
	ReadFileUsernamesFinance(UsernamesAndFinance, fileNameUsernamesFinance);
}
void Withdraw(map<string, double>& UsernamesAndFinance, string& clientUsername, double& clientFinance, string fileNameUsernamesFinance)
{
	double overdraft = 10000;

	cout << "How much money do you want to withdraw: ";
	double withdrawal;

	cin >> withdrawal;

	while (IsNumberPositive(withdrawal) == false || CanThisMoneyBeRemovedFromBankBalance(clientFinance, withdrawal, overdraft) == false)
	{
		if (IsNumberPositive(withdrawal) == false)
		{
			cout << "Withdrawal should be positive number, try again: ";
		}
		else if (CanThisMoneyBeRemovedFromBankBalance(clientFinance, withdrawal, overdraft) == false)
		{
			cout << "You cannot withdraw, because you will go over your overdraft limit: " << endl;
			cout << "How much money do you want to withdraw: ";
		}

		cin >> withdrawal;
	}
	if (DoesNumberHasMoreThanTwoDigitsAfterComma(withdrawal) == false)
	{
		RemoveDigitsAfterSecondSymAfterComma(withdrawal);
	}

	clientFinance -= withdrawal;

	UsernamesAndFinance[clientUsername] = clientFinance;
	AddAllUserFileUsernamesFinance(UsernamesAndFinance, fileNameUsernamesFinance);
	ReadFileUsernamesFinance(UsernamesAndFinance, fileNameUsernamesFinance);
}
void UserMenu(vector<User> Users, map<string, double> UsernamesAndFinance, string& clientUsername, string& clientPassword, double& clientFinance, string fileNameUsernamesPasswords, string fileNameUsernamesFinance)
{
	system("cls");
	ReadFileUsernamesPasswords(Users, fileNameUsernamesPasswords);
	ReadFileUsernamesFinance(UsernamesAndFinance, fileNameUsernamesFinance);

	cout << "You have " << fixed << setprecision(2) << UsernamesAndFinance[clientUsername] << " BGN. Choose one of the following options:" << endl;
	cout << "C - cancel account" << endl;
	cout << "D - deposit" << endl;
	cout << "L - logout" << endl;
	cout << "T - transfer" << endl;
	cout << "W - withdraw" << endl;
	cout << "Type here: ";

	string clientOption;
	cin >> clientOption;

	if (clientOption != "C" && clientOption != "D" && clientOption != "L" && clientOption != "T" && clientOption != "W")
	{
		while (clientOption != "C" && clientOption != "D" && clientOption != "L" && clientOption != "T" && clientOption != "W")
		{
			cout << "Sorry, but you have entered invalid input, please try again: ";
			cin >> clientOption;
		}
	}

	if (clientOption == "C")
	{
		bool isAccCanceled = CancelAcc(Users, UsernamesAndFinance, clientUsername, clientPassword, clientFinance, fileNameUsernamesPasswords, fileNameUsernamesFinance);

		if (isAccCanceled == true)
		{
			StartMenu(Users, UsernamesAndFinance, clientUsername, clientPassword, clientFinance, fileNameUsernamesPasswords, fileNameUsernamesFinance);
		}
		else
		{
			UserMenu(Users, UsernamesAndFinance, clientUsername, clientPassword, clientFinance, fileNameUsernamesPasswords, fileNameUsernamesFinance);
		}
	}
	else if (clientOption == "D")
	{
		Deposit(UsernamesAndFinance, clientUsername, clientFinance, fileNameUsernamesFinance);
		UserMenu(Users, UsernamesAndFinance, clientUsername, clientPassword, clientFinance, fileNameUsernamesPasswords, fileNameUsernamesFinance);
	}
	else if (clientOption == "L")
	{
		Logout(Users, UsernamesAndFinance, clientUsername, clientPassword, clientFinance, fileNameUsernamesPasswords, fileNameUsernamesFinance);
	}
	else if (clientOption == "T")
	{
		Transfer(Users, UsernamesAndFinance, clientUsername, clientFinance, fileNameUsernamesFinance);
		UserMenu(Users, UsernamesAndFinance, clientUsername, clientPassword, clientFinance, fileNameUsernamesPasswords, fileNameUsernamesFinance);
	}
	else if (clientOption == "W")
	{
		Withdraw(UsernamesAndFinance, clientUsername, clientFinance, fileNameUsernamesFinance);
		UserMenu(Users, UsernamesAndFinance, clientUsername, clientPassword, clientFinance, fileNameUsernamesPasswords, fileNameUsernamesFinance);
	}

	AddAllUserFileUsernamesPasswords(Users, fileNameUsernamesPasswords);
	AddAllUserFileUsernamesFinance(UsernamesAndFinance, fileNameUsernamesFinance);
}

int main()
{
	vector<User> Users;
	map<string, double> UsernamesAndFinance;

	string fileInfo;
	string const fileNameUsernamesPasswords = "users.txt";
	string const fileNameUsernamesFinance = "users_finance.txt";

	ReadFileUsernamesPasswords(Users, fileNameUsernamesPasswords);
	ReadFileUsernamesFinance(UsernamesAndFinance, fileNameUsernamesFinance);

	string clientUsername = "";
	string clientPassword = "";
	double clientFinance = 0;

	StartMenu(Users, UsernamesAndFinance, clientUsername, clientPassword, clientFinance, fileNameUsernamesPasswords, fileNameUsernamesFinance);

	while (true)
	{
		UserMenu(Users, UsernamesAndFinance, clientUsername, clientPassword, clientFinance, fileNameUsernamesPasswords, fileNameUsernamesFinance);
	}
	
	return 0;
}