#ifndef Menu_h
#define Menu_h

#include"Game.h"
#include"extgraph.h" 
#include"imgui.h"
#include"graphics.h"

int tp_first;
void MouseEvent_Main(int x,int y,int button,int event);
void MouseEvent_Choose(int x,int y,int button,int event);
void Menu_Main_Show();
void Menu_Choose_Show();
void Menu_Main(){registerMouseEvent(MouseEvent_Main);}
void Menu_Choose(){tp_first=1;DisplayClear();registerMouseEvent(MouseEvent_Choose);}
void MouseEvent_Main(int x,int y,int button,int event){
	uiGetMouse(x,y,button,event);
	Menu_Main_Show();
}
void Menu_Main_Show(){//显示主菜单
	DisplayClear();
	double W=GetWindowWidth(),H=GetWindowHeight();
	double X=W/2-1,Y=H/2+1;
	SetPenSize(10);
	SetPenColor("Yellow");
	drawRectangle(X-1,Y-4,4,7,0);
	SetFont("楷体");
	SetPointSize(30);
	SetPenSize(3);
	setButtonColors("White","Green","White","Blue",1);
	if(button(GenUIID(0),X,Y,2.0,1.0,"新游戏")) Menu_Choose();
	setButtonColors("White","Red","White","Blue",1);
	if(button(GenUIID(1),X,Y-=2,2.0,1.0,"退出")) Page_Exit(W/2,H/2); 
}
void MouseEvent_Choose(int x,int y,int button,int event){
	uiGetMouse(x,y,button,event);
	Menu_Choose_Show();
}
#define Tough_N 3
int tp_flag=0;
void Draw_Label(int Tough_Choose){//绘制关卡切换动画
	static char *Tough[]={0,"简 单","中 等","困 难"};
	static char s[128]="";
	double W=GetWindowWidth(),H=GetWindowHeight();
	double X=W/2-4,Y=H/2+1;
	SetPointSize(50);
	sprintf(s,"选择关卡：【%d】%s",Tough_Choose,Tough[Tough_Choose]);
	//完成一段切换的动画
	if(tp_flag||tp_first){
		DisplayClear();
		double tp_x=W/2-0.5,tp_y=Y+4;
		SetPenColor("violet");
		drawLabel(X,Y,"选择关卡：");
		for(int i=0;i<=3;i++){//自上而下落下
			SetPenColor("White");
			drawLabel(tp_x,tp_y,s+10);
			drawLabel(tp_x,tp_y,s+10);
			SetPenColor("Red");
			drawLabel(tp_x,tp_y-=1,s+10);
			Pause(0.02);
		}
		tp_flag=tp_first=0;
	}
}
void Menu_Choose_Show(){//显示选择关卡
	double W=GetWindowWidth(),H=GetWindowHeight();
	double X=W/2-4,Y=H/2+1;
	static int Tough_Choose=1;
	Draw_Label(Tough_Choose);
	setButtonColors("White","Red","Yellow","White",1);
	if(button(GenUIID(0),X+0.5,Y-2,2.0,1.0,"+")&&Tough_Choose<Tough_N) tp_flag=1,Draw_Label(++Tough_Choose);
	setButtonColors("White","Green","Yellow","White",1);
	if(button(GenUIID(1),X+4,Y-2,2.0,1.0,"-")&&Tough_Choose>1) tp_flag=1,Draw_Label(--Tough_Choose);
}
#endif
