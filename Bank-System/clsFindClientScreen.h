#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
#include <iomanip>


class clsFindClientScreen : protected clsScreen
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

    static void ShowFindClientScreen()
    {

        if (!CheckAccessRights(clsUser::enPermissions::pFindClient)) {
            return; //this will exist function because user not have permission to show this page.
        }

        _DrawScreenHeader("\t\t   Find Client Screen");

        string AccountNumber;
        cout << "\n" << setw(37) << left << "" << "Please Enter Account Number: ";
        AccountNumber = clsInputValidate::ReadString();
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\n" << setw(37) << left << "" << "Account Number Is NOT Found, Choose Another One: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);

        if (!Client1.IsEmpty())
        {
            cout << "\n" << setw(37) << left << "" << "==============================================\n";
            cout << "\n" << setw(37) << left << "" << "\t        Client Found :-)\n";
            cout << "\n" << setw(37) << left << "" << "==============================================\n";
        }
        else
        {
            cout << "\n" << setw(37) << left << "" << "==============================================\n";
            cout << "\n" << setw(37) << left << "" << "\t          Client Was not Found :-(\n";
            cout << "\n" << setw(37) << left << "" << "==============================================\n";
        }

        _PrintClient(Client1);

    }


};

