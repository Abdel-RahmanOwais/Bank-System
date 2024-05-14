#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include <iomanip>

class clsDeleteUserScreen : protected clsScreen
{

	static void _PrintUserCard(clsUser User)
	{
		cout << "\n" << setw(37) << left << "" << "______________________________________________\n";
		cout << "\n" << setw(37) << left << "" << "\t\t        User Card : ";
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


	static void ShowDeleteUserScreen() {
		_DrawScreenHeader("\t\t Delete User Screen");

		cout << "\n" << setw(37) << left << "" << "Please Enter Your UserName : ";
		string UserName = clsInputValidate::ReadString();

		while (!clsUser::IsUserExist(UserName)) {
			cout << "\n" << setw(37) << left << "" << "User Is NOT Found, Choose Anthor One : ";
			UserName = clsInputValidate::ReadString();
		}


		cout << setw(37) << left << "" << "==============================================\n";
		cout << setw(37) << left << "" << "\t\t    Delete User : " << endl;
		cout << setw(37) << left << "" << "==============================================\n";

		clsUser User = clsUser::Find(UserName);
		_PrintUserCard(User);

		cout << "\n" << setw(37) << left << "" << "Are You Sure Do You Want To Delete This User [Y] or [N] : ";
		char Answer = 'n';
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			if (User.Delete())
			{
				cout << "\n" << setw(37) << left << "" << "==============================================\n";
				cout << "\n" << setw(37) << left << "" << "\t      User Deleted Successfully :-)" << endl;
				cout << "\n" << setw(37) << left << "" << "==============================================\n";
				_PrintUserCard(User);
				cout << "\n";
			}
			else
			{
				cout << "\n" << setw(37) << left << "" << "Error User Was NOT Deleted" << endl << endl;
			}
		}
	}

};

