#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"graphics.h"
#include"imgui.h"
#include"extgraph.h"
#include"Game.h"
void Main(){
	InitConsole();
	InitGUI();
	SetWindowSize(10.0/0.618,10.0); 
	InitGraphics();
	Menu_Main();
}
