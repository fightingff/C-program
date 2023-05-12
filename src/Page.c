#ifndef Page_C
#define Page_C

#include"Game.h"
#include"math.h"
#include"graphics.h"
#include"imgui.h"
#include"extgraph.h"

static int Colors_N=8;
static char *Colors[]={"Red","Orange","Yellow","Green","Blue","Violet","Magenta","Cyan"};
void Page_About(){//退出的文字
	double W=GetWindowWidth(),H=GetWindowHeight();
	double X=W/2,Y=H/2;
	DisplayClear();
	SetPenSize(5);
	SetPenColor("Green");
	drawRectangle(X-2,Y-0.5,3.0/0.618,3.0,0);
	SetPenColor("Blue");
	SetFont("行楷");
	SetPointSize(30);
	MovePen(X-1.2,Y+1.5);
	DrawTextString("Thank you!");
	MovePen(X-1.2,Y+0.5);
	DrawTextString("Author: FMH & WZJ");
}
void Page_Exit(){//退出界面
	DisplayClear();
	cancelMouseEvent();
	cancelTimerEvent();
	SetPenSize(2);
	const double Pi=acos(-1),R=2,N=60;
	double W=GetWindowWidth(),H=GetWindowHeight();
	double X=W/2,Y=H/2;
	for(int i=0;i<=N*2;i++){//退出的动画
		SetPenColor(Colors[i%Colors_N]);
		MovePen(X+R+R*i/N*cos(2.0*Pi/N*i),Y+R*i/N*sin(2.0*Pi/N*i));
		DrawArc(R*i/N,0,360);
		Pause(0.02);
	}
	Page_About();
	//延迟后退出
	Pause(3.0);
	ExitGraphics();
}

void Page_Load(){
	DisplayClear();
	cancelMouseEvent();
	double W=GetWindowWidth(),H=GetWindowHeight();
	double X=W/2,Y=H/2;
	SetPenSize(2);
	const double Pi=acos(-1),R=2,N=60;
	for(int i=N*2;i>=0;i--){//加载的动画
		SetPenColor(Colors[i%Colors_N]);
		MovePen(X+R+R*i/N*cos(2.0*Pi/N*i),Y+R*i/N*sin(2.0*Pi/N*i));
		DrawArc(R*i/N,0,360);
		Pause(0.02);
	}
}

#endif

