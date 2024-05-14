#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include <iomanip>

class clsDepositScreen : protected clsScreen
{


    static string _ReadAccountNumber()
    {
        string AccountNumber = "";

        cout << "\n" << setw(37) << left << "" << "Please Enter Account Number : ";
        cin >> AccountNumber;

        return AccountNumber;
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

    static void ShowDepositScreen()
    {

        _DrawScreenHeader("\t\t       Dopsit Screen");

        cout << "\n" << setw(37) << left << "" << "______________________________________________\n";
        cout << "\n" << setw(37) << left << "" << "\t\t          Deposit ";
        cout << "\n" << setw(37) << left << "" << "______________________________________________\n";

        string AccountNumber = _ReadAccountNumber();


        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\n" << setw(37) << left << "" << "Client With [" << AccountNumber << "] Does NOT Exist.\n";
            AccountNumber = _ReadAccountNumber();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);

        double Amount = 0;
        cout << "\n" << setw(37) << left << "" << "Please Enter Deposit Amount : ";
        Amount = clsInputValidate::ReadDbNumber();

        cout << "\n" << setw(37) << left << "" << "Are You Sure You Want To Perform This Trancation [Y] or [N] : ";
        char Answer = 'n';
        cin >> Answer;


        if (Answer == 'y' || Answer == 'Y') {
            Client.Deposit(Amount);
            cout << "\n" << setw(37) << left << "" << "==============================================\n";
            cout << "\n" << setw(37) << left << "" << "\t    Amount Deposit Successfully :-)\n";
            cout << "\n" << setw(37) << left << "" << "\t    Your New Balance NOW Is : " << Client.AccountBalance;
            cout << "\n" << setw(37) << left << "" << "==============================================\n";
        }
        else {
            cout << "\n" << setw(37) << left << "" << "==============================================\n";
            cout << "\n" << setw(37) << left << "" << "\t       Operation Was Cancelled\n";
            cout << "\n" << setw(37) << left << "" << "==============================================";
        }


    }
};

