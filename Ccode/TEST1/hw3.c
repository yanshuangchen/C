#include <stdio.h>
#define MAX_SIZE 100

typedef struct {
    int items[MAX_SIZE];
    int front;
    int rear;
} Deque;

void init(Deque* D) {
    D->front = -1;
    D->rear = -1;
}

int is_empty(Deque* D) {
    return D->front == -1;
}

int is_full(Deque* D) {
    return (D->front == 0 && D->rear == MAX_SIZE - 1) || (D->front == D->rear + 1);
}

void push(int x, Deque* D) {
    if (is_full(D)) {
        printf("Deque is full. Cannot push element.\n");
        return;
    }
    if (D->front == -1) {
        D->front = 0;
        D->rear = 0;
    } else if (D->front == 0) {
        D->front = MAX_SIZE - 1;
    } else {
        D->front--;
    }
    D->items[D->front] = x;
}

int pop(Deque* D) {
    if (is_empty(D)) {
        printf("Deque is empty. Cannot pop element.\n");
        return -1;
    }
    int x = D->items[D->front];
    if (D->front == D->rear) {
        D->front = -1;
        D->rear = -1;
    } else if (D->front == MAX_SIZE - 1) {
        D->front = 0;
    } else {
        D->front++;
    }
    return x;
}

void inject(int x, Deque* D) {
    if (is_full(D)) {
        printf("Deque is full. Cannot inject element.\n");
        return;
    }
    if (D->front == -1) {
        D->front = 0;
        D->rear = 0;
    } else if (D->rear == MAX_SIZE - 1) {
        D->rear = 0;
    } else {
        D->rear++;
    }
    D->items[D->rear] = x;
}

int eject(Deque* D) {
    if (is_empty(D)) {
        printf("Deque is empty. Cannot eject element.\n");
        return -1;
    }
    int x = D->items[D->rear];
    if (D->front == D->rear) {
        D->front = -1;
        D->rear = -1;
    } else if (D->rear == 0) {
        D->rear = MAX_SIZE - 1;
    } else {
        D->rear--;
    }
    return x;
}

int main() {
    Deque D;
    init(&D);

    push(1, &D);
    push(2, &D);
    push(3, &D);
    printf("Pop: %d\n", pop(&D));  // Output: 3

    inject(4, &D);
    inject(5, &D);
    inject(6, &D);
    printf("Eject: %d\n", eject(&D));  // Output: 6

    return 0;
}