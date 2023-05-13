//author: Fmh & Wzj
//20230506 
//C大作业  迷宫
#ifndef GENERATINGMAZE_C
#define GENERATINGMAZE_C

#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<windows.h>
#include "Game.h"

extern int N;
extern int mp[maxn][maxn];
//控制复杂度，rank数值越大复杂度越低，>=0
static int Rank=0;
//存储地图 0表示墙 1表示路 3表示陷阱 -1表示起点，-2表示终点
typedef enum{
    Route,Wall,Trap     
}signs;
typedef struct Node {
    int IsWhat;
    struct Node* next;
}QNode;
typedef struct {
    QNode* head;
    QNode* tail;
}Queue;

int IsEmptyQ(Queue* q)
{
    return (q->head == NULL);
}
Queue* CreateQueue()
{
    Queue* q = ( Queue* ) malloc(sizeof(Queue));
    if(!q) {
        printf("No Room!\n");
        return NULL;
    }
    q->head = NULL;
    q->tail = NULL;
}

void AddNode(Queue* q, int IsWhat)
{
    QNode* qNode = (QNode*) malloc(sizeof(QNode));
    if(qNode == NULL) {
        printf("No Room!\n");
        return NULL;
    }
    qNode->IsWhat = IsWhat;
    qNode->next = NULL;
    if( q->head == NULL ) q->head = qNode;
    if( q->tail == NULL ) q->tail = qNode;
    else {
        q->tail->next = qNode;
        q->tail = qNode;
    }
}

void DeleteNode(Queue* q, int r)
{
    if(IsEmptyQ(q)) {
        printf("Empty Queue!\n");
        return 0;
    }
    QNode* temp = q->head;
    while( r>1 )
    {
        temp = temp->next;
    }
    if(q->head == q->tail) {
        q->head = NULL;
        q->tail = NULL;
    }
    else {
        temp->next = temp->next->next;
    }
}

int GetNode(Queue *q, int r)
{
    if(IsEmptyQ(q)) {
        printf("Empty Queue!\n");
        return 0;
    }
    QNode* qNode = q->head;
    while( r>0 )
    {
        qNode = qNode->next;
    }
    return qNode->IsWhat;
}

int QueueSize(Queue* q)
{
    if(IsEmptyQ(q)) {
        printf("Empty Queue!\n");
        return 0;
    }
    int size=0;
    QNode* qNode = q->head;
    while (qNode != NULL){
        size++;
        qNode = qNode->next;
    }
    return size;
    
}

static void MazeDfs(int x, int y) // 从（x,y) 开始生成地图
{
    mp[x][y] = Route;
    int dir[4][2]={{0,1},{0,-1},{1,0},{-1,0}};
    for (int i = 0; i < 4; i++) //实现每次拓展方向随机
    {
        int r=rand()%4;
        int temp=dir[0][0];
        dir[0][0] = dir[r][0];
        dir[r][0] = temp;
        temp = dir[0][1];
        dir[0][1] = dir[r][1];
        dir[r][1] = temp;
    }
    for (int i = 0; i < 4; i++) //
    {
        int dx=x;
        int dy=y;
        //
        int range = 1 + (Rank == 0 ? 0 : rand() % Rank); //range 决定此次朝这个方向走多远
        while (range > 0)
        {
            dx += dir[i][0];
            dy += dir[i][1];

            if (mp[dx][dy] == Route) break; //防止走回头路

            int count=0;
            for( int j = dx -1; j <= dx + 1; j++) //防止形成环
                for( int k = dy -1; k <= dy + 1; k++)
                    if ( (abs(j-dx)+abs(k-dy)) == 1 && mp[j][k] == Route ) count++;
            if ( count >= 2 ) break;
        
            range--;
            mp[dx][dy] = Route;
        }
        if ( range <= 0 ) MazeDfs( dx, dy ); //继续以此节点递归

    }
    
}

static void GeneratingMaze_Medium() 
{
   srand(GetTickCount());
   for(int i=1; i<=N; ++i )
        for(int j=1; j<=N; ++j)
            mp[i][j] = 1;
   for (int i=1; i<N; ++i)
    {
        mp[i][1] = Route;
        mp[1][i] = Route;
        mp[N][i] = Route;
        mp[i][N] = Route;
    }
    MazeDfs(3,3); //  起点定为(1,1)会产生环，出错
    while(1)      //  随机出口
    {
        int i = rand()%(N/2), j = rand()%(N/2);
        if( i>1 && j>1 && mp[N-i][N-j] == Route )
        {
            mp[N-i][N-j] = -2;
            break;
        }
    }
    for ( int k=pow(N/6,2); k>0; k--) //临时想法，添加随机多个陷阱
    {
        while (1)
        {
           int i = rand()%(N-2), j = rand()%(N-2);
            if (i>1&&j>1&&mp[N-i][N-j]==Route) 
		    {
			    mp[N-i][N-j]=3;
			    break;
		    }

        }  
    }

}

void GeneratingMaze_Hard()
{
    srand(GetTickCount());
   for(int i=1; i<=N; ++i )
        for(int j=1; j<=N; ++j)
            mp[i][j] = 1;
    for (int i=1; i<N; ++i)
    {
        mp[i][1] = Route;
        mp[1][i] = Route;
        mp[N][i] = Route;
        mp[i][N] = Route;
    }

    Queue* X = CreateQueue();
    Queue* Y = CreateQueue();
    
    AddNode(X,3);
    AddNode(Y,4);

    while(!IsEmptyQ(X)) {
        int r = rand() % QueueSize(X);
        int x = GetNode(X, r);
        int y = GetNode(Y, r);

        int count = 0;
		for (int i = x - 1; i < x + 2; i++) {	
			for (int j = y - 1; j < y + 2; j++) {
				if (abs(x - i) + abs(y - j) == 1 && mp[i][j] > 0) {
					++count;
				}
			}
        }

        if(count <= 1) {
            mp[x][y] = Route;
            for (int i = x - 1; i < x + 2; i++) {
				for (int j = y - 1; j < y + 2; j++) {
					if (abs(x - i) + abs(y - j) == 1 && mp[i][j] == 0) {
						AddNode(X, i);
                        AddNode(Y, j);
					}
                }
            }
        }

        DeleteNode(X, r);
        DeleteNode(Y, r);
    }

    mp[3][3] = Route;
    for( int i = N-2; i>=1; i--) {
        if(mp[i][N - 2] == Route) {
            mp[i][N - 1] = Route;
            break;
        }
    }
    
}
#endif
