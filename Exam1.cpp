
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include "json.hpp"
#include <mmsystem.h>
#include <thread>
#include <chrono>
#include<string>

using json = nlohmann::json;
#pragma comment(lib, "winmm.lib")
using namespace std;

void SetColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
#define key_up 72
#define key_down 80
#define key_enter 13
#define key_right 77
#define RED 12
#define GREEN 10
#define BLUE 9
#define WHITE 15
#include "AddTask.h"
#include"Menu.h"
#include"Registration.h"




int main()

{
    registrationMenu();
    

   
}