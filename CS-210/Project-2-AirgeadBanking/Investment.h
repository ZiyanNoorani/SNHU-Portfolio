// ============================================================================
// File:        Investment.h
// Project:     CS 210 Project Two - Airgead Banking
// Description: Class prototype for the Investment class. This class models a
//              compound-interest investment and is responsible for storing the
//              investment parameters and calculating year-end balances and
//              earned interest, both with and without additional monthly
//              deposits.
//
// Standards:   Follows the Airgead Banking Standards document:
//                - #define include guard using <PROJECT>_<PATH>_<FILE>_H_
//                - Types start with upper case (Investment)
//                - Functions/variables use camel case
//                - Private member data uses the m_ prefix
//                - Function parameters use the t_ prefix
//                - Class prototype lives in this .h file; the body lives in
//                  the matching .cpp file
// ============================================================================

#ifndef AIRGEAD_BANKING_INVESTMENT_H_
#define AIRGEAD_BANKING_INVESTMENT_H_

// The Investment class encapsulates all data and behavior required to
// project the growth of an investment over a number of years.
class Investment
{
public:
    // ------------------------------------------------------------------
    // Constructors
    // ------------------------------------------------------------------

    // Default constructor. Initializes all members to safe zero values.
    Investment();

    // Parameterized constructor. Allows the investment to be created with
    // all required values in a single call.
    //   t_initialInvestment - the opening principal amount
    //   t_monthlyDeposit     - the recurring monthly contribution
    //   t_annualInterest     - the annual interest rate as a percentage
    //   t_numberOfYears      - the length of the investment in years
    Investment(double t_initialInvestment,
               double t_monthlyDeposit,
               double t_annualInterest,
               int t_numberOfYears);

    // ------------------------------------------------------------------
    // Setters - each validates its argument by way of the caller, but
    // these mutators allow the data to be updated after construction.
    // ------------------------------------------------------------------
    void setInitialInvestment(double t_initialInvestment);
    void setMonthlyDeposit(double t_monthlyDeposit);
    void setAnnualInterest(double t_annualInterest);
    void setNumberOfYears(int t_numberOfYears);

    // ------------------------------------------------------------------
    // Getters - return values for observation. Simple value returns are
    // used here because the returned types are inexpensive built-in types.
    // ------------------------------------------------------------------
    double getInitialInvestment() const;
    double getMonthlyDeposit() const;
    double getAnnualInterest() const;
    int    getNumberOfYears() const;

    // ------------------------------------------------------------------
    // Reporting behavior
    // ------------------------------------------------------------------

    // Prints the year-by-year balance and earned interest table WITHOUT
    // any additional monthly deposits.
    void printWithoutMonthlyDeposits() const;

    // Prints the year-by-year balance and earned interest table WITH the
    // additional monthly deposit applied each month.
    void printWithMonthlyDeposits() const;

private:
    // ------------------------------------------------------------------
    // Private member data. The m_ prefix distinguishes member data from
    // local variables and parameters, per the Airgead standards.
    // ------------------------------------------------------------------
    double m_initialInvestment; // opening principal amount
    double m_monthlyDeposit;    // recurring monthly contribution
    double m_annualInterest;    // annual interest rate (as a percentage)
    int    m_numberOfYears;     // duration of the investment in years

    // ------------------------------------------------------------------
    // Private helper. Prints a formatted report table. Pulling the shared
    // table logic into one helper avoids duplicated code between the
    // "with" and "without" monthly-deposit reports (refactor for
    // maintainability, per the standards document).
    //   t_title          - heading printed above the table
    //   t_includeMonthly - when true, the monthly deposit is added each
    //                       month before interest is applied
    // ------------------------------------------------------------------
    void printReport(const char* t_title, bool t_includeMonthly) const;
};

#endif // AIRGEAD_BANKING_INVESTMENT_H_
