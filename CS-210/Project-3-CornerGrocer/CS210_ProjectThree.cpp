// main.cpp
// CS-210 Project Three: Corner Grocer item-tracking program.
// Displays a menu that lets the user query item purchase frequencies,
// list all frequencies, view a histogram, or exit. A backup data file
// (frequency.dat) is written automatically at startup.

#include "GroceryTracker.h"

#include <iostream>  // cout, cin
#include <limits>    // numeric_limits
#include <string>

// Display the menu options to the user.
void DisplayMenu() {
    std::cout << "\n===== Corner Grocer Item Tracker =====\n";
    std::cout << "1. Look up the frequency of a specific item\n";
    std::cout << "2. Print the frequency of all items\n";
    std::cout << "3. Print a histogram of all item frequencies\n";
    std::cout << "4. Exit the program\n";
    std::cout << "Enter your choice (1-4): ";
}

// Read a validated integer menu choice from the user.
// Re-prompts on non-numeric input or values outside 1-4.
int GetMenuChoice() {
    int choice = 0;
    while (true) {
        if (std::cin >> choice && choice >= 1 && choice <= 4) {
            return choice;
        }
        // Invalid input: clear the error state and discard the bad line.
        std::cout << "Invalid choice. Please enter a number from 1 to 4: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

int main() {
    // File names defined by the assignment.
    const std::string inputFileName = "CS210_Project_Three_Input_File.txt";
    const std::string backupFileName = "frequency.dat";

    GroceryTracker tracker(inputFileName, backupFileName);

    // Load the purchase data before doing anything else.
    if (!tracker.LoadDataFromFile()) {
        std::cout << "Error: could not open the input file \""
            << inputFileName << "\".\n";
        return 1; // Cannot continue without data.
    }

    // Create the backup file automatically, without user intervention.
    if (!tracker.BackupDataToFile()) {
        std::cout << "Warning: could not create the backup file \""
            << backupFileName << "\".\n";
    }

    int choice = 0;
    do {
        DisplayMenu();
        choice = GetMenuChoice();

        switch (choice) {
        case 1: {
            // Menu Option One: frequency of a single item.
            std::cout << "Enter the item to look up: ";
            std::string item;
            std::cin >> item;
            int count = tracker.GetFrequencyOfItem(item);
            std::cout << item << " was purchased " << count << " time(s).\n";
            break;
        }
        case 2:
            // Menu Option Two: all item frequencies.
            tracker.PrintAllFrequencies();
            break;
        case 3:
            // Menu Option Three: histogram of all items.
            tracker.PrintHistogram();
            break;
        case 4:
            // Menu Option Four: exit.
            std::cout << "Exiting the program. Goodbye!\n";
            break;
        }
    } while (choice != 4);

    return 0;
}