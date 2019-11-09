<<<<<<< HEAD
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>


bool calculate(char* op, int& value) {

    char c_operator = *(op);

    // Thank you StackOverflow!!!
    int second = *( op - 1 ) - '0';
    int first = *( op - 2 ) - '0';


    if (c_operator == '+') {
        value = first + second;
    } else if (c_operator == '-') {
        value = first - second;
    } else if (c_operator == '*') {
        value = first * second;
    } else if (c_operator == '/' ) {
        if (second == 0) {
            std::cout << "Error: Division by zero" << std::endl;
            return false;
        }
        value = first / second;
    } else {
        std::cout << "Error: Unknown character " << c_operator << std::endl;
        return false;
    }
    return true;

}

bool validate( char* front, int size ) {

    if (!isdigit(*front)) {
        // first element must be number
        std::cout << "Error: Expression must start with a number" << std::endl;
        return false;
    }

    int c_operatorCount = 0;
    int operandCount = 0;

    // TODO: cout operands and operators

    for (int i = 0; i < size; i++) {

        char current = *(front + i);
        if (isdigit(current))
            operandCount++;
        else
            c_operatorCount++;

    }

//    if (operandCount - c_operatorCount < 2) {
//        // Too many operators
//        std::cout << "Error: Too few operands" << std::endl;
//        return false;
//    } else if (operandCount - c_operatorCount > 2) {
//        std::cout << "Error: Too few operators" << std::endl;
//        return false;
//    } else {
//        return true;
//    }

    return true;



}

bool polishify( char* front, const int& size) {

    int value = 0;
    std::vector<int> stack;

    if (!validate(front, size)) {
        return false;
    }

    int i = 0;
    int stackIndex = 0;

    while (i < size-1) {

        if (*(front+i) == '#') {
            break;
        }

        if (!isdigit( *(front+i)) ) {

            calculate(front+i, value);
            stack.at(stackIndex - 2) = value;

            stackIndex -= 2;

            stack.pop_back();
            stack.pop_back();
            // Remove i-2 - i


        } else {

            stack.at(stackIndex) = *(front + i) - '0'; // This might cause problems

        }

        stackIndex++;
        i++;
    }


    std::cout << "Correct: " << value << " is the result" << std::endl;


    return true;
}

int main()
{

    std::cout << "Input an expression in reverse Polish notation (end with #):" << std::endl;

    std::cout << "EXPR> ";
    std::string line;
    getline(std::cin, line);

    line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
    polishify( &line[0], (int)line.length() );




    return 0;
}
=======

#include <iostream>
#include <array>
#include <stack>
#include <vector>
#include <algorithm>
#include <string>


std::vector<std::string> split(const std::string& s,
                               const char delimiter,
                               const bool ignore_empty = false) {
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos) {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty())) {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty())) {
        result.push_back(tmp);
    }
    return result;
}

bool is_int(std::string goal){
    try  {
        throw(std::stoi(goal));
    }
    catch (const std::invalid_argument&)  {
        return false;
    }
    catch (...){
        return true;
    }
}




int main()
{
    std::string expression;
    std::string input;
    std::cout << "Input an expression in reverse Polish notation (end with #):" << std::endl;
    std::cout << "EXPR> ";
    std::getline(std::cin, input);
    if (!isdigit(input.at(0))){
        std::cout << "Error: Expression must start with a number" << std::endl;
        return EXIT_FAILURE;
    }
    expression = input.substr(0, input.size()-2);
    std::vector<std::string> tokens = split(expression, ' ');
    std::stack<int> stackkis;
    int result;
    for (std::string item : tokens){
        if (!is_int(item)){
            if (item != "+" && item != "-" && item != "*" && item != "/"){
                std::cout << "Error: Unknown character" << std::endl;
                return EXIT_FAILURE;
            }
            int num1 = stackkis.top();
            stackkis.pop();
            if (stackkis.size() == 0){
                std::cout << "Error: Too few operands" << std::endl;
                return EXIT_FAILURE;
            }
            int num2 = stackkis.top();
            stackkis.pop();
            if (item == "+"){
                result = num1 + num2;
                stackkis.push(result);
            }
            else if (item == "-"){
                result = num2 - num1;
                stackkis.push(result);
            }
            else if(item == "*"){
                result = num1 * num2;
                stackkis.push(result);
            }
            else if(item == "/"){
                if(num1 == 0){
                    std::cout << "Error: Division by zero" << std::endl;
                    return EXIT_FAILURE;
                }else{
                    result = num2 / num1;
                    stackkis.push(result);
                }
            }
        }
        else if(is_int(item)){
            int num = std::stoi(item);
            stackkis.push(num);
        }
    }
    if (stackkis.size() > 1){
        std::cout << "Error: Too few operators" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Correct: " << stackkis.top() << " is the result" << std::endl;

}
>>>>>>> 3c8311bf3855e4c3183b7bdbd521d65868f2f857
