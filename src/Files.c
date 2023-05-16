#ifndef Files_C
#define Files_C

#include"Game.h"
#include<stdio.h>
#include<stdlib.h>
typedef Record *Tp;

static int Records_N=0;static Tp Head=NULL,Tail=NULL;
void LoadRecord(){
    FILE *fp=fopen("Records.txt","r");
    Records_N=0,Head=Tail=NULL;
    if(fp!=NULL){
        fscanf(fp,"%d",&Records_N);
        for(int i=1;i<=Records_N;i++){
            Tp p=(Tp)malloc(sizeof(Record));
            fscanf(fp,"%d%d",&p->rank,&p->cost);
            if(Head==NULL) Head=p;else Tail->next=p;
            Tail=p;
        }
        fclose(fp);
    }
}
void Modify(int id){
    char filename[20]="";
    sprintf(filename,"Record%d.txt",id);
    FILE *fp=fopen(filename,"w");
    fprintf(fp,"%d\n",Total);
    Pos *p=Head_List,*q;
    for(int i=1;i<=Total;i++){
        fprintf(fp,"%d %d\n",p->x,p->y);
        q=p,p=p->next;
        free(q);
    }
    fclose(fp);
}
int UpdateRecord(){
    LoadRecord();
    int id=0;Tp p=Head;
    for(int i=1;i<=Records_N;i++,p=p->next) if(p->rank==Rank) {id=i;break;}
    if(!id){
        p=(Tp)malloc(sizeof(Record));
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
    return id;
    fclose(fp);
}

#endif