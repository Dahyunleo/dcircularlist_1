#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 과일 구조체 정의
typedef struct Fruit {
    char name[20];
    int price;
    struct Fruit* prev;
    struct Fruit* next;
    int selected;
} Fruit;

// 전역 변수
Fruit* head = NULL;
Fruit* selectedFruit = NULL;

// 이중 원형 연결 리스트에 과일 추가
void addFruit(char name[]) {
    Fruit* newFruit = (Fruit*)malloc(sizeof(Fruit));
    strcpy(newFruit->name, name);
    
    newFruit->selected = 0;

    if (head == NULL) {
        head = newFruit;
        head->prev = head;
        head->next = head;
        selectedFruit = head;
        selectedFruit->selected = 1;
    }
    else {
        Fruit* last = head->prev;
        newFruit->next = head;
        newFruit->prev = last;
        head->prev = newFruit;
        last->next = newFruit;
    }

    printf("%s이(가) 메뉴에 추가되었습니다.\n", name);
}

// 현재 선택된 과일 삭제
void removeSelectedFruit() {
    if (head == NULL) {
        printf("메뉴가 비어있습니다.\n");
        return;
    }

    Fruit* current = selectedFruit;

    if (current == head && current->next == head) {
        head = NULL;
        selectedFruit = NULL;
    }
    else {
        current->prev->next = current->next;
        current->next->prev = current->prev;
        if (current == head) {
            head = current->next;
            selectedFruit = head;
            selectedFruit->selected = 1;
        }
        else {
            selectedFruit = current->next;
            selectedFruit->selected = 1;
        }
    }

    printf("%s이(가) 메뉴에서 삭제되었습니다.\n", current->name);
    free(current);
}

// 메뉴 출력
void printMenu() {
    if (head == NULL) {
        printf("menu is empty.\n");
        return;
    }

    printf("List:\n");

    Fruit* current = head;

    do {
        printf("- %s ", current->name);
        if (current->selected)
            printf("[o]");
        printf("\n");
        current = current->next;
    } while (current != head);
}

// 다음 과일 선택
void selectNextFruit() {
    if (head == NULL) {
        printf("menu is empty.\n");
        return;
    }

    selectedFruit->selected = 0;
    selectedFruit = selectedFruit->next;
    selectedFruit->selected = 1;

    printf("%s을(를) 선택하였습니다.\n", selectedFruit->name);
}

// 이전 과일 선택
void selectPreviousFruit() {
    if (head == NULL) {
        printf("menu is empty.\n");
        return;
    }

    selectedFruit->selected = 0;
    selectedFruit = selectedFruit->prev;
    selectedFruit->selected = 1;

    printf("%s을(를) 선택하였습니다.\n", selectedFruit->name);
}

int main() {
    int choice;
    char name[20];
    int price;

    do {
        printf("\n1. insert fruit\n");
        printf("2. delete the currnt fruit\n");
        printf("3. output the fruit list(Output [0] at the end of the currently selected fruit\n");
        printf("4. next fruit\n");
        printf("5. previous fruit\n");
        printf("6. exit the program\n");
        printf("select a menu: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter the name of the fruit to add: ");
            scanf("%s", name);
            
            addFruit(name);
            break;
        case 2:
            removeSelectedFruit();
            break;
        case 3:
            printMenu();
            break;
        case 4:
            selectNextFruit();
            break;
        case 5:
            selectPreviousFruit();
            break;
        case 6:
            printf("Exit the program.\n");
            break;
        default:
            printf("Invalid menu.\n");
        }
    } while (choice != 6);

    return 0;
}
