#include <stdio.h>
//#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>  

#define UNIT_NUM 50 // the numbers of unit or chromosome
#define CITY_NUM 10 // the numbers of the gene or city

#define MAX_GENERATION 60

#define CROSS_RATE 0.9 //the rate chose to cross
#define VARIATION_RATE 0.1 //the rate of variation

#define DEBUG_FLAG 0
#define DEBUG(format, ...) \
    printf ("[func:%s,line:%d] "format, __FUNCTION__, __LINE__, ## __VA_ARGS__)

int cost_between_city[CITY_NUM][CITY_NUM] = {
  /*  A   B  C   D   E  F   G   H    I    J*/
    { 0,12,20,38,17,22,24,41,25,40},// A
    {12, 0,13,23,16,15,17,25,24,35},// B
    {20,13, 0,12,24,22,18,20,34,36},// C
    {38,23,12, 0,30,22,16,17,41,36},// D
    {17,16,24,30, 0,18,22,33,20,30},// E
    {22,15,22,22,18, 0,10,19,18,17},// F
    {24,17,18,16,22,10, 0,12,22,19},// G
    {41,25,20,17,33,19,12, 0,25,17},// H
    {25,24,34,30,20,18,22,25, 0,21},// I
    {40,35,36,30,30,17,19,17,21, 0} // J
};
/*****************************************************************************
 * Function      : rand_num
 * Description   : generate a rand number from start to end (include start
                   and end)
 * Input         : int start  
                int end    
 * Output        : None
 * Return        : 
 * Others        : 
 * Record
 * 1.Date        : 20160723
 *   Author      : Nemo Ni
 *   Modification: Created function

*****************************************************************************/
int rand_num(int start, int end)
{
    int number = 0;
    
    number = rand()%(end - start + 1);
    
#if  DEBUG_FLAG
    DEBUG("sart:%d,end:%d,return:%d\n", start, end, number + start);
#endif /* #if DEBUG_FLAG */
    
    return (number + start);
}

bool if_exist(int unit[], int end, int num)
{
    int i = 0;
    
    for (i=0; i<end; i++){
        if (unit[i] == num){
            return true;
        }
    }
    return false;
}

void generate_entity(int unit[])
{
    int start = 1, end = CITY_NUM;
    int i = 0;
    int number = 0;

    for (i=0; i<CITY_NUM; i++){
        do {
            number = rand_num(start, end);
        }while (if_exist(unit, i, number));
        unit[i] = number;
    }
#if  DEBUG_FLAG
    int j = 0;
    DEBUG("------------------\n");
    for (j=0; j<CITY_NUM; j++){
        printf("-%3d", unit[j]);
    }
    printf("\n");
#endif /* #if DEBUG_FLAG */
}

void produce_first_generation(int popu[][CITY_NUM])
{
    int i = 0;
    for (i=0; i<UNIT_NUM; i++){
        generate_entity(popu[i]);
    }
}

void calculate_fitness(int popu[][CITY_NUM], int fitness[])
{
    int i = 0, j = 0;
    int from = 0, to = 0;
    memset(fitness, 0, sizeof(int)*UNIT_NUM);
    for (i=0; i<UNIT_NUM; i++){
        for (j=0; j<CITY_NUM; j++){
            from = popu[i][j];
            if (j == (CITY_NUM-1)){
                to = popu[i][0];
            }else{
                to = popu[i][j+1];
            }
            fitness[i] += cost_between_city[from][to];
        }
    }
#if  DEBUG_FLAG
    int n = 0;
    DEBUG("------------------\n");
    for (n=0; n<UNIT_NUM; n++){
        printf("fitness[%d]:%d\n", n, fitness[n]);
    }
#endif /* #if DEBUG_FLAG */
}

void roulette_choice(int fitness[], int choiced[])
{
    int sum = 0, negation_sum = 0, number = 0, total = 0;
    int negation[UNIT_NUM];
    int i = 0, j = 0;
    
    for (i=0; i<UNIT_NUM; i++){
        sum += fitness[i];
    }
    /* the fitness is biger the cost is biger, so use it's negation to get the choise rate */
    for (i=0; i<UNIT_NUM; i++){
        negation[i] = sum - fitness[i];
        negation_sum += negation[i];
    }
    for (j=0; j<UNIT_NUM*CROSS_RATE; j++){
        number = rand_num(1, negation_sum);
        total = 0;
        for (i=0; i<UNIT_NUM; i++){
            total += negation[i];
            if (total >= number){
                choiced[j] = i;
                break;
            }
        }        
    }
    
#if  DEBUG_FLAG
    int n = 0;
    DEBUG("------------------\n");
    for (n=0; n<UNIT_NUM*CROSS_RATE; n++){
        if (n % 10 == 0){
            printf("\n");
        }
        printf("-choiced[%d]:%d", n, choiced[n]);
    }
    printf("\n");
#endif /* #if DEBUG_FLAG */
}

int exchange_position_value(int unit[], int index, int value)
{
    int i = 0;
    int tmp = 0;
    
    tmp = unit[index];
    if (tmp == value){
        return 0;
    }
    for (i=0; i<CITY_NUM; i++){
        if (unit[i] == value){
            unit[i] = tmp;
            break;
        }
    }
    unit[index] = value;
    return 0;
}

int cross_calculate(int popu[][CITY_NUM], int choiced[])
{
    int start_index = 0, end_index = 0;
    int i = 0, j = 0, offset = 0, tmp = 0, value = 0;
    offset = (UNIT_NUM*CROSS_RATE)/2;
    int n = 0;
    
    for (i=0; i<offset; i++){
        start_index = rand_num(0,CITY_NUM-1);
        end_index = rand_num(0,CITY_NUM-1);
        if (start_index > end_index){
            tmp = start_index;
            start_index = end_index;
            end_index = tmp;
        }
#if  DEBUG_FLAG
        DEBUG("------------------\n");
        printf("choiced[%d]:%d, start_index:%d, end_index:%d\n", i, choiced[i], start_index, end_index);
        for (n=0; n<CITY_NUM; n++){
            printf("-%3d", popu[choiced[i]][n]);
        }
        printf("\n");
        printf("choiced[%d+%d]:%d\n", i, offset, choiced[i+offset]);
        for (n=0; n<CITY_NUM; n++){
            printf("-%3d", popu[choiced[i+offset]][n]);
        }
        printf("\n");
#endif /* #if DEBUG_FLAG */
        for (j=start_index; j<=end_index; j++){
            value = popu[choiced[i]][j];
            exchange_position_value(popu[choiced[i]], j, popu[choiced[i+offset]][j]);
            exchange_position_value(popu[choiced[i+offset]], j, value);
        }
#if  DEBUG_FLAG
        printf("\nafter cross calculate\n");
        printf("choiced[%d]:%d\n", i, choiced[i]);
        for (n=0; n<CITY_NUM; n++){
            printf("-%3d", popu[choiced[i]][n]);
        }
        printf("\n");
        printf("choiced[%d+%d]:%d\n", i, offset, choiced[i+offset]);
        for (n=0; n<CITY_NUM; n++){
            printf("-%3d", popu[choiced[i+offset]][n]);
        }
        printf("\n");
#endif /* #if DEBUG_FLAG */
    }    
}

void variation_calculate(int popu[][CITY_NUM])
{
    int i = 0, index = 0, value = 0, entity = 0;
    for (i=0; i<UNIT_NUM*VARIATION_RATE; i++){
        entity = rand_num(0,UNIT_NUM-1);
        index = rand_num(0,CITY_NUM-1);
        value = rand_num(1,CITY_NUM);
#if  DEBUG_FLAG
        DEBUG("------------------\n");
        printf("entity:%d,index:%d,value:%d\n", entity, index, value);
        printf("before variation:\n");
        int n = 0;
        printf("popu[%d]:\n", entity);
        for (n=0; n<CITY_NUM; n++){
            printf("-%3d", popu[entity][n]);
        }
        printf("\n");
#endif /* #if DEBUG_FLAG */

        exchange_position_value(popu[entity], index, value);

#if  DEBUG_FLAG
        printf("afer variation:\n");
        printf("popu[%d]:\n", entity);
        for (n=0; n<CITY_NUM; n++){
            printf("-%3d", popu[entity][n]);
        }
        printf("\n");
#endif /* #if DEBUG_FLAG */
    }
}

int best_fitness_find(int popu[][CITY_NUM], int fitness[])
{
    int i = 0, j = 0;
    int best = 0;
    int index = 0;
    for (j=0; j<UNIT_NUM; j++){
        printf("fitness[%2d]:%d ", j, fitness[j]);
        for (i=0; i<CITY_NUM; i++){
            printf("%4d ", popu[j][i]);
        }
        printf("\n");
    }
    best = fitness[0];
    for (i=0; i<UNIT_NUM; i++){
        if (best > fitness[i]){
            best = fitness[i];
            index = i;
        }
    }
    printf("best :fitness[%2d]:%d\n", index, best);
}

int genetic()
{
    int max_fitness = 0;
    int genaration = 0;    
    int popu[UNIT_NUM][CITY_NUM];
    int fitness[UNIT_NUM];
    int choiced_num = UNIT_NUM*CROSS_RATE;
    int choiced[choiced_num];
    
    srand((unsigned)time(NULL));
    produce_first_generation(popu);
    while (genaration < MAX_GENERATION){
        calculate_fitness(popu, fitness);
        best_fitness_find(popu, fitness);
        
        roulette_choice(fitness, choiced);

        cross_calculate(popu, choiced);
        variation_calculate(popu);

        genaration++;
    }
}

int main()
{
    genetic();
}
