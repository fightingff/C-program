#ifndef Page_C
#define Page_C

#include"Game.h"
#include"math.h"
#include"graphics.h"
#include"imgui.h"
#include"extgraph.h"

static double W,H;
extern struct Imaze imaze;
extern int number;
extern int inPage; 
static int Colors_N=6;
static char *Colors[]={"Red","Orange","Yellow","Green","Blue","Violet","Magenta","Cyan"};
void MouseEvent_Back(int x,int y,int btn,int event){//����������¼�
	uiGetMouse(x,y,btn,event);
	double W=GetWindowWidth(),H=GetWindowHeight();
	double X=W/2,Y=H/2;
	SetPointSize(30);
	if(button(GenUIID(555),W-2.1,2,1.5,0.8,"����")){
		cancelMouseEvent();
		ReDraw();
	}
}
void MouseEvent_BackEdit(int x,int y,int btn,int event){
	uiGetMouse(x,y,btn,event);
	double W=GetWindowWidth(),H=GetWindowHeight();
	double X=W/2,Y=H/2;
	SetPointSize(30);
	if(button(GenUIID(555),W-2.1,2,1.5,0.8,"����")){
		cancelMouseEvent();
		DisplayClear();
		Edit();
	}
}
void Page_About(){//�˳�������
	double W=GetWindowWidth(),H=GetWindowHeight();
	double X=W/2,Y=H/2;inPage=3;
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
	registerMouseEvent(MouseEvent_Back);inPage=0;
}
void Page_Exit(){//�˳�����
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
	//�ӳٺ��˳�
	Pause(3.0);
	ExitGraphics();
}

