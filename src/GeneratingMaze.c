//author: Fmh & Wzj
//20230506 
//C大作业  迷宫
#ifndef GENERATINGMAZE_C
#define GENERATINGMAZE_C

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<windows.h>
#include "Game.h"

extern int N;
extern int mp[maxn][maxn];
extern int Rank;
//控制复杂度，rank数值越大复杂度越低，>=0
//存储地图 0表示路 1表示墙 3表示奖励 4表示陷阱 -1表示起点，-2表示终点
typedef enum{
    Route,Wall,Trap     
}signs;


int IsOK(int rx,int ry) {return mp[rx-1][ry]+mp[rx+1][ry]+mp[rx][ry-1]+mp[rx][ry+1] > 2;}

void My_Delete(int h[], int r, int tail)
{
	for(int i=r ; i<tail-1; ++i) h[i]=h[i+1];
}

void MazeDfs(int x, int y) // 从（x,y) 开始生成地图
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

void GeneratingMaze_Medium() //深度优先算法生成迷宫 
{
   srand(GetTickCount());
   for(int i=1; i<=N; ++i )
        for(int j=1; j<=N; ++j)
            mp[i][j] = Wall;
   for (int i=1; i<=N; ++i)
    {
        mp[i][1] = Route;
        mp[1][i] = Route;
        mp[N][i] = Route;
        mp[i][N] = Route;
    }
    MazeDfs(3,3); //  起点定为(1,1)会产生环，出错
    while(1)      //  随机出口
    {
        int i = rand()%(N/3), j = rand()%(N/3);
        if( i>1 && j>1 && mp[N-i][N-j] == Route )
        {
            mp[N-i][N-j] = -2;
            break;
        }
    }
    mp[3][3] = -1;

}

void GeneratingMaze_Hard() //Prim算法生成迷宫 
{
   srand(GetTickCount());
   for(int i=1; i<=N; ++i )
        for(int j=1; j<=N; ++j)
            mp[i][j] = 1;
    for (int i=1; i<=N; ++i)
    {
        mp[i][1] = Route;
        mp[1][i] = Route;
        mp[N][i] = Route;
        mp[i][N] = Route;
    }
	
    int hX[N*N];//Queue* X = CreateQueue();
    int hY[N*N];//Queue* Y = CreateQueue();
    int head,tail;head=tail=0; 
    
    hX[tail]=3;hY[tail]=3;tail++;
    
    while(head < tail) {
    	
        int r = rand() % (tail-head); 
        
        int x = hX[r];
        int y = hY[r];

        int count = 0;
		for (int i = x - 1; i < x + 2; i++) {	
			for (int j = y - 1; j < y + 2; j++) {
				if (abs(x - i) + abs(y - j) == 1 && mp[i][j] == Route) {
					++count;
				}
			}
        }

        if(count <= 1) {
            mp[x][y] = Route;
            for (int i = x - 1; i < x + 2; i++) {
				for (int j = y - 1; j < y + 2; j++) {
					if (abs(x - i) + abs(y - j) == 1 && mp[i][j] == Wall) {
						hX[tail]=i;hY[tail]=j;tail++;
					}
                }
            }
        }

        My_Delete(hX, r, tail);
        My_Delete(hY, r, tail);
        tail--;
    }
    mp[3][3] = -1;
    for( int i = N-2; i>=1; i--) {
        if(mp[i][N - 2] == Route) {
            mp[i][N - 1] = -2;
            break;
        }
    }
    for ( int k=(inPage == 5 ? pow(N/10,2):8); k>0; k--) //添加随机多个奖励/钥匙 
    {
        while (1)
        {
           int i = rand()%(N-2), j = rand()%(N-2);
            if (i>1&&j>1&&mp[N-i][N-j]==Route) 
		    {
			    mp[N-i][N-j]=4;
			    break;
		    }

        }  
    }
    for ( int k=(inPage == 5 ? pow(N/10,2):4); k>0; k--) //添加随机多个陷阱 /门 
    {
        while (1)
        {
           int i = rand()%(N-2), j = rand()%(N-2);
           if( inPage != 5 ){
           		if (i>1&&j>1&&i<N-2&&j<N-2&&mp[N-i][N-j]==Wall) 
		    	{
			   		mp[N-i][N-j]=3;
			    	break;
		    	}
		   }
		   else{
            	if (i>1 && j>1 && i<N-5 && j<N-5 && mp[N-i][N-j]!=4  )
		    	{
		    		if((mp[N-i-1][N-j]+mp[N-i+1][N-j]==2 || mp[N-i][N-j+1] + mp[N-i][N-j-1]==2)\
							&& mp[N-i-1][N-j]+mp[N-i+1][N-j]+mp[N-i][N-j+1] + mp[N-i][N-j-1] <3) 
					{mp[N-i][N-j]=3;break;}
        		}
		    }
		}
    }  
}


