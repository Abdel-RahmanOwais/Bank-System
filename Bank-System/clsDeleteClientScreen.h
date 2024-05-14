#pragma once
#include <iostream> 
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include <iomanip>

using namespace std;

class clsDeleteClientScreen : protected clsScreen
{


	static void _PrintClient(clsBankClient Client)
	{
		cout << "\n" << setw(37) << left << "" << "______________________________________________\n";
		cout << "\n" << setw(37) << left << "" << "\t\t  Client Card : ";
		cout << "\n" << setw(37) << left << "" << "______________________________________________";
		cout << "\n" << setw(37) << left << "" << "FirstName      : " << Client.FirstName << endl;
		cout << "\n" << setw(37) << left << "" << "LastName       : " << Client.LastName << endl;
		cout << "\n" << setw(37) << left << "" << "Full Name      : " << Client.FullName() << endl;
		cout << "\n" << setw(37) << left << "" << "Email          : " << Client.Email << endl;
		cout << "\n" << setw(37) << left << "" << "Phone          : " << Client.Phone << endl;
		cout << "\n" << setw(37) << left << "" << "Account Number : " << Client.AccountNumber() << endl;
		cout << "\n" << setw(37) << left << "" << "Pin Code       : " << Client.PinCode << endl;
		cout << "\n" << setw(37) << left << "" << "Balance        : " << Client.AccountBalance << endl;
		cout << setw(37) << left << "" << "______________________________________________\n" << endl;
	}


public:

	static void ShowDeleteClientScreen() {
		if (!CheckAccessRights(clsUser::enPermissions::pDeleteClient)) {
			return; //this will exist function because user not have permission to show this page.
		}

		_DrawScreenHeader("\t\t Delete Client Screen");

		cout << "\n" << setw(37) << left << "" << "Please Enter Your Account Number : ";
		string AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber)) {
			cout << "\n" << setw(37) << left << "" << "Account Number Is NOT Found, Choose Anthor One : ";
			AccountNumber = clsInputValidate::ReadString();
		}


		cout  << setw(37) << left << "" << "==============================================\n";
		cout  << setw(37) << left << "" << "\t\t    Delete Client : " << endl;
		cout  << setw(37) << left << "" << "==============================================\n";

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClient(Client);

		cout << "\n" << setw(37) << left << "" << "Are You Sure Do You Want To Delete This Client y/n : ";
		char Answer = 'n';
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			if (Client.Delete())
			{
				cout << "\n" << setw(37) << left << "" << "==============================================\n";
				cout << "\n" << setw(37) << left << "" << "\t      Client Deleted Successfully :-)" << endl;
				cout << "\n" << setw(37) << left << "" << "==============================================\n";
				_PrintClient(Client);
				cout << "\n";
			}
			else
			{
				cout << "\n" << setw(37) << left << "" << "Error Client Was NOT Deleted" << endl << endl;
			}
		}
	}


};

