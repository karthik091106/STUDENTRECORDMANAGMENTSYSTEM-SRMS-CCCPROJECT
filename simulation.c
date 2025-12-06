#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   // for sleep()
#define MAX 5

int stack[MAX];
int top = -1;

// Cross-platform clear screen
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Display stack visually
void showStack() {
    printf("\n-----------------\n");
    printf("   STACK STATE\n");
    printf("-----------------\n");

    if (top == -1) {
        printf("|     EMPTY     |\n");
    } else {
        for (int i = MAX - 1; i >= 0; i--) {
            if (i <= top)
                printf("|     %3d      |\n", stack[i]);
            else
                printf("|              |\n");
        }
    }
    printf("-----------------\n");

    // Pause to view stack
    printf("\nPress Enter to continue...");
    while(getchar() != '\n');  // clear leftover input
    getchar();                  // wait for Enter
}

void push(int x) {
    clearScreen();
    printf("\nPUSH Operation Started...\n");
    sleep(1);

    if (top == MAX - 1) {
        printf("\nSimulation Result: STACK OVERFLOW!\n");
        sleep(1);
        return;
    }

    printf("Placing %d on top...\n", x);
    sleep(1);

    stack[++top] = x;

    printf("Element %d pushed successfully.\n", x);
    sleep(1);

    showStack();
}

void pop() {
    clearScreen();
    printf("\nPOP Operation Started...\n");
    sleep(1);

    if (top == -1) {
        printf("\nSimulation Result: STACK UNDERFLOW!\n");
        sleep(1);
        return;
    }

    printf("Removing %d from stack...\n", stack[top]);
    sleep(1);

    top--;

    printf("Element removed.\n");
    sleep(1);

    showStack();
}

void peek() {
    clearScreen();
    printf("\nPEEK Operation...\n");
    sleep(1);

    if (top == -1) {
        printf("Stack is EMPTY.\n");
    } else {
        printf("Top element is: %d\n", stack[top]);
    }

    showStack();
}

int main() {
    int choice, value;

    while (1) {
        printf("\n============ STACK SIMULATION ============\n");
        printf("1. Push\n2. Pop\n3. Peek\n4. Display Stack\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to push: ");
                scanf("%d", &value);
                push(value);
                break;

            case 2:
                pop();
                break;

            case 3:
                peek();
                break;

            case 4:
                clearScreen();
                showStack();
                break;

            case 5:
                printf("Exiting Simulation...\n");
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
