#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsClientsListScreen.h"
#include "clsAddNewClientsScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTrancactionsScreen.h"
#include "clsMangeUsersScreen.h"
#include "clsShowLoginRegisterScreen.h"
#include "clsCurrencyExchangeMainScreen.h"
#include "Global.h"

using namespace std;

class clsMainScreen : clsScreen
{
private:

    enum enMainMenueChoice {
        eClientsList = 1, eAddNewClient = 2,
        eDeleteClient = 3, eUpdateClient = 4,
        eFindClient = 5, eTransactionsMenue = 6,
        eMangeUsers = 7, eLoginRegister = 8, CurrencyExchange = 9, eExit = 10
    };

    static short _ReadMainMenueOption() {
        cout << setw(37) << left << "" << "Please Choose Number Between [1] to [10] : ";
        short Chois = clsInputValidate::ReadNumberBetween(1, 10, "\n\t\t\t\t     Erorr, You Must Chois Number Between [1] to [10] : ");

        return Chois;
    }
    
    static void _GoBackToMainMenue() {
        cout << "\n\t\t\t\t     Press any key to go back in main meune...";
        system("pause>0");
        ShowMainMeune();
    }
 
    static void _ShowClientsListScreen() {
        //cout << "Client List will came back nearly" << endl << endl;

        clsClientsListScreen::ShowClientsList();
    }   
    
    static void _ShowAddNewClientScreen() {
        //cout << "Add new client will came back nearly" << endl << endl;
    
        clsAddNewClientsScreen::ShowAddNewClientScreen();
    } 
    
    static void _ShowDeleteClientScreen() {
        //cout << "Delete client will came back nearly" << endl << endl;
        
        clsDeleteClientScreen::ShowDeleteClientScreen();
    }    
    
    static void _ShowUpdateClientScreen() {
        //cout << "Update client will came back nearly" << endl << endl;
    
        clsUpdateClientScreen::ShowUpdateClientScreen();
    }  
    
    static void _ShowFindClientScreen() {
        //cout << "Find client will came back nearly" << endl << endl;
    
        clsFindClientScreen::ShowFindClientScreen();
    }
      
    static void _ShowTransactionsMenueScreen() {
       //cout << "Transactions menue will came back nearly" << endl << endl;
    
        clsTrancactionsScreen::ShowTransactionsMenue();
    }  
    
    static void _ShowMangeUsersScreen() {
        //cout << "Mange users will came back nearly" << endl << endl;

        clsMangeUsersScreen::ShowManageUsersMenue();
    }
    
    static void _ShowLoginRegister() {
        //cout << "Login Register will came nearly." << endl << endl;

        clsShowLoginRegisterScreen::ShowLoginRegisterScreen();
    }

    static void _ShowCurrencyExchange() {
        //cout << "Currency Exchange will came nearly." << endl << endl;

        clsCurrencyExchangeMainScreen::ShowMainCurrencyExchange();
    }

    /*  static void _ShowExitScreen() {
        cout << "Exit will came back nearly" << endl << endl;
    }*/

    static void _Logout() {
        CurrentUser = clsUser::Find("", "");

    }


    static void _PerformMainMenueOption(enMainMenueChoice MainMenueOptions) {
        switch (MainMenueOptions)
        {
        case clsMainScreen::eClientsList:
             system("cls");
            _ShowClientsListScreen();
            _GoBackToMainMenue();
            break;
        case clsMainScreen::eAddNewClient:
             system("cls");
            _ShowAddNewClientScreen();
            _GoBackToMainMenue();
            break;
        case clsMainScreen::eDeleteClient:
             system("cls");
            _ShowDeleteClientScreen();
            _GoBackToMainMenue();
            break;
        case clsMainScreen::eUpdateClient:
             system("cls");
            _ShowUpdateClientScreen();
            _GoBackToMainMenue();
            break;
        case clsMainScreen::eFindClient:
             system("cls");
            _ShowFindClientScreen();
            _GoBackToMainMenue();
            break;
        case clsMainScreen::eTransactionsMenue:
             system("cls");
            _ShowTransactionsMenueScreen();
            _GoBackToMainMenue();
            break;
        case clsMainScreen::eMangeUsers:
            system("cls");
            _ShowMangeUsersScreen();
            _GoBackToMainMenue();
            break;
        case clsMainScreen::eLoginRegister:
            system("cls");
            _ShowLoginRegister();
            _GoBackToMainMenue();
        case clsMainScreen::CurrencyExchange:
            system("cls");
            _ShowCurrencyExchange();
            _GoBackToMainMenue();
        case clsMainScreen::eExit:
            system("cls");
            _Logout();
            break;
        }

    }


public:

	static void ShowMainMeune() {
        system("cls");
        
		_DrawScreenHeader("\t\t   Main Menue Screen");

        cout << setw(37) << left << "" << "==============================================\n";
        cout << setw(37) << left << "" << "\t\t       Main Menue" << endl;
        cout << setw(37) << left << "" << "==============================================\n";
        cout << setw(37) << left << "" << "\t[1] Show Client List\n";
        cout << setw(37) << left << "" << "\t[2] Add New Client\n";
        cout << setw(37) << left << "" << "\t[3] Delete Client\n";
        cout << setw(37) << left << "" << "\t[4] Update Client Info\n";
        cout << setw(37) << left << "" << "\t[5] Find Client\n";
        cout << setw(37) << left << "" << "\t[6] Transactions\n";
        cout << setw(37) << left << "" << "\t[7] Mange Users\n";
        cout << setw(37) << left << "" << "\t[8] Show Login Register\n";
        cout << setw(37) << left << "" << "\t[9] Currency Exchange\n";
        cout << setw(37) << left << "" << "\t[10] Logout\n";
        cout << setw(37) << left << "" << "==============================================\n";
	
        _PerformMainMenueOption(enMainMenueChoice(_ReadMainMenueOption()));
    }
};

