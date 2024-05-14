#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include <iomanip>


class clsTransferLoginScreen : protected clsScreen
{


    static void _PrintTransferLogRecordLine(clsBankClient::stTransferLogin Client)
    {

        cout << setw(8) << left << "" << "| " << setw(23) << left << Client.DateTime;
        cout << "| " << setw(8) << left << Client.ClientAccountNumber;
        cout << "| " << setw(8) << left << Client.DestinationClientAccountNumber;
        cout << "| " << setw(8) << left << Client.Amount;
        cout << "| " << setw(10) << left << Client.ClientBalance;
        cout << "| " << setw(10) << left << Client.DestinationClientBalance;
        cout << "| " << setw(8) << left << Client.UserName;
    }


public:

    static void ShowTransferLoginScreen() {

        vector <clsBankClient::stTransferLogin> vTransferLogRecord = clsBankClient::GetTransferLoginList();

        _DrawScreenHeader("\t\t Show Transfer Login Screen",
            "\t\t    (" + to_string(vTransferLogRecord.size()) + ") Login Register(s).");



        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(23) << "Date/Time";
        cout << "| " << left << setw(8) << "s.Acct";
        cout << "| " << left << setw(8) << "d.Acct";
        cout << "| " << left << setw(8) << "Amount";
        cout << "| " << left << setw(10) << "s.Balance";
        cout << "| " << left << setw(10) << "d.Balance";
        cout << "| " << left << setw(8) << "User";

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vTransferLogRecord.size() == 0)
            cout << "\t\t\t\t\t  No Transfers Available In the System!";
        else

            for (clsBankClient::stTransferLogin &Record : vTransferLogRecord)
            {

                _PrintTransferLogRecordLine(Record);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }

};

