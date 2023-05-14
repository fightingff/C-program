#ifndef GAME_H
#define GAME_H

#define maxn 2005
int N; //地图大小
int mp[maxn][maxn];
//存储地图 0表示空 1表示障碍，-1表示起点，-2表示终点
int Time; //游戏时间
typedef struct{
    int x,y,step;
}Pos;
int Step;
Pos Path[maxn*maxn];

void Menu_Main();
void Get_Fastest(int sx,int sy);
void TabBar();

void Page_About();
void Page_Exit(); 
void Page_Load();
void SideBar();

void GeneratingMaze(int rank);

void DrawMaze();
#endif
