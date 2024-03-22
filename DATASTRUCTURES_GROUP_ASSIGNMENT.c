/* Implementing Binary search Tree by use of linked list,
from an array data type
----------------------*/
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};
struct Node* createNode(int value);
struct Node* insert(struct Node* root, int value);
struct Node* deleteNode(struct Node* root, int key);
void inorderTraversal(struct Node* root) ;
void preorderTraversal(struct Node* root);
void postorderTraversal(struct Node* root);

int main() {
    int arr[] = {30, 20, 40, 10, 25, 35, 45, 5, 15};
    int n = sizeof(arr) / sizeof(arr[0]);
    struct Node* root = NULL;
    for (int i = 0; i < n; i++) {
        root = insert(root, arr[i]);
    }

    printf("Elements in BST  before deletion of node (inorder traversal): ");
    inorderTraversal(root);
    printf("\n");

    printf("Elements in BST before deletion of node (preorder traversal): ");
    preorderTraversal(root);
    printf("\n");

    printf("Elements in BST  before deletion of node (postorder traversal): ");
    postorderTraversal(root);
    printf("\n\n");

    int keyToDelete = 35;
    root = deleteNode(root, keyToDelete);
    printf("Node %d deleted from BST.\n", keyToDelete);

    printf("Height of the BST: %d\n", height(root));

    int keyToFind = 25;
    printf("For node %d:\n", keyToFind);
    Level_Height(root, keyToFind, 0);

    printf("\nElements in BST  after deleting node( 35)(inorder traversal): ");
    inorderTraversal(root);
    printf("\n");

    return 0;
}

struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct Node* insert(struct Node* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }
    if (value < root->data) {
        root->left = insert(root->left, value);
    } else if (value > root->data) {
        root->right = insert(root->right, value);
    }
    return root;
}

struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL) return root;

    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    } else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        struct Node* temp = root->right;
        while (temp->left != NULL) {
            temp = temp->left;
        }
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

int height(struct Node* root) {
    if (root == NULL) return -1;
    int HeightL  = height(root->left);
    int HeightR = height(root->right);
    return 1 + (HeightL  > HeightR ? HeightL  : HeightR);
}

void Level_Height(struct Node* root, int key, int level) {
    if (root == NULL) {
        printf("Node not found!\n");
        return;
    }
    if (root->data == key) {
        printf("Level: %d\n", level);
        printf("Height: %d\n", height(root));
        return;
    }
    if (key < root->data) {
        Level_Height(root->left, key, level + 1);
    } else {
        Level_Height(root->right, key, level + 1);
    }
}

void inorderTraversal(struct Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

void preorderTraversal(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

void postorderTraversal(struct Node* root) {
    if (root != NULL) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%d ", root->data);
    }
}



