/*
Name                : Juyeol Yang
Student Number      : 32192539
2022-2-DataST-HW6-2 : solve problems p.323 응용문제 7 and p.325 응용문제 8
*/
#include <stdio.h>
#include <stdlib.h>

typedef int element;// Queue data type
typedef int stack_element;// Stack data type

typedef struct QueueNode{ // Queue Node: store data and link
    struct QueueNode *link;
    element data;
}QueueNode;

typedef struct QueueType{ // store front and rear point
    QueueNode *front, *rear;
}QueueType;

typedef struct stackNode{// Stack struct
    stack_element data;
    struct stackNode* link;
}stackNode;

/*
 * Queue functions
 * createQueue: create Queue struct. Default setting is NULL.
 * isQueueEmpty: check Queue is empty. When Queue is empty, return 1, is not return 0
 * enQueue: store element into Queue. Before store element, Check isQueueEmtpy
 * deQueue: return front Queue data and delete it.
 * peekQ: return front Queue data.
 * printQ: show the element in 'cQ' Queue 
*/
QueueType* createQueue(void);
int isQueueEmpty(QueueType *cQ);
void enQueue(element data, QueueType *cQ);
element deQueue(QueueType *cQ);
element peekQ(QueueType* cQ);
void printQ(QueueType *cQ);

/*
 * Stack functions
 * isStackEmpty: check stack is empty
 * push: store stack_element TOS
 * pop: return TOS and delete it.
 * peek: show TOS
 * printStack: show the stack_element in 'top' stack
*/
int isStackEmpty(stackNode *top);
void push(stack_element item, stackNode **top);
stack_element pop(stackNode **top);
stack_element peek(stackNode *top);
void printStack(stackNode *top);

/* problem6_1
 * N과 K가 주어진다. N은 처음 총 인원 수, K는 K번째 사람을 가리킨다.
 * K번째 사람을 탈락시킨 후 1~K-1은 줄 뒤에 다시 선다.
 *      if N = 6, K = 3     
 *      1 2 3 4 5 6 -> 3 out
 *      4 5 6 1 2   -> 6 out
 *      ...
 * 1. N만큼 큐에 숫자를 넣는다.
 * 2. K-1번 deQueue해서 나온 값을 다시 enQueue를 한다. 그 후에 deQueue를 한 다음 그 숫자를 출력한다.
 *      1 2 3 4 5 6 => 2 3 4 5 6 1 => 3 4 5 6 1 2 -> 3 out
 *      4 5 6 1 2 => 5 6 1 2 4 => 6 1 2 4 5 -> 6 out
 *      ...
 */
void problem6_1(void);

/* problem6_2
 * 문제에서 1~N의 숫자가 주어지고 RQueue와 LQueue, Stack이 존재한다.
 * RQueue에는 1~N까지의 숫자가 중복없이 들어가있고 Stack과 LQueue에는 비어있다.
 * RQueue에 dequeue를 하는데 Stack에 저장할 수 있고 LQueue에 저장할 수 있다.
 * Stack은 RQueue에서 받은 값을 pop을 하여 LQueue에 저장할 수 있다.
 * 
 * 중복되지 않는 숫자 나열이 주어진다. LQueue는 RQueue나 Stack에서 받은 값으로 주어진 숫자 나열이 만족할 수 있는지 확인한다.
 * 1. RQueue, LQueue, Stack을 생성한다.
 * 2. RQueue에 1~N까지 숫자를 넣는다.
 * 3. itemQ = peekQ, itemS = peek 이라고 하면 index번째의 문자가 itemQ인지 itemS인지 확인하다. itemQ이면 deQueue를 하고, itemS이면 pop을 하여 LQueue에 저장한다.
 * 4. 만약 둘 다 아니면 deQueue한 값을 Stack에 저장한다.
 * 4. 만약 RQueue가 비어있고 Stack의 맨 위에 값이 주어진 숫자열 index번째와 같지 않다면 주어진 숫자열은 만족할 수 없는 숫자열이라고 판단하고 while문을 빠져나온다.
 * 5. RQueue와 Stack이 모두 비어 있으면 POSSIBLE을 아니면 IMPOSSIBLE을 출력한다.
 * 
 * 
 * RQueue: 1 2 3 4 5 6 
 * LQueue: 
 * Stack:
 * 
 * (1)                              (2)
 * index = 0    : 3 4 2 1 5 6       index = 0   : 3 4 2 1 5 6
 * item = 1                         item = 2
 * RQueue       : 2 3 4 5 6         RQueue      : 3 4 5 6 
 * LQueue       :                   LQueue      :
 * Stack        : 1                 Stack       : 1 2
 * 
 * 
 * (3)                              (4)
 * index = 0    : 3 4 2 1 5 6       index = 1   : 3 4 2 1 5 6
 * item = 3                         item = 4
 * RQueue       : 4 5 6             RQueue      : 5 6 
 * LQueue       : 3                 LQueue      : 3 4
 * Stack        : 1 2               Stack       : 1 2
 * 
 * (5)                              (6)
 * index = 2    : 3 4 2 1 5 6       index = 1   : 3 4 2 1 5 6
 * item = 2                         item = 1
 * RQueue       : 5 6               RQueue      : 5 6 
 * LQueue       : 3 4 2             LQueue      : 3 4 2 1
 * Stack        : 1                 Stack       :
 * ...
*/
void problem6_2(void);

