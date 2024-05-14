#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsBankClient.h"
#include <iomanip>

class clsWithdrawScreen : protected clsScreen
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

    static void ShowWithdrawScreen()
    {

        _DrawScreenHeader("\t\t     Withdraw Screen");

        cout << "\n" << setw(37) << left << "" << "______________________________________________\n";
        cout << "\n" << setw(37) << left << "" << "\t\t        Withdraw ";
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
        cout << "\n" << setw(37) << left << "" << "Please Enter Withdraw Amount : ";
        Amount = clsInputValidate::ReadDbNumber();

        cout << "\n" << setw(37) << left << "" << "Are You Sure You Want To Perform This Trancation [Y] or [N] : ";
        char Answer = 'n';
        cin >> Answer;


        if (Answer == 'y' || Answer == 'Y') {

            if (Client.Withdraw(Amount)) {
                cout << "\n" << setw(37) << left << "" << "==============================================\n";
                cout << "\n" << setw(37) << left << "" << "\t    Amount Withdraw Successfully :-)\n";
                cout << "\n" << setw(37) << left << "" << "\t    Your New Balance NOW Is : " << Client.AccountBalance;
                cout << "\n" << setw(37) << left << "" << "==============================================\n";
            }
            else {
                cout << "\n" << setw(37) << left << "" << "==============================================\n";
                cout << "\n" << setw(37) << left << "" << "\t Can NOT Withdraw, Insuffecient Balance :-(\n";
                cout << "\n" << setw(37) << left << "" << "\t       Amount To Withdraw Is  : " << Amount << endl;
                cout << "\n" << setw(37) << left << "" << "\t       Your Balance Is        : " << Client.AccountBalance;
                cout << "\n" << setw(37) << left << "" << "==============================================\n";
            }
        
        }
        else {
            cout << "\n" << setw(37) << left << "" << "==============================================\n";
            cout << "\n" << setw(37) << left << "" << "\t       Operation Was Cancelled\n";
            cout << "\n" << setw(37) << left << "" << "==============================================";
        }


    }

};

