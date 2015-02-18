// Postfix calculator

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_size 10

char expr[255], translated[255], tmp[5];
typedef enum {lparen, rparen, plus, minus, times, divide, mod, uminus, space, eos, operand} precedence;
int stack[max_size];
static int isp[] = {0, 19, 12, 12, 13, 13, 13, 15, 0, 0};
static int icp[] = {20, 19, 12, 12, 13, 13, 13, 15, 0, 0};

void add(int *top, int item)
{
    if (*top >= max_size - 1) { // This will not happen unless invalid input is given.
        fprintf(stderr, "Stack is full.\n");
        return;
    }
    stack[++*top] = item;
}

int delete(int *top)
{
    if (*top == -1) { // This will not happen unless invalid input is given.
        fprintf(stderr, "Stack is empty.\n");
        return -1;
    }
    return stack[(*top)--];
}

void print_token(int type)
{
    switch (type) {
        case plus:
            sprintf(tmp, "+ ");
            strcat(translated, tmp);
            break;
        case minus:
            sprintf(tmp, "- ");
            strcat(translated, tmp);
            break;
        case times:
            sprintf(tmp, "* ");
            strcat(translated, tmp);
            break;
        case divide:
            sprintf(tmp, "/ ");
            strcat(translated, tmp);
            break;
        case mod:
            sprintf(tmp, "%% ");
            strcat(translated, tmp);
            break;
        case uminus:
            sprintf(tmp, "~ ");
            strcat(translated, tmp);
            break;
    }
}

precedence get_token(char *symbol, int *n)
{
    *symbol = expr[(*n)++];
    switch (*symbol) {
        case '(':
            return lparen;
        case ')':
            return rparen;
        case '+':
            return plus;
        case '-':
            return minus;
        case '*':
            return times;
        case '/':
            return divide;
        case '%':
            return mod;
        case '~':
            return uminus;
        case ' ':
            return space;
        case '\n':
            return eos;
        default:
            return operand;
    }
}

void infix_to_postfix()
{
    char symbol;
    precedence token;
    int n = 0, top = 0;
    stack[0] = eos;
    strcpy(translated, ""); // Clean the array
    printf("Please input infix expression: ");
    fgets(expr, 255, stdin);
    printf("Postfix Notation is: ");
    for (token = get_token(&symbol, &n); ; token = get_token(&symbol, &n)) {
        while (token == operand) {
            sprintf(tmp, "%c", symbol); // Print the result to a temporary array
            strcat(translated, tmp); // Concat the array to "translated"
            if ((token = get_token(&symbol, &n)) != operand) {
                sprintf(tmp, " ");
                strcat(translated, tmp);
            }
        }
        if (token == eos) {
            break;
        }
        if (token == space) {
            continue;
        }
        if (token == rparen) {
            while (stack[top] != lparen) {
                print_token(delete(&top));
            }
            delete(&top);
        } else {
            while (isp[stack[top]] >= icp[token]) {
                print_token(delete(&top));
            }
            add(&top, token);
        }
    }
    while ((token = delete(&top)) != eos) {
        print_token(token);
    }
    printf("%s\n", translated); // "translated" is now a string in postfix notation with space to seperate each operand and operator
}

void postfix_eval()
{
    char *token;
    int op1, op2, top = -1;
    printf("Please input postfix expression (0 if converted from infix expression): ");
    fgets(expr, 255, stdin); // Assume the user will input in postfix notation with space to seperate each operand and operator
    expr[strlen(expr)-1] = '\0'; // Trim the '\n' character
    if (strcmp(expr, "0")) {
        strcpy(translated, expr);
    }
    for (token = strtok(translated, " "); token; token = strtok(NULL, " ")) {
        if (!(strcmp(token, "+") && strcmp(token, "-") && strcmp(token, "*") && strcmp(token, "/") && strcmp(token, "%") && strcmp(token, "~"))) {
            op2 = delete(&top);
            if (strcmp(token, "~")) { // No need to pop the second item for unary minus
                op1 = delete(&top);
            }
            switch (token[0]) {
                case '+':
                    add(&top, op1 + op2);
                    break;
                case '-':
                    add(&top, op1 - op2);
                    break;
                case '*':
                    add(&top, op1 * op2);
                    break;
                case '/':
                    add(&top, op1 / op2);
                    break;
                case '%':
                    add(&top, op1 % op2);
                    break;
                case '~':
                    add(&top, 0-op2); // Turn the positive operand to negative
                    break;
                default:
                    break;
            }
        } else { // Only include positive operands
            add(&top, atoi(token));
        }
    }
    printf("The result of the expression is: %d\n", delete(&top));
}

int main(int argc, char * argv[])
{
    while (1) {
        infix_to_postfix();
        postfix_eval();
    }
    return 0;
}