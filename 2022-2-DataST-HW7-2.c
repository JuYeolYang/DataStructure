/*
 *Name      : Juyeol Yang
 *StudentID : 32192539 
 *HW7-2     : solve p.226 응용문제 3, p.228 응용문제 4
 *Date      : 2022. 10. 18
 */
#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct CircularLinkedListNode{  // Store data, left node and right node
    element data;
    struct CircularLinkedListNode *llink;
    struct CircularLinkedListNode *rlink;
} CircularLinkedListNode;

typedef struct CircularLinkedQueue{ // CircularLinkedList is based on Queue.
    CircularLinkedListNode *tail;
}CircularLinkedList;

/*
 * CircularLinkedList function
 * 
 * createCircularLinkedList: create Double Circle linked Queue 
 * isEmtpy: cheak list is empty. If list is empty, return 1. or not return 0.
 * enqueue: store data in front(tail->rlink)
 * dequeue: delete rear data() and return it
 * getNode: Returns a CircularLinkedListNode with the position value received as a parameter.
 * insert: After creating a CircularLinkedListNode with data received as a parameter, insert it at the position received as a parameter.
 * replace: relpace data CircularLinkedListNode at the input location
 * peek: return front(tail->rlink) data
 * searchNode: Returns a node with the value received as a parameter.
 * printList: Prints from front(tail->rlink) to rear(tail) sequentially
 */
CircularLinkedList *createCircularLinkedList(void);
int isEmpty(CircularLinkedList *linked_tail);
void enqueue(CircularLinkedList *linked_tail, element data);
element dequeue(CircularLinkedList *linked_tail);
int size(CircularLinkedList *linked_tail);
CircularLinkedListNode *getNode(CircularLinkedList *linked_tail, int position);
void insert(CircularLinkedList *linked_tail, int position, element data);
void replace(CircularLinkedList *linked_tail, int position, element data);
element peek(CircularLinkedList *linked_tail);
CircularLinkedListNode *searchNode(CircularLinkedList *linked_tail, element data);
void printList(CircularLinkedList *linked_tail);

/*
 * probelm7_1
 * playlist: 음악 제목을 저장하는 리스트
 * selectsList: 반복할 음악 제목을 저장하는 리스트
 * 
 * 1. N과 K, 반복할 음악 제목을 매개변수로 받는다.
 * 2. N크기 만큼 playlist에 요소를 추가한다. 음악 제목은 A~Z순으로 들어간다.
 * 3. playlist에서 front부터 순차적으로 반복할 음악 제목이 있는지 검사한다. 만약 없다면 다음 음악 제목을 찾는다
 * 4. 음악 제목을 찾았으면 selectsList에 그 음악 제목을 추가한다
 * 5. 반복 재생할 음악을 모두 찾았으면 selectsList에 있는 음악 제목을 출력한다
 */
void problem7_1(int N, int K, char list[]);
/*
 * problem7_2
 * box: 박스 안에 있는 내용을 저장한다. 상자가 열여있다면 상자 안의 값은 0이다.
 * position: 현재 열어야 하는 상자 위치를 저장한다
 * 
 * 1. 1번 상자를 연 후 거기에 들어가 있는 수 만큼 오른쪽으로 이동한다. 만약 음수이면 왼쪽으로 이동한다. 이동하기 전에 상자 안의 값을 0으로 설정한다.
 * 2. 상자 안의 수 만큼 이동한다. 이 행동을 반복한다.
 * 3. 만약 이동한 상자가 이미 열려있다면, 즉 상자 안의 값이 0이라면 다음 상자로 이동한다. 안 열린 상자까지 이동한 후 상자 안의 값을 확인한다.
 *    오른쪽으로 이동하고 있었다면 0이 안나올 때 까지 오른쪽으로 이동하고, 그 반대면 왼쪽으로 계속 이동해 주면 된다.
 */
void problem7_2(int N, int K[]);
void test(void);

