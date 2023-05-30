#ifndef GAME_H
#define GAME_H

#define maxn 2005
int N; //��ͼ��С
int Xp,Yp;//��ǰλ��
int mp[maxn][maxn];
//�洢��ͼ 0��ʾ�� 1��ʾ�ϰ���-1��ʾ��㣬-2��ʾ�յ�
int Time; //��Ϸʱ��
int Rank; //��Ϸ�Ѷ�
int edit_mode; //�޸�ģʽ 

typedef struct Point{
    int x,y,step;
    struct Point *next;
}Pos;
struct Imaze{
	double x,y,mlen,ulen,slen;
}imaze;//Editģʽ����ʾ�ľ�����Ϣ 

int Step;//����

int Total;
Pos *Head_List,*Tail_List;//��¼��Ҳ���

void Menu_Main();//���˵�
void Get_Fastest();//�����·

void Clock();//��ʱ��
void TabBar();//�Ϸ���ǩ��
void SideBar();//�����
void ReDraw();//ȫͼ�ػ�
void SetFigures_Edit();//����Edit��ʼ���� 
void InitMaze_Edit();//���ÿհ��Թ� 

void Page_About();//����ҳ��
void Page_Exit(); //�˳�ҳ��
void Page_Edit(); // �ֶ��޸��Թ����� 
void Page_Load();//����ҳ��
void Page_Victory();//ʤ��ҳ��
void Page_Info();//��Ϣҳ��


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
void Edit();//�ֶ��޸� 

typedef Record *Rp;
typedef Pos *Tp;
#endif