int main(){
    printf("======Problem 6_1======\n");
    problem6_1();// solve problem 응용문제 7
    printf("\n======Problem 6_2======\n");
    problem6_2();// solve problem 응용문제 8
    return 0;
}

//Queue
QueueType* createQueue(void){
    QueueType *queue = (QueueType *)malloc(sizeof(QueueType));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

int isQueueEmpty(QueueType *cQ){
    if (cQ->front == NULL) return 1;
    else return 0;
}

void enQueue(element data, QueueType *cQ){
    QueueNode *temp = (QueueNode *)malloc(sizeof(QueueNode));
    temp->data = data;
    temp->link = NULL;
    if(isQueueEmpty(cQ)){
        cQ->front = temp;
        cQ->rear = temp;
    }
    else{
        cQ->rear->link = temp;
        cQ->rear = temp;
    }
}
element deQueue(QueueType *cQ){
    QueueNode *old = cQ->front;
    element item;
    if(isQueueEmpty(cQ)) return 0;
    else{
        item = old->data;
        cQ->front = cQ->front->link;
        if(cQ->front == NULL) cQ->rear == NULL;
        free(old);
        return item;
    }
}
element peekQ(QueueType *cQ){
    element item;
    if(isQueueEmpty(cQ)) return 0;
    else{
        item = cQ->front->data;
        return item;
    }
}

void printQ(QueueType *cQ){
    QueueNode *temp = cQ->front;
    printf("Linked Queue: [");
    while (temp){
        printf("%3d", temp->data);
        temp = temp->link;
    }
    printf("]");
}

//Stack
int isStackEmpty(stackNode *top){
    if(top == NULL) return 1;
    else return 0;
}
void push(stack_element item, stackNode **top){
    stackNode *temp = (stackNode *)malloc(sizeof(stackNode));

    temp->data = item;
    temp->link = *top;
    *top = temp;
}
stack_element pop(stackNode **top){
    stack_element item;
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
stack_element peek(stackNode *top){
    if(isStackEmpty(top)){
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
        printf("%d ", p->data);
        p = p->link;
    }
    printf("] ");
}

//problem
void problem6_1(void){
    QueueType *queue = createQueue(); //create Queue
    int N = 10, K = 4;
    printf("N: %d, K: %d\n",N, K);
    for(int i = 1; i < N+1; i++) enQueue((element)i, queue); // 초기화
    while(!isQueueEmpty(queue)){ // queue가 빌 때 까지 반복
        element item;
        for(int i = 0; i < K-1; i++){
            item = deQueue(queue);
            enQueue(item, queue);
        }
        item = deQueue(queue);
        printf("%d ", item);
    }
}

void problem6_2(void){
    QueueType *RQueue = createQueue();  // create RQueue
    QueueType *LQueue = createQueue();  // create LQueue
    stackNode *stack = NULL;            // create Stack

    int N = 10, index = 0;
    int K[] = {3,4,6,7,8,5,9,2,1,10};   // 문제에서 주어진 숫자열
    for(int i = 0; i < N; i++) printf("%d ", K[i]); 
    printf("\n");
    for(int i = 1; i < N+1; i++) enQueue((element)i, RQueue);   // 초기화

    while (index < N){  // 주어진 숫자열을 모두 검사한 후 끝낸다
        element itemQ = peekQ(RQueue);
        stack_element itemS = peek(stack);
        if(K[index] == itemQ){  // index 번째와 itemQ가 같은지 확인
            itemQ = deQueue(RQueue);
            enQueue(itemQ, LQueue);
            index++;
            continue;
        }
        else if(K[index] == itemS){ // index 번째와 itemS가 같은지 확인
            itemS = pop(&stack);
            enQueue((element)itemS, LQueue);
            index++;
            continue;
        }
        else{   //둘 다 아니면 Stack에 저장
            itemQ = deQueue(RQueue);
            push((stack_element)itemQ, &stack);
        }
        //RQueue가 비어있고 TOS값이 index번째의 값과 다르면 while문을 빠져나온다
        if(isQueueEmpty(RQueue) && K[index] != peek(stack)) break;
    }
    // RQueue와 Stack이 비어있으면 POSSIBLE, 아니면 IMPOSSIBLE 출력
    if(isQueueEmpty(RQueue) && isStackEmpty(stack)) printf("POSSIBLE\n");
    else printf("IMPOSSIBLE\n");
}