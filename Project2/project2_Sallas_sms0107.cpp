// Stephen Sallas sms0107
// Project 2: Target Accuracy
// Compiled on Auburn Engineering ssh using g++ project2_Sallas_sms0107.cpp -o p2 THEN ./p2

#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <ctime>
using namespace std;

/**************************************************************************************/
/**************************** Global Variables ****************************************/
/**************************************************************************************/
int aWins = 0;
int bWins = 0;
int cWins = 0;


/**************************************************************************************/
/**************************** Prototypes **********************************************/
/**************************************************************************************/
bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive);
/* Input: A_alive indicates whether Aaron is alive */
/*        B_alive indicates whether Bob is alive */
/*        C_alive indicates whether Charlie is alive */
/* Return: true if at least two are alive */ 
/*         otherwise return false */

void Aaron_shoots1(bool& B_alive, bool& C_alive);
/* Strategy 1: Use call by reference
 * Input: B_alive indicates whether Bob alive or dead
 *  	  C_alive indicates whether Charlie is alive or dead.
 * Return: Change B_alive into false if Bob is killed.
 *		   Change C_alive into false if Charlie is killed. */

void Bob_shoots(bool& A_alive, bool& C_alive);
/* Call by reference
 * Input: A_alive indicates if Aaron is alive or dead
 *		   C_alive indicates whether Charlie is alive or dead
 * Return: Change A_alive into false if Aaron is killed.
 *			Change C_alive into false if Charlie is killed. */

void Charlie_shoots(bool& A_alive, bool& B_alive);
/* Call by reference
 * Input: A_alive indicates if Aaron is alive or dead
 * 		  B_alive indicates if Bob is alive or dead
 * Return: Change A_alive into false if Aaron is killed
 *		   Change B_alive into false if Bob is killed */
 
void Aaron_shoots2(bool& B_alive, bool& C_alive);
/* Strategy 2: Use call by reference
 * Input: B_alive indicates whether Bob is alive or dead
 *		  C_alive indicates whether Charlie is alive or dead
 * Return: Change B_alive into false if Bob is killed
 *		   Change C_alive into false if Charlie is killed */
 
void strategy1(void);
/* Duel Stretegy 1 
 * Input: N/A
 * Return: Change global variables aWins, bWins, and cWins.
 * Uses Strategy 1 */
 
 void strategy2(void);
/* Duel Strategy 2
 * Input: N/A
 * Return: Change global variables aWins, bWins, and cWins.
 * Uses Strategy 2 */


/**************************************************************************************/
/**************************** Test Prototypes *****************************************/
/**************************************************************************************/
void atleast_two_alive_test(void);
/* This is a test driver for at_least_two_alive() */

void Aaron_shoots1_test(void);
/* This is a test driver for Aaron_shoots1() */

void Bob_shoots_test(void);
/* This is a test driver for Bob_shoots() */

void Charlie_shoots_test(void);
/* This is a test driver for Charlie_shoots() */

void Aaron_shoots2_test(void);
/* This is a test driver for Aaron_shoots() */


