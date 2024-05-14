#pragma once
#include <iostream>
#include "clsUser.h"
#include "clsDate.h"
#include "Global.h"

using namespace std;

class clsScreen
{

protected:

	static void _DrawScreenHeader(string Title, string SubTitle = "") {


		cout << setw(47) << left << "" << "============================\n";
		cout << setw(47) << left << "" << "     User : " << CurrentUser.UserName << endl;
		cout << setw(47) << left << "" << "     Date : " << clsDate::DateToString(clsDate()) << endl;
		cout << setw(47) << left << "" << "============================\n";

		//_______________________________________________________________________________

		cout << "\t\t\t\t     ______________________________________________" << endl;
		cout << "\t\t\t\t    " << Title << endl;
		if (SubTitle != "") {
			cout << "\t\t\t\t  " << SubTitle << endl;
		}
		cout << "\t\t\t\t     ______________________________________________" << endl;
	}

	static bool CheckAccessRights(clsUser::enPermissions Permission) {
		if (!CurrentUser.CheckAccessPermissions(Permission)) {
			cout << "\t\t\t\t     ______________________________________________" << endl;
			cout << "\n\n\t\t\t\t          " << "Access Denied! Contact Your Admin" << endl;
			cout << "\n\t\t\t\t     ______________________________________________" << endl;
			return false;
		}
		else {
			return true;
		}

	}






};
