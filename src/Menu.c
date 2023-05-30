#ifndef Menu_h
#define Menu_h

#include"Game.h"
#include"extgraph.h" 
#include"imgui.h"
#include"graphics.h"
#include<time.h>

int tp_first;
int lst;//尽力修正时钟
void MouseEvent_Main(int x,int y,int button,int event);
void MouseEvent_Choose(int x,int y,int button,int event);
void MouseEvent_TabBar(int x,int y,int button,int event);
void MouseEvent_Hint(int x,int y,int button,int event);
void Menu_Main_Show();
void Menu_Choose_Show();
void TabBar_Show();
//预声明MouseEvent函数

void Menu_Main(){registerMouseEvent(MouseEvent_Main);}
void Menu_Choose(){tp_first=1;registerMouseEvent(MouseEvent_Choose);}
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
	double dy=1.5;
	Y+=1,X-=0.5;
	setButtonColors("White","Green","White","Blue",1);
	//主操作选择
	if(button(GenUIID(0),X,Y,3.0,1.0,"新游戏")){
		cancelMouseEvent();
		Menu_Choose();
		return;
	}
	setButtonColors("White","Green","White","Blue",1);
	if(button(GenUIID(1),X,Y-=dy,3.0,1.0,"继续")){
		cancelMouseEvent();
		LoadGame(),Page_Load(),ReDraw();
		Go();
		return;
	}
	setButtonColors("White","Green","White","Blue",1);
	if(button(GenUIID(1),X,Y-=dy,3.0,1.0,"绘制地图")) {
		cancelMouseEvent();
		MouseEditMaze(); 
		return;
	}
	setButtonColors("White","Red","White","Blue",1);
	if(button(GenUIID(1),X+0.5,Y-=dy,2.0,1.0,"退出")) Page_Exit(); 
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
	sprintf(s,"选择关卡：【%d】%s",Tough_Choose,Tough[Tough_Choose]);
	//完成一段切换的动画
	if(tp_flag){
		DisplayClear();
		double tp_x=W/2-0.5,tp_y=Y+4;
		SetPenColor("violet");
		SetPointSize(50);
		drawLabel(X,Y,"选择关卡：");
		for(int i=0;i<=3;i++){//自上而下落下
			DisplayClear();
			SetPenColor("violet");
			SetPointSize(50);
			drawLabel(X,Y,"选择关卡：");
			SetPenColor("Red");
			SetPointSize(50);
			drawLabel(tp_x,tp_y-=1,s+10);
			Pause(0.02);
		}
		tp_flag=0;
	}else if(tp_first){//第一次显示，无动画，避免画面闪动的BUG
		DisplayClear();
		double tp_x=W/2-0.5,tp_y=Y;
		SetPenColor("violet");
		SetPointSize(50);
		drawLabel(X,Y,"选择关卡：");
		SetPenColor("Red");
		SetPointSize(50);
		drawLabel(tp_x,tp_y,s+10);
		tp_first=0;
	}
}
void Menu_Choose_Show(){//显示选择关卡
	double W=GetWindowWidth(),H=GetWindowHeight();
	double X=W/2-4,Y=H/2+1;
	static int Tough_Choose=1;
	if(tp_first) Draw_Label(Tough_Choose);//加入tp_first判断，防止闪烁
	
	//通过加减按钮切换关卡
	SetPointSize(30);
	setButtonColors("White","Red","Yellow","White",1);
	if(button(GenUIID(0),X+0.5,Y-2,2.0,1.0,"+")&&Tough_Choose<Tough_N) tp_flag=1,Draw_Label(++Tough_Choose);
	SetPointSize(30);
	setButtonColors("White","Green","Yellow","White",1);
	if(button(GenUIID(1),X+4,Y-2,2.0,1.0,"-")&&Tough_Choose>1) tp_flag=1,Draw_Label(--Tough_Choose);
	SetPointSize(30);
	setButtonColors("White","Blue","Green","Red",1);
	if(button(GenUIID(2),X+1,Y-4,5.0,1.0,"开始游戏")){
		Page_Load();
		Time=0,SideBar();
		TabBar();
		GeneratingMaze(Rank=Tough_Choose);
		Head_List=Tail_List=NULL,Total=0,Go();
	}
}

