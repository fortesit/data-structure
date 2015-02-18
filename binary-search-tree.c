// Binary search tree

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct node* tree_pointer;
typedef struct node{
    int data;
    tree_pointer left_child, right_child;
} node;

char inputString[50], treeDiagram[1024][5], buf[5], outputTree[2][2048], outputInorder[2048], outputPath[50];
int inputTree[2][50], level, arrayIndex;
tree_pointer root[2], curr[2];

void insert(tree_pointer * tree, tree_pointer item)
{
    if (!(*tree)) { // If the subtree is null
        *tree = item;
        sprintf(buf, "%d", item->data);
        strcpy(treeDiagram[arrayIndex], buf);
        return;
    }
    if (item->data < (*tree)->data) { // If the insert item's value is smaller than the subtree item's value
        level++;
        arrayIndex = (int)pow(2, level) + 2 * (arrayIndex - pow(2, level - 1)); // The index of the 1D array representing the tree is 2^k+2(i-2^(k-1)) where k and i are the level of the next subtree and the current index respectively.
        insert(&(*tree)->left_child, item); // Let the left child be the subtree
    } else if (item->data > (*tree)->data) {
        level++;
        arrayIndex = (int)pow(2, level) + 2 * (arrayIndex - pow(2, level - 1)) + 1; // 2^k+2(i-2^(k-1))+1
        insert(&(*tree)->right_child, item);
    }
}

void inorder(tree_pointer ptr)
{
    if (ptr) { // LVR
        inorder(ptr->left_child);
        sprintf(buf, "%d", ptr->data);
        strcat(outputInorder, strcat(buf, ","));
        inorder(ptr->right_child);
    }
    
}

void buildBST()
{
    char tmp[2][50], *ptr;
    int i, j, k, l, depth;
    strcpy(outputTree[0], "");
    strcpy(outputTree[1], "");
    printf("Please input the two traversal strings: ");
    fgets(inputString, sizeof(inputString), stdin); // No invalid input handling
    if (!strcmp(inputString, "!\n")) {
        exit(EXIT_SUCCESS);
    }
    for (i = 0, ptr = strtok(inputString, "."); i < 2; i++, ptr = strtok(NULL, ".")) { // First seperate two strings by '.'
        strcpy(tmp[i], ptr);
    }
    for (i = 0; i < 2; i++) {
        depth = 0;
        for (j = 0, ptr = strtok(tmp[i], ","); ptr; j++, ptr = strtok(NULL, ",")) { // Then by ','
            inputTree[i][j] = atoi(ptr);
        }
        for (l = 0; l < 1024;  l++) {
            strcpy(treeDiagram[l], "*");
        }
        for (k = 0; k < j; k++) { // j = # of elements to be inserted
            curr[i] = (tree_pointer)malloc(sizeof(node));
            curr[i]->left_child = curr[i]->right_child = NULL;
            curr[i]->data = inputTree[i][k];
            level = 0;
            arrayIndex = 1; // The 1D array representing the BST is indexed 1 as root
            if (k == 0) { // Root initialization
                root[i] = curr[i];
                sprintf(buf, "%d", root[i]->data);
                strcpy(treeDiagram[arrayIndex], buf);
            } else {
                insert(&root[i], curr[i]);
            }
            if (depth < level) { // depth is the max. level
                depth = level;
            }
        }
        printf("The %s tree graph is:\n", (i ? "second" : "first"));
        for (k = 0; k <= depth; k++) { // sprintf for each line
            for (l = 0; l < pow(2, k); l++) { // 2^k element per line
                sprintf(buf, "%s", treeDiagram[(int)pow(2, k) + l]);
                strcat(outputTree[i], strcat(buf, " "));
            }
            sprintf(buf, "\n"); // Break for each line
            strcat(outputTree[i], buf);
        }
        printf("%s", outputTree[i]);
    }
}

void compareTrees()
{
    printf("The two trees are %sthe same.\n", (strcmp(outputTree[0], outputTree[1]) ? "not " : "")); // Compare the output string
}

void inorderTraversal()
{
    int i;
    for (i = 0; i < 2; i++) {
        strcpy(outputInorder, "");
        printf("The inorder of the %s tree is: ", (i ? "second" : "first"));
        inorder(root[i]);
        outputInorder[strlen(outputInorder) - 1] = '.'; // Change the last character ',' to '.'
        printf("%s\n", outputInorder);
    }
}

void searchKey(tree_pointer tree, int key)
{
    if (tree) {
        if (key == tree->data) { // Cases when key found
            printf("The path from the root is: ");
            sprintf(buf, "%d", tree->data);
            strcat(outputPath, strcat(buf, "."));
            printf("%s\n", outputPath);
        } else if (key < tree->data) { // Cases when key smaller than the root node of a subtree
            sprintf(buf, "%d", tree->data);
            strcat(outputPath, strcat(buf, ","));
            searchKey(tree->left_child, key);
        } else if (key > tree->data) { // Cases when key greater than the root node of a subtree
            sprintf(buf, "%d", tree->data);
            strcat(outputPath, strcat(buf, ","));
            searchKey(tree->right_child, key);
        }
    } else { // Cases when the tree is empty or the key is not found (i.e. the subtree is empty)
        printf("The key does not exist!\n");
    }
}

int main(int argc, char * argv[])
{
    for (; ; free(root[0]), free(root[1]), free(curr[0]), free(curr[1])) {
        buildBST();
        compareTrees();
        inorderTraversal();
        do {
            strcpy(outputPath, "");
            printf("The key you are looking for is: ");
            fgets(inputString, sizeof(inputString), stdin);
            inputString[strlen(inputString)-1] = '\0';
            if (!strcmp(inputString, "!")) {
                exit(EXIT_SUCCESS);
            }
            if (strcmp(inputString, "#")) {
                searchKey(root[0], atoi(inputString));
            }
        } while (strcmp(inputString, "#"));
    }
    return 0;
}