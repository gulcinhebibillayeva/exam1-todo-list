#pragma once
void OpenMainMenu(const string& currentUsername) {
	int choice = 0;

	while (true) {
		system("cls");

		if (choice == 0) {
			SetColor(GREEN);
			cout << "Add Task <<" << endl;
		}
		else {
			SetColor(WHITE);
			cout << "Add Task" << endl;
		}

		if (choice == 1) {
			SetColor(GREEN);
			cout << "Update Task <<" << endl;
		}
		else {
			SetColor(WHITE);
			cout << "Update Task" << endl;
		}

		if (choice == 2) {
			SetColor(GREEN);
			cout << "Show Tasks <<" << endl;
		}
		else {
			SetColor(WHITE);
			cout << "Show Tasks" << endl;
		}

		SetColor(WHITE);
		int c = _getch();

		if (c == key_up) {
			choice = (choice > 0) ? choice - 1 : 2;
		}
		else if (c == key_down) {
			choice = (choice < 2) ? choice + 1 : 0;
		}
		else if (c == key_enter) {
			if (choice == 0) {
				Task task;  
				try {
					task.addTask(currentUsername);  
					SetColor(GREEN);
					cout << "Task uğurla əlavə olundu!" << endl;
				}
				catch (const exception& e) {
					SetColor(RED);
					cout << "Xəta: " << e.what() << endl;
				}
				SetColor(WHITE);
				system("pause");
			}
			else if (choice == 1) {
				
			}
			else if (choice == 2) {
				
			}
		}
	}
}