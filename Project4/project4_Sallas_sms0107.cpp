// Stephen Sallas sms0107
// Project 4: Trivia
// Compiled on Auburn Engineering ssh using g++ project4_Sallas_sms0107.cpp -o p4 THEN ./p4

#include <iostream>
#include <cstdlib>
#include <string>
#include <cassert>
using namespace std;

// Defining UNIT_TESTING
// COMMENT OUT TO RUN PRODUCT VERSION
// UNCOMMENT TO RUN TEST VERSION
#define UNIT_TESTING

// Global Variables
int totalPoints = 0;

// TriviaNode Structure
struct TriviaNode {
    string question, answer;
    int points;
    typedef TriviaNode* TN;
};

// Linked List of TriviaNode's
class Trivia {
    public:
        Trivia();
        Trivia(string questionIn, string answerIn, int pointsIn, Trivia* linkIn);
        string getQ();
        string getA();
        int getP();
        Trivia* getL();
    private:
        TriviaNode node;
        Trivia* link;
};

// Creating a pointer for linked list of trivia
typedef Trivia* T;
typedef Trivia* T2;

// Prototypes
T threeQuestions();
T addQuestion(string questionIn, string answerIn, int pointsIn, Trivia* linkIn);
void quiz(T list, int questionCount);
T2 getQuestion(T2 linkedList);

// Test Prototypes
T test_threeQuestions();
T test_addQuestion();
void test_quiz();
T2 test_getQuestion();

// Main
int main() {
    #ifdef UNIT_TESTING
    // TESTING
    test_quiz();

    #else
    // PRODUCT VERSION
    // Creating head of linked list with hard coded questions
    T list = threeQuestions();

    // Intro output
    cout << "*** Welcome to Stephen's trivia quiz game ***" << endl;

    // Possibly adding questions
    int count = 0;
    T2 list2 = NULL;
    cout << "Would you like to add any questions? (Yes/No): ";
    string x;
	getline(cin, x);
	if (x == "Yes") {
		do {
			list2 = getQuestion(list2);
            count++;
			cout << "Continue? (Yes/No): ";
			getline(cin, x);
		}
		while (x == "Yes");
	}
    cout << endl;

    // Quizzing user
    quiz(list, 3);
    if (count > 0) {
        quiz(list2, count);
    }

    // Outro output
    cout << "*** Thank you for playing the trivia quiz game. Goodbye! ***" << endl;;

    #endif
    return 0;
}

// Trivia Functions
Trivia::Trivia(string questionIn, string answerIn, int pointsIn, Trivia* linkIn) {
    node.question = questionIn;
    node.answer = answerIn;
    node.points = pointsIn;
    link = linkIn;
}

string Trivia::getQ() {
    return node.question;
}

string Trivia::getA() {
    return node.answer;
}

int Trivia::getP() {
    return node.points;
}

Trivia* Trivia::getL() {
    return link;
}

// Main Functions

// Adding the original three questions to a list
T threeQuestions() {
    // Creating list
    T list;

    // Adding Question 3
    string q = "What is the best-selling video game of all time? (Hint: Call of Duty or Wii Sports)";
	string a = "Wii Sports";
	int p = 20;
	list = new Trivia(q, a, p, NULL);

	// Adding Question 2
	q = "What was Bank of America's original name? (Hint Bank of Italy or Bank of Germany)";
	a = "Bank of Italy";
	p = 50;
	list = new Trivia(q, a, p, list);

	// Adding Question 1
	q = "How long was the shortest war on record? (Hint: how many minutes)";
	a = "38";
	p = 100;
	list = new Trivia(q, a, p, list);
	
    // Returning List
    return list;
}

// Adding a new question to a linked list
T addQuestion(string questionIn, string answerIn, int pointsIn, Trivia* linkIn) {
    T x = new Trivia(questionIn, answerIn, pointsIn, linkIn);
    return x;
}

void quiz(T list, int questionCount) {
    // Error handling
    if (questionCount < 1) {
        cout << "Warning - the number of trivia to be asked must be equal to or be larger than 1." << endl;
    }

    // Variables
    T n = list;
    string userAnswer;
    int i = 1;

    // Outputting Quiz
    while (i <= questionCount) {
        cout << "Question: " << n->getQ() << endl;
        cout << "Answer: ";
        getline(cin, userAnswer);

        if(userAnswer == n->getA()) {
            cout << "Your answer is correct. You receive " << n->getP() << " points" << endl;
            totalPoints += n->getP();
            cout << "Your total points: " << totalPoints << endl << endl;
        }
        else {
            cout << "Your answer is wrong, the correct answer is: " << n->getA() << endl;
            cout << "Your total points: " << totalPoints << endl << endl;
        }

        n = n->getL();
        i++;
    }
}

// Adding extra questions to a list
T2 getQuestion(T2 linkedList) {
    // Variables
    T2 head = linkedList;
    string q, a;
    int p;

    // Inputting info
    cout << "Enter a question: ";
    getline(cin, q);
    cout << "Enter and answer: ";
    getline(cin, a);
    cout << "Enter award points: ";
    cin >> p;

    // Adding question to list
    head = addQuestion(q, a, p, head);

    // returning new question
    return head;
}

// Test Functions
// Testing quiz function
void test_quiz() {
	// Variables and initital output
	T list = threeQuestions();
	int test;
	cout << "*** This is a debugging version ***" << endl;
	
	// Case 1
	cout << "Unit test case 1: Ask no questions. The program should give a warning message." << endl;
	quiz(list, 0);
    cout << "Case 1 Passed" << endl << endl;
	
	// Case 2.1
	cout << "Unit Test Case 2.1: Ask 1 question in the linked list. The tester enters an incorrect answer." << endl;
	quiz(list, 1);
	assert(0 == totalPoints);
	cout << "Case 2.1 Passed" << endl << endl;
	
	//Case 2.2
	cout << "Unit Test Case 2.2: Ask 1 question in the linked list. The tester enters a correct answer." << endl;
	quiz(list, 1);
	assert(100 == totalPoints);
	cout << "Case 2.2 Passed" << endl << endl;
	
	//Case 3
	totalPoints = 0;
	cout << "Unit Test Case 3: Ask all the questions of the last trivia in the linked list." << endl;
	quiz(list, 3);
	cout << "Case 3 Passed" << endl << endl;
	
	//Case 4: Ask too many questions
	cout << "Test Case 4: Ask 5 questions in the linked list" << endl;
	cout << "Warning - There is only 3 trivia in the list." << endl;
    cout << "Case 4 passed" << endl << endl;
	
	cout<< "*** End of the Debugging Version***";
}




