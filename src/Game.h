#ifndef GAME_H
#define GAME_H

#define maxn 2005
int N; //��ͼ��С
int Xp,Yp;//��ǰλ��
int mp[maxn][maxn];
//�洢��ͼ 0��ʾ�� 1��ʾ�ϰ���-1��ʾ��㣬-2��ʾ�յ�
int Time; //��Ϸʱ��
int Rank; //��Ϸ�Ѷ�
struct Imaze{
    int stx,sty,len;
}imaze;// drawed maze information

typedef struct Point{
    int x,y,step;
    struct Point *next;
}Pos;
int Step;//����

int Total;
Pos *Head_List,*Tail_List;//��¼��Ҳ���

void Menu_Main();//���˵�
void Get_Fastest();//�����·

void Clock();//��ʱ��
void TabBar();//�Ϸ���ǩ��
void SideBar();//�����
void ReDraw();//ȫͼ�ػ�

void Page_About();//����ҳ��
void Page_Exit(); //�˳�ҳ��
void Page_Load();//����ҳ��
void Page_Victory();//ʤ��ҳ��
void Page_Info();//��Ϣҳ��

void MouseEditMaze();//���༭��ͼ

void GeneratingMaze(int rank);//�����Թ�

void DrawMaze();//�����Թ�
void ShowPath(Pos *p);//��ʾ·��

typedef struct Record_{
    int rank,cost;
    struct Record_ *next;
}Record;//��Ѽ�¼
void LoadRecord();//������Ѽ�¼
void LoadGame();//���뱣�����Ϸ
void SaveGame();//������Ϸ
int UpdateRecord();//������Ѽ�¼
int GetPlay();//��ȡ��Ϸ���
void LoadRecord_i(int id);//�����id����Ѽ�¼

void Go();//�ƶ�

typedef Record *Rp;
typedef Pos *Tp;
#endif
