/*
 * File:   ChadaTech_Clocks.cpp
 * Author: Ziyan Noorani
 * Course: CS-210 Programming Languages
 * Date:   5/13/2026
 *
 * Description: Chada Tech dual-clock application that displays a 12-hour and
 *              24-hour clock simultaneously and allows the user to add hours,
 *              minutes, or seconds via an interactive menu. Meets ISO 8601
 *              international time-display requirements.
 */

#include <iostream>
#include <iomanip>   // setw, setfill
#include <string>
#include <sstream>   // ostringstream for formatted time strings
#include <limits>    // numeric_limits (input validation)

using namespace std;

// ---------------------------------------------------------------------------
// Constants
// ---------------------------------------------------------------------------
const int HOURS_IN_DAY    = 24;
const int MINS_IN_HOUR    = 60;
const int SECS_IN_MIN     = 60;
const int CLOCK_WIDTH     = 26; // width of one clock display box
const int BORDER_CHAR_CNT = 26; // number of '*' chars per border row

// ---------------------------------------------------------------------------
// Struct: ClockTime
//   Stores hours, minutes, and seconds in 24-hour internal representation.
//   All display formatting is derived from these values.
// ---------------------------------------------------------------------------
struct ClockTime {
    int hours;    // 0-23
    int minutes;  // 0-59
    int seconds;  // 0-59
};

// ---------------------------------------------------------------------------
// Function: buildBorderRow
//   Returns a string of BORDER_CHAR_CNT asterisks (e.g. "**************************")
// ---------------------------------------------------------------------------
string buildBorderRow() {
    return string(BORDER_CHAR_CNT, '*');
}

// ---------------------------------------------------------------------------
// Function: twoDigit
//   Returns an integer formatted as a zero-padded two-digit string.
//   Example: twoDigit(5) -> "05"
// ---------------------------------------------------------------------------
string twoDigit(int value) {
    ostringstream oss;
    oss << setw(2) << setfill('0') << value;
    return oss.str();
}

// ---------------------------------------------------------------------------
// Function: format12Hour
//   Converts a ClockTime (24-hour internal) to a 12-hour formatted string.
//   Example: {15, 22, 1} -> "03:22:01 PM"
// ---------------------------------------------------------------------------
string format12Hour(const ClockTime& t) {
    string period = (t.hours < 12) ? "AM" : "PM"; // determine AM or PM
    int displayHour = t.hours % 12;                // convert to 12-hour base
    if (displayHour == 0) displayHour = 12;        // midnight/noon edge case

    return twoDigit(displayHour) + ":" +
           twoDigit(t.minutes)   + ":" +
           twoDigit(t.seconds)   + " " + period;
}

// ---------------------------------------------------------------------------
// Function: format24Hour
//   Converts a ClockTime to a 24-hour formatted string.
//   Example: {15, 22, 1} -> "15:22:01"
// ---------------------------------------------------------------------------
string format24Hour(const ClockTime& t) {
    return twoDigit(t.hours)   + ":" +
           twoDigit(t.minutes) + ":" +
           twoDigit(t.seconds);
}

// ---------------------------------------------------------------------------
// Function: buildClockRow
//   Centers a label string inside a clock box row.
//   Example: buildClockRow("12-Hour Clock") -> "*      12-Hour Clock      *"
// ---------------------------------------------------------------------------
string buildClockRow(const string& label) {
    // Total inner width = CLOCK_WIDTH - 2 (for leading/trailing '*')
    int innerWidth = CLOCK_WIDTH - 2;
    int padding    = (innerWidth - (int)label.size()) / 2;
    int extra      = (innerWidth - (int)label.size()) % 2; // handle odd lengths

    return "*" + string(padding, ' ') + label +
           string(padding + extra, ' ') + "*";
}

// ---------------------------------------------------------------------------
// Function: displayClocks
//   Renders both the 12-hour and 24-hour clocks side by side to the console.
//   Follows the Chada Tech functional requirements layout exactly.
// ---------------------------------------------------------------------------
void displayClocks(const ClockTime& t) {
    string border   = buildBorderRow();
    string time12   = format12Hour(t);
    string time24   = format24Hour(t);

    cout << "\n";
    // Row 1: top borders
    cout << border << "    " << border << "\n";
    // Row 2: clock labels
    cout << buildClockRow("12-Hour Clock") << "    "
         << buildClockRow("24-Hour Clock") << "\n";
    // Row 3: time values
    cout << buildClockRow(time12) << "    "
         << buildClockRow(time24) << "\n";
    // Row 4: bottom borders
    cout << border << "    " << border << "\n";
}

