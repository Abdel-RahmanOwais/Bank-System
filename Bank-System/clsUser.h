#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include "clsDate.h"
#include "clsUtil.h"
#include <vector> 
#include <fstream>

class clsUser : public clsPerson
{
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };

	enMode _Mode;
	string _UserName = "";
	string _Password = "";
	int _Permissions = 0;
	bool _MarkForDeleted = false;

	static clsUser _ConvertLineToUserObject(string Line, string Seperator = "#//#") {
		vector <string> vUsersData;
		vUsersData = clsString::Split(Line, Seperator);

		return clsUser(enMode::UpdateMode, vUsersData[0], vUsersData[1], vUsersData[2], vUsersData[3],
			vUsersData[4], clsUtil::DecryptText(vUsersData[5]), stoi(vUsersData[6]));
	}

	string _PrepareLogInRecord(string Seperator = "#//#") {
		string LogingRecord = "";

		LogingRecord += clsDate::GetSystemDateTimeToString() + Seperator;
		LogingRecord += UserName + Seperator;
		//Here we encrypt the password not the real one.
		LogingRecord += clsUtil::EncryptText(Password) + Seperator;
		LogingRecord += to_string(Permissions);

		return LogingRecord;
	}

	static string _ConverUserObjectToLine(clsUser User, string Seperator = "#//#")
	{

		string UserRecord = "";
		UserRecord += User.FirstName + Seperator;
		UserRecord += User.LastName + Seperator;
		UserRecord += User.Email + Seperator;
		UserRecord += User.Phone + Seperator;
		UserRecord += User.UserName + Seperator;
		//Here we encrypt the password not the real one.
		UserRecord += clsUtil::EncryptText(User.Password) + Seperator;
		UserRecord += to_string(User.Permissions);

		return UserRecord;

	}

	static  vector <clsUser> _LoadUsersDataFromFile() {
		vector <clsUser> vUsers;
		
		fstream UsersFile;

		UsersFile.open("Users.txt", ios::in); //Read Mode
	
		if (UsersFile.is_open()) {
			string Line;

			while (getline(UsersFile, Line)) {
				clsUser User = _ConvertLineToUserObject(Line);

				vUsers.push_back(User);
			}

			UsersFile.close();
		}

		return vUsers;
	}

	void _SaveUserDataToFile(vector <clsUser> vUsers) {
		fstream UserFile;

		UserFile.open("Users.txt", ios::out); //OverWright

		string DataLine;

		if (UserFile.is_open()) {

			for (clsUser& U : vUsers) {
				
				if (U.MarkForDeleted() == false) {

					//we only write records that are not marked for delete. 
					DataLine = _ConverUserObjectToLine(U);
					UserFile << DataLine << endl;

				}
			}

			UserFile.close();
		}
	}

	void _Update() {
		vector <clsUser> _vUsers;

		_vUsers = _LoadUsersDataFromFile();

		for (clsUser& U : _vUsers) {

			if (U.UserName == _UserName) {
				U = *this;
				break;
			}

		}

		_SaveUserDataToFile(_vUsers);
	}

	void _AddDataLineToFile(string  stDataLine)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << stDataLine << endl;

			MyFile.close();
		}

	}

	void _AddNew()
	{
		_AddDataLineToFile(_ConverUserObjectToLine(*this));
	}


	static clsUser _GetEmptyUserObject()
	{
		return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

public:

	enum enPermissions {
		eAll = -1, pListClients = 1, pAddNewClient = 2,
		pDeleteClient = 4, pUpdateClients = 8,
		pFindClient = 16, pTranactions = 32,
		pMangeUsers = 64, pLoginRegister = 128
		
	};

	struct stLoginRegisterRecord
	{
		string DateTime;
		string UserName;
		string Password;
		int Perimssions;
	};

	static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(string Line, string Seperator = "#//#") {
		stLoginRegisterRecord LoginRegisterRecord;
				
		vector <string> vLoginRegisterDataLine = clsString::Split(Line, Seperator);

		LoginRegisterRecord.DateTime = vLoginRegisterDataLine[0];
		LoginRegisterRecord.UserName = vLoginRegisterDataLine[1];
		LoginRegisterRecord.Password = clsUtil::DecryptText(vLoginRegisterDataLine[2]);
		LoginRegisterRecord.Perimssions = stoi(vLoginRegisterDataLine[3]);

		return LoginRegisterRecord;
	}


	clsUser(enMode Mode, string FirstName, string LastName, string Email,
		string Phone, string UserName, string Password, int Permissions) :
		clsPerson(FirstName, LastName, Email, Phone) 
	{
		_Mode = Mode;
		_UserName = UserName;
		_Password = Password;
		_Permissions = Permissions;
	}

	bool IsEmpty() {
		return (_Mode == enMode::EmptyMode);
	}

	bool MarkForDeleted() {
		return _MarkForDeleted;
	}

	void SetUserName(string UserName) {
		_UserName = UserName;
	}

	string GetUserName() {
		return _UserName;
	}

	_declspec(property(get = GetUserName, put = SetUserName)) string UserName;

	void SetPassword(string Password) {
		_Password = Password;
	}

	string GetPassword() {
		return _Password;
	}

	_declspec(property(get = GetPassword, put = SetPassword)) string Password;

	void SetPermissions(int Permissions) {
		_Permissions = Permissions;
	}

	int GetPermissions() {
		return _Permissions;
	}

	_declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;


	static clsUser Find(string UserName) {
		fstream UserFile;

		UserFile.open("Users.txt", ios::in); //Read Mode
		
		if (UserFile.is_open()) {

			string Line = "";

			while (getline(UserFile, Line)) {
				clsUser User = _ConvertLineToUserObject(Line);

				if (User.UserName == UserName) {
					UserFile.close();
					return User;
				}

			}

			UserFile.close();
		}
		return _GetEmptyUserObject();
	}
	
	static clsUser Find(string UserName, string Password) {
		fstream UserFile;

		UserFile.open("Users.txt", ios::in); //Read Mode
		
		if (UserFile.is_open()) {

			string Line = "";

			while (getline(UserFile, Line)) {
				clsUser User = _ConvertLineToUserObject(Line);

				if (User.UserName == UserName && User.Password == Password) {
					UserFile.close();
					return User;
					
				}

			}

			UserFile.close();
		}

		return _GetEmptyUserObject();
	}

	static bool IsUserExist(string UserName) {
		clsUser User = clsUser::Find(UserName);

		return (!User.IsEmpty());
	}

	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserExsit = 2};

	enSaveResults Save() {
		
		switch (_Mode)
		{
		case clsUser::EmptyMode:

			if (IsEmpty()) {
				return enSaveResults::svFaildEmptyObject;
			}

		case clsUser::UpdateMode:
			_Update();

			return enSaveResults::svSucceeded;
			break;
		case clsUser::AddNewMode:

			if (clsUser::IsUserExist(_UserName)) {
				return enSaveResults::svFaildUserExsit;
			}
			else {
				_AddNew();

				//We need to set the mode to update after add new
				_Mode = enMode::UpdateMode;
				return enSaveResults::svSucceeded;

			}

			break;
		}

	}

	bool Delete()
	{
		vector <clsUser> _vUsers;
		_vUsers = _LoadUsersDataFromFile();

		for (clsUser& U : _vUsers)
		{
			if (U.UserName == _UserName)
			{
				U._MarkForDeleted = true;
				break;
			}

		}

		_SaveUserDataToFile(_vUsers);

		*this = _GetEmptyUserObject();

		return true;

	}

	static clsUser GetAddNewUserObject(string UserName)
	{
		return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
	}

	static vector <clsUser> GetUsersList()
	{
		return _LoadUsersDataFromFile();
	}


	bool CheckAccessPermissions(enPermissions Permission) {
		if (this->Permissions == enPermissions::eAll) {
			return true;
		}

		if ((Permission & this->Permissions) == Permission) {
			return true;
		}
		else {
			return false;
		}

	}

	void RegisterLogIn() {
		string DataLine = _PrepareLogInRecord();

		fstream LoginFile;

		LoginFile.open("LoginRegister.txt", ios::out | ios::app);

		if (LoginFile.is_open()) {
			
			LoginFile << DataLine << endl;

			LoginFile.close();
		}
	}

	static vector <stLoginRegisterRecord> GetLoginRegisterList() {

		vector <stLoginRegisterRecord> vLoginRegisterRecord;

		fstream LoginFile;

		LoginFile.open("LoginRegister.txt", ios::in); //Read Mode

		if (LoginFile.is_open()) {
			
			string Line;

			stLoginRegisterRecord LoginRegisterRecord;

			while (getline(LoginFile, Line)) {
				
				LoginRegisterRecord = _ConvertLoginRegisterLineToRecord(Line);

				vLoginRegisterRecord.push_back(LoginRegisterRecord);
			}

			LoginFile.close();
		}

		return vLoginRegisterRecord;
	}
};

