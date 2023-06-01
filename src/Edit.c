#ifndef EDIT_C_
#define EDIT_C_
#include"Game.h"
#include"graphics.h"
#include"extgraph.h"
#include"imgui.h"
#include <math.h>

extern int mp[maxn][maxn];
extern int N;
extern int edit_mode;
extern struct Imaze imaze;

void MouseEvent_Edit(int x ,int y, int button ,int event);
void Edit(){registerMouseEvent(MouseEvent_Edit);}
int CheckArea(double x, double y)
{//判断地图合法性
	//printf("\nmaze's x = %lf, maze's y = %lf",imaze.x, imaze.y);
	//printf("x = %lf, y = %lf\n",x,y);
	return ( x>=imaze.x && x<=imaze.x+imaze.mlen && y<=imaze.y && y>=imaze.y-imaze.mlen) ;
}
void MouseEvent_Edit(int x, int y, int button, int event)
{//鼠标点击绘制地图
	uiGetMouse(x,y,button,event);
	double mx=ScaleXInches(x),my=ScaleYInches(y);
	if(CheckArea(mx, my)){
		int dx = (mx-imaze.x)/imaze.ulen;
		int dy = (imaze.y-my)/imaze.ulen;
	//	printf("dx = %d, dy = %d\n",dx,dy);
		switch (edit_mode){
			case 1:
				if (button == LEFT_BUTTON && event == BUTTON_DOWN) mp[2+dy][2+dx] = 0;	break;
			case 2: 
				if (button == LEFT_BUTTON && event == BUTTON_DOWN) mp[2+dy][2+dx] = 1;	break;
			case 3:
				if (button == LEFT_BUTTON && event == BUTTON_DOWN) {// 4)let -3 be entry temperaril ,to be changed
					for(int i=2;i<N;i++)
						for(int j=2;j<N;j++) if(mp[i][j]==-3) mp[i][j]=0;
					mp[2+dy][2+dx] = -3;	
					break; 
			}
			case 4:
				if (button == LEFT_BUTTON && event == BUTTON_DOWN) mp[2+dy][2+dx] = -2;	break;
			case 5:
				if (button == LEFT_BUTTON && event == BUTTON_DOWN) mp[2+dy][2+dx] = 3;	break;
			default:;
		}
	}
	Page_Edit();
}
void InitMaze_Edit(){//地图初始化
	for(int i=1; i<= N; i++)
		for(int j=1; j<=N; j++) mp[i][j] = 1;
	for(int i=3; i< N-1; i++)
		for(int j=3; j<N-1; j++) mp[i][j] = 0;
}
void SetFigures_Edit() // initial figures for Page_Edit;
{
	N = 22;
	SetPointSize(18);
	double W=GetWindowWidth(),H=GetWindowHeight();
	double fH = GetFontHeight();
	double h = fH*1.5, X = h, Y = H-h*4, len = H -h*4;
	imaze.x = X, imaze.y = Y+len/N ,imaze.mlen = len*(1-2/N),imaze.slen = len;
	imaze.ulen = len/N;
	InitMaze_Edit();
}

// void debug_matrix(){
// 	for(int i=2;i<=N-1;++i){
// 		for(int j=2;j<=N-1;++j) printf("%d ", mp[i][j] );
// 		printf("\n");
// 	}		
// }
#endif
