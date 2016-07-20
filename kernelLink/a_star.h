#ifndef __A_STAR__
#define __A_STAR__

#define ESTIMATE_DISTANCE(start, dest) \
    sqrt(pow(dest.posX - start.posX, 2) + pow(dest.posY - start.posY, 2))*10

#define WIDTH    20
#define HEIGHT   20

typedef struct POSTITION
{
    int posX;
    int posY;
}POSTITION_STRU;

typedef struct SEARCHNODE
{
    struct list_head list;
    POSTITION_STRU position;
    int fScore;
    int gScore;    
    int hScore;
    struct SEARCHNODE *parent;
}SEARCHNODE_STRU;

#endif /* __A_STAR__ */
