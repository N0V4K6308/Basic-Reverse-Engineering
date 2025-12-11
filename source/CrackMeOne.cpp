#include <iostream>
#include <string>
using namespace std;

// Function to check if credentials are valid
bool checkCredentials(const string& username, const string& password) {
    // Hardcoded valid credentials
    const string validUsername = "admin";
    const string validPassword = "secret123";
    
    return (username == validUsername && password == validPassword);
}

// Function to display success message
void showSuccess() {
    cout << "\n=== SUCCESS! ===" << endl;
    cout << "Congratulations! You entered the correct credentials." << endl;
    cout << "CrackMeOne has been successfully completed!" << endl;
}

// Function to display error message
void showError() {
    cout << "\n=== ERROR! ===" << endl;
    cout << "Invalid username or password. Access denied!" << endl;
    cout << "Try again or reverse engineer this program to find the correct credentials." << endl;
}

int main() {
    string username, password;
    
    // Display banner
    cout << "===================================" << endl;
    cout << "        CrackMeOne v1.0" << endl;
    cout << "    Basic Reverse Engineering Challenge" << endl;
    cout << "===================================" << endl;
    cout << endl;
    
    // Get user input
    cout << "Enter username: ";
    getline(cin, username);
    
    cout << "Enter password: ";
    getline(cin, password);
    
    // Check credentials
    if (checkCredentials(username, password)) {
        showSuccess();
    } else {
        showError();
    }
    
    // Pause before exit
    cout << "\nPress Enter to exit...";
    cin.get();
    
    return 0;
}