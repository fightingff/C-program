#ifndef BFS_H
#define BFS_H

#include"Game.h"

extern int N;
extern int mp[maxn][maxn];
extern const int d[4][2];
Pos Q[maxn*maxn],Pre[maxn][maxn];
int vis[maxn][maxn];
int Check(int x,int y){return (x>=1&&x<=N&&y>=1&&y<=N&&mp[x][y]!=1&&!vis[x][y]);}
Pos BFS(int sx,int sy){
    int Hd=0,Tl=0;memset(vis,0,sizeof(vis));
    Q[++Tl]=(Pos){sx,sy,0},vis[sx][sy]=1;
    while(Hd<Tl){
        Pos now=Q[++Hd];
        for(int i=0;i<4;i++){
            int nx=now.x+d[i][0],ny=now.y+d[i][1];
            if(!Check(nx,ny)) continue;
            Q[++Tl]=(Pos){nx,ny,now.step+1};
            Pre[nx][ny]=now,vis[nx][ny]=1;
            if(mp[nx][ny]==-2) return Q[Tl];
        }
    }
}
extern int Step;
extern Pos Path[maxn*maxn];
void Get_Fastest(int sx,int sy){
    Pos T=BFS(sx,sy);
    Step=T.step,memset(Path,0,sizeof(Path));
    while(T.step) Path[T.step]=T,T=Pre[T.x][T.y];
}

#endif