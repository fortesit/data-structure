// Matrix operation

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct
{
    int row, col, val;
} term;

int firstTriple[3], frequencyCnt;

char printPrompt()
{
    char operation[3];
    printf("\n-----------------------------\n1. Matrix input and output\n2. Matrix Addition\n3. Exit\n\nPlease choose an operation: ");
    if (fgets(operation, sizeof(operation), stdin) != NULL) {
        if (strchr(operation, '\n')) { // Success input
            return operation[0];
        } else {
            do {
                fgets(operation, sizeof(operation), stdin); // Clear string buffer
            } while (!strchr(operation, '\n')); // until '\n' appear
            strcpy(operation, "");
        }
    }
    if (feof(stdin)) { // Clear EOF from stdin on cases where ^D is input
        clearerr(stdin);
        printf("\n");
    }
    return operation[0];
}

void transformer()
{
    char inputString[30], *ptr;
    int i, j;
    bool invalid;
    do {
        invalid = false;
        strcpy(inputString, "");
        ptr = inputString;
        printf("\nPlease input matrix size: ");
        fgets(inputString, sizeof(inputString), stdin);
        for (i = 0, ptr = strtok(ptr, ","); ptr; i++, ptr = strtok(NULL, ",")) {
            firstTriple[i] = atoi(ptr);
        }
        if (!firstTriple[0] || !firstTriple[1] || firstTriple[2] > (firstTriple[0] * firstTriple [1])) {
            fprintf(stderr, "\nInvalid input! Please enter again.\n");
            invalid = true;
        }
    } while (invalid);
    term a[firstTriple[2]+1];
    a[0].row = firstTriple[0];
    a[0].col = firstTriple[1];
    a[0].val = firstTriple[2];
    int matrixM[a[0].row][a[0].col];
    for (i = 0; i < a[0].row; i++) {
        for (j = 0; j < a[0].col; j++) {
            matrixM[i][j] = 0; // Initialize
        }
    }
    for (i = 1; i <= a[0].val; i++) {
        do {
            invalid = false;
            strcpy(inputString, "");
            ptr = inputString;
            printf("\nPlease input matrix: ");
            fgets(inputString, sizeof(inputString), stdin);
            for (j = 0, ptr = strtok(ptr, ","); ptr; j++, ptr = strtok(NULL, ",")) {
                switch (j) {
                    case 0:
                        a[i].row = atoi(ptr) - 1;
                        break;
                    case 1:
                        a[i].col = atoi(ptr) - 1;
                        break;
                    case 2:
                        a[i].val = atoi(ptr);
                        break;
                    default:
                        fprintf(stderr, "\nInvalid input! Back to main menu.\n");
                        return;
                        break;
                }
            }
            if (a[i].row < 0 || a[i].row > a[0].row - 1 || a[i].col < 0 || a[i].col > a[0].col - 1) {
                fprintf(stderr, "\nInvalid input! Please enter again.\n");
                invalid = true;
                continue;
            }
            if (matrixM[a[i].row][a[i].col]) {
                fprintf(stderr, "\nYou have input value to this position already. Please input for another position.\n");
                invalid = true;
            }
        } while (invalid);
        matrixM[a[i].row][a[i].col] = a[i].val;
    }
    printf("\nMatrix M is: \n");
    for (i = 0; i < a[0].row; i++) {
        for (j = 0; j < a[0].col; j++) {
            printf("%d ", matrixM[i][j]);
        }
        printf("\n");
    }
}

void add(term a[], term b[], term c[])
{
    int i, j, curr;
    frequencyCnt = 0;
    for (i = j = curr = 1; i <= a[0].val && j<= b[0].val;) {
        switch ((a[i].row == b[j].row ? 0 : (a[i].row > b[j].row ? 1 : -1))) {
            case -1: // a[i].row < b[j].row
                frequencyCnt += 2; // switch statement condition
                c[curr++] = a[i++]; /* Statement count */ frequencyCnt += 5;
                break;
            case 0: // a[i].row == b[j].row
                frequencyCnt += 1; // switch statement condition
                switch ((a[i].col == b[j].col ? 0 : (a[i].col > b[j].col ? 1 : -1))) {
                    case -1: // a[i].col < b[j].col
                        frequencyCnt += 2; // switch statement condition
                        c[curr++] = a[i++]; /* Statement count */ frequencyCnt += 5;
                        break;
                    case 0: // a[i].col == b[j].col
                        frequencyCnt += 1; // switch statement condition
                        c[curr].row = a[i].row; /* Statement count */ frequencyCnt += 1;
                        c[curr].col = a[i].col; /* Statement count */ frequencyCnt += 1;
                        c[curr++].val = a[i++].val + b[j++].val; /* Statement count */ frequencyCnt += 4;
                        break;
                    case 1: // a[i].col > b[j].col
                        frequencyCnt += 2; // switch statement condition
                        c[curr++] = b[j++]; /* Statement count */ frequencyCnt += 5;
                        break;
                    default:
                        break;
                }
                break;
            case 1: // a[i].row > b[j].row
                frequencyCnt += 2; // switch statement condition
                c[curr++] = b[j++]; /* Statement count */ frequencyCnt += 5;
                break;
            default:
                break;
        }
    }
    while (i <= a[0].val) {
        c[curr++] = a[i++]; /* Statement count */ frequencyCnt += 5;
    }
    while (j<= b[0].val) {
        c[curr++] = b[j++]; /* Statement count */ frequencyCnt += 5;
    }
    c[0].val = curr - 1; /* Statement count */ frequencyCnt += 1;
}

