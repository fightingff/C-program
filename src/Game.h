#ifndef GAME_H
#define GAME_H

#define maxn 2005
int Tough_N;//难度
int N; //地图大小
int Xp,Yp;//当前位置
int mp[maxn][maxn];
//存储地图 0表示空 1表示障碍，-1表示起点，-2表示终点
int Time; //游戏时间
int Rank; //游戏难度
int edit_mode; //修改模式 

typedef struct Point{
    int x,y,step;
    struct Point *next;
}Pos;
struct Imaze{
	double x,y,mlen,ulen,slen;
}imaze;//Edit模式中显示的矩阵信息 

int Step;//步数

int Total;
Pos *Head_List,*Tail_List;//记录玩家操作

void Menu_Main();//主菜单
void Get_Fastest();//求最短路
void GetAll();//求所有路径

void MenuCSS();//菜单样式
void Clock();//计时器
void TabBar();//上方标签栏
void SideBar();//侧边栏
void ReDraw();//全图重绘
void SetFigures_Edit();//设置Edit初始参数 
void InitMaze_Edit();//设置空白迷宫 

void Page_About();//关于页面
void Page_Exit(); //退出页面
void Page_Edit(); // 手动修改迷宫界面 
void Page_Load();//加载页面
void Page_Victory();//胜利页面
void Page_Info();//信息页面
void Page_EditInfo();//编辑地图提示页面


void GeneratingMaze(int rank);//生成迷宫

void DrawMaze();//绘制迷宫
void ShowPath(Pos *p);//显示路径
void PaintUnits(double X, double Y,double len);//绘制迷宫单元

typedef struct Record_{
    int rank,cost;
    struct Record_ *next;
}Record;//最佳记录
void InitGames();//初始化游戏
void LoadRecord();//载入最佳记录
void LoadGame();//载入保存的游戏
void SaveGame();//保存游戏
int UpdateRecord();//更新最佳记录
int GetPlay();//获取游戏标号
void LoadRecord_i(int id);//载入第id个最佳记录
void Modify(int id);//修改第id个最佳记录

void Go();//移动
void Edit();//手动修改 

typedef Record *Rp;
typedef Pos *Tp;
#endif
