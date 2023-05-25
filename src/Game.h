#ifndef GAME_H
#define GAME_H

#define maxn 2005
int N; //地图大小
int Xp,Yp;//当前位置
int mp[maxn][maxn];
//存储地图 0表示空 1表示障碍，-1表示起点，-2表示终点
int Time; //游戏时间
int Rank; //游戏难度
struct Imaze{
    int stx,sty,len;
}imaze;// drawed maze information

typedef struct Point{
    int x,y,step;
    struct Point *next;
}Pos;
int Step;//步数

int Total;
Pos *Head_List,*Tail_List;//记录玩家操作

void Menu_Main();
int Check(int x,int y);
void Get_Fastest();
void TabBar();
void SideBar();
void ReDraw();

void Page_About();
void Page_Exit(); 
void Page_Load();
void Page_Victory();

void MouseEditMaze();

void GeneratingMaze(int rank);

void DrawMaze();
void ShowPath(Pos *p);

typedef struct Record_{
    int rank,cost;
    struct Record_ *next;
}Record;
void LoadRecord();
void LoadGame();
void SaveGame();
int UpdateRecord();

void Go();

typedef Record *Rp;
typedef Pos *Tp;
#endif
