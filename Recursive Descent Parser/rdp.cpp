/* I will be taking the following grammar for example:
E -> E + T | T
T -> T * F | F
F -> c | ( E ) 
Where c is a constant.
After removing the left recursion we get the following equivalent grammar:
E –> T E’
E’ –> + T E’ | e
T –> F T’
T’ –> * F T’ | e
F –> c | ( E ) 
*/

  
#include <iostream>
#include <string>

using namespace std;

class RecursiveDescentParser {
private:
    string input;
    size_t position;
    bool hasError;

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
            hasError = true;
        }
    }

    void E() {
        T();
        if (hasError) return;
        EPrime();
    }

    void EPrime() {
        if (input[position] == '+') {
            match('+');
            if (hasError) return;
            T();
            if (hasError) return;
            EPrime();
        }
        // Epsilon production
    }

    void T() {
        F();
        if (hasError) return;
        TPrime();
    }

    void TPrime() {
        if (input[position] == '*') {
            match('*');
            if (hasError) return;
            F();
            if (hasError) return;
            TPrime();
        }
        // Epsilon production
    }

    void F() {
        if (input[position] == 'c') {
            match('c');
        } else if (input[position] == '(') {
            match('(');
            if (hasError) return;
            E();
            if (hasError) return;
            match(')');
        } else {
            cout << "Error: Expected 'c' or '(', found '" << input[position] << "'" << endl;
            hasError = true;
        }
    }


public:
    RecursiveDescentParser(const string& input) : input(input), position(0), hasError(false) {}

    void parse() {
        E();
        if (position != input.length()) {
            cout << "Error: Extra characters found after the expression" << endl;
            hasError = true;
        }
    }

    bool hasParsingError() const {
        return hasError;
    }
};

int main() {
    string input;
    cout << "Enter a string: ";
    cin >> input;

    RecursiveDescentParser parser(input);
    parser.parse();

    if (!parser.hasParsingError()) {
        cout << "Parsing completed successfully!" << endl;
    }

    return 0;
}

