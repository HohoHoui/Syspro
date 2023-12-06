#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};


void addq(struct node **head, struct node **tail, int data) {
    
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

   
    newNode->data = data;
    newNode->next = NULL;

    if (*tail == NULL) {
        *head = *tail = newNode;
    } else {
        (*tail)->next = newNode;
        *tail = newNode;
    }
}

int delete(struct node **head, struct node **tail) {
    if (*head == NULL) {
        fprintf(stderr, "Queue is empty\n");
        exit(EXIT_FAILURE);
    }

    struct node *temp = *head;
    int data = temp->data;

    *head = temp->next;
    free(temp);

    if (*head == NULL) {
        *tail = NULL;
    }

    return data;
}

void printQueue(struct node *head) {
    printf("Queue: ");
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

int main() {
    struct node *head = NULL; 
    struct node *tail = NULL; 

    while (1) {

        int data;
        if (scanf("%d", &data) == 1) {
            addq(&head, &tail, data);
        } else {
            printQueue(head);
            break;
        }
    }

    while (head != NULL) {
        printf("%d\n", delete(&head, &tail));
    }

    return 0;
}