int main(){
    printf("======problem7_1======\n");
    int N = 15, K = 4;
    char list[] = {'H', 'A', 'N', 'B'};
    printf("N = %d, K = %d\n", N, K);
    problem7_1(15 ,4, list);
    
    printf("\n======problem7_2======\n");
    int box[] = {2, -1, 3, -2, 2, -1};
    N = 6;
    printf("N = %d, box: ", N);
    for(int i = 0; i < N; i++){
        printf("%d ", box[i]);
    }
    printf("\n");
    problem7_2(N, box);
}

CircularLinkedList *createCircularLinkedList(void){ // 새로운 리스트를 생성한다
    CircularLinkedList *l_tail = (CircularLinkedList *)malloc(sizeof(CircularLinkedList));
    l_tail->tail = NULL;
    return l_tail;
}

int isEmpty(CircularLinkedList *linked_tail){   // 리스트가 비어있는지 확인
    if (linked_tail->tail == NULL) return 1;    // 리스트가 비어있는 경우
    else return 0;  // 리스트가 비어있지 않은 경우
}

void enqueue(CircularLinkedList *linked_tail, element data){    // 리스트에 새로운 값을 저장한다
    CircularLinkedListNode *Node = (CircularLinkedListNode *)malloc(sizeof(CircularLinkedListNode));
    Node->data = data;
    if(linked_tail->tail == NULL){  // 리스트가 비어있을 경우
        Node->llink = Node;
        Node->rlink = Node;
        linked_tail->tail = Node;
    }
    else{   // 리스트가 비어있지 않은 경우
        Node->llink = linked_tail->tail;
        Node->rlink = linked_tail->tail->rlink;
        CircularLinkedListNode *linked_tail_rNode = linked_tail->tail->rlink;
        linked_tail->tail->rlink = Node;
        linked_tail_rNode->llink = Node;
        linked_tail->tail = Node;
    }
}

element dequeue(CircularLinkedList *linked_tail){   // 리스트의 front 값을 반환한다
    if(!isEmpty(linked_tail)){  // 리스트가 비어있지 않은 경우
        CircularLinkedListNode *front = linked_tail->tail->rlink;
        element data = front->data;
        if(front == linked_tail->tail){ // 리스트의 개수가 1개인 경우
            linked_tail->tail = NULL;
            free(front);
            return data;
        }
        else{   // 리스트의 개수가 2개 이상인 경우
            CircularLinkedListNode *temp_rNode = front->rlink;
            linked_tail->tail->rlink = temp_rNode;
            temp_rNode->llink = linked_tail->tail;
            free(front);
            return data;
        }
    }
}

int size(CircularLinkedList *linked_tail){  // 리시트의 크기를 반환한다
    if(isEmpty(linked_tail)){
        return 0;
    }
    else{
        CircularLinkedListNode *temp = linked_tail->tail->rlink;
        int count = 1;  // 위에서 이미 리스트가 비어있는지 확인하였기 때문에 리스트이 크기는 최소 1이다.
        while(temp != linked_tail->tail){
            temp = temp->rlink;
            count += 1;
        }
        return count;
    }
}

CircularLinkedListNode *getNode(CircularLinkedList *linked_tail, int position){ // 특정 위치의 노드를 반환한다
    if(position < 0) return NULL;
    else{
        CircularLinkedListNode *temp = linked_tail->tail->rlink;
        while(position > 0 && temp != linked_tail->tail){
            temp = temp->rlink;
            position -= 1;
        }
        return temp;
    }
}

void insert(CircularLinkedList *linked_tail, int position, element data){   // 특정 위치에 새로운 노드를 생성하고 데이터를 저장한다
    CircularLinkedListNode *before = getNode(linked_tail, position - 1);
    if(before != NULL){
        CircularLinkedListNode *temp = (CircularLinkedListNode *)malloc(sizeof(CircularLinkedListNode));
        CircularLinkedListNode *before_rNode = before->rlink;
        temp->data = data;
        temp->llink = before;
        temp->rlink = before_rNode;
        before_rNode->llink = temp;
        before->rlink = temp;
    }
    else{
        enqueue(linked_tail, data);
        linked_tail->tail = linked_tail->tail->llink;
    }
}

