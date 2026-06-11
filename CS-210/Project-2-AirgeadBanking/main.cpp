// ============================================================================
// File:        main.cpp
// Project:     CS 210 Project Two - Airgead Banking
// Author:      Ziyan Noorani
// Course:      CS 210
// Description: Driver / entry point for the Airgead Banking investment
//              application. Per the Airgead Banking Standards document, main()
//              is intentionally minimal: it gathers and validates user input,
//              instantiates an Investment object, and calls that object's
//              methods to produce the required output. All of the real work
//              (the compound-interest math and report formatting) lives in the
//              Investment class.
// ============================================================================

#include "Investment.h"

#include <iostream>  // std::cin, std::cout
#include <limits>    // std::numeric_limits

// ----------------------------------------------------------------------------
// getValidatedDouble
//   Repeatedly prompts the user until a numeric value is entered. The value
//   must be strictly positive when t_requirePositive is true (used for the
//   initial investment and the interest rate) or non-negative otherwise
//   (used for the monthly deposit, which is allowed to be 0).
//
//   try/catch is used so the program "exits gracefully" on unexpected stream
//   states rather than crashing, per the standards document. assert() is
//   intentionally NOT used.
// ----------------------------------------------------------------------------
double getValidatedDouble(const std::string& t_prompt, bool t_requirePositive)
{
    double value = 0.0;

    while (true)
    {
        try
        {
            std::cout << "  " << t_prompt;
            std::cin  >> value;

            // Detect non-numeric input (cin fails and sets the fail bit).
            if (std::cin.fail())
            {
                std::cin.clear(); // clear the error state
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                                '\n'); // discard the bad input
                throw std::runtime_error(
                    "Invalid input. Please enter a numeric value.");
            }

            // Range checks. Initial investment and interest must be > 0.
            // Monthly deposit may be 0 but never negative.
            if (t_requirePositive && value <= 0.0)
            {
                throw std::runtime_error(
                    "Value must be a positive number greater than 0.");
            }
            if (!t_requirePositive && value < 0.0)
            {
                throw std::runtime_error(
                    "Value cannot be negative.");
            }

            // Input is valid - leave the loop.
            break;
        }
        catch (const std::exception& e)
        {
            std::cout << "  Error: " << e.what() << "\n\n";
        }
    }

    return value;
}

// ----------------------------------------------------------------------------
// getValidatedInt
//   Same idea as getValidatedDouble but for the number of years, which must
//   be a positive whole number.
// ----------------------------------------------------------------------------
int getValidatedInt(const std::string& t_prompt)
{
    int value = 0;

    while (true)
    {
        try
        {
            std::cout << "  " << t_prompt;
            std::cin  >> value;

            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                                '\n');
                throw std::runtime_error(
                    "Invalid input. Please enter a whole number.");
            }

            if (value <= 0)
            {
                throw std::runtime_error(
                    "Number of years must be greater than 0.");
            }

            break;
        }
        catch (const std::exception& e)
        {
            std::cout << "  Error: " << e.what() << "\n\n";
        }
    }

    return value;
}

// ----------------------------------------------------------------------------
// pause - mimics the "Press any key to continue..." prompt from the sample
// displays in a portable, standard C++ way.
// ----------------------------------------------------------------------------
void pause()
{
    std::cout << "\n  Press ENTER to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

// ----------------------------------------------------------------------------
// main - minimal driver.
// ----------------------------------------------------------------------------
int main()
{
    std::cout << "\n  ***************************************************\n";
    std::cout << "  *           Airgead Banking Investment App        *\n";
    std::cout << "  ***************************************************\n\n";

    // ----- Data input screen -----
    std::cout << "  ********** Data Input **********\n\n";

    double initialInvestment =
        getValidatedDouble("Initial Investment Amount: $", true);
    double monthlyDeposit =
        getValidatedDouble("Monthly Deposit: $", false);
    double annualInterest =
        getValidatedDouble("Annual Interest: %", true);
    int numberOfYears =
        getValidatedInt("Number of Years: ");

    // ----- Echo the entered values back, like the sample "Input Values" -----
    std::cout << "\n  ********** Entered Values **********\n";
    std::cout.setf(std::ios::fixed);
    std::cout.precision(2);
    std::cout << "  Initial Investment Amount: $" << initialInvestment << "\n";
    std::cout << "  Monthly Deposit: $"           << monthlyDeposit   << "\n";
    std::cout << "  Annual Interest: %"           << annualInterest   << "\n";
    std::cout << "  Number of Years: "            << numberOfYears    << "\n";

    pause();

    // ----- Create the Investment object and produce the reports -----
    Investment investment(initialInvestment,
                          monthlyDeposit,
                          annualInterest,
                          numberOfYears);

    investment.printWithoutMonthlyDeposits();
    investment.printWithMonthlyDeposits();

    std::cout << "\n  Thank you for using the Airgead Banking app.\n\n";

    return 0;
}