/**************************************************************************************/
/**************************** Main  ***************************************************/
/**************************************************************************************/
int main() {
    // Initializing Constant and Random Seed
    const int NUM_DUELS = 10000;
    srand(time(0));

    // Formatting
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);

    // Intro Message 
    cout << "*** Welcome to Stephen's Duel Simulator ***\n";

    // Running Tests
    atleast_two_alive_test();
    cout << "Press any key to continue...";
    cin.ignore().get();
    Aaron_shoots1_test();
	cout << "Press any key to continue...";
	cin.ignore().get(); 
	Bob_shoots_test();
	cout << "Press any key to continue...";
	cin.ignore().get(); 
	Charlie_shoots_test();
	cout << "Press any key to continue...";
	cin.ignore().get(); 
	Aaron_shoots2_test();
	cout << "Press any key to continue...";
	cin.ignore().get();

    // Simulating Strategy1 10000 times
    cout << "Ready to test strategy 1 (run 10000 times):\n";
    cout << "Press any key to continue...";
    cin.ignore().get();
    aWins = 0;
    bWins = 0;
    cWins = 0;
    for (int i = 0; i <= NUM_DUELS; i++) {
        strategy1();
    }
    // Calculating results
    double aWinPercentage = (double)aWins / 10000.0 * 100.0;
    double bWinPercentage = (double)bWins / 10000.0 * 100.0;
    double cWinPercentage = (double)cWins / 10000.0 * 100.0;
    // Outputting Results
    cout << "Aaron won " << aWins << "/10000 duels or " << aWinPercentage << "%\n";
    cout << "Bob won " << bWins << "/10000 duels or " << bWinPercentage << "%\n";
    cout << "Charlie won " << cWins << "/10000 duels or " << cWinPercentage << "%\n\n";

    // Simulating Strategy2 10000 times
    cout << "Ready to test strategy 2 (run 10000 times):\n";
    cout << "Press any key to continue...";
    cin.ignore().get();
    aWins = 0;
    bWins = 0;
    cWins = 0;
    for (int i = 0; i <= NUM_DUELS; i++) {
        strategy2();
    }
    // Calculating results
    double aWinPercentage2 = (double)aWins / 10000.0 * 100.0;
    double bWinPercentage2 = (double)bWins / 10000.0 * 100.0;
    double cWinPercentage2 = (double)cWins / 10000.0 * 100.0;
    // Outputting Results
    cout << "Aaron won " << aWins << "/10000 duels or " << aWinPercentage2 << "%\n";
    cout << "Bob won " << bWins << "/10000 duels or " << bWinPercentage2 << "%\n";
    cout << "Charlie won " << cWins << "/10000 duels or " << cWinPercentage2 << "%\n\n";

    if (aWinPercentage2 > aWinPercentage) {
        cout << "Strategy 2 is better than straegy 1.\n";
    }
    else {
        cout << "Strategy 1 is better than straegy 2.\n";
    }
}

/**************************************************************************************/
/**************************** Functions  **********************************************/
/**************************************************************************************/
bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive){
    // First seeing if A and another are alive
    if (A_alive) {
        if (B_alive || C_alive) {
            return true;
        }
    }

    // Checking B and C if A is dead
    if (B_alive && C_alive) {
        return true;
    }

    // Returning false because two must be dead at this point
    return false;
}


void Aaron_shoots1(bool& B_alive, bool& C_alive){
    // Constant percentage A hits the target
    const int A_PROB = 33;

    // Randomly finding if he hit the target
    int shoot_target_result;
    shoot_target_result = rand()%100;
    if (shoot_target_result <= A_PROB) {
        // Shooting the most accurate shooter
        if (C_alive) {
            C_alive = false;
        }
        else {
            B_alive = false;
        }
    }
}


void Bob_shoots(bool& A_alive, bool& C_alive){
    // Constant percentage A hits the target
    const int B_PROB = 50;

    // Randomly finding if he hit the target
    int shoot_target_result;
    shoot_target_result = rand()%100;
    if (shoot_target_result <= B_PROB) {
        // Shooting the most accurate shooter
        if (C_alive) {
            C_alive = false;
        }
        else {
            A_alive = false;
        }
    }
}


void Charlie_shoots(bool& A_alive, bool& B_alive){
    // C never misses
    if (B_alive) {
        B_alive = false;
    }
    else {
        A_alive = false;
    }
}

 
void Aaron_shoots2(bool& B_alive, bool& C_alive){
    // This is for strategy two so A must skip the first round
    // This means either B or C must be dead before A shoots
    // This is because B might hit C, but C never misses

    // Constant percentage A hits the target
    const int A_PROB = 33;

    // Randomly finding if he hit the target
    int shoot_target_result;
    if (!B_alive || !C_alive) {
        shoot_target_result = rand()%100; 
        if (shoot_target_result <= 33) {
            // Shoot at the most accurate
            if (C_alive){
                C_alive = false;
            }
            else {
                B_alive = false;
            }
        }
    }
    
}

 
void strategy1(){
    // Make sure everyone starts alive
    bool A_alive = true;
    bool B_alive = true;
    bool C_alive = true;

    // Loop until only one is alive
    while (at_least_two_alive(A_alive, B_alive, C_alive)) {
        if (A_alive) {
            Aaron_shoots1(B_alive, C_alive);
        }
        if (B_alive) {
            Bob_shoots(A_alive, C_alive);
        }
        if(C_alive) {
            Charlie_shoots(A_alive, B_alive);
        }
    }

    // Add up wins
    if (A_alive) {
		aWins++;
	}
	else if (B_alive) {
		bWins++;
	}
	else {
		cWins++;
	}

}

