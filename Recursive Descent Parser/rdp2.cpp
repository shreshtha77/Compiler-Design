/*

construct a recursive descent parser for the following grammar 
E->iE' 
E'->+iE' | epsilon

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

    void E() {
        if (input[position] == 'i') {
            match('i');
            EPrime();
        } else {
            cout << "Error: Expected 'i', found '" << input[position] << "'" << endl;
        }
    }

    void EPrime() {
        if (input[position] == '+') {
            match('+');
            match('i');
            EPrime();
        }
        // Epsilon production
    }

public:
    RecursiveDescentParser(const string& input) : input(input), position(0) {}

    void parse() {
        E();
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

