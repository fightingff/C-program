#ifndef Page_C
#define Page_C

#include"Game.h"
#include"math.h"
#include"graphics.h"
#include"imgui.h"
#include"extgraph.h"

static int Colors_N=8;
static char *Colors[]={"Red","Orange","Yellow","Green","Blue","Violet","Magenta","Cyan"};
void MouseEvent_Back(int x,int y,int btn,int event){//鼠标点击返回事件
	uiGetMouse(x,y,btn,event);
	double W=GetWindowWidth(),H=GetWindowHeight();
	double X=W/2,Y=H/2;
	SetPointSize(30);
	if(button(GenUIID(555),W-2.1,2,1.5,0.8,"返回")){
		cancelMouseEvent();
		ReDraw();
	}
}
void Page_About(){//退出的文字
	double W=GetWindowWidth(),H=GetWindowHeight();
	double X=W/2,Y=H/2;
	DisplayClear();
	SetPenSize(5);
	SetPenColor("Green");
	drawRectangle(X-2,Y-0.5,3.0/0.618,3.0,0);
	SetPenColor("Blue");
	SetPointSize(30);
	MovePen(X-1.2,Y+1.5);
	DrawTextString("Thank you!");
	MovePen(X-1.2,Y+0.5);
	DrawTextString("Author: FMH & WZJ");
	registerMouseEvent(MouseEvent_Back);
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
		Pause(0.01);
	}
	Page_About();
	cancelMouseEvent();
	//延迟后退出
	Pause(3.0);
	ExitGraphics();
}

void Page_Load(){//加载界面
	DisplayClear();
	cancelMouseEvent();
	double W=GetWindowWidth(),H=GetWindowHeight();
	double X=W/2,Y=H/2;
	SetPenSize(2);
	const double Pi=acos(-1),R=2,N=60;
	for(int i=N*2;i>=0;i--){//加载的动画，螺旋线
		SetPenColor(Colors[i%Colors_N]);
		MovePen(X+R+R*i/N*cos(2.0*Pi/N*i),Y+R*i/N*sin(2.0*Pi/N*i));
		DrawArc(R*i/N,0,360);
		Pause(0.01);
	}
}

void EraseMap(){//用条纹擦除地图
	double W=GetWindowWidth(),H=GetWindowHeight();
	double X=W-H-1.2,Y=H,Edge=H;
	const int N=100;
	for(int i=1;i<=N;i++){
		SetPenColor("White");
		drawRectangle(X,Y-Edge,Edge/N,Edge,1);
		SetPenColor("Red");
		drawRectangle(X+=Edge/N,Y-Edge,Edge/N,Edge,1);
		Pause(0.01);
	}
}
void Page_Victory(){//胜利界面
	Clock();
	EraseMap();
	cancelTimerEvent();
	double W=GetWindowWidth(),H=GetWindowHeight();
	double X=W-H-1.2,Y=H,Edge=H;
	SetPenSize(10);
	SetPointSize(100);
	SetPenColor("Green");
	double label_w=TextStringWidth("Victory!")+0.2,label_h=GetFontHeight()+0.2;
	drawBox(X+Edge/2-label_w/2,Y-Edge/2+label_h/2,label_w,label_h,1,"Victory!",'C',"Yellow");
    if(UpdateRecord()){
		label_w=TextStringWidth("New Record!")+0.2,label_h=GetFontHeight()+0.2;
		drawBox(X+Edge/2-label_w/2,Y-Edge/2-label_h-0.5,label_w,label_h,1,"New Record!",'C',"red");
	}
	Pause(5.0);
	Menu_Main();
}

void Page_Info(){//操作说明
	double W=GetWindowWidth(),H=GetWindowHeight();
	double X=W/2,Y=H/2;
	DisplayClear();
	SetPenSize(5);
	SetPenColor("Green");
	drawRectangle(X-4,Y-0.5,10.0,3.0,0);
	SetPenColor("Orange");
	SetPointSize(30);
	MovePen(X-3.2,Y+1.5);
	DrawTextString("方向键 / [W][A][S][D]   控制移动");
	MovePen(X-3.2,Y+0.5);
	DrawTextString("用最短的时间到达终点！");
	registerMouseEvent(MouseEvent_Back);
}
#endif