void replace(CircularLinkedList *linked_tail, int position, element data){  // 특정 위치에 있는 노드의 값을 바꾼다
    CircularLinkedListNode *temp = getNode(linked_tail, position);
    if(temp != NULL) temp->data = data;
}

element peek(CircularLinkedList *linked_tail){  // 리스트 front값 출력
    if(!isEmpty(linked_tail)){
        CircularLinkedListNode *front = linked_tail->tail->rlink;
        element data = front->data;
        return data;
    }
}

CircularLinkedListNode *searchNode(CircularLinkedList *linked_tail, element data){  // 리스트 안에 특정 데이터가 있는 노드를 반환한다
    if(!isEmpty(linked_tail)){
        CircularLinkedListNode *temp = linked_tail->tail->rlink;
        while(temp != linked_tail->tail){
            if(temp->data == data) return temp;
            else temp = temp->rlink;
        }
        return NULL;
    }
    else return NULL;
}

void printList(CircularLinkedList *linked_tail){
    if(!isEmpty(linked_tail)){
        CircularLinkedListNode *temp = linked_tail->tail->rlink;
        printf("Linked List: ");
        do{
            printf("%d ", temp->data);
            temp = temp->rlink;
        }
        while(temp->llink != linked_tail->tail);
        printf("\n");
    }
    else printf("Linked List is empty\n");
}

void problem7_1(int N, int K, char list[]){
    CircularLinkedList *playlist = createCircularLinkedList();
    CircularLinkedList *selectsList = createCircularLinkedList();
    for(int i = 0; i < N; i++){
        int music = (int)'A' + i;
        enqueue(playlist, music);
    }
    int index = 0;
    CircularLinkedListNode *temp = playlist->tail->rlink;
    while(index < K){
        int data = (int)list[index];
        if(temp->data == data){
            enqueue(selectsList, data);
            index += 1;
            temp = playlist->tail->rlink;
            continue;
        }
        temp = temp->rlink;
        if(temp->llink == playlist->tail) index += 1;
    }
    temp = selectsList->tail->rlink;
    while(temp != selectsList->tail){
        printf("%c ", temp->data);
        temp = temp->rlink;
    }
    printf("%c ", temp->data);
    while(!isEmpty(playlist)) dequeue(playlist);
    free(playlist);
}

void problem7_2(int N, int K[]){
    CircularLinkedList *box = createCircularLinkedList();       //상자 리스트
    CircularLinkedList *position = createCircularLinkedList();  //위치 리스트
    for(int i = 0; i < N; i++){
        enqueue(box, K[i]);
        enqueue(position, i+1);
    }
    CircularLinkedListNode *front = box->tail->rlink;
    for(int k = 0; k < N - 1; k++){
        int data = peek(box);   // 상자 안의 값 저장
        front->data = 0;        // 상자를 열었기 때문에 값을 0으로 저장
        printf("%d ", peek(position));  // 상자의 현재 위치 출력
        if(data > 0){
            for(int i = 0; i < data; i++){
                box->tail = box->tail->rlink;   // 상자 안의 값 만큼 tail 위치를 움직여 준다
                position->tail = position->tail->rlink; // 동일하게 움직여준다
            }
            front = box->tail->rlink;   // 현재 위치의 상자
            while(front->data == 0){    // 상자가 열린지 확인한다. 열려있다면 다음 상자를 확인한다
                box->tail = box->tail->rlink;
                position->tail = position->tail->rlink;
                front = box->tail->rlink;
            }
        }
        else{
            for(int i = 0; i > data; i--){  // 상자 안의 값이 양수 일 때와 동일하게 작동한다
                box->tail = box->tail->llink;
                position->tail = position->tail->llink;
            }
            front = box->tail->rlink;
            while(front->data == 0){
                box->tail = box->tail->llink;
                position->tail = position->tail->llink;
                front = box->tail->rlink;
            }
        }
    }
    printf("%d \n", peek(position));
    for(int i = 0; i < N; i++){
        dequeue(box);
        dequeue(position);
    }
    free(box);
    free(position);
}