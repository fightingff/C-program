#ifndef Page_C
#define Page_C

#include"Game.h"
#include"math.h"
#include"graphics.h"
#include"imgui.h"
#include"extgraph.h"

static double W,H; //window width & height
extern struct Imaze imaze;
static int Colors_N=6;
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
	double W=GetWindowWidth(),H=GetWindowHeight();
	const double Pi=acos(-1),N=600,theta=Pi/3+Pi/180;
	double X=W/2,Y=H/2;
	MovePen(X,Y);
	for(int i=1;i<=N;i++){
		SetPenColor(Colors[i%Colors_N]);
		double R=i/200.0;
		MovePen(X+R*cos(theta*i)+R,Y+R*sin(theta*i));
		DrawArc(R,0,360);
		Pause(0.005);
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
	const double Pi=acos(-1),N=600,theta=Pi/3+Pi/180;
	MovePen(X,Y);
	for(int i=1;i<=N;i++){
		SetPenColor(Colors[i%Colors_N]);
		DrawLine(i/100.0*cos(theta*i),i/100.0*sin(theta*i));
		Pause(0.005);
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

void Page_Edit(){
	W=GetWindowWidth(),H=GetWindowHeight();
	display();
}

void display()
{
	DisplayClear();
	DrawMenu_Edit();
	DrawButton_Edit();
	DrawMaze_Edit();
}

void DrawMenu_Edit()
{
	static char * menuListFile[] = {"File",  
		"Open    | Ctrl-R", 
		"Save    | Ctrl-S"};
	static char * menuListTool[] = {"Tool",
		"速成模板  | Ctrl-P",
		"重新绘制  | Ctrl-R"};
	static char * menuListHelp[] = {"Help",
		"关于本软件",
		"Exit    | Ctrl-E"};
	double fH = GetFontHeight();
	double x = 0; 
	double y = H;
	double h = fH*1.5; 
	double w = TextStringWidth(menuListFile[0])*2; 
	double wlist = TextStringWidth(menuListFile[1])*1.2;
	int   selection;
	
	drawMenuBar(0,y-h,W,h);
	// File 
	selection = menuList(GenUIID(0), x, y-h, w, wlist, h, menuListFile, sizeof(menuListFile)/sizeof(menuListFile[0]));
	if( selection==2 ) SaveGame(); // 2) Problem : will flash into Menu_choose
	else if( selection==1 ) LoadGame();
	
	// Tool 
	selection = menuList(GenUIID(0),x+w,  y-h, w, wlist,h, menuListTool, sizeof(menuListTool)/sizeof(menuListTool[0]));
	if( selection==1 ) {
		GeneratingMaze_Hard();
	}
	else if ( selection==2 ) InitMaze_Edit();
	
	// Help ???
	selection = menuList(GenUIID(0),x+2*w,y-h, w, wlist, h, menuListHelp,sizeof(menuListHelp)/sizeof(menuListHelp[0]));
	if( selection==2 ) exit(-1); //  5) to be improved : back to the previous page
	else if ( selection==1 ){
		// 4) information can be added
	}
}

void DrawButton_Edit()
{
	double fH = GetFontHeight();
	double h = fH*2;
	double x =  W*2/3;
	double y = H - h*4;
	double w = TextStringWidth("四个汉字")*2; 
	double dy = h*2;
	
	if( button(GenUIID(1), x,y,w,h, "设置道路")) {
		if( edit_mode == 1 ) edit_mode = 0;
		else edit_mode = 1;
		printf("edit_mode is %d\n", edit_mode);
		}
	if( button(GenUIID(1), x,y-dy,w,h, "设置障碍")) {
		if( edit_mode == 2 ) edit_mode = 0;
		else edit_mode = 2;
		printf("edit_mode is %d\n", edit_mode);
		}
	if( button(GenUIID(1), x,y-dy*2,w,h, "设置起点")) {
		if( edit_mode == 3 ) edit_mode = 0;
		else edit_mode = 3;
	}
	if( button(GenUIID(1), x,y-dy*3,w,h, "设置终点")) {
		if( edit_mode == 4 ) edit_mode = 0;
		else edit_mode = 4;
	}
	if( button(GenUIID(1), x,y-dy*4,w,h, "设置陷阱")) {
		if( edit_mode == 5 ) edit_mode = 0;
		else edit_mode = 5;
	}
	
}
void DrawMaze_Edit()
{
	SetPenSize(2);
	SetPenColor("Gray");
	PaintUnits(imaze.x, imaze.y - imaze.ulen, imaze.slen); 
	drawLines(imaze.x, imaze.y - imaze.ulen, imaze.mlen);
	
}

void drawLines(double X, double Y ,double len)
{
	double ul = len/N; 
	double mlen = len - 2*ul;
	for (int i=0; i<=N-2; ++i ) {
		MovePen(X+ul*i,Y+ul); DrawLine(0, -mlen);
	}
	for (int i=0; i<=N-2; ++i ) {
		MovePen(X,Y-ul*(i-1)); DrawLine(mlen, 0);
	}
}
#endif