void strategy2(){
    // Make sure everyone starts alive
    bool A_alive = true;
    bool B_alive = true;
    bool C_alive = true;

    // Loop until only one is alive
    while (at_least_two_alive(A_alive, B_alive, C_alive)) {
        if (A_alive) {
            Aaron_shoots2(B_alive, C_alive);
        }
        if (B_alive) {
            Bob_shoots(A_alive, C_alive);
        }
        if(C_alive) {
            Charlie_shoots(A_alive, B_alive);
        }
    }

    // Add up wins
    if (A_alive) {
		aWins++;
	}
	else if (B_alive) {
		bWins++;
	}
	else {
		cWins++;
	}
}

/**************************************************************************************/
/**************************** Testing  ************************************************/
/**************************************************************************************/
void atleast_two_alive_test(){
    cout << "Unit Testing 1: Function - at_least_two_alive()\n";
	
	cout<< "\tCase 1: Aaron alive, Bob alive, Charlie alive\n";
	assert(true == at_least_two_alive(true, true, true));
	cout << "\tCase passed...\n";
	
	cout<< "\tCase 2: Aaron dead, Bob alive, Charlie alive\n";
	assert(true == at_least_two_alive(false, true, true));
	cout << "\tCase passed...\n";
	
	cout<< "\tCase 3: Aaron alive, Bob dead, Charlie alive\n";
	assert(true == at_least_two_alive(true, false, true));
	cout << "\tCase passed...\n";
	
	cout<< "\tCase 4: Aaron alive, Bob alive, Charlie dead\n";
	assert(true == at_least_two_alive(true, true, false));
	cout << "\tCase passed...\n";
	
	cout<< "\tCase 5: Aaron dead, Bob dead, Charlie alive\n";
	assert(false == at_least_two_alive(false, false, true));
	cout << "\tCase passed...\n";
	
	cout<< "\tCase 6: Aaron dead, Bob alive, Charlie dead\n";
	assert(false == at_least_two_alive(false, true, false));
	cout << "\tCase passed...\n";
	
	cout<< "\tCase 7: Aaron alive, Bob dead, Charlie dead\n";
	assert(false == at_least_two_alive(true, false, false));
	cout << "\tCase passed...\n";
	
	cout<< "\tCase 8: Aaron dead, Bob dead, Charlie dead\n";
	assert(false == at_least_two_alive(false, false, false));
	cout << "\tCase passed...\n";
}


void Aaron_shoots1_test(){
    cout << "Unit Test 2: Function Aaron_shoots1(Bob_alive, Charlie_alive)\n";

    // Testing when B and C are alive
    bool B_alive_2 = true;
    bool C_alive_2 = true;
    cout << "\tCase 1: Bob alive, Charlie alive\n";
	cout << "\t\tAaron is shooting at Charlie\n";
    Aaron_shoots1(B_alive_2, C_alive_2);
    // B must be alive because A always shoots at C
    assert(true == B_alive_2);

    // Testing when B is dead and C is alive
    B_alive_2 = false;
    C_alive_2 = true;
    cout << "\tCase 2: Bob dead, Charlie alive\n";
	cout << "\t\tAaron is shooting at Charlie\n";
    // B must be dead
    Aaron_shoots1(B_alive_2, C_alive_2);
    assert(false == B_alive_2);

    // Testing when B is alive and C is dead
    B_alive_2 = true;
    C_alive_2 = false;
    cout << "\tCase 3: Bob alive, Charlie dead\n";
	cout << "\t\tAaron is shooting at Bob\n";
    // C must be dead
    Aaron_shoots1(B_alive_2, C_alive_2);
    assert(false == C_alive_2);
}

