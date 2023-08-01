#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Node
{
    char* number;
    char* variable;
    char operation;
    struct Node* left;
    struct Node* right;
};

// Function prototypes
char* ltrim(char*);
char* rtrim(char*);
char* trim(char*);
int isOperator(char);
int getPrecedence(char);
struct Node* buildAST(const char*, int, int);
void deleteAST(struct Node*);
char* printTAC(struct Node*);

char* ltrim(char* s)
{
    while (isspace((unsigned char)*s)) s++;
    return s;
}

char* rtrim(char* s)
{
    char* back = s + strlen(s);
    while (isspace((unsigned char)*--back));
    *(back + 1) = '\0';
    return s;
}

char* trim(char* s)
{
    return rtrim(ltrim(s));
}

int isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '=' || c == '&' || c == '|' || c == '!');
}

int getPrecedence(char op)
{
    if (op == '+' || op == '-')
    {
        return 1;
    }
    else if (op == '*' || op == '/')
    {
        return 2;
    }
    else if (op == '=')
    {
        return 0; // Lowest precedence for assignment
    }
    else if (op == '&' || op == '|')
    {
        return 3; // Precedence for boolean AND and OR operators
    }
    else if (op == '!')
    {
        return 4; // Precedence for boolean NOT operator
    }
    return -1; // Invalid operator
}

struct Node* buildAST(const char* expr, int start, int end)
{
    if (start == end)
    {
        char* num = malloc(2);
        num[0] = expr[start];
        num[1] = '\0';
        struct Node* node = malloc(sizeof(struct Node));
        node->number = num;
        node->variable = NULL;
        node->operation = '\0';
        node->left = NULL;
        node->right = NULL;
        return node;
    }

    int parentheses = 0;
    int lowestPrecedence = 3; // Highest precedence level initially
    int lowestPrecedenceIndex = -1;
    int i;

    for (i = end; i >= start; i--)
    {
        if (expr[i] == ')')
        {
            parentheses++;
        }
        else if (expr[i] == '(')
        {
            parentheses--;
        }
        else if (parentheses == 0 && isOperator(expr[i]))
        {
            char op = expr[i];
            int precedence = getPrecedence(op);

            if (op == '-' && (i == start || isOperator(expr[i - 1])))
            {
                precedence = 3; // Higher precedence for unary minus
            }

            if (precedence <= lowestPrecedence)
            {
                lowestPrecedence = precedence;
                lowestPrecedenceIndex = i;
            }
        }
    }

    if (lowestPrecedenceIndex != -1)
    {
        char op = expr[lowestPrecedenceIndex];
        struct Node* newNode = malloc(sizeof(struct Node));
        newNode->number = NULL;
        newNode->variable = NULL;
        newNode->operation = op;
        newNode->left = NULL;
        newNode->right = NULL;

        if (op == '-' || op == '!')
        {
            newNode->right = buildAST(expr, lowestPrecedenceIndex + 1, end);
        }
        else
        {
            newNode->left = buildAST(expr, start, lowestPrecedenceIndex - 1);
            newNode->right = buildAST(expr, lowestPrecedenceIndex + 1, end);
        }

        return newNode;
    }
    else if (expr[start] == '(' && expr[end] == ')' && parentheses == 0)
    {
        return buildAST(expr, start + 1, end - 1);
    }
    else
    {
        int length = end - start + 2;
        char* val = malloc(length);
        strncpy(val, expr + start, length - 1);
        val[length - 1] = '\0';
        struct Node* node = malloc(sizeof(struct Node));
        node->number = NULL;
        node->variable = val;
        node->operation = '\0';
        node->left = NULL;
        node->right = NULL;
        return node;
    }
}

void deleteAST(struct Node* root)
{
    if (root == NULL)
    {
        return;
    }
    deleteAST(root->left);
    deleteAST(root->right);
    free(root->number);
    free(root->variable);
    free(root);
}

int global_count = 0;
struct
{
    char* key;
    char* value;
} rtol[1000];


char* printTAC(struct Node* root)
{
    if (root == NULL)
    {
        return NULL;
    }
    if (root->number != NULL)
    {
        return trim(root->number);
    }
    else if (root->variable != NULL)
    {
        return trim(root->variable);
    }
    else if (root->operation == '=')
    {
        char* leftv = printTAC(root->left);
        char* rightv = printTAC(root->right);
        printf("%s = %s\n", leftv, rightv);
        return NULL;
    }
    else
    {
        char* leftv = printTAC(root->left);
        char* rightv = printTAC(root->right);
        char rhs[100];
        sprintf(rhs, "%s %c %s", leftv, root->operation, rightv);
        int i;
        for (i = 0; i < global_count; i++)
        {
            if (strcmp(rhs, rtol[i].key) == 0)
            {
                // already contains so just return that mapping
                return rtol[i].value;
            }
        }
        int localcount = global_count;
        global_count++;
        char* lhs = malloc(4);
        sprintf(lhs, "t%d", localcount);
        rtol[localcount].key = strdup(rhs);
        rtol[localcount].value = lhs;
        printf("%s = %s\n", lhs, rhs);
        return lhs;
    }
}

int main()
{
    char expr[100];

    printf("Enter an expression: ");
    fgets(expr, sizeof(expr), stdin);
    expr[strcspn(expr, "\n")] = '\0';

    struct Node* root = buildAST(expr, 0, strlen(expr) - 1);

    printf("Three address Code: \n");

    printTAC(root);
    deleteAST(root);

    return 0;
}
