#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef char element;
/* 
 * treeNode: 이진트리 노드이다
 * generalTreeNode: 일반트리 노드이다. node 맴버변수는 자식노드의 주소값을 저장하는 array이다
 */
typedef struct treeNode{
    element data;
    struct treeNode *left;  // 왼쪽 자식 노드
    struct treeNode *right; // 오른쪽 자식 노드
} treeNode;

typedef struct generalTreeNode{
    element data;
    int node_count; //자식노드의 개수
    struct generalTreeNode **node; // 자식노드를 배열로 저장
} generalTreeNode;

/*
 * makeRootNode: 매개변수로 저장할 데이터 값과 왼쪽, 오른쪽 자식 노드를 받는다. 
 * makegeneralRootNode: 
 * preorder: 이진트리를 전윈순회하여 노드의 data을 출려한다
 */
treeNode* makeRootNode(element data, treeNode *leftNode, treeNode *rightNode);
generalTreeNode *makegeneralRootNode(element data);
void preorder(treeNode *root);

/* ============ makeTree ============
 * node: 노드의 내용이 순서대로 들어가 있다. ex) node[0]: 'A'이면 0번째 노드의 값은 'A'라는 것을 의미한다
 * childs_count: 각 노드의 자식 개수가 저장되어 있다. ex) childs_count[0]: 3 이면 node[0]은 자식 노드를 총 3개를 가지고 있다는 의미이다.
 * length: 노드의 총 개수
 * 
 * 1. 자식 노드 접근을 편리하게 하기 위해서 generalTreeNode타입인 list 배열을 생성한다.
 *    length값 만큼 배열을 동적할당한다.
 * 
 * 2. list[N]에 node[N]의 값을 가지는 generalTreeNode를 생성하여 저장한다.(0<= N < length)
 * 
 * 3. list[N]->node는 childs_count[N]값만큼 동적할당해준다.
 * 
 * 4. index은 부모 노드의 자식노드의 위치를 가리킨다. 즉 list[N]->node[K] = list[index]인 것이다.(0<= K < childs_count[N]) 
 *    모든 자식노드를 저장하기 위해서 자식 노드 개수 만큼 index를 1증가시키면서 자식노드를 list[N]->node[K]에 저장한다.
 * 
 * 5. index가 length보다 커지면 반복문을 종료하고 list[0]을 반환한다. 즉, root 노드를 반환하는 것이다.
 */
generalTreeNode *makeTree(char node[], int childs_count[], int length);


/* ============ ConvertToBST ============
 * ConvertToBST: generalTreeNode(일반트리)의 root노드를 입력받으면 이진트리로 변환 후 treeNode로 반환한다
 * 
 * node: 노드의 내용이 순서대로 들어가 있다. ex) node[0]: 'A'이면 0번째 노드의 값은 'A'라는 것을 의미한다
 * childs_count: 각 노드의 자식 개수가 저장되어 있다. ex) childs_count[0]: 3 이면 node[0]은 자식 노드를 총 3개를 가지고 있다는 의미이다.
 * length: 노드의 총 개수
 * 
 * 기본적인 ConvertToBST는 재귀를 이용하는 것이다. 자식 노드 배열에서 첫 번째 자식 노드는 부모노드의 왼쪽 자식노드게 될 것이고 K번째 자식 노드의 오른쪽 노드는 K+1번째 자식노드가 될 것이다. 
 * 이 과정을 반복하는 것이다. 만약 자식 노드들이 없다면 leaf 노드이기 때문에 이진트리 노드를 생성 후 return해주면 된다
 */
treeNode *ConvertToBST(generalTreeNode *root);


/* ============ problem_12_1 ============
 * N: 나무가지 단계
 * K: 고양이가 울은 횟수
 * branch: 나뭇가지에 대한 정보. 1은 가지가 있는 것이고 0은 가지가 없는 것이다
 * 
 * 1. 매개변수로 입력받은 branch는 0 ~ 2^N-1이기 때문에 배열에서 자식 노드를 접근할 때 번거롭다
 *    따라서 branch 크기 보다 하나 더 큰 배열을 생성하여 시작 나무가지를 1번 위치로 바꿔준다.
 * 2. 고양이가 울은 횟수 만큼 나뭇가지를 올라간다. 그 후에 그 나뭇가지의 자식 나뭇가지가 있으면 나뭇가지 번호를 출력하지 않고
 *    그렇지 않다면 나뭇가지 번호를 출력한다
 */
void problem_12_1(int N, int K, int branch[]);


