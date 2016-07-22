#define UNIT_NUM 50 // the numbers of unit or chromosome
#define CITY_NUM 10 // the numbers of the gene or city

#define MAX_GENERATION 20

#define CROSS_RATE 0.9 //the rate chose to cross
#define VARIATION_RATE 0.9 //the rate of variation


int cost_between_city[CITY_NUM][CITY_NUM] = {
    { 0,10,20,30,40,50,60,70,80,90},
    {10, 0,20,30,40,50,60,70,80,90},
    {20,20, 0,30,40,50,60,70,80,90},
    {30,30,20, 0,40,50,60,70,80,90},
    {40,40,20,30, 0,50,60,70,80,90},
    {50,50,20,30,40, 0,60,70,80,90},
    {60,60,60,60,60,60, 0,70,80,90},
    {70,70,70,70,70,70,70, 0,80,90},
    {80,10,20,30,40,50,60,70, 0,90},
    {90,10,20,30,40,50,60,70,80, 0}
}

int produce_first_generation(int popu[][CITY_NUM])
{

}

int calculate_fitness(int popu[][CITY_NUM], int fitness[])
{

}

int roulette_choice(int fitness[], int choiced[])
{

}

int cross_calculate(int popu[][CITY_NUM], int choiced[])
{

}
int variation_calculate(int popu[][CITY_NUM])
{

}

int best_fitness_find(int popu[][CITY_NUM], int fitness[])
{

}

int genetic()
{
    int max_fitness = 0;
    int genaration = 0;    
    int popu[UNIT_NUM][CITY_NUM];
    int fitness[UNIT_NUM];
    int choiced[UNIT_NUM*CROSS_RATE];

    produce_first_generation(popu);
    while (genaration < 10){
        calculate_fitness(popu, fitness);
        best_fitness_find(popu, fitness);
        
        roulette_choice(fitness, choiced);

        cross_calculate(popu, choiced);
        variation_calculate(popu);

        genaration++;
    }
}
