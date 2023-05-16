#ifndef Menu_h
#define Menu_h

#include"Game.h"
#include"extgraph.h" 
#include"imgui.h"
#include"graphics.h"

int tp_first;
void MouseEvent_Main(int x,int y,int button,int event);
void MouseEvent_Choose(int x,int y,int button,int event);
void MouseEvent_TabBar(int x,int y,int button,int event);
void Menu_Main_Show();
void Menu_Choose_Show();
void TabBar_Show();
//Ԥ����MouseEvent����

void Menu_Main(){registerMouseEvent(MouseEvent_Main);}
void Menu_Choose(){tp_first=1;registerMouseEvent(MouseEvent_Choose);}
void MouseEvent_Main(int x,int y,int button,int event){
	uiGetMouse(x,y,button,event);
	Menu_Main_Show();
}
void Menu_Main_Show(){//��ʾ���˵�
	DisplayClear();
	double W=GetWindowWidth(),H=GetWindowHeight();
	double X=W/2-1,Y=H/2+1;
	SetPenSize(10);
	SetPenColor("Yellow");
	drawRectangle(X-1,Y-4,4,7,0);
	SetFont("����");
	SetPointSize(30);
	SetPenSize(3);
	setButtonColors("White","Green","White","Blue",1);
	if(button(GenUIID(0),X,Y,2.0,1.0,"����Ϸ")) Menu_Choose();
	setButtonColors("White","Red","White","Blue",1);
	if(button(GenUIID(1),X,Y-=2,2.0,1.0,"�˳�")) Page_Exit(); 
}

void MouseEvent_Choose(int x,int y,int button,int event){
	uiGetMouse(x,y,button,event);
	Menu_Choose_Show();
}
#define Tough_N 3
int tp_flag=0;
void Draw_Label(int Tough_Choose){//���ƹؿ��л�����
	static char *Tough[]={0,"�� ��","�� ��","�� ��"};
	static char s[128]="";
	double W=GetWindowWidth(),H=GetWindowHeight();
	double X=W/2-4,Y=H/2+1;
	sprintf(s,"ѡ��ؿ�����%d��%s",Tough_Choose,Tough[Tough_Choose]);
	//���һ���л��Ķ���
	if(tp_flag||tp_first){
		DisplayClear();
		double tp_x=W/2-0.5,tp_y=Y+4;
		SetPenColor("violet");
		SetPointSize(50);
		drawLabel(X,Y,"ѡ��ؿ���");
		for(int i=0;i<=3;i++){//���϶�������
			SetPenColor("White");
			SetPointSize(50);
			drawLabel(tp_x,tp_y,s+10);
			SetPenColor("Red");
			SetPointSize(50);
			drawLabel(tp_x,tp_y-=1,s+10);
			Pause(0.02);
		}
		tp_flag=tp_first=0;
	}
}
void Menu_Choose_Show(){//��ʾѡ��ؿ�
	double W=GetWindowWidth(),H=GetWindowHeight();
	double X=W/2-4,Y=H/2+1;
	static int Tough_Choose=1;
	if(tp_first) Draw_Label(Tough_Choose);//����tp_first�жϣ���ֹ��˸
	SetPointSize(30);
	setButtonColors("White","Red","Yellow","White",1);
	if(button(GenUIID(0),X+0.5,Y-2,2.0,1.0,"+")&&Tough_Choose<Tough_N) tp_flag=1,Draw_Label(++Tough_Choose);
	SetPointSize(30);
	setButtonColors("White","Green","Yellow","White",1);
	if(button(GenUIID(1),X+4,Y-2,2.0,1.0,"-")&&Tough_Choose>1) tp_flag=1,Draw_Label(--Tough_Choose);
	SetPointSize(30);
	setButtonColors("White","Blue","Green","Red",1);
	if(button(GenUIID(2),X+1,Y-4,5.0,1.0,"��ʼ��Ϸ")){
		Page_Load();
		Time=0,SideBar();
		TabBar();
		GeneratingMaze(Rank=Tough_Choose);
	}
}

extern int Time;
void Clock(){//��ʱ��
	static char Time_s[10]="";
	double H=GetWindowHeight();
	SetPointSize(50);
	SetPenColor("White");
	drawLabel(0.95,H-2,Time_s);
	SetPenColor("Red");
	++Time;
	sprintf(Time_s,"%02d:%02d:%02d",Time/3600,Time/60%60,Time%60);
	// printf("%s\n",Time_s);
	drawLabel(0.95,H-2,Time_s);
}
void SideBar(){
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

void TabBar(){registerMouseEvent(MouseEvent_TabBar);}
void MouseEvent_TabBar(int x,int y,int button,int event){
	uiGetMouse(x,y,button,event);
	TabBar_Show();
}
void TabBar_Show(){
	static char *MenuListGame[]={
		"Game",
		"New Game",
		"Save Game",
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
	int opt1=menuList(GenUIID(101),W-H-0.5,H-0.5,1,1.5,0.5,MenuListGame,4);
	switch(opt1){
		case 1:cancelTimerEvent(),cancelMouseEvent();Menu_Choose();break;
		case 2:cancelTimerEvent(),cancelMouseEvent();Page_Victory();break;
		case 3:Page_Exit();break;
	}
	setMenuColors("White","Orange","Blue","Green",0);
	SetPointSize(20);
	SetPenSize(2);
	int opt2=menuList(GenUIID(102),W-H+1,H-0.5,1,1.2,0.5,MenuListHelp,3);
	switch(opt2){
		case 2:Page_About();break;
	}
	printf("%d %d\n",opt1,opt2);
	if(!opt1||!opt2) DisplayClear(),SideBar(),DrawMaze();
}
#endif
