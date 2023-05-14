#ifndef DRAWMAZE_C
#define DRAWMAZE_C
#include"Game.h"
#include"math.h"
#include"graphics.h"
#include"imgui.h"
#include"extgraph.h"

#define MIN(x,y) ((x) < (y) ? (x) : (y))
extern int N;
extern int mp[maxn][maxn];


void drawLines(double X, double Y,double len)
{
	SetPenSize(1.5);
    double ul = len/N;
    for (int i=1; i<=N-1; ++i)
    {
        MovePen(X, Y-(i-1)*ul);
        DrawLine(len-2*ul, 0);
    }
    for (int j=1; j<=N-1; ++j)
    {
        MovePen(X+(j-1)*ul, Y);
        DrawLine(0, len-2*ul);
    }
}
void PaintUnits(double X, double Y,double len)
{
    double ul = len/N;
    for (int i=2; i<=N-1;++i) // omit the wrapper
    {
        for(int j=2; j<=N-1;++j)
        {
            MovePen(X+(i-2)*ul, Y-(j-2)*ul);
            if( mp[i][j] == 1 || mp[i][j] == 3 ){
                StartFilledRegion(1);
                    DrawLine(ul, 0);
                    DrawLine(0, ul);
                    DrawLine(-ul, 0);
                    DrawLine(0, -ul);
                EndFilledRegion();
            }
        }
    }
}

void DrawMaze()
{
    //(st, st)为迷宫左上角，len为迷宫边长，两者可以改为外部传入
    double W=GetWindowWidth(),H=GetWindowHeight(),len = H*0.9; 
    SetPenColor("Gray");
    SetPenSize(2);
    
	PaintUnits(W-H,H-2, len);
    // drawLines(W-H,H-2, len);
    
}


#endif
