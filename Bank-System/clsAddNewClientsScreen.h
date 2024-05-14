#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
#include <iomanip>

using namespace std;

class clsAddNewClientsScreen : protected clsScreen
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

	static void ShowAddNewClientScreen() {
		if (!CheckAccessRights(clsUser::enPermissions::pAddNewClient)) {
			return; //this will exist function because user not have permission to show this page.
		}

		_DrawScreenHeader("\t\t  Add New Client Screen");

		cout << "\n" << setw(37) << left << "" << "Please Enter Account Number : ";
		string AccountNumber = clsInputValidate::ReadString();

		while (clsBankClient::IsClientExist(AccountNumber)) {
			cout << "\n" << setw(37) << left << "" << "Account Number Is Already Used, Choose Anthor One : ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);

		cout << "\n" << setw(37) << left << "" << "===============================================";
		cout << setw(37) << left << "" << "\t\t\t\t\t\t   Add New Client : " << endl;
		cout << setw(37) << left << "" << "===============================================\n";

		_ReadClientInfo(NewClient);

		clsBankClient::enSaveResults SaveResult;
		SaveResult = NewClient.Save();

		switch (SaveResult)
		{
		case clsBankClient::svSucceeded:
			cout << "\n" << setw(37) << left << "" << "==============================================\n";
			cout << "\n" << setw(37) << left << "" << "\t       Account Added Successfully :-)\n";
			cout << "\n" << setw(37) << left << "" << "==============================================\n";
			_PrintClient(NewClient);
			break;

		case clsBankClient::svFalidEmptyObject:

			cout << "\nError Account Was NOT Saved Because It's Empty :-(\n";
			break;

		case clsBankClient::svFailedAccountNumberExsit:
			cout << "\nError Account Was NOT Saved Because Account Number Is Already Used :-(\n";
		}


	}




};

