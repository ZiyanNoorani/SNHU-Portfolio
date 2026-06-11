#ifndef GROCERY_TRACKER_H
#define GROCERY_TRACKER_H

#include <string>
#include <map>

// GroceryTracker
// Reads a list of purchased grocery items from an input file, tallies how
// often each item appears, and reports those frequencies in several formats.
// Demonstrates a class with both public (interface) and private (data) sections.
class GroceryTracker {
public:
    // Constructor: stores the names of the input and backup files.
    GroceryTracker(const std::string& inputFile,
        const std::string& backupFile);

    // Reads the input file and builds the frequency map.
    // Returns true on success, false if the file could not be opened.
    bool LoadDataFromFile();

    // Writes the accumulated frequency data to the backup file (frequency.dat).
    // Called automatically at startup, with no user intervention.
    // Returns true on success, false if the file could not be opened.
    bool BackupDataToFile() const;

    // Returns how many times a single item was purchased.
    // Returns 0 if the item was never purchased.
    int GetFrequencyOfItem(const std::string& item) const;

    // Prints every item paired with its purchase frequency (Menu Option 2).
    void PrintAllFrequencies() const;

    // Prints every item as a text-based histogram of asterisks (Menu Option 3).
    void PrintHistogram() const;

private:
    std::string inputFileName;            // Source data file
    std::string backupFileName;           // Backup data file (frequency.dat)
    std::map<std::string, int> itemFrequencies; // Item name -> purchase count

    // Helper: normalizes capitalization so "Corn" and "corn" tally together.
    static std::string NormalizeCase(const std::string& word);
};

#endif // GROCERY_TRACKER_H