void Bob_shoots_test(){
    cout << "Unit Testing 3: Function Bob_shoots(Aaron_alive, Charlie_alive)\n";

    // Testing when A and C are alive
    bool A_alive_2 = true;
    bool C_alive_2 = true;
    cout << "\tCase 1: Aaron alive, Charlie alive\n";
	cout << "\t\tBob is shooting at Charlie\n";
    Bob_shoots(A_alive_2, C_alive_2);
    // B must be alive because A always shoots at C
    assert(true == A_alive_2);

    // Testing when A is dead and C is alive
    A_alive_2 = false;
    C_alive_2 = true;
    cout << "\tCase 2: Aaron dead, Charlie alive\n";
	cout << "\t\tBob is shooting at Charlie\n";
    Bob_shoots(A_alive_2, C_alive_2);
    // A must be dead
    assert(false == A_alive_2);

    // Testing when A is alive and C is dead
    A_alive_2 = true;
    C_alive_2 = false;
    cout << "\tCase 3: Aaron alive, Charlie dead\n";
	cout << "\t\tBob is shooting at Aaron\n";
    // C must be dead
    Bob_shoots(A_alive_2, C_alive_2);
    assert(false == C_alive_2);
    
}

void Charlie_shoots_test(){
    cout << "Unit Testing 4: Function Charlie_shoots(Aaron_alive, Bob_alive)\n";
    
    // Testing when A and B are alive
    bool A_alive_2 = true;
    bool B_alive_2 = true;
    cout << "\tCase 1: Aaron alive, Bob alive\n";
	cout << "\t\tCharlie is shooting at Bob\n";
    Charlie_shoots(A_alive_2, B_alive_2);
    // A must be alive because C always shoots at B
    assert(true == A_alive_2);
    assert(false == B_alive_2);

    // Testing when A is dead and B is alive
    A_alive_2 = false;
    B_alive_2 = true;
    cout << "\tCase 2: Aaron dead, Bob alive\n";
	cout << "\t\tCharlie is shooting at Bob\n";
    Charlie_shoots(A_alive_2, B_alive_2);
    // A and B must be dead
    assert(false == A_alive_2);
    assert(false == B_alive_2);

    // Testing when A is alive and B is dead
    A_alive_2 = true;
    B_alive_2 = false;
    cout << "\tCase 3: Aaron alive, Bob dead\n";
	cout << "\t\tCharlie is shooting at Aaron\n";
    // A and B must be dead
    Charlie_shoots(A_alive_2, B_alive_2);
    assert(false == B_alive_2);
    assert(false == A_alive_2);
    
}

void Aaron_shoots2_test(){
    cout << "Unit Testing 5: Function Aaron_shoots2(Bob_alive, Charlie_alive)\n";

     // Testing when B and C are alive
    bool B_alive_2 = true;
    bool C_alive_2 = true;
    cout << "\tCase 1: Bob alive, Charlie alive\n";
	cout << "\t\tAaron intentionally misses his first shot\n";
    Aaron_shoots2(B_alive_2, C_alive_2);
    // B and C must be alive
    assert(true == B_alive_2);
    assert(true == B_alive_2);
    cout << "\t\tBoth Bob and Charlie are alive.\n";

    // Testing when B is dead and C is alive
    B_alive_2 = false;
    C_alive_2 = true;
    cout << "\tCase 2: Bob dead, Charlie alive\n";
	cout << "\t\tAaron is shooting at Charlie\n";
    // B must be dead
    Aaron_shoots2(B_alive_2, C_alive_2);
    assert(false == B_alive_2);

    // Testing when B is alive and C is dead
    B_alive_2 = true;
    C_alive_2 = false;
    cout << "\tCase 3: Bob alive, Charlie dead\n";
	cout << "\t\tAaron is shooting at Bob\n";
    // C must be dead
    Aaron_shoots2(B_alive_2, C_alive_2);
    assert(false == C_alive_2);

}