
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include "json.hpp"
#include <mmsystem.h>
#include <thread>
#include <chrono>
#include "AddTask.h"
#pragma comment(lib, "winmm.lib")
using namespace std;
using json = nlohmann::json;

#define key_up 72
#define key_down 80
#define key_enter 13
#define key_right 77
#define RED 12
#define GREEN 10
#define BLUE 9
#define WHITE 15
void   playSuccessSound() {
    if (PlaySound(L"C:\\Users\\YourUserName\\Desktop\\sound.wav", NULL, SND_FILENAME)) {
        cout << "Səs uğurla çalındı!" << endl;
    }
    else {
        cout << "Səs çalınmadı." << endl;
    }
}
void playErrorSound() {
    PlaySound(L"C:\\Users\\YourUserName\\Desktop\\error.wav", NULL, SND_FILENAME);
}
void SetColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void LoadingEffect() {
    for (int i = 0; i < 3; i++)
    {
        cout << "Yuklenir";
    }for (int i = 0; i < 3; i++)
    {
        cout << ".";Sleep(300);
    }
    system("cls");
}
string inputPassword() {
    string password;
    char ch;
    while ((ch = _getch()) != 13) {  
        if (ch == 8 && !password.empty()) {  
            password.pop_back();
            cout << "\b \b";
        }
        else if (isprint(ch)) {
            password += ch;
            cout << "*";
        }
    }
    cout << endl;
    return password;
}
bool isValidPassword(const string& password) {
    if (password.length() < 8) return false;
    bool hasDigit = false, hasAlpha = false;
    for (char ch : password) {
        if (isdigit(ch)) hasDigit = true;
        if (isalpha(ch)) hasAlpha = true;
    }
    return hasDigit && hasAlpha;
}

void signUp() {
    system("cls");
    string username, password;
    cout << "İstifadəçi adınızı daxil edin: ";
    cin >> username;

    if (username.length() < 3) {
        SetColor(RED);
        cout << "İstifadəçi adı ən az 3 simvol olmalıdır!" << endl;
        playErrorSound();
        return;
    }

    cout << "Parol daxil edin (ən az 8 simvol, hərf və rəqəm daxilində): ";
    password = inputPassword();

    if (!isValidPassword(password)) {
        SetColor(RED);
        cout << "Parol tələblərə uyğun deyil!" << endl;
        playErrorSound();
        return;
    }

    json users = json::array();
    ifstream inFile("users.json");
    if (inFile.is_open()) {
        inFile >> users;
        inFile.close();
    }

    for (auto& user : users) {
        if (user["username"] == username) {
            SetColor(RED);
            cout << "Bu istifadəçi artıq mövcuddur!" << endl;
            playErrorSound();
            return;
        }
    }

    json newUser;
    newUser["username"] = username;
    newUser["password"] = password;
    users.push_back(newUser);

    ofstream outFile("users.json");
    outFile << users.dump(4);
    outFile.close();

    LoadingEffect();
    playSuccessSound();
    SetColor(GREEN);
    cout << "Qeydiyyat uğurla tamamlandı!" << endl;
    SetColor(WHITE);
}

void signIn() {
    system("cls");
    string username, password;
    cout << "İstifadəçi adınızı daxil edin: ";
    cin >> username;
    cout << "Parolu daxil edin: ";
    password = inputPassword();

    json users = json::array();
    ifstream inFile("users.json");
    if (inFile.is_open()) {
        inFile >> users;
        inFile.close();
    }

    for (auto& user : users) {
        if (user["username"] == username && user["password"] == password) {
            LoadingEffect();
            playSuccessSound();
            SetColor(GREEN);
            cout << "Daxilolma uğurlu!" << endl;
            SetColor(WHITE);
            return;
        }
    }

    SetColor(RED);
    cout << "İstifadəçi adı və ya parol yanlışdır!" << endl;
    playErrorSound();
    SetColor(WHITE);
}

int main()

{

    int choice = 0;
    while (true)
    {
        system("cls");
        if (choice == 0) {
            SetColor(GREEN);
            cout << "Sign up << " << endl;
        }
        else {
            SetColor(WHITE);
            cout << "Sign up" << endl;
        }

        if (choice == 1) {
            SetColor(GREEN);
            cout << "Sign in <<" << endl;
        }
        else {
            SetColor(WHITE);
            cout << "Sign in" << endl;
        }

        SetColor(WHITE);
        int c = _getch();
        if (c == key_up) {
            choice = (choice > 0) ? choice - 1 : 1;
        }
        else if (c == key_down) {
            choice = (choice < 1) ? choice + 1 : 0;
        }
        else if (c == key_enter) {
            if (choice == 0) {
                signUp();
                system("pause");
            }
            else if (choice == 1) {
                signIn();
                system("pause");
            }
        }
    }

}