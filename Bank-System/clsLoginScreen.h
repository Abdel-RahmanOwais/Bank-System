#pragma once
#include <iostream>
#include "clsUser.h"
#include <iomanip>
#include "clsScreen.h"
#include "clsMainScreen.h"
#include "clsDate.h"
#include "clsString.h"
#include "Global.h"

class clsLoginScreen : protected clsScreen
{

	static bool _Login() {
		bool LoginFaild = false;
		short Trials = 3;
		string UserName, Password;

		do {

			if (LoginFaild) {
				Trials--;
				cout << "\n" << setw(37) << left << "" << "Invalid Username/Password !";
				cout << "\n" << setw(37) << left << "" << "You Have (" << Trials << ") Trail(s) to Login! \n";
			}

			if (Trials == 0) {

				cout << "\n\n" << setw(37) << left << "" << "===========================================\n";
				cout << "\n" << setw(37) << left << "" << "  You Are Locked After Faild 3 Trials :-(\n";
				cout << "\n" << setw(37) << left << "" << "===========================================\n";

				return false;
			}

			cout << "\n" << setw(37) << left << "" << "Enter Username : ";
			cin >> UserName;

			cout << setw(37) << left << "" << "Enter Password : ";
			cin >> Password;

			CurrentUser = clsUser::Find(UserName, Password);

			LoginFaild = CurrentUser.IsEmpty();

		} while (LoginFaild);

		CurrentUser.RegisterLogIn();

		clsMainScreen::ShowMainMeune();

		return true;
	}

public:

	static bool ShowLoginScreen() {
		system("cls");

		_DrawScreenHeader("\t\t   Login Screen");

		return _Login();
	}

};

