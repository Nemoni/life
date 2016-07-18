#ifndef _A_STAR_
#define _A_STAR_

typedef struct SearchNode{
    int posX;
    int posY;
    int fScore;
    int gScore;    
    int hScore;
	int available;
    struct SearchNode *parent;
}SearchNode;

#define WIDTH 20
#define HEIGHT 20

#define ESTIMATE_DISTANCE(start, dest) \
    sqrt(pow(dest.posX - start.posX, 2) + pow(dest.posY - start.posY, 2))

#define NEIGHBORS_NUM 8

#endif