void Page_Load(){//���ؽ���
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

void EraseMap(){//�����Ʋ�����ͼ
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
void Page_Victory(){//ʤ������
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

void Page_Info(){//����˵��
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
	DrawTextString("������");SetPenColor("Orange");
	MovePen(X-3.2+TextStringWidth("������"),Y-0.5);
	DrawTextString("��ɫ����");
	MovePen(X-3.2+TextStringWidth("�����ֳ�ɫ����"),Y-0.5);SetPenColor("Black");
	DrawTextString(",ʰ�����ɼ��ټ�ʱ��3��!");
	MovePen(X-3.2,Y-=1.5);
	DrawTextString("������");SetPenColor("Red");
	MovePen(X-3.2+TextStringWidth("������"),Y);
	DrawTextString("��ɫ����");
	MovePen(X-3.2+TextStringWidth("�����ֺ�ɫ����"),Y);SetPenColor("Black");
	DrawTextString(",ͨ�������ܻ�ʹ�����ﵽ");
	MovePen(X-3.2,Y-=1) ;DrawTextString("�������Ӽ�ʱ��8�룡");
	registerMouseEvent(MouseEvent_Back);
}
void Page_EditInfo(){//�༭˵��
	double W=GetWindowWidth(),H=GetWindowHeight();
	double X=W/2,Y=H/2;
	cancelMouseEvent();
	DisplayClear();
	SetPenSize(5);
	SetPenColor("Green");
	drawRectangle(X-4,Y-3.5,9.0,6.0,0);
	SetPenColor("Orange");
	SetPointSize(30);
	Y+=1.5;
	MovePen(X-3.2,Y);
	DrawTextString("ѡ����Ӧ��ť��ֱ�ӵ������༭");
	MovePen(X-3.2,Y-=1);
	DrawTextString("��Open��������༭�ĵ�ͼ�ļ�");
	MovePen(X-3.2,Y-=1);
	DrawTextString("��Save�����浱ǰ�༭�ĵ�ͼ�ļ�");
	MovePen(X-3.2,Y-=1);
	DrawTextString("��QuickMade�� �������ɵ�ͼ");
	MovePen(X-3.2,Y-=1);
	DrawTextString("��Redraw�����»��Ƶ�ͼ");
	registerMouseEvent(MouseEvent_BackEdit);
}

void DrawMenu_Edit();
void DrawButton_Edit();
void DrawMaze_Edit();
void DrawEditText_Edit();

void display()
{//�༭ҳ����ʾ
	DisplayClear();
	DrawButton_Edit();
	DrawEditText_Edit();
	DrawMaze_Edit();
	DrawMenu_Edit();
}

void Page_Edit(){   
	W=GetWindowWidth(),H=GetWindowHeight();inPage=2;
	display();inPage=0;
}
void DrawMenu_Edit()
{//���˵�
	static char * menuListFile[] = {"File",  
		"Open    | Ctrl-R", 
		"Save    | Ctrl-S"};
	static char * menuListTool[] = {"Tool",
		"QuickMade | Ctrl-P",
		"Redraw    | Ctrl-R"};
	static char * menuListHelp[] = {"Help",
		"About",
		"Menu",
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
	MenuCSS();
	selection = menuList(GenUIID(0), x, y-h, w, wlist, h, menuListFile, sizeof(menuListFile)/sizeof(menuListFile[0]));
	if( selection==2 ){
		Modify(2-++Tough_N);
		double W=GetWindowWidth(),H=GetWindowHeight();
		SetPointSize(50),SetPenColor("Red");
		drawBox(W-H+2,H/2,4,2,1,"����ɹ�",'C',"Yellow");
		Pause(1.0);
		Menu_Main();
	}
	else if( selection==1 ){
		if(Tough_N<3) return;
		LoadRecord_i(2-Tough_N); 
	}
	
	// Tool 
	MenuCSS();
	selection = menuList(GenUIID(0),x+w,  y-h, w, wlist,h, menuListTool, sizeof(menuListTool)/sizeof(menuListTool[0]));
	if( selection==1 ) {
		GeneratingMaze(1);
	}
	else if ( selection==2 ) InitMaze_Edit();
	
	// Help ???
	MenuCSS();
	selection = menuList(GenUIID(0),x+2*w,y-h, w, wlist, h, menuListHelp,sizeof(menuListHelp)/sizeof(menuListHelp[0]));
	if( selection==3 ) Page_Exit(); 
	else if ( selection==1 ){
		Page_EditInfo();
	}else if ( selection==2 ){
		Menu_Main();
	}
}

void DrawButton_Edit()
{//��Ҫ��ť
	double fH = GetFontHeight();
	double h = fH*2;
	double x =  W*2/3;
	double y = H - h*4;
	double w = TextStringWidth("�ĸ�����")*2; 
	double dy = h*2;
	
	if( button(GenUIID(1), x,y,w,h, "���õ�·")) {
		if( edit_mode == 1 ) edit_mode = 0;
		else edit_mode = 1;
		printf("edit_mode is %d\n", edit_mode);
		}
	if( button(GenUIID(1), x,y-dy,w,h, "�����ϰ�")) {
		if( edit_mode == 2 ) edit_mode = 0;
		else edit_mode = 2;
		printf("edit_mode is %d\n", edit_mode);
		}
	if( button(GenUIID(1), x,y-dy*2,w,h, "�������")) {
		if( edit_mode == 3 ) edit_mode = 0;
		else edit_mode = 3;
	}
	if( button(GenUIID(1), x,y-dy*3,w,h, "�����յ�")) {
		if( edit_mode == 4 ) edit_mode = 0;
		else edit_mode = 4;
	}
	if( button(GenUIID(1), x,y-dy*4,w,h, "��������")) {
		if( edit_mode == 5 ) edit_mode = 0;
		else edit_mode = 5;
	}
	if( button(GenUIID(1), x+w*1.2,y-dy*5,w/2,h,"ȷ��")) {
		SetFigures_Edit();
	}
}

void DrawEditText_Edit()
{//�����ı��� 
	static char memo[80]="Maze Size:";
	static char size[10]="22";
	static char tips[20] = "";
	static char tips2[20] = "";
	double fH = GetFontHeight();
	double h = fH*2;
	double x =  W*2/3;
	double y = H - h*14;
	double w = TextStringWidth("�ĸ�����")*2; 
	
	SetPenColor("Brown");
	drawLabel(x-TextStringWidth(memo), y+fH*0.6,memo);
	if(textbox(GenUIID(0), x,y, w,h,size, sizeof(size))){  // for debug : remember to cancel char and keyboard event in other page!
		number=0;
		for(int i=0;size[i]!='\0';++i)
		{	
			if(size[i]>'9' || size[i]<'0') {sprintf(tips,"[ERROR] Please enter digits!");return;}
			else if( i > 1) {sprintf(tips,"Too Large!",size);return;}
		}
		for(int i=0; size[i]<='9' && size[i]>='0';++i) number = size[i]-'0' + number*10;
			if( number <= 12 ) {sprintf(tips,"Too Small!", size);return;}
			sprintf(tips,"Press [ȷ��] to confirm the change! ");
	}
	
	SetPenColor("Gray");
	drawLabel(x, y-fH,tips);
}

void drawLines(double X, double Y ,double len)//����������
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

void DrawMaze_Edit()
{//�����Թ�
	SetPenSize(2);
	SetPenColor("Gray");
	PaintUnits(imaze.x, imaze.y - imaze.ulen, imaze.slen); 
	drawLines(imaze.x, imaze.y - imaze.ulen, imaze.mlen);
	
}

#endif

