#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include <iomanip>

class clsFindUserScreen : protected clsScreen 
{

	static void _PrintUserCard(clsUser User)
	{
		cout << "\n" << setw(37) << left << "" << "______________________________________________\n";
		cout << "\n" << setw(37) << left << "" << "\t\t     User Card : ";
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


    static void ShowFindUserScreen()
    {

        _DrawScreenHeader("\t\t   Find User Screen");

        string UserName;
        cout << "\n" << setw(37) << left << "" << "Please Enter UserName: ";
        UserName = clsInputValidate::ReadString();
        while (!clsUser::IsUserExist(UserName))
        {
            cout << "\n" << setw(37) << left << "" << "User Is NOT Found, Choose Another One: ";
            UserName = clsInputValidate::ReadString();
        }

        clsUser User = clsUser::Find(UserName);

        if (!User.IsEmpty())
        {
            cout << "\n" << setw(37) << left << "" << "==============================================\n";
            cout << "\n" << setw(37) << left << "" << "\t           User Found :-)\n";
            cout << "\n" << setw(37) << left << "" << "==============================================\n";
        }
        else
        {
            cout << "\n" << setw(37) << left << "" << "==============================================\n";
            cout << "\n" << setw(37) << left << "" << "\t          User Was not Found :-(\n";
            cout << "\n" << setw(37) << left << "" << "==============================================\n";
        }

        _PrintUserCard(User);

    }


};

