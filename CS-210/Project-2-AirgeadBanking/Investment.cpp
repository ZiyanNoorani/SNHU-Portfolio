// ============================================================================
// File:        Investment.cpp
// Project:     CS 210 Project Two - Airgead Banking
// Description: Implementation (body) of the Investment class declared in
//              Investment.h. Contains the compound-interest math and the
//              formatted report output.
//
// Calculation notes:
//   Interest is compounded MONTHLY. The monthly rate is the annual
//   percentage rate divided by 100 (to convert percent to a fraction)
//   and then divided by 12 (to convert annual to monthly).
//
//   For each month:
//       interest      = (openingBalance + monthlyDeposit) * monthlyRate
//       closingBalance = openingBalance + monthlyDeposit + interest
//
//   The "without monthly deposits" report uses the same logic with the
//   monthly deposit treated as 0. Year-end earned interest is the sum of
//   the twelve monthly interest amounts for that year.
//
//   This approach reproduces the sample output in the project images:
//     - $1.00 initial, $0 monthly, 5% annual, 5 years -> Year 1 = $1.05
//     - $1.00 initial, $50 monthly, 5% annual, 5 years -> Year 1 = $617.55
// ============================================================================

#include "Investment.h"

#include <iostream>  // std::cout
#include <iomanip>   // std::setw, std::fixed, std::setprecision

// ----------------------------------------------------------------------------
// Default constructor - safe zero initialization.
// ----------------------------------------------------------------------------
Investment::Investment()
    : m_initialInvestment(0.0),
      m_monthlyDeposit(0.0),
      m_annualInterest(0.0),
      m_numberOfYears(0)
{
}

// ----------------------------------------------------------------------------
// Parameterized constructor.
// ----------------------------------------------------------------------------
Investment::Investment(double t_initialInvestment,
                       double t_monthlyDeposit,
                       double t_annualInterest,
                       int t_numberOfYears)
    : m_initialInvestment(t_initialInvestment),
      m_monthlyDeposit(t_monthlyDeposit),
      m_annualInterest(t_annualInterest),
      m_numberOfYears(t_numberOfYears)
{
}

// ----------------------------------------------------------------------------
// Setters
// ----------------------------------------------------------------------------
void Investment::setInitialInvestment(double t_initialInvestment)
{
    m_initialInvestment = t_initialInvestment;
}

void Investment::setMonthlyDeposit(double t_monthlyDeposit)
{
    m_monthlyDeposit = t_monthlyDeposit;
}

void Investment::setAnnualInterest(double t_annualInterest)
{
    m_annualInterest = t_annualInterest;
}

void Investment::setNumberOfYears(int t_numberOfYears)
{
    m_numberOfYears = t_numberOfYears;
}

// ----------------------------------------------------------------------------
// Getters
// ----------------------------------------------------------------------------
double Investment::getInitialInvestment() const
{
    return m_initialInvestment;
}

double Investment::getMonthlyDeposit() const
{
    return m_monthlyDeposit;
}

double Investment::getAnnualInterest() const
{
    return m_annualInterest;
}

int Investment::getNumberOfYears() const
{
    return m_numberOfYears;
}

// ----------------------------------------------------------------------------
// printReport - private helper that builds and prints one report table.
// Shared by both public report methods so the formatting logic exists in
// exactly one place (maintainability / refactor guidance).
// ----------------------------------------------------------------------------
void Investment::printReport(const char* t_title, bool t_includeMonthly) const
{
    // Convert the annual percentage rate into a per-month fraction.
    // Example: 5 -> 5/100 = 0.05 annual -> 0.05/12 monthly.
    double monthlyRate = (m_annualInterest / 100.0) / 12.0;

    // The deposit that is actually applied each month. When the report is
    // the "no additional deposits" version, this is forced to zero.
    double monthlyDeposit = t_includeMonthly ? m_monthlyDeposit : 0.0;

    // Running balance starts at the opening principal.
    double balance = m_initialInvestment;

    // ----- Table header -----
    std::cout << "\n  ===========================================================\n";
    std::cout << "   " << t_title << "\n";
    std::cout << "  ===========================================================\n";
    std::cout << "  " << std::left << std::setw(8) << "Year"
              << std::right << std::setw(20) << "Year End Balance"
              << std::setw(28) << "Year End Earned Interest" << "\n";
    std::cout << "  -----------------------------------------------------------\n";

    // Use fixed-point notation with two decimal places for currency.
    std::cout << std::fixed << std::setprecision(2);

    // ----- Year loop -----
    for (int year = 1; year <= m_numberOfYears; ++year)
    {
        // Accumulates the twelve monthly interest amounts for this year.
        double yearlyInterest = 0.0;

        // ----- Month loop (interest compounds monthly) -----
        for (int month = 1; month <= 12; ++month)
        {
            // Add this month's deposit before interest is applied.
            double openingPlusDeposit = balance + monthlyDeposit;

            // Interest earned this month on the deposited balance.
            double monthlyInterest = openingPlusDeposit * monthlyRate;

            // Roll the interest into the balance and track it for the year.
            balance = openingPlusDeposit + monthlyInterest;
            yearlyInterest += monthlyInterest;
        }

        // ----- Print the row for this year -----
        std::cout << "  " << std::left << std::setw(8) << year
                  << std::right << std::setw(13) << "$ "
                  << std::setw(7) << balance
                  << std::setw(21) << "$ "
                  << std::setw(7) << yearlyInterest << "\n";
    }

    std::cout << "  ===========================================================\n";
}

// ----------------------------------------------------------------------------
// Public report: WITHOUT additional monthly deposits.
// ----------------------------------------------------------------------------
void Investment::printWithoutMonthlyDeposits() const
{
    printReport("Balance and Interest Without Additional Monthly Deposits",
                false);
}

// ----------------------------------------------------------------------------
// Public report: WITH additional monthly deposits.
// ----------------------------------------------------------------------------
void Investment::printWithMonthlyDeposits() const
{
    printReport("Balance and Interest With Additional Monthly Deposits",
                true);
}
