#pragma once
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
            cout << '*';
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


void playSuccessSound() {
    PlaySound(L"qeydiyyat.wav", NULL, SND_FILENAME | SND_ASYNC);
}


void playErrorSound() {
    PlaySound(L"C:\\Users\\YourUserName\\Desktop\\error.wav", NULL, SND_FILENAME);
}


void LoadingEffect() {
    for (int i = 0; i < 3; i++) {
        cout << "Yuklenir";
    }
    for (int i = 0; i < 3; i++) {
        cout << ".";
        Sleep(300);
    }
    system("cls");
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
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    password = inputPassword();

    ifstream file("users.json");
    if (!file.is_open()) {
        cout << "Error opening file!" << endl;
        return;
    }

    json j;
    file >> j;
    file.close();

    bool found = false;

    for (auto& user : j) {
        if (user["username"] == username && user["password"] == password) {
            cout << "Login successful!" << endl;
            found = true;
            Sleep(1000);
            OpenMainMenu(username); 
            break;
        }
    }

    if (!found) {
        SetColor(RED);
        cout << "Invalid username or password!" << endl;
        playErrorSound();
        SetColor(WHITE);
        Sleep(1500);
    }
}


void registrationMenu() {
    int choice = 0;

    while (true) {
        system("cls");

        if (choice == 0) {
            SetColor(GREEN);
            cout << "Qeydiyyat (Sign Up) " << endl;
        }
        else {
            SetColor(WHITE);
            cout << "Qeydiyyat (Sign Up)" << endl;
        }

        if (choice == 1) {
            SetColor(GREEN);
            cout << "Giris (Sign In) " << endl;
        }
        else {
            SetColor(WHITE);
            cout << "Giris (Sign In)" << endl;
        }

        SetColor(WHITE);
        int key = _getch();
        if (key == 72) {  
            choice = (choice > 0) ? choice - 1 : 1;
        }
        else if (key == 80) {  
            choice = (choice < 1) ? choice + 1 : 0;
        }
        else if (key == 13) { 
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
