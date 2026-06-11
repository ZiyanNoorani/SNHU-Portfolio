#include "GroceryTracker.h"

#include <fstream>   // ifstream, ofstream
#include <iostream>  // cout
#include <cctype>    // tolower
#include <algorithm> // transform

// Constructor: save the file names supplied by the caller.
GroceryTracker::GroceryTracker(const std::string& inputFile,
    const std::string& backupFile)
    : inputFileName(inputFile), backupFileName(backupFile) {
}

// Convert a word to a consistent capitalization (first letter upper, rest lower)
// so that differences in case do not create duplicate entries.
std::string GroceryTracker::NormalizeCase(const std::string& word) {
    std::string result = word;
    std::transform(result.begin(), result.end(), result.begin(),
        [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    if (!result.empty()) {
        result[0] = static_cast<char>(std::toupper(static_cast<unsigned char>(result[0])));
    }
    return result;
}

// Open the input file and count each item as it is read.
bool GroceryTracker::LoadDataFromFile() {
    std::ifstream inputStream(inputFileName);
    if (!inputStream.is_open()) {
        return false; // Caller reports the error to the user.
    }

    std::string item;
    // Reading word-by-word handles one item per line as well as
    // multiple items separated by spaces.
    while (inputStream >> item) {
        ++itemFrequencies[NormalizeCase(item)];
    }

    inputStream.close();
    return true;
}

// Save every item and its count to the backup file (frequency.dat).
bool GroceryTracker::BackupDataToFile() const {
    std::ofstream outputStream(backupFileName);
    if (!outputStream.is_open()) {
        return false;
    }

    for (const auto& entry : itemFrequencies) {
        outputStream << entry.first << " " << entry.second << "\n";
    }

    outputStream.close();
    return true;
}

// Look up a single item. map::find avoids inserting a missing key.
int GroceryTracker::GetFrequencyOfItem(const std::string& item) const {
    auto it = itemFrequencies.find(NormalizeCase(item));
    if (it == itemFrequencies.end()) {
        return 0;
    }
    return it->second;
}

// Print every item with its numeric frequency.
void GroceryTracker::PrintAllFrequencies() const {
    std::cout << "\nItem Purchase Frequencies\n";
    std::cout << "-------------------------\n";
    for (const auto& entry : itemFrequencies) {
        std::cout << entry.first << " " << entry.second << "\n";
    }
}

// Print every item as a histogram, using one asterisk per purchase.
void GroceryTracker::PrintHistogram() const {
    std::cout << "\nItem Purchase Histogram\n";
    std::cout << "-----------------------\n";
    for (const auto& entry : itemFrequencies) {
        std::cout << entry.first << " ";
        for (int i = 0; i < entry.second; ++i) {
            std::cout << "*";
        }
        std::cout << "\n";
    }
}