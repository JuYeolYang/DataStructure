#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct result_type{
    unsigned int student_number;
    char *name;
    int grading[4];
};
struct result_type a[] = {{1001, "name 1", 99, 88, 77, 66}, {1002,"name 2", 96, 86, 73, 65},
                            {1003,"name 3", 93, 83, 72, 63}, {1004,"name 4", 94, 84, 74, 64}};

void insert_student(struct result_type *std_array, int index);
void print_students(struct result_type *std_array, int std_total_number);

int main(){
    //std_array 선언
    struct result_type *std_array = (struct result_type *)malloc(sizeof(struct result_type) * 4);

    //데이터 삽입
    for(int i = 0; i < 4; i++){
        insert_student(std_array, i);
    }
    //std_array 출력
    print_students(std_array, 4);
    free(std_array);
}

void insert_student(struct result_type *std_array, int index){
    for(int i = 0; i < index; i++) std_array++;

    //학번
    std_array->student_number = a[index].student_number;

    //이름
    std_array->name = a[index].name;

    //4과목 점수
    for(int j = 0; j < 4; j++){
        std_array->grading[j] = a[index].grading[j];
    }
}

void print_students(struct result_type *std_array, int std_total_number){
    int sum = 0;
    for(int i = 0; i < std_total_number; i++){
        printf("#std_array[%d]\n", i);
        printf("학번 : %u\n", std_array->student_number);
        printf("이름 : %s\n", std_array->name);
        printf("과목 점수 : %d, %d, %d, %d\n", std_array->grading[0], std_array->grading[1], std_array->grading[2], std_array->grading[3]);
        for(int j = 0; j < 4; j++){
            sum += std_array->grading[j];
        }
        printf("합계 : %d\n\n", sum);
        sum = 0;
        std_array++;
    }
}