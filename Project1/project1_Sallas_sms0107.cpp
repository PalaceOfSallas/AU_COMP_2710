// Stephen Sallas sms0107
// Project 1: Loan Calculator
// I used Visual Studio Code to create and compile this program.

#include <iostream>
using namespace std;

int main() {
    // Variables
    float loanAmount, interestRate, interestRateDec, monthlyPayments, payment, interest, principal;
    float totalInterest = 0;
    int currentMonth = 0;
    bool insufficient;

    // Currency Formatting
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);

    // Loan Amount Input
    // Must be positive
    cout << "\nLoan Amount: ";
    cin >> loanAmount;

    while (loanAmount < 0) {
        cout << "\nLoan Amount: ";
        cin >> loanAmount;
    }

    // Interest Rate Input
    // Must be positive
    cout << "Interest Rate (% per year): ";
    cin >> interestRate;

    while (interestRate < 0) {
        cout << "Interest Rate (% per year): ";
        cin >> interestRate;
    }

    // Interest Rate Adjustments
    interestRate /= 12;
    interestRateDec = interestRate / 100;

    // Monthly Payment Input
    // Must be positive and sufficient
    cout << "Monthly Payments: ";
    cin >> monthlyPayments;

    if (((loanAmount + (loanAmount * interestRateDec)) - monthlyPayments) >= loanAmount) {
        insufficient = true;
    }
    else {
        insufficient = false;
    }

    while ((monthlyPayments < 0) || insufficient){
        cout << "Monthly Payments: ";
        cin >> monthlyPayments;

        if (((loanAmount + (loanAmount * interestRateDec)) - monthlyPayments) >= loanAmount) {
            insufficient = true;
        }
        else {
            insufficient = false;
        }
    }
    cout << endl;

    // Amortization Table
    cout << "*****************************************************************\n"  
         << "\tAmortization Table\n"
         << "*****************************************************************\n"
         << "Month\tBalance\t\tPayment\tRate\tInterest\tPrincipal\n";

    // Filling Table
    while (loanAmount > 0) {
        if (currentMonth == 0) {
            cout << currentMonth++ << "\t$" << loanAmount;
            if (loanAmount < 1000) cout << "\t";
            cout << "\t" << "N/A\tN/A\tN/A\t\tN/A\n";
        }

        else {
            // Calculating Interest and Updating Total Interest
            interest = loanAmount * interestRateDec;
            totalInterest += interest;

            // Calculating Principal
            if (monthlyPayments < loanAmount) {
                principal = monthlyPayments - interest;
            }
            else {
                principal = loanAmount;
            }

            // Calculating Payment
            payment = interest + principal;

            // Calculating Balance
            loanAmount -= principal;

            // Outputting Table
            cout << currentMonth++ << "\t$" << loanAmount;
            if (loanAmount < 1000) cout << "\t";
            cout << "\t$" << payment << "\t" << interestRate <<  "\t$" << interest << "\t\t$" << principal << endl;
        }
    }
    
    cout << "****************************************************************\n";
    cout << "\nIt takes " << -- currentMonth <<  " months to pay off the loan.\n"
         << "Total interest paid is: $" << totalInterest << endl << endl;
    return 0;
}