// ---------------------------------------------------------------------------
// Function: displayMenu
//   Prints the interactive user menu.
// ---------------------------------------------------------------------------
void displayMenu() {
    string border = buildBorderRow();
    cout << "\n" << border << "\n";
    cout << buildClockRow("1 - Add One Hour")   << "\n";
    cout << buildClockRow("2 - Add One Minute") << "\n";
    cout << buildClockRow("3 - Add One Second") << "\n";
    cout << buildClockRow("4 - Exit Program")   << "\n";
    cout << border << "\n";
    cout << "Enter your choice: ";
}

// ---------------------------------------------------------------------------
// Function: addHour
//   Adds one hour to the clock, wrapping at 23 back to 0.
// ---------------------------------------------------------------------------
void addHour(ClockTime& t) {
    t.hours = (t.hours + 1) % HOURS_IN_DAY;
}

// ---------------------------------------------------------------------------
// Function: addMinute
//   Adds one minute to the clock, rolling over into hours when needed.
// ---------------------------------------------------------------------------
void addMinute(ClockTime& t) {
    t.minutes++;
    if (t.minutes >= MINS_IN_HOUR) {
        t.minutes = 0;
        addHour(t); // carry into hours
    }
}

// ---------------------------------------------------------------------------
// Function: addSecond
//   Adds one second to the clock, rolling over into minutes when needed.
// ---------------------------------------------------------------------------
void addSecond(ClockTime& t) {
    t.seconds++;
    if (t.seconds >= SECS_IN_MIN) {
        t.seconds = 0;
        addMinute(t); // carry into minutes
    }
}

// ---------------------------------------------------------------------------
// Function: getInitialTime
//   Prompts the user for an initial time, validates input, and returns a
//   ClockTime struct populated with the entered values.
// ---------------------------------------------------------------------------
ClockTime getInitialTime() {
    ClockTime t;

    cout << "==============================\n";
    cout << "  Chada Tech Clock Setup\n";
    cout << "==============================\n";
    cout << "Enter initial time (24-hour format):\n";

    // -- Hours --
    while (true) {
        cout << "  Hour   (0-23): ";
        cin  >> t.hours;
        // Reject bad input or out-of-range values
        if (cin.fail() || t.hours < 0 || t.hours > 23) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  Invalid input. Please enter a whole number between 0 and 23.\n";
        } else {
            break;
        }
    }

    // -- Minutes --
    while (true) {
        cout << "  Minute (0-59): ";
        cin  >> t.minutes;
        if (cin.fail() || t.minutes < 0 || t.minutes > 59) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  Invalid input. Please enter a whole number between 0 and 59.\n";
        } else {
            break;
        }
    }

    // -- Seconds --
    while (true) {
        cout << "  Second (0-59): ";
        cin  >> t.seconds;
        if (cin.fail() || t.seconds < 0 || t.seconds > 59) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  Invalid input. Please enter a whole number between 0 and 59.\n";
        } else {
            break;
        }
    }

    return t;
}

// ---------------------------------------------------------------------------
// Function: processMenuSelection
//   Reads a menu choice, executes the corresponding action on the clock,
//   and returns false when the user chooses to exit; true otherwise.
// ---------------------------------------------------------------------------
bool processMenuSelection(ClockTime& t) {
    int choice;
    cin >> choice;

    // Guard against non-integer input
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter 1, 2, 3, or 4.\n";
        return true; // stay in loop
    }

    switch (choice) {
        case 1:
            addHour(t);
            displayClocks(t);
            break;
        case 2:
            addMinute(t);
            displayClocks(t);
            break;
        case 3:
            addSecond(t);
            displayClocks(t);
            break;
        case 4:
            cout << "\nExiting Chada Tech Clocks. Goodbye!\n";
            return false; // signal to exit loop
        default:
            cout << "Invalid choice. Please enter 1, 2, 3, or 4.\n";
            break;
    }

    return true; // continue loop
}

// ---------------------------------------------------------------------------
// Function: runClockApp
//   Orchestrates the full clock application:
//     1. Collect initial time from user
//     2. Display clocks
//     3. Loop: show menu -> process selection -> display updated clocks
// ---------------------------------------------------------------------------
void runClockApp() {
    // Step 1 - Get initial time from user
    ClockTime currentTime = getInitialTime();

    // Step 2 - Show clocks with the initial time entered
    displayClocks(currentTime);

    // Step 3 - Main loop: menu -> action -> display (matches flowchart)
    bool keepRunning = true;
    while (keepRunning) {
        displayMenu();
        keepRunning = processMenuSelection(currentTime);
    }
}

// ---------------------------------------------------------------------------
// main()
//   Entry point - kept minimal per project requirements.
//   All logic is delegated to runClockApp().
// ---------------------------------------------------------------------------
int main() {
    runClockApp();
    return 0;
}
