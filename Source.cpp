#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stack>
#include <cmath>

#include "ArgumentManager.h"


using namespace std;

struct node {

	node *next;
	char data;
	long long int data2;
};
class stacker {
private:
	node *top;
public:
	stacker() {
		top = nullptr;
	}
	string expression;
	bool isEmpty() {
		if (top == nullptr) {
			return true;
		}
		else {
			return false;
		}
	}
	bool isoperand(char x) {
		if (x == '+' || x == '-' || x == '*' || x == '/' || x == '(' || x == ')' || x == ' ') {
			return false;
		}
		else {
			return true;
		}
	}
	int precedence(char x) {
		if (x == '+' || x == '-') {
			return 3;
		}
		else if (x == '*' || x == '/') {
			return 4;
		}
		else if (x == '(') {
			return 1;
		}
		else if (x == ')') {
			return 2;
		}
		else {
			return 0;
		}
	}
	void push(char x) {

		node *temp = new node;
		//if (temp == nullptr) {
		//	cout << "stack is full" << endl;
		//}
		//else{
		temp->data = x;
		temp->next = top;
		top = temp;
		//}

	}
	char pop() {

		node *temp = new node;
		int x = -1;
		if (top == nullptr) {
			cout << "stack is empty" << endl;
		}
		else {
			temp = top;
			top = top->next;
			x = temp->data;
			delete temp;
		}
		return x;
	}
	bool isBalanced(string exp) {
		//cout << "printing exp: " << exp << endl;

		int len = exp.length();
		if (exp[len - 1] == '+' || exp[len - 1] == '-' || exp[len - 1] == '*' || exp[len - 1] == '/') {
			return false;
		}
		else {
			for (int i = 0; exp[i] != '\0'; i++) {
				if (exp[i + 1] != '\0') {
					if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/') {
						if (exp[i + 1] == '+' || exp[i+1] == '-' || exp[i+1] == '*' || exp[i+1] == '/') {
							return false;
						}
					}

				}
			}
		}



