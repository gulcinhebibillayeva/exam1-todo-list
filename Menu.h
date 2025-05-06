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
		if (choice == 3) {
			SetColor(GREEN);
			cout << "Delete Task <<\n";
		}
		else {
			SetColor(WHITE);
			cout << "Delete Task\n";
		}

		if (choice == 4 ){
			SetColor(GREEN);
			cout << "Search Task <<\n";
		}
		else {
			SetColor(WHITE);
			cout << "Search Task\n";
		}

		if (choice == 5) {
			SetColor(GREEN);
			cout << "Filter by Time Range <<\n";
		}
		else {
			SetColor(WHITE);
			cout << "Filter by Time Range\n";
		}



		SetColor(WHITE);
		int c = _getch();

		if (c == key_up) {
			choice = (choice > 0) ? choice - 1 : 5;
		}
		else if (c == key_down) {
			choice = (choice < 5) ? choice + 1 : 0;
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
				Task task;
				try {
					task.updateTask(currentUsername);
				}
				catch (const exception& e) {
					SetColor(RED);
					cout << "Xəta: " << e.what() << endl;
				}
				SetColor(WHITE);
				system("pause");
			}
			else if (choice == 2) {
				Task task;
				try {
					task.showTasks(currentUsername);
				}
				catch (const exception& e) {
					SetColor(RED);
					cout << "Xəta: " << e.what() << endl;
				}
				SetColor(WHITE);
				system("pause");
				
			}
			else if (choice == 3) {
				Task task;
				try {
					task.deleteTask(currentUsername);
				}
				catch (const exception& e) {
					SetColor(RED);
					cout << "Xəta: " << e.what() << endl;
				}
				SetColor(WHITE);
				system("pause");
			}
			else if (choice == 4) {
				Task task;
				try {
					task.searchTasks(currentUsername);
				}
				catch (const exception& e) {
					SetColor(RED);
					cout << "Xəta: " << e.what() << endl;
				}
				SetColor(WHITE);
				system("pause");
			}

			else if (choice == 5) {
				Task task;
				try {
					task.showTasksByTimeRange(currentUsername);
				}
				catch (const exception& e) {
					SetColor(RED);
					cout << "Xəta: " << e.what() << endl;
				}
				SetColor(WHITE);
				system("pause");
			}



		}
	}


}