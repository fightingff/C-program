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
extern int Xp,Yp;

void PaintUnits(double X, double Y,double len)
{
    double ul = len/N;
    for (int i=2; i<=N-1;++i) // omit the wrapper
    {
        for(int j=2; j<=N-1;++j)
        {
            MovePen(X+(j-2)*ul, Y-(i-2)*ul);//转置过来
            if(mp[i][j] != 0||((i==Xp&&j==Yp)) )
			{
				switch(mp[i][j])
				{
					case 1:break;
					case -1:SetPenColor("White");break;
					case -2:SetPenColor("Blue");break;
					case -3:SetPenColor("Yellow");break;
					case 3: SetPenColor("Red");break;
				}
                if(i==Xp&&j==Yp) SetPenColor("Green");
					StartFilledRegion(1);
                    	DrawLine(ul, 0);
                    	DrawLine(0, ul);
                    	DrawLine(-ul, 0);
                    	DrawLine(0, -ul);
                	EndFilledRegion();
            	SetPenColor("Gray");
        	}
        }
    }
	if(mp[Xp][Yp]==-2) Page_Victory();
}

void DrawMaze()
{
    //(st, st)为迷宫左上角，len为迷宫边长，两者可以改为外部传入
    double W=GetWindowWidth(),H=GetWindowHeight(),len = H*0.9;
    SetPenColor("Gray");
    SetPenSize(2);
	PaintUnits(W-H,H-2, len);
}

void MouseEditMaze(){

}

void ShowPath(Pos *p){
	Tp tp=p;
	for(;p!=NULL;p=p->next){
		mp[p->x][p->y]=-3;
		ReDraw();
		Pause(0.1);
	}
	LoadGame();
	Pause(3.0);
    ReDraw();
}
#endif
