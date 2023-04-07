#ifndef GAME_H
#define GAME_H

#define maxn 2005
int N;//地图大小
int mp[maxn][maxn];
//存储地图 0表示空 1表示障碍，-1表示起点，-2表示终点
const int d[4][2]={{0,1},{0,-1},{1,0},{-1,0}};//四个方向
typedef struct{
    int x,y,step;
}Pos;
int Step;
Pos Path[maxn*maxn];


void Get_Fastest(int sx,int sy);

#endif