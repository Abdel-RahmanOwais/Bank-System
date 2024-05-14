#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include <iomanip>

class clsTransferScreen : protected clsScreen
{


	static void _PrintClient(clsBankClient Client)
	{
		cout << "\n" << setw(37) << left << "" << "______________________________________________\n";
		cout << "\n" << setw(37) << left << "" << "\t\t  Client Card : ";
		cout << "\n" << setw(37) << left << "" << "______________________________________________";
		cout << "\n" << setw(37) << left << "" << "Full Name      : " << Client.FullName() << endl;
		cout << "\n" << setw(37) << left << "" << "Account Number : " << Client.AccountNumber() << endl;
		cout << "\n" << setw(37) << left << "" << "Balance        : " << Client.AccountBalance << endl;
		cout << setw(37) << left << "" << "______________________________________________\n" << endl;
	}

	static string _ReadAccountNumber(string FromOrTo = "From") {
		string AccountNumber;

		cout << "\n" << setw(37) << left << "" << "Please Enter Account Number To Transfer " << FromOrTo << " : ";
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\n" << setw(37) << left << "" << "Account Number Is NOT Found, Choose Anthor One : ";
			AccountNumber = clsInputValidate::ReadString();
		}

		return AccountNumber;
	}

	static double _ReadAmount(clsBankClient Client) {
		double Amount = 0;

		cout << "\n" << setw(37) << left << "" << "Enter Transfer Amount : \n";
		Amount = clsInputValidate::ReadDbNumber();
		
		while (Amount > Client.AccountBalance) {
			cout << "\n" << setw(37) << left << "" << "Amount Exceeds The Available Balance, Enter Anthor Amount : ";
			Amount = clsInputValidate::ReadDbNumber();
		}
		
		return Amount;
	}

public:

    static void ShowTransferScreen()
    {
        system("cls");

        _DrawScreenHeader("\t\t    Transfer Screen");

		clsBankClient SourceClient = clsBankClient::Find(_ReadAccountNumber());

		_PrintClient(SourceClient);

		clsBankClient DestinaitionClient = clsBankClient::Find(_ReadAccountNumber("To"));

		_PrintClient(DestinaitionClient);

		double Amount = _ReadAmount(SourceClient);

		cout << "\n" << setw(37) << left << "" << "Are You Sure You Want To Perform This Operation [Y] or [N] : ";
		char Answer = 'n';
		cin >> Answer;


		if (Answer == 'y' || Answer == 'Y') {
			
			if (SourceClient.Transfer(Amount, DestinaitionClient, CurrentUser.UserName))
			cout << "\n" << setw(37) << left << "" << "==============================================\n";
			cout << "\n" << setw(37) << left << "" << "\t   Transfer Done Successfully :-)\n";
			cout << "\n" << setw(37) << left << "" << "==============================================\n";
		}
		else {
			cout << "\n" << setw(37) << left << "" << "==============================================\n";
			cout << "\n" << setw(37) << left << "" << "\t       Transfer Was Cancelled\n";
			cout << "\n" << setw(37) << left << "" << "==============================================";
		}

		_PrintClient(SourceClient);
		_PrintClient(DestinaitionClient);

	}

};

