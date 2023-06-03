#ifndef Go_C
#define Go_C
#include"Game.h"
#include"graphics.h"
#include"extgraph.h"
#include"imgui.h"

extern int Xp,Yp;
extern int Yaoshi; 
void Go_Move(int key,int event);
void Go(){registerKeyboardEvent(Go_Move);}
const int Dp[4][2]={{0,-1},{-1,0},{0,1},{1,0}};
const char Dc[]="AWDS";
int Get(int key){//获取按键
    if(key>=37&&key<=40) return key-37;
    for(int i=0;i<4;i++) if(key==Dc[i]) return i;
    return -1;
}
int OK(int x,int y){return (x>=1&&x<=N&&y>=1&&y<=N&&mp[x][y]!=1);}//地图合法性判断
//判断合法性
void Go_Move(int key,int event){//移动
    uiGetKeyboard(key,event);
    if(event==KEY_UP) return;
    int f=Get(key);
    if(~f){
        if(OK(Xp+Dp[f][0],Yp+Dp[f][1])){
            if(inPage==5){
            	if(mp[Xp+Dp[f][0]][Yp+Dp[f][1]]==4) {Xp+=Dp[f][0],Yp+=Dp[f][1];mp[Xp][Yp]=0;Yaoshi++;}
            	else if(mp[Xp+Dp[f][0]][Yp+Dp[f][1]]==3) {
					if(Yaoshi==0) return;
					else {Yaoshi--;Xp+=Dp[f][0],Yp+=Dp[f][1];mp[Xp][Yp]=0;}
				}
				else Xp+=Dp[f][0],Yp+=Dp[f][1];;
			}
			else{ 
					Xp+=Dp[f][0],Yp+=Dp[f][1];
            		if(mp[Xp][Yp]==4) {mp[Xp][Yp]=0;Time = Time<3 ? 0:Time-3;}
            		if(mp[Xp][Yp]==3) {mp[Xp][Yp]=0;Time+=8;}
        		}
            	Tp p=(Tp)malloc(sizeof(Pos));
            	p->x=Xp,p->y=Yp,++Total;
            	if(Head_List==NULL) Head_List=p;else Tail_List->next=p;
            	Tail_List=p;
            	ReDraw();
				if(inPage==5) {
					static char yaoshi[30]="";
					double W=GetWindowWidth(),H=GetWindowHeight();
					double X=W/2,Y=H;
					SetPointSize(30);
					SetPenColor("Red");
					sprintf(yaoshi,"您持有的钥匙数为：%d",Yaoshi);
					MovePen(X-2.5,Y-1);
					DrawTextString(yaoshi);
				}
        	}
   		}
}
#endif
