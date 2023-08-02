/*
construct recursive descent parser for the following grammar 
S->01S' 
S'->0S1SS' | epsilon
*/


#include <iostream>
#include <string>

using namespace std;

class RecursiveDescentParser {
private:
    string input;
    size_t position;

    char getNextToken() {
        if (position < input.length()) {
            return input[position++];
        }
        return '\0';
    }

    void match(char expectedToken) {
        if (getNextToken() == expectedToken) {
            cout << "Matched token: " << expectedToken << endl;
        } else {
            cout << "Error: Expected token '" << expectedToken << "', found '" << input[position - 1] << "'" << endl;
        }
    }

    void S() {
        if (input[position] == '0' && input[position + 1] == '1') {
            match('0');
            match('1');
            SPrime();
        } else {
            cout << "Error: Expected '01', found '" << input[position] << input[position + 1] << "'" << endl;
        }
    }

    void SPrime() {
        if (input[position] == '0') {
            match('0');
            S();
            match('1');
            S();
            SPrime();
        }
        // Epsilon production
    }

public:
    RecursiveDescentParser(const string& input) : input(input), position(0) {}

    void parse() {
        S();
        if (position < input.length()) {
            cout << "Error: Extra characters found after the expression" << endl;
        } else {
            cout << "Parsing completed successfully!" << endl;
        }
    }
};

int main() {
    string input;
    cout << "Enter a string: ";
    cin >> input;

    RecursiveDescentParser parser(input);
    parser.parse();

    return 0;
}
