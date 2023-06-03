#ifndef _EXTRAFUNC_C_
#define _EXTRAFUNC_C_

#include"Game.h"
#include"extgraph.h" 
#include"imgui.h"
#include"graphics.h"
#include<time.h>

void eTabBar_Show();
void MouseEvent_eTabBar(int x,int y,int button,int event){
	uiGetMouse(x,y,button,event);
	eTabBar_Show();
}
void eMouseEvent_Back(int x,int y,int btn,int event){//����������¼�
	uiGetMouse(x,y,btn,event);
	double W=GetWindowWidth(),H=GetWindowHeight();
	double X=W/2,Y=H/2;
	SetPointSize(30);
	if(button(GenUIID(555),W-2.1,2,1.5,0.8,"����")){
		cancelMouseEvent();
		Page_Extra();
	}
}

void eTabBar(){registerMouseEvent(MouseEvent_eTabBar);}
void Page_Info_Extra()
{
	double W=GetWindowWidth(),H=GetWindowHeight();
	double X=W/2,Y=H/2;
	DisplayClear();
	SetPenSize(5);
	SetPenColor("Blue");
	drawRectangle(X-4,Y-3.5,9.0,6.0,0);
	SetPenColor("Black");
	SetPointSize(30);
	MovePen(X-3.2,Y+1.5);
	DrawTextString("����� / [W][A][S][D]   �����ƶ�");
	MovePen(X-3.2,Y+0.5);
	DrawTextString("����̵�ʱ�䵽���յ㣡");
	MovePen(X-3.2,Y-0.5);
	DrawTextString("��ͼ�ϵ�");SetPenColor("Orange");
	MovePen(X-3.2+TextStringWidth("��ͼ�ϵ�"),Y-0.5);
	DrawTextString("��ɫ����");
	MovePen(X-3.2+TextStringWidth("��ͼ�ϵĳ�ɫ����"),Y-0.5);SetPenColor("Black");
	DrawTextString("ΪԿ��,ʰ�������ڿ���!");
	MovePen(X-3.2,Y-=1.5);
	DrawTextString("��ͼ�ϵ�");SetPenColor("Red");
	MovePen(X-3.2+TextStringWidth("��ͼ�ϵ�"),Y);
	DrawTextString("��ɫ����");
	MovePen(X-3.2+TextStringWidth("��ͼ�ϵĺ�ɫ����"),Y);SetPenColor("Black");
	DrawTextString("Ϊ�ţ�������Կ�״�!");
	registerMouseEvent(eMouseEvent_Back);
}
void eTabBar_Show(){//ѡ�
	GetHint();
	BestPlay();
	static char *MenuListGame[]={
		"Game",
		"Save Game",
		"Menu"
	};
	static char *MenuListHelp[]={
		"Help",
		"Options",
		"Exit"
	};
	double W=GetWindowWidth(),H=GetWindowHeight();
	MenuCSS();
	int opt1=menuList(GenUIID(101),W-H-0.5,H-0.5,1,1.5,0.5,MenuListGame,3);
	switch(opt1){
		case 1:cancelTimerEvent(),cancelMouseEvent();SaveGame();break;   //���浱ǰ��Ϸ״̬
		case 2:cancelTimerEvent(),cancelMouseEvent();Menu_Main();break;  //�������˵�
	}
	MenuCSS();
	int opt2=menuList(GenUIID(102),W-H+1,H-0.5,1,1.2,0.5,MenuListHelp,4);
	switch(opt2){
		case 1:cancelTimerEvent();cancelMouseEvent();Page_Info_Extra();break;//������Ϣ
		case 2:Page_Exit();break;										//�˳���Ϸ
	}
	if(!opt1||!opt2) DisplayClear(),SideBar(),DrawMaze();
}

void Page_Extra()
{
	    static char yaoshi[30]="";
		double W=GetWindowWidth(),H=GetWindowHeight();
		double X=W/2,Y=H;
		DisplayClear();inPage=5;
		Time=0,SideBar();
		eTabBar();
		GeneratingMaze(3);
		Head_List=Tail_List=NULL,Total=0,Go();	
		SetPointSize(30);
		SetPenColor("Red");
		sprintf(yaoshi,"�����е�Կ����Ϊ��%d",Yaoshi);
		MovePen(X-2.5,Y-1);
		DrawTextString(yaoshi);
}

#endif
