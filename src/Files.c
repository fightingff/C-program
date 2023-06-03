#ifndef Files_C
#define Files_C

#include"Game.h"
#include<stdio.h>
#include<stdlib.h>
#include"imgui.h"
#include"graphics.h"
#include"extgraph.h"

static int Records_N=0;
static Rp Head=NULL,Tail=NULL;
extern int Xp,Yp;
extern int Tough_N;
extern int number,inPage;
void InitGames(){//载入游戏关卡
    char filename[20]="";
    Tough_N=3;
    number=22,inPage=0;
    for(int i=-1;;i--,Tough_N++){
        sprintf(filename,"Game%d.txt",i);
        if(fopen(filename,"r")==NULL) break;
    }
}
void LoadRecord(){//读取最佳记录
    FILE *fp=fopen("Records.txt","r");
    Records_N=0,Head=Tail=NULL;
    if(fp!=NULL){
        fscanf(fp,"%d",&Records_N);
        for(int i=1;i<=Records_N;i++){
            Rp p=(Rp)malloc(sizeof(Record));
            fscanf(fp,"%d%d",&p->rank,&p->cost);
            if(Head==NULL) Head=p;else Tail->next=p;
            Tail=p;
        }
        fclose(fp);
    }
}
int GetPlay(){//获取当前游戏的id
    Rp p=Head;
    for(int i=1;i<=Records_N;i++,p=p->next) if(p->rank==Rank) return Time=p->cost,i;
    return -1; 
}
void Modify(int id){//更新最佳记录
    char filename[20]="";
    sprintf(filename,"Record%d.txt",id);
    FILE *fp=fopen(filename,"w");
    fprintf(fp,"%d\n",Total);
    Tp p=Head_List,q;
    for(int i=1;i<=Total;i++){//保存路径
        fprintf(fp,"%d %d\n",p->x,p->y);
        q=p,p=p->next;
        free(q);
    }
    fclose(fp);

    sprintf(filename,"Game%d.txt",id);//保存地图
    fp=fopen(filename,"w");
    fprintf(fp,"%d\n",N);
    for(int i=1;i<=N;i++,fprintf(fp,"\n")) 
      for(int j=1;j<=N;j++) fprintf(fp,"%d ",mp[i][j]);
    fclose(fp);
}
void LoadRecord_i(int id){//读取第id个最佳记录
    char filename[20]="";
    sprintf(filename,"Record%d.txt",id);
    FILE *fp=fopen(filename,"r");
    fscanf(fp,"%d",&Total);
    Head_List=Tail_List=NULL;
    for(int i=1;i<=Total;i++){//读取路径
        Tp p=(Tp)malloc(sizeof(Pos));
        fscanf(fp,"%d%d",&p->x,&p->y);
        if(Head_List==NULL) Head_List=p;else Tail_List->next=p;
        Tail_List=p;
    }
    if(Tail_List!=NULL) Tail_List->next=NULL;
    fclose(fp);

    sprintf(filename,"Game%d.txt",id);//读取地图
    fp=fopen(filename,"r");
    fscanf(fp,"%d",&N);
    for(int i=1;i<=N;i++) 
      for(int j=1;j<=N;j++) fscanf(fp,"%d",&mp[i][j]);
    fclose(fp);
}

int UpdateRecord(){//更新最佳记录
    LoadRecord();
    int id=0;Rp p=Head;
    for(int i=1;i<=Records_N;i++,p=p->next) if(p->rank==Rank) {id=i;break;}
    if(!id){
        p=(Rp)malloc(sizeof(Record));
        p->rank=Rank,p->cost=Time;
        if(Head==NULL) Head=p;else Tail->next=p;
        Tail=p;
        Modify(id=++Records_N);
    }else if(Time<p->cost){
        p->cost=Time;
        Modify(id);
    }else id=0;


    FILE *fp=fopen("Records.txt","w");
    fprintf(fp,"%d\n",Records_N);
    p=Head;
    for(int i=1;i<=Records_N;i++,p=p->next) fprintf(fp,"%d %d\n",p->rank,p->cost);
    fclose(fp);
    return id;
}

void SaveGame(){//将当前游戏保存到文件
    FILE *fp=fopen("Game.txt","w");//保存当前状态
    fprintf(fp,"%d %d\n",N,Rank);
    for(int i=1;i<=N;i++,fprintf(fp,"\n"))
      for(int j=1;j<=N;j++) fprintf(fp,"%d ",mp[i][j]);
    fprintf(fp,"%d %d\n",Xp,Yp);
    fprintf(fp,"%d\n",Time);
    fclose(fp);
    Modify(0);//将路径也存下
    double W=GetWindowWidth(),H=GetWindowHeight();
    SetPointSize(50),SetPenColor("Red");
    drawBox(W-H+2,H/2,4,2,1,"保存成功",'C',"Yellow");
    Pause(1.0);
    DisplayClear();
    ReDraw();
}
void LoadGame(){//回到上次保存的游戏
    FILE *fp=fopen("Game.txt","r");
    fscanf(fp,"%d%d",&N,&Rank);
    for(int i=1;i<=N;i++)
      for(int j=1;j<=N;j++) fscanf(fp,"%d",&mp[i][j]);
    fscanf(fp,"%d%d",&Xp,&Yp);
    fscanf(fp,"%d",&Time);
    fclose(fp);
    LoadRecord_i(0);
}
#endif