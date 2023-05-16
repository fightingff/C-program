#ifndef GAME_H
#define GAME_H

#define maxn 2005
int N; //地图大小
int mp[maxn][maxn];
//存储地图 0表示空 1表示障碍，-1表示起点，-2表示终点
int Time; //游戏时间
int Rank; //游戏难度
typedef struct Point{
    int x,y,step;
    struct Point *next;
}Pos;
int Step;
Pos Path[maxn*maxn];
int Total;
Pos *Head_List;

void Menu_Main();
void Get_Fastest(int sx,int sy);
void TabBar();

void Page_About();
void Page_Exit(); 
void Page_Load();
void Page_Victory();
void SideBar();

void GeneratingMaze(int rank);

void DrawMaze();

typedef struct Record_{
    int rank,cost;
    struct Record_ *next;
}Record;
void LoadRecord();
int UpdateRecord();
#endif
