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
void eMouseEvent_Back(int x,int y,int btn,int event){//鼠标点击返回事件
	uiGetMouse(x,y,btn,event);
	double W=GetWindowWidth(),H=GetWindowHeight();
	double X=W/2,Y=H/2;
	SetPointSize(30);
	if(button(GenUIID(555),W-2.1,2,1.5,0.8,"返回")){
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
	DrawTextString("方向键 / [W][A][S][D]   控制移动");
	MovePen(X-3.2,Y+0.5);
	DrawTextString("用最短的时间到达终点！");
	MovePen(X-3.2,Y-0.5);
	DrawTextString("地图上的");SetPenColor("Orange");
	MovePen(X-3.2+TextStringWidth("地图上的"),Y-0.5);
	DrawTextString("橙色方块");
	MovePen(X-3.2+TextStringWidth("地图上的橙色方块"),Y-0.5);SetPenColor("Black");
	DrawTextString("为钥匙,拾起它用于开门!");
	MovePen(X-3.2,Y-=1.5);
	DrawTextString("地图上的");SetPenColor("Red");
	MovePen(X-3.2+TextStringWidth("地图上的"),Y);
	DrawTextString("红色方块");
	MovePen(X-3.2+TextStringWidth("地图上的红色方块"),Y);SetPenColor("Black");
	DrawTextString("为门，可消耗钥匙打开!");
	registerMouseEvent(eMouseEvent_Back);
}
void eTabBar_Show(){//选项卡
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
		case 1:cancelTimerEvent(),cancelMouseEvent();SaveGame();break;   //保存当前游戏状态
		case 2:cancelTimerEvent(),cancelMouseEvent();Menu_Main();break;  //返回主菜单
	}
	MenuCSS();
	int opt2=menuList(GenUIID(102),W-H+1,H-0.5,1,1.2,0.5,MenuListHelp,4);
	switch(opt2){
		case 1:cancelTimerEvent();cancelMouseEvent();Page_Info_Extra();break;//操作信息
		case 2:Page_Exit();break;										//退出游戏
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
		sprintf(yaoshi,"您持有的钥匙数为：%d",Yaoshi);
		MovePen(X-2.5,Y-1);
		DrawTextString(yaoshi);
}

#endif
