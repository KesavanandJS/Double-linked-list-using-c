#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the doubly linked list
struct node {
    int data;
    struct node *llink;
    struct node *rlink;
};

// Function to create a new node
struct node* createNode(int data) {
    struct node* newNode = (struct node*) malloc(sizeof(struct node));
    if (!newNode) {
        printf("Memory error\n");
        return NULL;
    }
    newNode->data = data;
    newNode->llink = newNode->rlink = NULL;
    return newNode;
}

// Function to add a node at the beginning of the list
void addAtBeginning(struct node** start, int data) {
    struct node* newNode = createNode(data);
    if (*start == NULL) {
        *start = newNode;
    } else {
        newNode->rlink = *start;
        (*start)->llink = newNode;
        *start = newNode;
    }
}

// Function to add a node at the end of the list
void addAtEnd(struct node** start, int data) {
    struct node* newNode = createNode(data);
    if (*start == NULL) {
        *start = newNode;
    } else {
        struct node* temp = *start;
        while (temp->rlink != NULL) {
            temp = temp->rlink;
        }
        temp->rlink = newNode;
        newNode->llink = temp;
    }
}

// Function to add a node at the middle of the list
void addAtPosition(struct node** start, int data, int position) {
    struct node* newNode = createNode(data);
    if (position == 0) {
        addAtBeginning(start, data);
    } else {
        struct node* temp = *start;
        int i = 0;
        while (temp != NULL && i < position - 1) {
            temp = temp->rlink;
            i++;
        }
        if (temp == NULL) {
            addAtEnd(start, data);
        } else {
            newNode->rlink = temp->rlink;
            newNode->llink = temp;
            if (temp->rlink != NULL) {
                temp->rlink->llink = newNode;
            }
            temp->rlink = newNode;
        }
    }
}

// Function to delete a node from the beginning of the list
void deleteAtBeginning(struct node** start) {
    if (*start == NULL) {
        printf("List is empty\n");
        return;
    }
    struct node* temp = *start;
    *start = (*start)->rlink;
    if (*start != NULL) {
        (*start)->llink = NULL;
    }
    free(temp);
}

// Function to delete a node from the end of the list
void deleteAtEnd(struct node** start) {
    if (*start == NULL) {
        printf("List is empty\n");
        return;
    }
    if ((*start)->rlink == NULL) {
        deleteAtBeginning(start);
        return;
    }
    struct node* temp = *start;
    while (temp->rlink->rlink != NULL) {
        temp = temp->rlink;
    }
    free(temp->rlink);
    temp->rlink = NULL;
}

// Function to delete a node from the middle of the list
void deleteAtPosition(struct node** start, int position) {
    if (position == 0) {
        deleteAtBeginning(start);
    } else {
        struct node* temp = *start;
        int i = 0;
        while (temp != NULL && i < position - 1) {
            temp = temp->rlink;
            i++;
        }
        if (temp == NULL || temp->rlink == NULL) {
            printf("Invalid position\n");
            return;
        }
        struct node* nodeToDelete = temp->rlink;
        temp->rlink = nodeToDelete->rlink;
        if (nodeToDelete->rlink != NULL) {
            nodeToDelete->rlink->llink = temp;
        }
        free(nodeToDelete);
    }
}

// Function to print the list
void printList(struct node* start) {
    while (start != NULL) {
        printf("%d ", start->data);
        start = start->rlink;
    }
    printf("\n");
}

int main() {
    int count = 0;
    struct node* start = NULL;

    // Add nodes to the list
    addAtEnd(&start, 10);
    addAtEnd(&start, 20);
    addAtEnd(&start, 30);

    // Print the list
    printf("List: ");
