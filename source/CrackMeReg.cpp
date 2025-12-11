#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <windows.h>

// Registration algorithm
std::string GenerateRegCode(const std::string& username) {
    if (username.empty()) {
        return "INVALID";
    }
    
    // First stage: simple hash
    unsigned int hash = 0x12345678; // Initial seed
    
    for (size_t i = 0; i < username.length(); i++) {
        hash = (hash << 5) | (hash >> 27); // Rotate left 5
        hash ^= username[i];
        hash += (username[i] * 0x1F) ^ 0xABCDEF;
    }
    
    // Second stage: additional processing
    hash ^= 0xF0F0F0F0;
    hash = ~hash;
    hash = (hash & 0x55555555) << 1 | (hash & 0xAAAAAAAA) >> 1; // Bit swap
    
    // Third stage: final transformation
    hash = hash * 0x9E3779B9;
    hash ^= (hash >> 16);
    
    // Convert to formatted string (XXXX-XXXX-XXXX-XXXX)
    std::stringstream ss;
    ss << std::uppercase << std::setfill('0') << std::setw(8) << std::hex << hash;
    
    std::string part1 = ss.str();
    ss.str("");
    ss << std::uppercase << std::setfill('0') << std::setw(8) << std::hex << (hash ^ 0x87654321);
    std::string part2 = ss.str();
    
    // Format: XXXX-XXXX-XXXX-XXXX
    std::string result;
    result += part1.substr(0, 4) + "-";
    result += part1.substr(4, 4) + "-";
    result += part2.substr(0, 4) + "-";
    result += part2.substr(4, 4);
    
    return result;
}

// Validate registration code
bool ValidateRegCode(const std::string& username, const std::string& regcode) {
    // Clean the input code (remove dashes, convert to uppercase)
    std::string cleanCode = regcode;
    cleanCode.erase(std::remove(cleanCode.begin(), cleanCode.end(), '-'), cleanCode.end());
    std::transform(cleanCode.begin(), cleanCode.end(), cleanCode.begin(), ::toupper);
    
    // Generate expected code
    std::string expected = GenerateRegCode(username);
    std::string expectedClean = expected;
    expectedClean.erase(std::remove(expectedClean.begin(), expectedClean.end(), '-'), expectedClean.end());
    
    // Compare
    return (cleanCode == expectedClean);
}

// Display colored text in console
void PrintColored(const std::string& text, int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
    std::cout << text;
    SetConsoleTextAttribute(hConsole, 7); // Reset to default
}

// Print success message
void PrintSuccess(const std::string& username) {
    std::cout << std::endl;
    PrintColored("╔══════════════════════════════════════════════════╗\n", 10);
    PrintColored("║            REGISTRATION SUCCESSFUL!              ║\n", 10);
    PrintColored("╚══════════════════════════════════════════════════╝\n", 10);
    std::cout << std::endl;
    
    std::cout << "Congratulations, " << username << "!" << std::endl;
    std::cout << "Your software has been successfully registered." << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
}

// Print failure message
void PrintFailure() {
    std::cout << std::endl;
    PrintColored("╔══════════════════════════════════════════════════╗\n", 12);
    PrintColored("║            REGISTRATION FAILED!                  ║\n", 12);
    PrintColored("╚══════════════════════════════════════════════════╝\n", 12);
    std::cout << std::endl;
    
    std::cout << "Invalid registration code!" << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
}

// Print banner
void PrintBanner() {
    PrintColored("\n", 7);
    PrintColored("▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄\n", 11);
    PrintColored("█                                                    █\n", 11);
    PrintColored("█              REGISTRATION CRACKME                  █\n", 11);
    PrintColored("█                 Version 1.0                        █\n", 11);
    PrintColored("█                                                    █\n", 11);
    PrintColored("▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀\n", 11);
    std::cout << std::endl;
    
    std::cout << "Welcome to the Registration Challenge!" << std::endl;
    std::cout << "Enter your username and registration code to unlock" << std::endl;
    std::cout << "the full version of this software." << std::endl;
    std::cout << std::endl;
    std::cout << "Registration code format: XXXX-XXXX-XXXX-XXXX" << std::endl;
    std::cout << "Example: 1A2B-3C4D-5E6F-7890" << std::endl;
    std::cout << std::endl;
}

int main() {
    // Enable UTF-8 for Windows console
    SetConsoleOutputCP(65001);
    // Detect debugger and exit with a popup if present
    if (IsDebuggerPresent()) {
        MessageBoxA(NULL, "Restricted to debug", "Debugger detected", MB_OK | MB_ICONERROR);
        return 1;
    }
    
    std::string username, regcode;
    
    // Print banner
    PrintBanner();
    
    // Get user input
    std::cout << "Enter username: ";
    std::getline(std::cin, username);
    
    // Validate username
    if (username.empty()) {
        PrintColored("Error: Username cannot be empty!\n", 12);
        std::cout << "Press Enter to exit...";
        std::cin.get();
        return 1;
    }
    
    std::cout << "Enter registration code: ";
    std::getline(std::cin, regcode);
    
    // Validate registration code format
    if (regcode.empty()) {
        PrintColored("Error: Registration code cannot be empty!\n", 12);
        std::cout << "Press Enter to exit...";
        std::cin.get();
        return 1;
    }
    
    // Check registration
    if (ValidateRegCode(username, regcode)) {
        PrintSuccess(username);
    } else {
        PrintFailure();
    }
    
    // Wait for user input before exiting
    std::cout << std::endl;
    std::cout << "Press Enter to exit...";
    std::cin.get();
    
    return 0;
}