		for (int i = 0; exp[i] != '\0'; i++) {
			if (exp[i] == '(') {
				push(exp[i]);
			}
			else if (exp[i] == ')')
			{
				if (top == nullptr)
				{
					return false;
				}
				else
				{
					pop();
				
				}
			}
		}

	
		if (top == nullptr){
			return true;
		}
		else {
			//cout << top->data;
			return false;
		}
	}

	node *returnTop() {
		return top;
	}

	string inToPost(string infix) {

		int i = 0, j = 0;
		long long int length = infix.length();

		string postfix = ""; //our final postfix string
		string x = ""; //a string to store the numbers digit by digit so we can append this to the postfix string as a whole number 

		//if ((infix[0] == '-' || infix[0] == '+') && !(isoperand(infix[1]))) { //checking if the first is a negative sign or positive sign 
		//		push(infix[0]);
		//		i++;
		//		cout << "top data: " << top->data << endl;
		//}

		if (infix[0] == '-' || infix[0] == '+') { //checking if the first is a negative sign or positive sign 
			if (!isoperand(infix[1])) {
				push(infix[0]);
				i++;
			}
			else {
				x += infix[0];
				infix = infix.substr(1);

				while (isoperand(infix[0])) {
					x += infix[0];
					infix = infix.substr(1);
				}
				postfix.append(x);
				postfix.append(" ");
				cout << "printing post: " << postfix << endl;
				x = "";
			}
		}
		while (infix[i] != '\0') {

			if (isoperand(infix[i])) {
				x += infix[i]; //storing the number in x digit by digt 
				i++;
			}

			else { //if its not an operand, then its an operator, so check precedence 
				if (x != "") {
					postfix.append(x); //we hit an operator. now if we see that x is not empty, then it has a number and since we hit an operator, we know that we reached the end of that number, so we are appending to our postfix string as a number. 
					postfix.append(" ");
					x = "";
				}
				if (top == nullptr) {
					push(infix[i]);
					i++;
					if (top->data == '(') {
						if (infix[i] == '-' || infix[i] == '+') {
							x += infix[i];
							i++;
							while ((isoperand(infix[i]))) {
								x += infix[i];
								i++;
							}
							postfix.append(x);
							postfix.append(" ");
							//i++;
							x = "";
						}
					}
				}
				else if (precedence(infix[i]) == 1) { //checking if it '('
					push(infix[i]);
					i++;

					if ((infix[i] == '-' || infix[i] == '+') && (isoperand(infix[i+1]))) {
						cout << infix[i] << "   going in when" << endl;
						x += infix[i];
						i++;
						while ((isoperand(infix[i]))) {
							x += infix[i];
							i++;
						}
						postfix.append(x);
						postfix.append(" ");
						//i++;
						x = "";
					}

				}
				else if (precedence(infix[i]) == 2) { //checking if its ')' 
					string z = ""; //temp string to store stuff thats inbetween ( ... )
					while (top->data != '(') {
						z += pop();
						z += " ";
					}
					postfix.append(z);
					if (z != "") {
						//postfix.append(" ");
					}
					pop(); //popping the '('
					i++;
					//cout << "printing post: " << postfix;

				}
				else if (precedence(infix[i]) > precedence(top->data)) {

					push(infix[i]);
					i++;
				}

				else {
					string z = "";
					z = pop();
					postfix.append(z);
					postfix.append(" ");

				}
			}
		}

		if (x != "") {
			postfix.append(x);
			postfix.append(" ");
			x = "";
		}

		string m = ""; //for the last number in a string

		while (!isEmpty()) {
			m += pop();
			m += " ";
		}
		postfix.append(m);
		//postfix.append(" ");

		postfix.append("\0");
		//cout << "printing postfix: " << postfix << endl;
		return postfix;
	}

	//--------------------------
	void push2(long long int post) {
		node *temp = new node;
		temp->data2 = post;
		temp->next = top;
		top = temp;
	}
	long long int pop2() {
		node *temp = new node;
		long long int x = -1;
		if (top == nullptr) {
			cout << "stack is empty" << endl;
		}
		else {
			temp = top;
			top = top->next;
			x = temp->data2;
			delete temp;
		}
		return x;
	}

	long long int evalPost(string postfix) {
		int i = 0;
		int k = 0;
		long long int val1, val2, value;
		long long int stringVal;
		string temp = "";

		if (postfix[0] == '-' || postfix[0] == '+') { // checking case where the - or + is in the beginning 
			while (postfix[i] != ' ') {
				temp += postfix[i];
				//k++;
				i++;
			}
			if (temp != " " && temp != "") {

				istringstream iss(temp);
				iss >> stringVal;

				push2(stringVal);
			}
			temp = "";
		}
		
		for (i; postfix[i] != '\0'; i++) {

			if (postfix[i+1] != '\0' && (postfix[i] == '+' || postfix[i] == '-')) {
				if (isoperand(postfix[i + 1])) {
					while (postfix[i] != ' ') {
						temp += postfix[i];
						//k++;
						i++;
					}
					if (temp != " " && temp != "") {

						istringstream iss(temp);
						iss >> stringVal;

						push2(stringVal);
					}
					temp = "";
				}
				//cout << "not doing anything, printing current i: " << i << endl;
			}
			if (isoperand(postfix[i])) {
				while (postfix[i] != ' ') {
					temp += postfix[i];
					i++;
				}
				if (temp != " " && temp != "") {

					istringstream iss(temp);
					iss >> stringVal;

					push2(stringVal);

				}
				temp = "";

			}


			else if (postfix[i] != ' ' && (postfix[i] != '-' && postfix[i] !='+')) {
				if (!isEmpty()) {
					val2 = pop2();
				}
				else {
					val2 = 0;
				}
				if (!isEmpty()) {
					val1 = pop2();
				}
				else {
					val1 = 0;
				}
					//cout << "val1: " << val1 << endl;
					//cout << "val2: " << val2 << endl;

				if (postfix[i] == '+') {
					push2(value = val1 + val2);

				}
				else if (postfix[i] == '-') {
					push2(value = val1 - val2);

				}
				else if (postfix[i] == '*') {
					push2(value = val1 * val2);

				}
				else if (postfix[i] == '/') {
					push2(value = val1 / val2);

				}
			}

			else if ((postfix[i + 1] == '\0' || postfix[i+1] == ' ') && (postfix[i] == '-' || postfix[i] == '+')) {
				if (!isEmpty()) {
					val2 = pop2();
				}
				else {
					val2 = 0;
				}
				if (!isEmpty()) {
					val1 = pop2();
				}
				else {
					val1 = 0;
				}
				cout << "val1: " << val1 <<"!!!" << endl;
				cout << "val2: " << val2 << "!!!"<< endl;

				if (postfix[i] == '+') {
					push2(value = val1 + val2);

				}
				else if (postfix[i] == '-') {
					push2(value = val1 - val2);

				}
				else if (postfix[i] == '*') {
					push2(value = val1 * val2);

				}
				else if (postfix[i] == '/') {
					push2(value = val1 / val2);

				}
	
			}
			else if ((postfix[i] == '-' || postfix[i] =='+' )&& (postfix[i + 1] != '\0') ){
				temp += postfix[i];
				i++;
				if (isoperand(postfix[i])) {

					while (postfix[i] != ' ') {
						temp += postfix[i];
						//k++;
						i++;
					}
					if (temp != " " && temp != "") {

						istringstream iss(temp);
						iss >> stringVal;

						push2(stringVal);
					}
					temp = "";
				}

			}
		}
		return top->data2;

	}
};

