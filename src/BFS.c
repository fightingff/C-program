#ifndef BFS_C
#define BFS_C

#include"Game.h"
#include<string.h>
#include<stdlib.h>
#include"extgraph.h"
#include"graphics.h"
#include"imgui.h"

extern int N;
extern int mp[maxn][maxn];
const int Dpos[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
Pos Q[maxn*maxn],Pre[maxn][maxn];
int vis[maxn][maxn];
int Check(int x,int y){return (x>=1&&x<=N&&y>=1&&y<=N&&mp[x][y]!=1&&!vis[x][y]);}
Pos BFS(int sx,int sy){//BFS求最短路，以(sx,sy)为起点
    int Hd=0,Tl=0;memset(vis,0,sizeof(vis));
    Q[++Tl]=(Pos){sx,sy,0},vis[sx][sy]=1;
    while(Hd<Tl){
        Pos now=Q[++Hd];
        for(int i=0;i<4;i++){
            int nx=now.x+Dpos[i][0],ny=now.y+Dpos[i][1];
            if(!Check(nx,ny)) continue;
            Q[++Tl]=(Pos){nx,ny,now.step+1};
            Pre[nx][ny]=now,vis[nx][ny]=1;
            if(mp[nx][ny]==-2) return Q[Tl];
        }
    }
    Q[1].step=-1;
    return Q[1];
}
extern int Step;
void Get_Fastest(){
    Pos T=BFS(Xp,Yp);
    if(!~T.step){
        double W=GetWindowWidth(),H=GetWindowHeight();
        SetPointSize(50),SetPenColor("Red");
        drawBox(W-H+2,H/2,4,2,1,"Error!",'C',"Yellow");
        Pause(1.0);
        DisplayClear();
        ReDraw();
        return;
    }
    Step=T.step;
    Tp p=NULL;
    while(T.step){//用链表存储路径
        Tp q=(Tp)malloc(sizeof(Pos));
        q->x=T.x,q->y=T.y,q->step=T.step;
        q->next=p,p=q,T=Pre[T.x][T.y];
    }
    SaveGame();
    ShowPath(p);
}
void GetAll(){
    BFS(Xp,Yp);
    Tp Hd=NULL,Tl=NULL;
    for(int i=1;;i++){
        Tp q=(Tp)malloc(sizeof(Pos));
        q->x=Q[i].x,q->y=Q[i].y,q->step=Q[i].step;
        if(Hd==NULL) Hd=q;else Tl->next=q;
        Tl=q; 
        if(mp[q->x][q->y]==-2) break;
    }
    SaveGame();
    ShowPath(Hd);
}

#endif
