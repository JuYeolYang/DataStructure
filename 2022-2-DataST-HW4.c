/*
yang juyeol-32192539
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

void problem_3_1(){
    char swing[100];
    int N, x = 1, y = 1;
    scanf("%d", &N);
    getchar();
    scanf("%s", swing);
    getchar();
    

    int **field = (int **)malloc(sizeof(int*) * (N + 1));
    for(int i = 0; i < N + 1; i++) *(field + i) = (int *)malloc(sizeof(int) * (N + 1));
    
    //초기화
    for(int i = 0; i < N + 1; i++){
        for(int j = 0; j < N + 1; j++){
            *(*(field + i) + j) = 0;
        }
    }
    *(*(field + 1) + 1) = 1;
    for(int i = 0; swing[i]; i++){
        if(swing[i] == 'U'){
            if(x == 1) continue;
            else{
                *(*(field + x) + y) = 0;
                x--;
                *(*(field + x) + y) = 1;
            }
        }else if(swing[i] == 'D'){
            if(x == N) continue;
            else{
                *(*(field + x) + y) = 0;
                x++;
                *(*(field + x) + y) = 1;
            }
        }else if(swing[i] == 'L'){
            if(y == 1) continue;
            else{
                *(*(field + x) + y) = 0;
                y--;
                *(*(field + x) + y) = 1;
            }
        }else if(swing[i] == 'R'){
            if(y == N) continue;
            else{
                *(*(field + x) + y) = 0;
                y++;
                *(*(field + x) + y) = 1;
            }
        }
    }
    for(int i = 1; i < N + 1; i++){
        for(int j = 1; j < N + 1; j++){
            if(*(*(field + i) + j) == 1) {
                printf("(%d, %d)\n", i, j);
                break;
            }
        }
    }
    for(int i = 0; i < N + 1; i++) free(*(field + i));
    free(field);
}
void probelm_3_2(){
    char input[100];
    int M;
    
    //첫째 줄과 둘째 줄 입력
    scanf("%[^\n]s", input);
    getchar();
    scanf("%d", &M);
    getchar();
    
    char *ptr = strtok(input, " ");
    int N = atoi(ptr);

    //첫째 줄에 단어 추출
    char **terms = (char **)malloc(sizeof(char*) * N);
    for(int i = 0; i < N; i++){
        ptr = strtok(NULL, " ");
        *(terms + i) = (char *)malloc(strlen(ptr) + 1);
        strcpy(*(terms + i), ptr);
    }

    //셋째 줄 입력
    int **table = (int **)malloc(sizeof(int *) * N);
    int count_NonZero = 0;
    for(int i = 0; i < N; i++){
        *(table + i) = (int *)malloc(sizeof(int) * M);
        for(int j = 0; j < M; j++){
            scanf("%d", *(table + i) + j);
            if(*(*(table + i) + j) != 0) count_NonZero++;
        }
    }

    int **TDM = (int **)malloc(sizeof(int *) * count_NonZero);
    for(int i = 0; i < count_NonZero; i++) *(TDM + i) = (int *)malloc(sizeof(int) * 3);
    
    int k = 0;// 0 < k < count_NonZero
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(*(*(table + i) + j) != 0){
                *(*(TDM + k) + 0) = i;
                *(*(TDM + k) + 1) = j + 1;
                *(*(TDM + k) + 2) = *(*(table + i) + j);
                k++;
            }
        }
    }

    for(int i = 0; i < count_NonZero; i++){
        int temp = *(*(TDM + i) + 0);
        printf("%s 문서%d %d\n", *(terms + temp), *(*(TDM + i) + 1), *(*(TDM + i) + 2));
    }

    free(terms);

    for(int i = 0; i < N; i++) free(*(table + i));
    free(table);

    for(int i = 0; i < count_NonZero; i++) free(*(TDM + i));
    free(TDM);
}

int main(){
    printf("=====Problem_3_1()=====\n");
    problem_3_1();
    printf("\n=====Problem_3_2()=====\n");
    probelm_3_2();
}