/* ============ problem_12_2 ============
 * list: 노드 번호와 그 곳에 들어갈 질문(or 답)이 저장되어 있다. 노드 번호는 오름차순으로 들어가 있다. ex) 1 날개가 있나요?
 * N: 노드의 총 개수를 의미한다
 * answer: 예, 아니요로 답한 순서가 저장되어 있다.
 * K: 질문의 개수를 의미한다.
 * 
 * 1. list의 마지막 문자열의 노드번호가 가장 큰 노드번호 이므로 그 숫자보다 크지만 가장 인접한 2의 제곱수를 구한다.
 *    만약 그 숫자가 2^N이라면 배열의 크기를 2^N개를 만든다,즉 포화이진트리를 만드는 것이다. 그 후 0번째 값은 비운채로 배열 안에는 노드내용만 순서대로 추가한다(자식 노드를 쉽게 접근하기 위해서이다)
 * 2. answer을 순서대로 읽고 만약 false이면 오른쪽 자식 노드로, true이면 왼쪽 자식노드로 넘어간다
 * 3. answer을 모두 마치고 현재 위치한 노드의 내용을 출력한다
*/
void problem_12_2(char *list[], int N, char *answer[], int K);


/* ============ problem_12_3 ============
 * node: 노드의 내용이 순서대로 들어가 있다. ex) node[0]: 'A'이면 0번째 노드의 값은 'A'라는 것을 의미한다
 * childs_count: 각 노드의 자식 개수가 저장되어 있다. ex) childs_count[0]: 3 이면 node[0]은 자식 노드를 총 3개를 가지고 있다는 의미이다.
 * length: 노드의 총 개수
 * 
 * ex)
 * node[] = {'A', 'B', 'C', 'D'}
 * childs_count[] = {2, 0, 1, 0}
 * length = 4
 * 
 *      A
 *    /   \
 *   B     C
 *          \
 *           D 
 * 
 * 
 * 1. length만큼 treeNode인 list 배열을 생성한다. 앞으로의 작업을 편리하게 진행하기 위해서는 노드의 접근 편리하게 할 수 있어야 한다.
 *    배열에 저장해두고 그 노드의 위치만 알 수 있다면 각 노드에 접근하기 편리해진다
 *    index를 이용하여 자식노드에 접근한다
 * 
 * 2. 자식 노드들 중에 첫 번째 자식노드는 이진트리로 표현하였을 때 왼쪽 자식노드이고 두 번째 자식 노드는 첫 번째 자식의 오른쪽 노드이다.
 *    즉 K번쨰 자식노드의 오른쪽 자식노드는 K+1번째 자식노드인 것이다.(1<= K <= childs_count[N]);
 * 
 * 3. 이진트리로 변환하여 왼쪽 자식 노드와 오른쪽 자식노드를 구분하는 방법
 * 
 * 4. index가 가리키는 노드는 부모 노드가 이진트리로 변환 하였을 때 왼쪽 자식 노드이다. 왼쪽 자식 노드에 child[index]를 넣는다
 * 
 * 5. child->right = child이다. 오른쪽 자식노드에 넣었다면 index를 1 증가시킨다. 
 *    이 방법을 for문을 이용하여 총 child_count[N]-1번 반복한다. 그 이유는 마지막 자식 노드는 오른쪽 자식을 갖지 않기 때문이다.
 */
void problem_12_3(char node[], int childs_count[], int length);


/* ============ problem_12_4 ============
 * root: 일반트리이다.
 * 
 * 1. 이진트리로 변환된 root노드를 preorder 형태로 출력한다. 이진트리로 변환되는 부분은 ConvertToBST이다.
 */
void problem_12_4(generalTreeNode *root);

