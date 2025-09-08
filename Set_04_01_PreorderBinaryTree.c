#include <stdio.h>
#include <stdlib.h>

// Structure for a binary tree node
struct Node {
    int data;
    struct Node *left, *right;
};

// Function to create a new node
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// Stack structure
struct Stack {
    int top;
    int capacity;
    struct Node** array;
};

// Function to create a stack
struct Stack* createStack(int capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (struct Node**)malloc(stack->capacity * sizeof(struct Node*));
    return stack;
}

// Check if stack is empty
int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

// Push a node to stack
void push(struct Stack* stack, struct Node* node) {
    stack->array[++stack->top] = node;
}

// Pop a node from stack
struct Node* pop(struct Stack* stack) {
    if (isEmpty(stack))
        return NULL;
    return stack->array[stack->top--];
}

// Preorder traversal without recursion
void preorderTraversal(struct Node* root) {
    if (root == NULL)
        return;

    // Create stack
    struct Stack* stack = createStack(100);
    push(stack, root);

    while (!isEmpty(stack)) {
        struct Node* node = pop(stack);
        printf("%d ", node->data);

        if (node->right)
            push(stack, node->right);
        if (node->left)
            push(stack, node->left);
    }
}
int main() {
    struct Node* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    root->right->right = newNode(6);

    printf("Preorder Traversal (non-recursive): ");
    preorderTraversal(root);

    return 0;
}
