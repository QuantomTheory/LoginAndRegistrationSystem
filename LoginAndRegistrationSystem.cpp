// LoginAndRegistrationSystem.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Create the Universal Variables
int SystemScreen = 1;
std::string CurrentUser;

// Function to check if the credentials are valid. 
int CheckCredentials(string& InputUsername, string& InputPassword)
{
    cout << "\n\nCheckCredentials\n";

    string StoredUsername, StoredPassword;

    // Attempts to read the credential file with the name of the input Username
    ifstream read("Credentials//" + InputUsername + ".txt");
    getline(read, StoredUsername);
    getline(read, StoredPassword);

    if (InputUsername == StoredUsername && InputPassword == StoredPassword)
    {
        // Returns 0 if the account is found, and the password is valid.
        return 0;
    }
    else if (InputUsername == StoredUsername && InputPassword != StoredPassword)
    {
        // Returns 1 if the account is found, but the password doesn't match.
        return 1;
    }
    else
    {
        // Returns 2 if the account was not found.
        return 2;
    }
}

// This functions displays and recieves input for the Start Screen.
int StartScreen()
{
    // Display the Start Screen menu
    cout << "Do you have an account or would you like to create one?\n";
    cout << "1 - Login to an existing account\n";
    cout << "2 - Create a new account\n";
    cout << "3 - Exit System\n\n";
    cout << "Select Option: ";
    int UserSelection;
    cin >> UserSelection;

    // Checks if the user input was invalid
    while (cin.fail()) 
    {
        cin.clear();
        cin.ignore();
        cout << "Non-Numeric Selection, select a valid option number.\n";
        cin >> UserSelection;
    }

    // Based on the user selection, return the number that will set the next System Screen int.
    switch (UserSelection)
    {
    case 1: return 2; // Returns 2 to navigate to the Log In page

    case 2: return 3; // Returns 3 to navigate to the Register User page

    case 3: return 0; // Returns 0 to close the program

    default:
        cout << "Invalid Selection, select a valid option number.\n"; 
        return 1; // Returns back to the Start Screen again
    }
}

// 
int MainMenu()
{
    // Display the Main Menu
    cout << "\n\nMAIN MENU\n\n";

    cout << "Welcome " + CurrentUser;

    cout << "\n\nSelect an option?\n";
    cout << "1 - Change Password\n";
    cout << "2 - Log Out\n";
    cout << "3 - Exit System\n\n";
    cout << "Select Option: ";
    int UserSelection;
    cin >> UserSelection;

    // Checks if the user input was invalid
    while (cin.fail())
    {
        cin.clear();
        cin.ignore();
        cout << "Non-Numeric Selection, select a valid option number.\n";
        cin >> UserSelection;
    }

    // Based on the user selection, return the number that will set the next System Screen int.
    switch (UserSelection)
    {
    case 1: return 6; // Returns 6 to navigate to the Change Password page

    case 2: return 5; // Returns 5 to navigate to the Log Out page

    case 3: return 0; // Returns 0 to close the program

    default:
        cout << "Invalid Selection, select a valid option number.\n";
        return 4; // Returns back to the Main Menu again
    }
}

// Displays the Log In menu
int LogIn()
{
    cout << "\n\nLOGIN MENU";

    // Repeats the Login Menu until a valid response is created
    bool LoginSuccessful = false;
    while (!LoginSuccessful) 
    {
        cout << "\nPlease enter your credentials (Type 'EXIT' as Username to close program)";
        cout << "\nUsername: ";
        string Username;
        cin >> Username;

        // Exit Program
        if (Username == "EXIT") return 0;

        cout << "Password: ";
        string Password;
        cin >> Password;

        // Run the CheckCredentials funtion.
        switch (CheckCredentials(Username, Password))
        {
        case 0: // Username and Password are both valid
            cout << "\nCredentials Valid";
            CurrentUser = Username;
            LoginSuccessful = true;
            return 4;

        case 1: // Account found, password not valid
            cout << "\nUsername Found, Password does not Match. Try Again...";
            break;

        case 2: // No account found, user asked if they wish to create it.
            cout << "\nCredentials Not Found. Would you like to create an account? (Y/N): ";
            char UserResponse;
            cin >> UserResponse;

            // Checks if the user input was invalid
            while (cin.fail())
            {
                cin.clear();
                cin.ignore();
                cout << "\nInvalid Selection. Would you like to create an account? (Y/N): ";
                char UserResponse;
                cin >> UserResponse;
            }
            if (UserResponse == 'Y' || UserResponse == 'y')
            {
                return 3; // Navigates to the Create User Screen
            }
            else if (UserResponse == 'N' || UserResponse == 'n')
            {
                return 1; // Navigates to the Start Screen
            }
            break;

        default:
            cout << "\nSystem Error";
            return 0; // Closes the program

        }
    }
    
}