void readfile(const char * argv)
{
    FILE *fp;
    char buf[30], *ptr;
    int i, j, count;
    if (!(fp = fopen(argv, "r"))) {
        fprintf(stderr, "\n");
        perror("Error");
        fprintf(stderr, "\nBack to menu.\n");
        return;
    }
    
    // Matrix A
    strcpy(buf, "");
    ptr = buf;
    fgets(buf, sizeof(buf), fp);
    for (i = 0, ptr = strtok(ptr, ","); ptr; i++, ptr = strtok(NULL, ",")) {
        firstTriple[i] = atoi(ptr);
    }
    term a[firstTriple[2]+1];
    a[0].row = firstTriple[0];
    a[0].col = firstTriple[1];
    a[0].val = firstTriple[2];
    int matrixA[a[0].row][a[0].col];
    for (i = 0; i < a[0].row; i++) {
        for (j = 0; j < a[0].col; j++) {
            matrixA[i][j] = 0; // Initialize
        }
    }
    for (i = 1; i <= a[0].val; i++) {
        ptr = buf;
        fgets(buf, sizeof(buf), fp);
        for (j = 0, ptr = strtok(ptr, ","); ptr; j++, ptr = strtok(NULL, ",")) {
            switch (j) {
                case 0:
                    a[i].row = atoi(ptr) - 1;
                    break;
                case 1:
                    a[i].col = atoi(ptr) - 1;
                    break;
                case 2:
                    a[i].val = atoi(ptr);
                    break;
                default:
                    break;
            }
        }
        matrixA[a[i].row][a[i].col] = a[i].val;
    }
    printf("\nMatrix a is: \n");
    for (i = 0; i < a[0].row; i++) {
        for (j = 0; j < a[0].col; j++) {
            printf("%d ", matrixA[i][j]);
        }
        printf("\n");
    }
    
    // Matrix B
    strcpy(buf, "");
    ptr = buf;
    fgets(buf, sizeof(buf), fp);
    for (i = 0, ptr = strtok(ptr, ","); ptr; i++, ptr = strtok(NULL, ",")) {
        firstTriple[i] = atoi(ptr);
    }
    term b[firstTriple[2]+1];
    b[0].row = firstTriple[0];
    b[0].col = firstTriple[1];
    b[0].val = firstTriple[2];
    if (a[0].row != b[0].row || a[0].col != b[0].col) {
        fprintf(stderr, "Matrices of different size cannot perform addition. Back to main menu.\n");
        fclose(fp);
        return;
    }
    int matrixB[b[0].row][b[0].col];
    for (i = 0; i < b[0].row; i++) {
        for (j = 0; j < b[0].col; j++) {
            matrixB[i][j] = 0; // Initialize
        }
    }
    for (i = 1; i <= b[0].val; i++) {
        ptr = buf;
        fgets(buf, sizeof(buf), fp);
        for (j = 0, ptr = strtok(ptr, ","); ptr; j++, ptr = strtok(NULL, ",")) {
            switch (j) {
                case 0:
                    b[i].row = atoi(ptr) - 1;
                    break;
                case 1:
                    b[i].col = atoi(ptr) - 1;
                    break;
                case 2:
                    b[i].val = atoi(ptr);
                    break;
                default:
                    break;
            }
        }
        matrixB[b[i].row][b[i].col] = b[i].val;
    }
    printf("\nMatrix b is: \n");
    for (i = 0; i < b[0].row; i++) {
        for (j = 0; j < b[0].col; j++) {
            printf("%d ", matrixB[i][j]);
        }
        printf("\n");
    }
    
    // Counting of non-zero value after addition
    count = 0;
    for (i = 0; i < a[0].row; i++) {
        for (j = 0; j < a[0].col; j++) {
            if (matrixA[i][j] + matrixB[i][j]) {
                count++;
            }
        }
    }
    
    // Matrix C
    term c[count+1];
    c[0].row = firstTriple[0];
    c[0].col = firstTriple[1];
    int matrixC[c[0].row][c[0].col];
    for (i = 0; i < c[0].row; i++) {
        for (j = 0; j < c[0].col; j++) {
            matrixC[i][j] = 0; // Initialize
        }
    }
    
    // Addition
    add(a, b, c);
    
    for (i = 1; i <= c[0].val; i++) {
        matrixC[c[i].row][c[i].col] = c[i].val;
    }
    
    printf("\nMatrix c is: \n");
    for (i = 0; i < c[0].row; i++) {
        for (j = 0; j < c[0].col; j++) {
            printf("%d ", matrixC[i][j]);
        }
        printf("\n");
    }
    
    printf("\nThe frequency count is %d\n", frequencyCnt);
    
    fclose(fp);
}

int main(int argc, const char * argv[])
{
    while (1) {
        switch (printPrompt()) {
            case '1':
                transformer();
                break;
            case '2':
                readfile(argv[1]);
                break;
            case '3':
                exit(EXIT_SUCCESS);
            default:
                fprintf(stderr, "\nInvalid input! Please enter again.\n");
                break;
        }
    }
    return 0;
}