int main(){
    printf("=====problem_12_1=====\n");
    int branch[] = {1,1,1,1,1,1,1,0,0,1,1,0,0,0,1};
    problem_12_1(3, 2, branch);

    printf("\n=====problem_12_2=====\n");
    char *list[] = {"1 날개가 있나요?", "2 날 수 있나요?", "3 털이 있나요?", "4 까치", "5 펭귄", "6 빨리 움직이나요?", "7 개구리", "12 다람쥐", "13 나무늘보"};
    char *answer[] = {"false", "true", "false"};
    problem_12_2(list, 9, answer, 3);
    

/*
        일반 트리
                A
           /    |   \
          B     C     D       
         / \    |   / | \ 
        E   F   G  H  I  J   
           / \
          K   L
        
        이진 트리
            A
           /  
          B  - C  - D       
         /     |   / 
        E - F  G  H - I - J   
           / 
          K - L

    ==>       A
             /
            B
          /   \
         E     C
          \   / \
           F G   D
          /     /  
         K     H
          \     \
           L     I
                  \
                   J
*/
    printf("\n=====problem_12_3=====\n");
    // 노드 번호 순서대로 노드의 값을 저장하는 배열이다
    char node[] = {'A','B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L'};
    // 자식 노드가 몇개가 있는지 알려주는 배열. 각 숫자의 위치는 node배열의 노드와 일대일대응된다
    int count_level_node[] = {3, 2, 1, 3, 0, 2, 0, 0, 0, 0, 0, 0};
    // 노드의 총 개수
    int N = sizeof(count_level_node)/sizeof(int);
    problem_12_3(node, count_level_node, N);
    
    printf("\n=====problem_12_4=====\n");
    // 배열로 표현된 일반트리를 연결된 일반트리로 바꾸는 과정
    generalTreeNode *root = makeTree(node, count_level_node, N);
    problem_12_4(root);
}

