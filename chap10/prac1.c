#include <stdio.h>
#include <stdlib.h>

// Node 구조체 정의
struct node {
    int data;
    struct node *next;
};

// 스택에 데이터를 삽입하는 함수 (push)
void push(struct node **top, int data) {
    // 새로운 노드 생성
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // 데이터 설정 및 연결
    newNode->data = data;
    newNode->next = *top;
    *top = newNode;

    //printf("Pushed: %d\n", data);
}

// 스택에서 데이터를 제거하고 반환하는 함수 (pop)
int pop(struct node **top) {
    if (*top == NULL) {
        fprintf(stderr, "Stack is empty\n");
        exit(EXIT_FAILURE);
    }

    // 제거할 노드를 top에 설정하고 데이터 추출
    struct node *temp = *top;
    int data = temp->data;

    // top을 다음 노드로 이동하고 제거된 노드 해제
    *top = temp->next;
    free(temp);

    return data;
}

// 스택 전체를 출력하는 함수
void printStack(struct node *top) {
    printf("Print Stack: ");
    while (top != NULL) {
        printf("%d ", top->data);
        top = top->next;
    }
    printf("\n");
}

int main() {
    struct node *top = NULL; // 스택의 top 노드를 가리키는 포인터

    while (1) {
        //printf("Enter a number to push, or a non-numeric value to exit: ");

        int data;
        if (scanf("%d", &data) == 1) {
            // 숫자가 입력된 경우 push
            push(&top, data);
        } else {
            // 숫자 이외의 값이 입력된 경우 스택 출력 후 종료
            printStack(top);
            break;
        }
    }

    // 스택이 비어있을 때까지 pop하며 출력
    while (top != NULL) {
        printf("%d\n", pop(&top));
    }

    return 0;
}