extern int Time;
static char Time_s[10]="";
void Clock(){//计时器
	double H=GetWindowHeight();
	SetPointSize(50);
	SetPenColor("White");
	drawLabel(0.95,H-2,Time_s);
	SetPenColor("Red");
	++Time,lst=clock();
	sprintf(Time_s,"%02d:%02d:%02d",Time/3600,Time/60%60,Time%60);
	// printf("%s\n",Time_s);
	drawLabel(0.95,H-2,Time_s);
}
void SideBar(){//侧边栏绘制
	DisplayClear();
	double W=GetWindowWidth(),H=GetWindowHeight();
	SetPenColor("Green");
	SetPenSize(5);
	drawRectangle(0,0,W-H-1.2,H,0);
	SetPenColor("Red");
	drawRectangle(0.8,H-2.2,3,1,0);
	drawRectangle(0.7,H-2.3,3.2,1.2,0);
	registerTimerEvent(Clock);
	startTimer(GenUIID(666),1000);
}
void GetHint(){//获取提示
	SetPointSize(30);
	setButtonColors("White","Green","Yellow","Yellow",1);
	if(button(GenUIID(999),0.95,5.0,3.0,0.9,"提   示")) Get_Fastest();
}
void BestPlay(){//最佳表现
	SetPointSize(30);
	setButtonColors("White","Red","Red","Yellow",1);
	if(button(GenUIID(996),0.95,4.0,3.0,0.9,"最 佳 表 现")){
		SaveGame();
		LoadRecord();
		int id=GetPlay();
		if(!~id){//无记录
			double W=GetWindowWidth(),H=GetWindowHeight();
			SetPointSize(50),SetPenColor("Red");
			drawBox(W-H+2,H/2,4,2,1,"No Record!",'C',"Yellow");
			Pause(1.0);
			DisplayClear();
			ReDraw();
			return;
		}
		LoadRecord_i(id),--Time,Clock(),ReDraw();//载入和展示最佳表现的时间
		Pause(2.0);
		Time=0;
		ShowPath(Head_List);//演示最佳表现的路径
	}
}
void TabBar(){registerMouseEvent(MouseEvent_TabBar);}
void MouseEvent_TabBar(int x,int y,int button,int event){
	uiGetMouse(x,y,button,event);
	TabBar_Show();
}
void TabBar_Show(){//选项卡
	GetHint();
	BestPlay();
	static char *MenuListGame[]={
		"Game",
		"New Game",
		"Save Game",
		"Menu",
		"Exit"
	};
	static char *MenuListHelp[]={
		"Help",
		"Options",
		"About"
	};
	double W=GetWindowWidth(),H=GetWindowHeight();
	setMenuColors("White","Orange","Blue","Green",0);
	SetPointSize(20);
	SetPenSize(2);
	int opt1=menuList(GenUIID(101),W-H-0.5,H-0.5,1,1.5,0.5,MenuListGame,5);
	switch(opt1){
		case 1:cancelTimerEvent(),cancelMouseEvent();Menu_Choose();break;//新游戏
		case 2:cancelTimerEvent(),cancelMouseEvent();SaveGame();break;   //保存当前游戏状态
		case 3:cancelTimerEvent(),cancelMouseEvent();Menu_Main();break;  //返回主菜单
		case 4:Page_Exit();break;										//退出游戏
	}
	setMenuColors("White","Orange","Blue","Green",0);
	SetPointSize(20);
	SetPenSize(2);
	int opt2=menuList(GenUIID(102),W-H+1,H-0.5,1,1.2,0.5,MenuListHelp,3);
	switch(opt2){
		case 1:cancelTimerEvent();cancelMouseEvent();Page_Info();break;//操作信息
		case 2:cancelTimerEvent();cancelMouseEvent();Page_About();break;//关于
	}
	printf("%d %d\n",opt1,opt2);
	if(!opt1||!opt2) DisplayClear(),SideBar(),DrawMaze();
}
void ReDraw(){//全图重绘
	DisplayClear();
	SideBar();TabBar();DrawMaze();
	if(clock()-lst>=1000) lst=clock(),Clock();
	SetPointSize(50),SetPenColor("Red"),drawLabel(0.95,GetWindowHeight()-2,Time_s);
}
#endif