// Logs Out of the Current User
int LogOut()
{
    cout << "\n\nLogOut\n";

    // Sets the current user to blank
    CurrentUser = "";

    // Returns 1 to navigate to the Start Screen
    return 1;

}

// This funtion allows the user to create a new account.
int RegisterUser()
{
    cout << "\n\nCREATE ACCOUNT\n";

    bool ChoosingCredentials = true;
    string Username, Password;

    // A loop that repeats until a valid credential set is created, or the program is closed.
    while (ChoosingCredentials)
    {
        cout << "\nPlease enter your desired credentials (Type 'EXIT' as Username to close program)";
        cout << "\nUsername: ";
        cin >> Username;

        // Exit Program
        if (Username == "EXIT") return 0;

        cout << "Password: ";
        cin >> Password;

        // Checks if there is already an account with the supplied username
        ifstream read("Credentials//" + Username + ".txt");
        if (read.is_open())
        {
            cout << "The Username " + Username + " already exists, please chose a different Username...";
        }
        else
        {
            ChoosingCredentials = false;
        }
    }

    // Creates the credential file with the supplied credentials
    ofstream file;
    file.open("Credentials//" + Username + ".txt");

    file << Username << endl << Password;
    file.close();
    cout << "\nAccount Created, please Log In...";

    // Return 2, to navigate to the Log In menu.
    return 2;
}

// A function to allow a logged in user to change tehir password.
int ChangePassword()
{
    cout << "\n\nCHANGE PASSWORD\n";

    string NewPassword;

    cout << "Please enter your new Password: ";
    cin >> NewPassword;

    // Open the credential file of the Current User
    ofstream file;
    file.open(CurrentUser + ".txt");

    // Clear the file of contents are rewrite the username and password into the txt file
    file.clear();
    file << CurrentUser << endl << NewPassword;
    file.close();

    // Return 4, to navigate back to the main menu
    return 4;
}


// The high level navigation structure for the system. All handled from here to avoid convoluted nested funtion calls.
int main()
{
    cout << "Welcome to the Login and Registration System!\n\n";

    // A variable to manage the while loop
    bool SystemOnline = true;

    // a while loop that loops after each finished screen, until the program is closed.
    while (SystemOnline)
    {
        switch (SystemScreen) // Navigates to the currently selected funtion.
        {
        case 0: // Sets the SystemOnline variable to false to end the while loop, closing the program.
            cout << "\n\nEXITING SYSTEM...\n\n";
            SystemOnline = false;
            break;

        case 1: 
            SystemScreen = StartScreen(); // Runs the StartScreen function, and sets it's return value as the next screen to navigate to.
            break;

        case 2:
            SystemScreen = LogIn(); // Runs the LogIn function, and sets it's return value as the next screen to navigate to.
            break;

        case 3:
            SystemScreen = RegisterUser(); // Runs the RegisterUser function, and sets it's return value as the next screen to navigate to.
            break;

        case 4:
            SystemScreen = MainMenu(); // Runs the MainMenu function, and sets it's return value as the next screen to navigate to.
            break;

        case 5:
            SystemScreen = LogOut(); // Runs the LogOut function, and sets it's return value as the next screen to navigate to.
            break;

        case 6:
            SystemScreen = ChangePassword(); // Runs the ChangePassword function, and sets it's return value as the next screen to navigate to.
            break;

        default: // Sets the SystemOnline variable to false to end the while loop, closing the program.
            SystemOnline = false;
            break;

        }
    }

    return 0; // Ends the program
}