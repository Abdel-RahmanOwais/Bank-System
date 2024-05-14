#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLoginScreen.h"
#include <iomanip>

class clsTrancactionsScreen : protected clsScreen
{
	enum enTransactionsMenueOptions { eDeposit = 1, eWithdraw = 2, 
		eShowTotalBalance = 3, eShowTransfer = 4, eShowTransferLogin, eShowMainMenue = 6 };


    static short _ReadTransactionsMenueOption()
    {
        cout << setw(37) << left << "" << "Choose What Do You Want To Do [1] to [6] : ";

        short Choice = clsInputValidate::ReadNumberBetween(1, 6, "Erorr, Choose Number Between [1] to [6]");

        return Choice;
    }

    static void _GoBackToTransactionsMenue()
    {
        cout << "\n\t\t\t\t     Press any key to go back to Transactions Menue...";
        system("pause>0");
        ShowTransactionsMenue();

    }
    
    static void _ShowDepositScreen() {
        //cout << "Deposit Screen Will Be Here Nearly :-)" << endl;
        
        clsDepositScreen::ShowDepositScreen();
    }   
    
    static void _ShowWithdrawScreen() {
        //cout << "Withdraw Screen Will Be Here Nearly :-)" << endl;
    
        clsWithdrawScreen::ShowWithdrawScreen();
    }
    
    static void _ShowTotalBalancesScreen() {
        //cout << "Total Balances Screen Will Be Here Nearly :-)" << endl;
        
        clsTotalBalancesScreen::ShowTotalBalances();
    }

    static void _ShowTransferScreen() {
        //cout << "Transfer Screen Will Be Here Nearly :-)" << endl;

        clsTransferScreen::ShowTransferScreen();
    }   
    
    static void _ShowTransferLoginScreen() {
        //cout << "Transfer Login Screen Will Be Here Nearly :-)" << endl;

        clsTransferLoginScreen::ShowTransferLoginScreen();
    }

    static void _PerfromTranactionsMenueOption(enTransactionsMenueOptions TransactionMenueOption)
    {
        switch (TransactionMenueOption)
        {
            case enTransactionsMenueOptions::eDeposit:
            {
                system("cls");
                _ShowDepositScreen();
                _GoBackToTransactionsMenue();
                break;
            }

            case enTransactionsMenueOptions::eWithdraw:
            {
                system("cls");
                _ShowWithdrawScreen();
                _GoBackToTransactionsMenue();
                break;
            }


            case enTransactionsMenueOptions::eShowTotalBalance:
            {
                system("cls");
                _ShowTotalBalancesScreen();
                _GoBackToTransactionsMenue();
                break;
            }
            
            case enTransactionsMenueOptions::eShowTransfer:
            {
                system("cls");
                _ShowTransferScreen();
                _GoBackToTransactionsMenue();
                break;
            }
               
            case enTransactionsMenueOptions::eShowTransferLogin:
            {
                system("cls");
                _ShowTransferLoginScreen();
                _GoBackToTransactionsMenue();
                break;
            }

            case enTransactionsMenueOptions::eShowMainMenue:
            {

                cout << "\n\n";

            }

        }

    }

public:
	
	
   static void ShowTransactionsMenue()
    {
        system("cls");

        if (!CheckAccessRights(clsUser::enPermissions::pTranactions)) {
            return; //this will exist function because user not have permission to show this page.
        }

        _DrawScreenHeader("\t\t Trancactios Menue Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Transactions Menue \n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Deposit\n";
        cout << setw(37) << left << "" << "\t[2] Withdraw\n";
        cout << setw(37) << left << "" << "\t[3] Total Balances\n";
        cout << setw(37) << left << "" << "\t[4] Transfer\n";
        cout << setw(37) << left << "" << "\t[5] Transfer Login\n";
        cout << setw(37) << left << "" << "\t[6] Main Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        _PerfromTranactionsMenueOption((enTransactionsMenueOptions)_ReadTransactionsMenueOption());
    }

};

