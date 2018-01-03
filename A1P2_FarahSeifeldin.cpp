//FARAH SEIF EL-DIN - 900160195
//ASSIGNMENT 1
//Problem 2: A Simple Calculator Program

#include <iostream>
#include <string>
#include "Stackt.h"
using namespace std;

//returns a value that represents the priority of an operator
//the bigger the value the higher the priority
int precedence(char oper) {
	switch (oper) {
	case '+':
	case '-':
		return 1;
		break;
	case '*':
	case '/':
		return 2;
		break;
	}
}

// pops everything in the stack until it is empty or until it pops a '('
// after each pop, the popped value is concatinated to the postfix string
void popAll(Stackt <char> &s, string &postfix) {

	if (!s.stackempty()) {
		char popped;
		s.pop(popped);
		while (popped != '(' && !s.stackempty()) {
			postfix += popped;
			s.pop(popped);
		}
	}
}

// deals with + or - operators and adds them to the postfix correctly
void popPlus(Stackt <char> &s, string &postfix, char pORm) {

	if (!s.stackempty()) {
		char top;
		s.seeTop(top);
		while (top != '(' && !s.stackempty()) {
			if (precedence(top) > precedence(pORm)) {
				s.pop(top);
				postfix += top;
				if(!s.stackempty())
				s.seeTop(top);
			}
			else if (precedence(top) == precedence(pORm)) {
				s.pop(top);
				postfix += top;
				top = '(';
			}
		}
	}
	s.push(pORm);
}

// deals with * or / operators, and adds them to the correct location in the postfix string
void popMultp(Stackt <char> &s, string &postfix, char mORd) {

	char top;
	if (!s.stackempty()) {
		s.seeTop(top);
		if (precedence(top) < precedence(mORd))
			s.push(mORd);
		else if (precedence(top) == precedence(mORd)) {
			s.pop(top);
			postfix += top;
			s.push(mORd);
		}
		else s.push(mORd);
	}
	else s.push(mORd);
	
}

// pops everything out of the stack till its empty 
//and concatinates every popped value to the postfix string 
void popFinal(Stackt <char> &s, string &postfix) {

	char popped;
	while (!s.stackempty()) {
		s.pop(popped);
		postfix += popped;
	}
}

// converts from infix to postfix
// returns the postfix string
string convert_toPost(string infix) {

	int i = 0;
	Stackt <char> precedence;
	string postfix = "";

	while (i<infix.size()) {

		switch (infix[i]) {
		case '(':
			precedence.push('(');
			break;
		case ')':
			popAll(precedence,postfix);
			break;
		case '+':
		case '-':
			popPlus(precedence, postfix, infix[i]);
			break;
		case '*':
		case '/':
			popMultp(precedence, postfix, infix[i]);
			break;
		default:
			postfix += infix[i];
			break;

		}
		i++;
	}
	popFinal(precedence, postfix);
	return postfix;
}

//pops the topmost 2 operands from the stack when it encounters an operator
void popOperands(Stackt <double> &operands, char o) {

	// initialize them to zero incase the user types -3+4 (starts with a '-' sign)
	double n1=0, n2 = 0;
	if (!operands.stackempty()) {
		
		operands.pop(n2);
		if(!operands.stackempty())
		operands.pop(n1);
	}
	
	
	// switch to see which operator is in char o and treat the operands accordingly
	switch (o) {
	case '+':
		operands.push(n1 + n2);
		break;
	case '-':
		operands.push(n1 - n2);
		break;
	case '*':
		operands.push(n1 * n2);
		break;
	case '/':
		operands.push(n1 / n2);
		break;
	default:
		break;

	}

	
}

// evaluates a postfix string and returns the result
double evaluate(string postfix) {
	// index counter
	int i = 0;
	// result will contain the final result of evaluating the expression
	double result = 0;

	//create a stack to push the operands in it
	Stackt <double> operands;

	// parse each char in the string and switch on its value
	while (i < postfix.size()) {

		switch (postfix[i]) {

		// if postfix[i] is an operator then you pop the 2 topmost operands from the stack
		// and perform the specified operation on them
		case '+':
		case '-':
		case '*':
		case '/':
			popOperands(operands, postfix[i]);
		break;

		//in case any of the paranthesis were mismatched in the infix
		// and stayed in the postfix, this will help get rid of them
		case '(':
		case ')':
			break;

		// if postfix[i] is neither an operator nor paranthesis, then it is definitely an operand
		// in this case, just push the operand on the stack
		// first you need to convert from char to double
		default:
			operands.push(double(postfix[i]-'0'));
			break;
		}
		//increment index counter
		i++;
	}
	//the top of the stack now contains the final result, so we pop it
	operands.pop(result);

	return result;
}

int main() {

	string infix;
	cout << "Please enter an expression to evaluate" << endl;
	getline(cin, infix);
	cout << endl;

	// converts infix to postfix
	string postfix = convert_toPost(infix);

	cout << "The postfix expression is: ";
	cout << postfix << endl;

	// prints the result of the expression to the user
	cout << "The result is: " << evaluate(postfix);
	cout << endl;
	
	
	system("pause");

	return 0;

}