int main() {
//int main(int argc, char * argv[])
//{
//
//	ArgumentManager am(argc, argv);
//	const string in = am.get("input");
//	const string out = am.get("output");

	ifstream readfile;
	ofstream writefile;


	string line;
	string post;

	string in = "input38.txt";
	string out = "output.txt";

	readfile.open(in);
	writefile.open(out);

	stacker object;

	if (readfile.is_open()) {
		cout << "file is open" << endl;
	}
	else {
		cout << "unable to open file" << endl;
	}
	int flag = 0;
	while (!readfile.eof()) {
		getline(readfile, line);
		if (line.length() != 0) {
			flag = 1;
			if (object.isBalanced(line)) {
				//cout << " is balanced" << endl;
				cout << "printing postfix: " << endl;
				post = object.inToPost(line);
				cout << post << endl;
				cout << "result is: " << object.evalPost(post) << endl;
				writefile << line;
				writefile << "=" << object.evalPost(post) << endl;
				while (!object.isEmpty()) {
					object.pop();
				}
				while (!object.isEmpty()) {
					object.pop2();
				}
			}
			else {

				cout << "error" << endl;
				writefile << "error" << endl;
				while (!object.isEmpty()) {
					object.pop();
				}
			}
		}
		else {
	
			cout << "error" << endl;
		}

	}
	if (flag == 0) {
		writefile << "error" << endl;
	}
	writefile.close();

	//
	//cout << endl << endl << endl;
	//cout << "printing exp : " << "8-(-(-(-(-(-(-(-(-(-(-(-(-(-(-(-(-(-(-(-(-(-(-1))))-2)+4)+16)+24)+32)+40)+48)+56)+64)+72)+80)+88)+96*2)+104)+112)+120)+128)+256)/2" << endl;
	//string ex = "8 - (-(-(-(-(-(-(-(-(-(-(-(-(-(-(-(-(-(-(-(-(-(-1)))) - 2) + 4) + 16) + 24) + 32) + 40) + 48) + 56) + 64) + 72) + 80) + 88) + 96 * 2) + 104) + 112) + 120) + 128) + 256) / 2";
	//post = object.inToPost(ex);
	//	cout << "print : " << post <<"!" << endl;
	//	cout << "result!!! " << object.evalPost(post) << endl;
	
	system("pause");
	return 0;
}


