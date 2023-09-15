/*
@author     : Juyeol Yang
@StudentID  : 32192539
@date       : 2022. 10. 04

@Information: fromInorderToPostorder()
symbol: 사칙연산 기호를 저장하는 스택
item: 스택에서 pop()해서 나온 값
myStack: 중위 표기법으로 표시된 문자열을 역순으로 들어가 있는 스택

우선순위가 같거나 높으면 우선순위가 높은 순으로 출력하는 것이 원칙
1. '('가 들어오면 symbol 스택에 저장한다
2. ')'가 들어오면 symbol 스택에 '('가 나올 때 까지 pop()연산을 반복한다.
3. '*, /'은 사칙연산 중 가장 우선순위가 높기 때문에 symbol 스택 가장위에 저장되어 있는 사칙연산 기호가 우선순위가 낮으면 스택에 저장하고, 아니면 symbol 스택이 빌 때까지, 혹은 '('가 나올 때 까지, 우선순위가 낮은 기호가 나올 때 까지 pop()연산을 반복한다.
4. '+, -'은 사칙역산 중에 우선순위가 가장 낮으므로 '('가 나오거나 symbol 스택이 비어질 때 까지 pop()연산을 반복한다. symbol 스택이 비어있으면 저장한다.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef char element;

typedef struct stackNode{
    element data;
    struct stackNode* link;
} stackNode;


int isStackEmpty(stackNode *top);
void push(element item, stackNode **top);
element pop(stackNode **top);
element peek(stackNode *top);
void printStack(stackNode *top);
void fromInorderToPostorder(stackNode *myStack);

int main(){
    char test[100]="A/(B+C)*D"; //ABC+/D*
    stackNode *test_top = NULL;
    for(int i = strlen(test) - 1; i > -1; i--) {
        push(test[i], &test_top);
    }
    printStack(test_top);
    printf("\n후위 표기식: ");
    fromInorderToPostorder(test_top);
    printf("\n");
    return 0;
}



int isStackEmpty(stackNode *top){
    if(top == NULL) return 1;
    else return 0;
}
void push(element item, stackNode **top){
    stackNode *temp = (stackNode *)malloc(sizeof(stackNode));

    temp->data = item;
    temp->link = *top;
    *top = temp;
}
element pop(stackNode **top){
    element item;
    stackNode *temp = *top;

    if(isStackEmpty(*top)){
        printf("\n\n Stack is empty !\n");
        return 0;
    }
    else{
        item = temp->data;
        *top = temp->link;
        free(temp);
        return item;
    }
}
element peek(stackNode *top){
    if(isStackEmpty(top)){
        printf("\n\n Stack is empty !\n");
        return 0;
    }
    else{
        return (top->data);
    }
}
void printStack(stackNode *top){
    stackNode *p = top;
    printf("\n STACK [");
    while(p){
        printf("%c ", p->data);
        p = p->link;
    }
    printf("] ");
}
void fromInorderToPostorder(stackNode *myStack){
    stackNode *symbol = NULL;
    while(!isStackEmpty(myStack)){
        element item = pop(&myStack);
        switch (item)
        {
        case '(':
            push(item, &symbol);
            break;
        case ')':
            while(!isStackEmpty(symbol) && peek(symbol) != '('){
                printf("%c", pop(&symbol));
            }
            pop(&symbol);//symbol 스택에 '('을 지우는 과정
            break;
        case '*':
        case '/':
            if(!isStackEmpty(symbol)){
                element temp = item;
                item = peek(symbol);
                switch(item){
                    case '*':
                    case '/':
                        while(!isStackEmpty(symbol) && peek(symbol) != '(' && peek(symbol) != '+' && peek(symbol) != '-'){
                            printf("%c",pop(&symbol));
                        }
                        push(temp, &symbol);
                        break;
                    case '(':
                        push(temp, &symbol);
                        break;
                    default:
                        push(temp, &symbol);
                        break;
                }
                break;
            }
            else push(item, &symbol);
            break;
        case '+':
        case '-':
            if(!isStackEmpty(symbol)){
                element temp = item;
                item = peek(symbol);
                switch(item){
                    case '*':
                    case '/':
                    case '+':
                    case '-':
                        while(!isStackEmpty(symbol) && peek(symbol) != '('){
                            printf("%c",pop(&symbol));
                        }
                        push(temp, &symbol);
                        break;
                    case '(':
                        push(temp, &symbol);
                        break;
                    default:
                        push(temp, &symbol);
                        break;
                }
                break;
            }
            else push(item, &symbol);
            break;
        default:
            printf("%c",item);
            break;
        }
    }
    while(!isStackEmpty(symbol)) printf("%c",pop(&symbol));
}