treeNode* makeRootNode(element data, treeNode *leftNode, treeNode *rightNode){
    treeNode *root = (treeNode *)malloc(sizeof(treeNode));  // 이진트리 노드 생성
    root->data = data;      
    root->left = leftNode;
    root->right = rightNode;
    return root;
}
generalTreeNode *makegeneralRootNode(element data){
    generalTreeNode *root = (generalTreeNode *)malloc(sizeof(generalTreeNode)); //일반트리 노드 생성
    root->data = data;
    root->node_count = 0;
    root->node = NULL;
    return root;
}
generalTreeNode *makeTree(char node[], int childs_count[], int length){
    /*
     * list: 노드들을 모두 저장하고 있는 배열
     * index: 자식 노드의 위치를 가리키고 있는 변수
     */
    generalTreeNode **list = (generalTreeNode **)malloc(sizeof(generalTreeNode *) * length);
    int index = 1;

    for(int i = 0; i < length; i++){    // list 초기화
        list[i] = makegeneralRootNode(node[i]); // 일반 노드 생성
        list[i]->node_count = childs_count[i];  // 자식 노드가 몇개 있는지 저장한다
        generalTreeNode **child = (generalTreeNode **)malloc(sizeof(generalTreeNode*) * childs_count[i]);   // 자식 노드 개수 만큼 공간을 할당해준다
        for(int j = 0; j < childs_count[i]; j++){   
            child[j] = (generalTreeNode *)malloc(sizeof(generalTreeNode));  // 자식 노드의 공간을 할당
        }
        list[i]->node = child;
    }
    
    for(int i = 0; i < length; i++){
        generalTreeNode **temp = list[i]->node; // i번째 노드의 자식 노드 배열
        for(int j = 0; j < childs_count[i]; j++){   
            temp[j] = list[index];  // 자식 노드를 저장한다
            index++;    // 다음 자식노드로 이동
        }
    }
    return list[0]; // root 노드 반환
}
treeNode *ConvertToBST(generalTreeNode *root){
    /* 
     * node: root->data값을 가진 노드를 생성한다
     * childs: root의 자식 노드 배열
     * left_node: 이진트리로 변환되었을 때 왼쪽 자식 노드
     * temp: 같은 레벨에 있는 자식 노드를 이진트리로 변환하였을 때 K+1번째 노드는 K번재의 오른쪽 자식 노드가 되므로
     *       K+1번째 노드가 K+2번째 노드를 오른쪽 자식노드로 저장할 때는 temp = temp->right를 한후 진행한다
     */
    if(root != NULL){
        treeNode *node = makeRootNode(root->data, NULL, NULL);
        if(root->node_count > 0){
            generalTreeNode **childs = root->node;
            treeNode *left_node = ConvertToBST(childs[0]);
            treeNode *temp = left_node;
            for(int i = 1; i < root->node_count; i++){
                temp->right = ConvertToBST(childs[i]);  // i번째 노드를 오른쪽 자식 노드로 저장한다
                temp = temp->right; // root의 다음 자식 노드로 이동
            }
            node->left = left_node; // node의 왼쪽 자식노드를 저장한다
        }
        return node;
    }
    else return NULL;
}
void preorder(treeNode *root){
    if(root){
        printf("%c ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void problem_12_1(int N, int K, int branch[]){
    /*
     * childs_count: 노드의 총 개수를 저장한다.
     * branch_start, branch_end: 고양이가 있을 나뭇가지 범위를 표시한 것이다. 따라서 고양이는 branch_start <= cat index <= branch_end 사이에 있다
     * new_branch: 계산을 편리하게 하기 위해서 branch 배열의 크기보다 하나 더 큰 배열로 동적할당하고 1번째 부터 사용한다.
     */
    int childs_count = pow(2, N + 1) - 1;   //노드의 총 개수를 저장한다.
    int branch_start = pow(2, K), branch_end = pow(2, K + 1) - 1;
    int *new_branch;

    printf("N: %d, K: %d\n", N, K);
    new_branch = (int *)malloc(sizeof(int) * (childs_count + 1));   // 새로운 나뭇가지 배열
    new_branch[0] = 0;  // 0번째는 사용하지 않는다
    for(int i = 0; i < childs_count; i++){  // branch의 값을 new_branch로 옮기는 과정이다
        printf("%d ", branch[i]);
        new_branch[i+1] = branch[i];
    }
    printf("\nresult: ");
    for(int i = branch_start; i <= branch_end; i++){ // 고양이가 있을 수 있는 범위
        if(new_branch[i] == 1){
            if(new_branch[i*2] == 0 && new_branch[i*2 + 1] == 0) {  // 자식 나뭇가지가 없다면 그 위치에 고양이가 있을 수 있다.
                printf("%d ",i);
            }
        }
    }
    free(new_branch);
}
void problem_12_2(char *list[], int N, char *answer[], int K){
    /* 
     * level: 트리의 레벨을 저장한다
     * total_node: 노드 총 개수의 + 1을 한 값이다.
     * number: 노드 중 가장 큰 노드 번호를 저장한다
     * index: answer을 따라서 최종적으로 도달하는 노드를 가리킨다.
     * root: 노드를 저장하고 있는 배열이다. 0번째는 사용하지 않는다.
    */
    int level = 0, total_node, number = atoi(list[N-1]);
    int index = 1;
    char **root;

    printf("N: %d\n", N);
    for(int i = 0; i < N; i++) printf("%s\n", list[i]);
    while(pow(2, level) < number) level++; //트리의 레벨을 구하는 과정
    total_node = pow(2, level); // 노드의 총 개수 + 1

    root = (char**)malloc(sizeof(char*) * total_node);  // 노드를 배열로 저장
    for(int i = 0; i < total_node; i++) root[i] = (char *)malloc(sizeof(char)); // 노드의 공간을 할당해준다
    for(int i = 0; i < N; i++){ // root의 노드 번호 위치에 노드 내용을 저장
        int temp = atoi(list[i]);   // 노드 위치
        if(list[i][1] == 32){   // 빈칸의 ASCII값은 32이다.
            root[temp] = list[i] + 2;  // 노드 번호가 한 자리인 경우
        }
        else root[temp] = list[i] + 3;  // 노드 번호가 두 자리인 경우
    }
    for(int i = 0; i < K; i++){ // 질문 확인
        if(answer[i] == "false"){
            printf("false ");
            index = index * 2 + 1;  // 오른쪽 자식 노드 위치로 이동
        }
        else{
            printf("true ");
            index = index * 2;  // 왼쪽 자식 노드 위치로 이동
        }
    }
    printf("\n\nresult: %s", root[index]);
}
void problem_12_3(char node[], int childs_count[], int length){
    /*
     * list: 일반트리 노드를 저장하고 있는 배열
     * index: 자식 노드 위치를 가리킨다
     */
    treeNode **list = (treeNode **)malloc(sizeof(treeNode*) * length);  // 노드를 저장할 배열 생성
    int index = 1;
    for(int i = 0; i < length; i++){
        *(list + i) = (treeNode *)malloc(sizeof(treeNode));
        list[i] = makeRootNode(node[i], NULL, NULL);
        printf("%d: %c\n", i, list[i]->data);
    }
    
    for(int i = 0; i < length; i++){
        if(index > length) break;
        list[i]->left = list[index];    // 왼쪽 자식 노드
        for(int j = 1; j < childs_count[i]; j++){   //오른쪽 자식 노드로 넣어 준다
            list[index]->right = list[index + 1];
            index += 1;
        }
        index += 1;
    }
    printf("preorder: ");
    preorder(list[0]);
}
void problem_12_4(generalTreeNode *root){
    /*
     * result: 이진트리로 변환된 root노드이다. 
     */
    treeNode *result = ConvertToBST(root);
    printf("preorder: ");
    preorder(result);
    printf("\n\n");
}