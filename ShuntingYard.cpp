#include<iostream>
#include<sstream>
#include<stack>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <cstdlib>
std::string infixToPostfix(const std::string& infix) {
	const std::string ops = "-+/*^";
	std::stringstream ss;
	std::stack<int> s;

	std::stringstream input(infix);
	std::string token;
	while (std::getline(input, token, ' ')) {
		std::cout << token << std::endl;
		if (token.empty()) {
			continue;
		}

		char c = token[0];
		size_t idx = ops.find(c);

		// check for operator
		if (idx != std::string::npos) {
			while (!s.empty()) {
				int prec2 = s.top() / 2;
				int prec1 = idx / 2;
				if (prec2 > prec1 || (prec2 == prec1 && c != '^')) {
					ss << ops[s.top()] << ' ';
					s.pop();
				}
				else break;
			}
			s.push(idx);
		}
		else if (c == '(') {
			s.push(-2); // -2 stands for '('
		}
		else if (c == ')') {
			// until '(' on stack, pop operators.
			while (s.top() != -2) {
				ss << ops[s.top()] << ' ';
				s.pop();
			}
			s.pop();
		}
		else {
			ss << token << ' ';
		}
	}

	while (!s.empty()) {
		ss << ops[s.top()] << ' ';
		s.pop();
	}

	return ss.str();
}



double rpn(const std::string& expr) {
	std::istringstream iss(expr);
	std::vector<double> stack;
	//std::cout << "Input\tOperation\tStack after" << std::endl;
	std::string token;
	while (iss >> token) {
		//std::cout << token << "\t";
		double tokenNum;
		if (std::istringstream(token) >> tokenNum) {
			//std::cout << "Push\t\t";
			stack.push_back(tokenNum);
		}
		else {
			//std::cout << "Operate\t\t";
			double secondOperand = stack.back();
			stack.pop_back();
			double firstOperand = stack.back();
			stack.pop_back();
			if (token == "*")
				stack.push_back(firstOperand * secondOperand);
			else if (token == "/")
				stack.push_back(firstOperand / secondOperand);
			else if (token == "-")
				stack.push_back(firstOperand - secondOperand);
			else if (token == "+")
				stack.push_back(firstOperand + secondOperand);
			else if (token == "^")
				stack.push_back(std::pow(firstOperand, secondOperand));
			else { //just in case
				std::cerr << "Error" << std::endl;
				std::exit(1);
			}
		}
		std::copy(stack.begin(), stack.end(), std::ostream_iterator<double>(std::cout, " "));
		//std::cout << std::endl;
	}
	return stack.back();
}


int main(int argv, const char* const const* argc) {

	std::string infix = "2.0 ^ 3";
	std::cout << infixToPostfix(infix) << std::endl;
	std::cout << rpn(infixToPostfix(infix)) << std::endl;




}
