#pragma once
#include <iostream>
#include "clsUser.h"
#include "clsScreen.h"
#include "Global.h"
#include <iomanip>


class clsShowLoginRegisterScreen : protected clsScreen
{

    static void _PrintLoginRegisterRecordLine(clsUser::stLoginRegisterRecord User)
    {

        cout << setw(8) << left << "" << "| " << setw(35) << left << User.DateTime;
        cout << "| " << setw(20) << left << User.UserName;
        cout << "| " << setw(20) << left << User.Password;
        cout << "| " << setw(10) << left << User.Perimssions;

    }

public:

	static void ShowLoginRegisterScreen() {
		if (!CheckAccessRights(clsUser::enPermissions::pLoginRegister)) {
			return; //this will exist function because user not have permission to show this page.
		}

        vector <clsUser::stLoginRegisterRecord> vLoginRegisterRecord = clsUser::GetLoginRegisterList();

		_DrawScreenHeader("\t\tShow Login Register Screen",
            "\t\t    (" + to_string(vLoginRegisterRecord.size()) + ") Login Register(s).");


        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(35) << "Date/Time";
        cout << "| " << left << setw(20) << "Username";
        cout << "| " << left << setw(20) << "Password";
        cout << "| " << left << setw(10) << "Permissions";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vLoginRegisterRecord.size() == 0)
            cout << "\t\t\t\tNo Users Login In the System!";
        else

            for (clsUser::stLoginRegisterRecord &U : vLoginRegisterRecord)
            {

                _PrintLoginRegisterRecordLine(U);
                cout << setw(8) << left << "" << "\t" << endl;

            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
	}

};

