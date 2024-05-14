#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "iomanip"
#include "clsListUsersScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"


class clsMangeUsersScreen : protected clsScreen
{

    enum enManageUsersMenueOptions {
        eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3,
        eUpdateUser = 4, eFindUser = 5, eMainMenue = 6
    };


    static short _ReadManageUsersMenueOption()
    {
        cout << setw(37) << left << "" << "Choose What Do You Want To Do [1] to [6] : ";
        short Choice = clsInputValidate::ReadNumberBetween(1, 6, "\n\t\t\t\t     Erorr, Enter Number Between [1] to [6] : ");
        return Choice;
    }

    static void _GoBackToManageUsersMenue()
    {
        cout << "\n\n" << setw(37) << left << "" << "Press any key to go back to Manage Users Menue...";
        system("pause>0");
        ShowManageUsersMenue();
    }

    static void _ShowListUsersScreen() {
       // cout << "List Users Will Be Here Nearly\n";
    
        clsListUsersScreen::ShowUsersList();
    }
    
    static void _ShowAddNewUserScreen() {
        //cout << "Add New User Will Be Here Nearly\n";
    
        clsAddNewUserScreen::ShowAddNewUserScreen();
    }
    
    static void _ShowDeleteUserScreen() {
        //cout << "Delete User Will Be Here Nearly\n";
    
        clsDeleteUserScreen::ShowDeleteUserScreen();
    }
    
    static void _ShowUpdateUserScreen() {
        //cout << "Update User Will Be Here Nearly\n";
    
        clsUpdateUserScreen::ShowUpdateUserScreen();
    }
    
    static void _ShowFindUserScreen() {
        //cout << "Find User Will Be Here Nearly\n";
    
        clsFindUserScreen::ShowFindUserScreen();
    }

    static void _PerformManageUsersMenueOptions(enManageUsersMenueOptions ManangeUserOptions) {

        switch (ManangeUserOptions)
        {
        case clsMangeUsersScreen::eListUsers:
            system("cls");
            _ShowListUsersScreen();
            _GoBackToManageUsersMenue();
            break;
        case clsMangeUsersScreen::eAddNewUser:
            system("cls");
            _ShowAddNewUserScreen();
            _GoBackToManageUsersMenue();
            break;
        case clsMangeUsersScreen::eDeleteUser:
            system("cls");
            _ShowDeleteUserScreen();
            _GoBackToManageUsersMenue();
            break;
        case clsMangeUsersScreen::eUpdateUser:
            system("cls");
            _ShowUpdateUserScreen();
            _GoBackToManageUsersMenue();
            break;
        case clsMangeUsersScreen::eFindUser:
            system("cls");
            _ShowFindUserScreen();
            _GoBackToManageUsersMenue();
            break;
        case clsMangeUsersScreen::eMainMenue:

            break;
        }
    }

public:


    static void ShowManageUsersMenue()
    {

        system("cls");

        if (!CheckAccessRights(clsUser::enPermissions::pMangeUsers)) {
            return; //this will exist function because user not have permission to show this page.
        }

        _DrawScreenHeader("\t\t  Manage Users Screen");

        cout << setw(37) << left << "" << "==============================================\n";
        cout << setw(37) << left << "" << "\t\t  Manage Users Menue\n";
        cout << setw(37) << left << "" << "==============================================\n";
        cout << setw(37) << left << "" << "\t[1] List Users.\n";
        cout << setw(37) << left << "" << "\t[2] Add New User.\n";
        cout << setw(37) << left << "" << "\t[3] Delete User.\n";
        cout << setw(37) << left << "" << "\t[4] Update User.\n";
        cout << setw(37) << left << "" << "\t[5] Find User.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
        cout << setw(37) << left << "" << "==============================================\n";

        _PerformManageUsersMenueOptions(enManageUsersMenueOptions(_ReadManageUsersMenueOption()));

    }


};

