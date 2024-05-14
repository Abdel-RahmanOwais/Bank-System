#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include <iomanip>


class clsUpdateUserScreen : protected clsScreen
{

	static clsUser _ReadNewUser(clsUser& User) {

		cout << "\n" << setw(37) << left << "" << "Enter First Name : ";
		User.FirstName = clsInputValidate::ReadString();

		cout << "\n" << setw(37) << left << "" << "Enter Last Name  : ";
		User.LastName = clsInputValidate::ReadString();

		cout << "\n" << setw(37) << left << "" << "Enter Email      : ";
		User.Email = clsInputValidate::ReadString();

		cout << "\n" << setw(37) << left << "" << "Enter Phone      : ";
		User.Phone = clsInputValidate::ReadString();

		cout << "\n" << setw(37) << left << "" << "Enter Password   : ";
		User.Password = clsInputValidate::ReadString();

		cout << "\n" << setw(37) << left << "" << "Enter Permission : ";
		User.Permissions = _ReadPermissionsToSet();

		return User;
	}

	static int _ReadPermissionsToSet() {
		int Permissions = 0;
		char Answer = 'n';

		cout << "\n" << setw(37) << left << "" << "Do You Want To Give Full Access [Y] or [N] : ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y') {
			return -1;
		}

		cout << "\n\n" << setw(37) << left << "" << "Do You Want To Give Access To : \n";

		cout << "\n\n" << setw(37) << left << "" << "Show Client List [Y] or [N]: ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			Permissions += clsUser::enPermissions::pListClients;
		}

		cout << "\n\n" << setw(37) << left << "" << "Add New Client [Y] or [N]  : ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			Permissions += clsUser::enPermissions::pAddNewClient;
		}

		cout << "\n\n" << setw(37) << left << "" << "Delete Client [Y] or [N]   : ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			Permissions += clsUser::enPermissions::pDeleteClient;
		}

		cout << "\n\n" << setw(37) << left << "" << "Update Client [Y] or [N]   : ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			Permissions += clsUser::enPermissions::pUpdateClients;
		}

		cout << "\n\n" << setw(37) << left << "" << "Find Client [Y] or [N]     : ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			Permissions += clsUser::enPermissions::pFindClient;
		}

		cout << "\n\n" << setw(37) << left << "" << "Transactions[Y] or [N]     : ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			Permissions += clsUser::enPermissions::pTranactions;
		}

		cout << "\n\n" << setw(37) << left << "" << "Mange Users [Y] or [N]     : ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			Permissions += clsUser::enPermissions::pMangeUsers;
		}

		cout << "\n\n" << setw(37) << left << "" << "Login Register [Y] or [N]  : ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			Permissions += clsUser::enPermissions::pLoginRegister;
		}

		return Permissions;
	}

	static void _PrintUserCard(clsUser User)
	{
		cout << "\n" << setw(37) << left << "" << "______________________________________________\n";
		cout << "\n" << setw(37) << left << "" << "\t\t       User Card : ";
		cout << "\n" << setw(37) << left << "" << "______________________________________________";
		cout << "\n" << setw(37) << left << "" << "FirstName      : " << User.FirstName << endl;
		cout << "\n" << setw(37) << left << "" << "LastName       : " << User.LastName << endl;
		cout << "\n" << setw(37) << left << "" << "Email          : " << User.Email << endl;
		cout << "\n" << setw(37) << left << "" << "Phone          : " << User.Phone << endl;
		cout << "\n" << setw(37) << left << "" << "Password       : " << User.Password << endl;
		cout << "\n" << setw(37) << left << "" << "Permissions    : " << User.Permissions << endl;
		cout << setw(37) << left << "" << "______________________________________________\n" << endl;
	}

public:


	static void ShowUpdateUserScreen() {
		_DrawScreenHeader("\t\t Update User Screen");

		cout << "\n" << setw(37) << left << "" << "Please Enter Your UserName: ";
		string UserName= clsInputValidate::ReadString();

		while (!clsUser::IsUserExist(UserName)) {
			cout << "\n" << setw(37) << left << "" << "User Is NOT Found, Choose Anthor One : ";
			UserName= clsInputValidate::ReadString();
		}

		clsUser User = clsUser::Find(UserName);
		_PrintUserCard(User);

		cout << "\n" << setw(37) << left << "" << "Update User Information : " << endl;
		cout << "\n" << setw(37) << left << "" << "______________________________________________\n" << endl;

		_ReadNewUser(User);

		clsUser::enSaveResults SaveResult;
		SaveResult = User.Save();

		switch (SaveResult)
		{
		case clsUser::enSaveResults::svFaildEmptyObject:

			cout << "\n" << setw(37) << left << "" << "Error User Was NOT Saved Because It's Empty :-(\n";
			break;
		case clsUser::enSaveResults::svSucceeded:
			cout << "\n" << setw(37) << left << "" << "==============================================\n";
			cout << "\n" << setw(37) << left << "" << "\t     User Updated Successfully :-)\n";
			cout << "\n" << setw(37) << left << "" << "==============================================\n";
			_PrintUserCard(User);
			break;
		}
	}

};

