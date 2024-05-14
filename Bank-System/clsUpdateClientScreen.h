#pragma once
#include <iostream> 
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsBankClient.h"
#include <iomanip>

using namespace std;

class clsUpdateClientScreen : protected clsScreen
{


	static void _ReadClientInfo(clsBankClient& Client) {
		cout << "\n" << setw(37) << left << "" << "Enter First Name : ";
		Client.FirstName = clsInputValidate::ReadString();

		cout << "\n" << setw(37) << left << "" << "Enter Last Name  : ";
		Client.LastName = clsInputValidate::ReadString();

		cout << "\n" << setw(37) << left << "" << "Enter Email      : ";
		Client.Email = clsInputValidate::ReadString();

		cout << "\n" << setw(37) << left << "" << "Enter Phone      : ";
		Client.Phone = clsInputValidate::ReadString();

		cout << "\n" << setw(37) << left << "" << "Enter Pin Code   : ";
		Client.PinCode = clsInputValidate::ReadString();

		cout << "\n" << setw(37) << left << "" << "Enter Balance    : ";
		Client.AccountBalance = clsInputValidate::ReadDbNumber();

	}

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

	static void ShowUpdateClientScreen() {

		if (!CheckAccessRights(clsUser::enPermissions::pUpdateClients)) {
			return; //this will exist function because user not have permission to show this page.
		}

		_DrawScreenHeader("\t\t Update Client Screen");

		cout << "\n" << setw(37) << left << "" << "Please Enter Your Account Number : ";
		string AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber)) {
			cout << "\n" << setw(37) << left << "" << "Account Number Is NOT Found, Choose Anthor One : ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClient(Client);

		cout << "\n" << setw(37) << left << "" << "Update Client Information : " << endl;
		cout << "\n" << setw(37) << left << "" << "______________________________________________\n" << endl;

		_ReadClientInfo(Client);

		clsBankClient::enSaveResults SaveResult;
		SaveResult = Client.Save();

		switch (SaveResult)
		{
		case clsBankClient::svFalidEmptyObject:

			cout << "\n" << setw(37) << left << "" << "Error Account Was NOT Saved Because It's Empty :-(\n";
			break;
		case clsBankClient::svSucceeded:
			cout << "\n" << setw(37) << left << "" << "==============================================\n";
			cout << "\n" << setw(37) << left << "" << "\t     Account Updated Successfully :-)\n";
			cout << "\n" << setw(37) << left << "" << "==============================================\n";
			_PrintClient(Client);
			break;
		}
	}

};