void Eazymaze(int x1, int y1, int x2, int y2){
	if(x2-x1<2 || y2-y1<2) return;
	int x=x1+1+rand()%(x2-x1-1);
	int y=y1+1+rand()%(y2-y1-1);
	
	for(int i=x1;i<=x2;i++) mp[i][y]=Wall;
    for(int i=y1;i<=y2;i++) mp[x][i]=Wall;
    
    Eazymaze(x1,y1,x-1,y-1);
    Eazymaze(x+1, y+1, x2, y2);
    Eazymaze(x+1,y1,x2,y-1);
    Eazymaze(x1, y+1, x-1, y2);
    
    int r[4]={0};
    r[rand()%4]=1;
    
    for(int i=0;i<4;i++){
    	if(r[i]==0){
    		int rx=x,ry=y;
    		switch(i) {
    			case 0:{
    				rx=x1+rand()%(x-x1);
    				while(IsOK(rx,ry)) rx=x1+rand()%(x-x1); //printf("rx = %d, ????????:%d %d %d %d\n",rx,mp[rx][ry-1],mp[rx][ry+1],mp[rx-1][ry],mp[rx+1][ry]);}
					break;
				}
				case 1:{
					rx=x+1+rand()%(x2-x);
    				while(IsOK(rx,ry)) rx=x+1+rand()%(x2-x);
					break;
				}
				case 2:{
					ry=y1+rand()%(y-y1);
    				while(IsOK(rx,ry)) ry=y1+rand()%(y-y1);
					break;
				}
				case 3:{
					ry=y+1+rand()%(y2-y);
    				while(IsOK(rx,ry)) ry=y+1+rand()%(y2-y);
					break;
				}
			}
		mp[rx][ry] = Route;
		}
	}
}
void GeneratingMaze_Eazy() //递归算法生成迷宫 
{
	srand(GetTickCount());
	for( int i=2; i<=N-1; ++i)
		for (int j=2; j<=N-1; ++j) mp[i][j] = Wall;
	for(int i=3; i< N-1; i++)
		for(int j=3; j<N-1; j++) mp[i][j] = Route;
    
    Eazymaze(3, 3, N-2,N-2);
    //mp[2][0] = -1;
    mp[N-2][N-2] = -2; 
    
}
extern int Tough_N;
void GeneratingMaze(int rank){
	if(inPage==2) GeneratingMaze_Eazy();
	else if(inPage==5) {N=42;GeneratingMaze_Hard();}
	else switch(rank){
        	case 1:N=32;GeneratingMaze_Eazy();break;  
        	case 2:N=32;GeneratingMaze_Medium();break; 
        	case 3:N=32;GeneratingMaze_Hard();break;
        	default:LoadRecord_i(Tough_Base-rank);break;
    	}
    Xp=Yp=3;
    for(int i=2;i<=N;i++)
       for(int j=2;j<=N;j++) if(mp[i][j]==-1||mp[i][j]==-3) {Xp=i,Yp=j;return (void)(DrawMaze());}
    DrawMaze();
}

#endif
