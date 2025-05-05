// Task.h
#pragma once
#include <limits>
#include <string>
using namespace std;
class Task {
private:
    string _taskName;
    string _description;
    string _priority;
    string _date;
    string _time;
    bool _completed;

public:
    Task(const string& taskName, const string& description, const string& priority, const string& date, const string& time, bool completed)
        : _taskName(taskName), _description(description), _priority(priority), _date(date), _time(time), _completed(completed) {
    }

    Task() = default;


    string gettaskName() const { return _taskName; }
    string getDescription() const { return _description; }
    string getPriority() const { return _priority; }
    string getDate() const { return _date; }
    string getTime() const { return _time; }
    bool getCompleted()const { return _completed; }

    void settaskName(const string& taskName) { _taskName = taskName; }
    void setDescription(const string& description) { _description = description; }
    void setPriority(const string& priority) { _priority = priority; }
    void setDate(const string& date) { _date = date; }
    void setTime(const string& time) { _time = time; }
    void setCompleted(const bool& completed) { _completed = completed; }


    json toJson() const {
        return {
            {"taskName", _taskName},
            {"description", _description},
            {"priority", _priority},
            {"date", _date},
            {"time", _time},
            { "completed", _completed }
        };
    }

    void addTask(const string& currentUsername) {
        vector<json> usersData;
        ifstream inFile("users.json");
        if (inFile) {
            json j;
            inFile >> j;
            usersData = j.get<vector<json>>();
            inFile.close();
        }
        string name, description, priority, date, time;

        cout << "Task name(max 100 simvol): ";
        getline(cin, name);
        if (name.length() > 100) {
            cout << " Name is soo long .\n";
            return;
        }

        cout << "Enter description: ";
        getline(cin, description);
        do {
            cout << "Prioritet (Low/Medium/High): ";
            getline(cin, priority);
            if (priority != "Low" && priority != "Medium" && priority != "High") {
                cout << "Wrong input. try again.\n";
            }
        } while (priority != "Low" && priority != "Medium" && priority != "High");

        do {
            cout << "Tarix (DD.MM.YYYY): ";
            getline(cin, date);
            tm tm{};
            istringstream ss(date);
            ss >> get_time(&tm, "%d.%m.%Y");
            if (ss.fail()) {
                cout << "time format is wrong. Düzgün format: DD.MM.YYYY (ex: 05.05.2025)\n";
            }
            else {
                break;
            }
        } while (true);

        do {
            cout << "Clock (HH:MM): ";
            getline(cin, time);
            tm tm{};
            istringstream ss(time);
            ss >> get_time(&tm, "%H:%M");
            if (ss.fail()) {
                cout << "Formate is not true.Try again\n";
            }
            else {
                break;
            }
        } while (true);

        json newTask;
        newTask["name"] = name;
        newTask["description"] = description;
        newTask["priority"] = priority;
        newTask["date"] = date;
        newTask["clock"] = time;
        newTask["completed"] = false;

        bool userFound = false;
        for (auto& user : usersData) {
            if (user["username"] == currentUsername) {
                user["tasks"].push_back(newTask);
                userFound = true;
                break;
            }
        }

        if (!userFound) {
            json newUser;
            newUser["username"] = currentUsername;
            newUser["tasks"] = json::array({ newTask });
            usersData.push_back(newUser);
        }


        ofstream outFile("users.json");
        outFile << setw(4) << usersData << endl;
        outFile.close();

        cout << "Task is added successfully!\n";
    }

    void updateTask(const string& username) {
        ifstream inFile("users.json");
        if (!inFile.is_open()) {
            throw runtime_error("users.json could not be opened!");
        }

        json users;
        inFile >> users;
        inFile.close();

        bool userFound = false;
        for (auto& user : users) {
            if (user["username"] == username) {
                userFound = true;

                if (!user.contains("tasks") || user["tasks"].empty()) {
                    cout << "There is no task.\n";
                    return;
                }

                cout << "Tasks:\n";
                for (size_t i = 0; i < user["tasks"].size(); ++i) {
                    cout << i + 1 << ". " << user["tasks"][i]["taskName"] << endl;
                }

                size_t index;
                cout << "Enter number of task you want to update: ";
                cin >> index;

                // ENTER axınını udmaq üçün boş getline
                string dummy;
                getline(cin, dummy);

                if (index < 1 || index > user["tasks"].size()) {
                    cout << "Wrong choice.\n";
                    return;
                }

                json& task = user["tasks"][index - 1];

                string taskName, priority, description, date, time;
                char completedChar;
                bool completed;

                cout << "New task name (" << task["taskName"] << "): ";
                getline(cin, taskName);
                if (!taskName.empty() && taskName.length() > 100) {
                    cout << "Task name must be up to 100 characters.\n";
                    return;
                }

                while (true) {
                    cout << "New priority [low, medium, high] (" << task["priority"] << "): ";
                    getline(cin, priority);
                    if (priority.empty() || priority == "low" || priority == "medium" || priority == "high") {
                        break;
                    }
                    cout << "Invalid priority. Please enter low, medium, or high.\n";
                }

                cout << "New description (" << task["description"] << "): ";
                getline(cin, description);

                while (true) {
                    cout << "New date [DD.MM.YYYY] (" << task["date"] << "): ";
                    getline(cin, date);
                    if (date.empty()) break;
                    regex dateRegex(R"(\d{2}\.\d{2}\.\d{4})");
                    if (regex_match(date, dateRegex)) break;
                    cout << "Invalid date format. Must be DD.MM.YYYY.\n";
                }

                while (true) {
                    cout << "New time [HH:MM] (" << task["time"] << "): ";
                    getline(cin, time);
                    if (time.empty()) break;
                    regex timeRegex(R"(^([01]\d|2[0-3]):([0-5]\d)$)");
                    if (regex_match(time, timeRegex)) break;
                    cout << "Invalid time format. Must be HH:MM in 24h format.\n";
                }

                while (true) {
                    cout << "Completed? (Y/N): ";
                    string input;
                    getline(cin, input);
                    if (input == "Y" || input == "y") {
                        completed = true;
                        break;
                    }
                    else if (input == "N" || input == "n") {
                        completed = false;
                        break;
                    }
                    else {
                        cout << "Please enter Y or N.\n";
                    }
                }

                if (!taskName.empty()) task["taskName"] = taskName;
                if (!priority.empty()) task["priority"] = priority;
                if (!description.empty()) task["description"] = description;
                if (!date.empty()) task["date"] = date;
                if (!time.empty()) task["time"] = time;
                task["completed"] = completed;

                break;
            }
        }

        if (!userFound) {
            throw runtime_error("İstifadəçi tapılmadı!");
        }

        ofstream outFile("users.json");
        if (!outFile.is_open()) {
            throw runtime_error("users.json yazıla bilmədi!");
        }

        outFile << users.dump(4);
        outFile.close();

        PlaySound(TEXT("applause-alks-ses-efekti-125030.wav"), NULL, SND_FILENAME | SND_ASYNC);
        cout << "Task updated!\n";
    }



    void deleteTask(const string& username) {
        ifstream inFile("users.json");
        if (!inFile.is_open()) {
            throw runtime_error("users.json could not be opened!");
        }

        json users;
        inFile >> users;
        inFile.close();

        bool userFound = false;
        for (auto& user : users) {
            if (user["username"] == username) {
                userFound = true;

                if (!user.contains("tasks") || user["tasks"].empty()) {
                    cout << "There are no tasks to delete.\n";
                    return;
                }

                cout << "Tasks:\n";
                for (size_t i = 0; i < user["tasks"].size(); ++i) {
                    cout << i + 1 << ". " << user["tasks"][i]["taskName"] << endl;
                }

                size_t index = 0;
                while (true) {
                    cout << "Enter number of the task you want to delete but if you want to cancel enter 0: ";
                    string input;
                    getline(cin, input);

                    try {
                        index = stoi(input);
                        if (index == 0) {
                            cout << "Task deletion cancelled.\n";
                            return;
                        }
                        if (index >= 1 && index <= user["tasks"].size()) {
                            break;
                        }
                        else {
                            cout << "Invalid number. Try again.\n";
                        }
                    }
                    catch (...) {
                        cout << "Please enter a valid number.\n";
                    }
                }

                string deletedTask = user["tasks"][index - 1]["taskName"];
                user["tasks"].erase(user["tasks"].begin() + (index - 1));
                cout << "Task \"" << deletedTask << "\" deleted successfully.\n";
                break;
            }
        }

        if (!userFound) {
            throw runtime_error("User not found!");
        }

        ofstream outFile("users.json");
        if (!outFile.is_open()) {
            throw runtime_error("users.json Could not be written!");
        }

        outFile << users.dump(4);
        outFile.close();
    }

    void searchTasks(const string& username) {
        ifstream inFile("users.json");
        if (!inFile.is_open()) {
            throw runtime_error("users.json could not be opened!");
        }

        json users;
        inFile >> users;
        inFile.close();

        string keyword;
        cout << "Enter any word: ";
        cin.ignore();
        getline(cin, keyword);

        bool userFound = false;
        bool anyFound = false;

        for (auto& user : users) {
            if (user["username"] == username) {
                userFound = true;

                if (!user.contains("tasks") || user["tasks"].empty()) {
                    cout << "There is no any task." << endl;
                    return;
                }

                for (auto& task : user["tasks"]) {
                    string name = task["taskName"];
                    string priority = task["priority"];
                    string desc = task["description"];
                    string date = task["date"];
                    string time = task["time"];

                    if (
                        name.find(keyword) != string::npos ||
                        priority.find(keyword) != string::npos ||
                        desc.find(keyword) != string::npos ||
                        date.find(keyword) != string::npos ||
                        time.find(keyword) != string::npos
                        ) {
                        cout << "Task name: " << name << endl;
                        cout << "Prioritet: " << priority << endl;
                        cout << "Description: " << desc << endl;
                        cout << "Time: " << date << endl;
                        cout << "Time: " << time << endl;
                        cout << "Completed or not: " << (task["completed"] ? "Yes" : "No") << endl;
                        cout << "------------------------" << endl;
                        anyFound = true;
                    }
                }
                break;
            }
        }

        if (!userFound) {
            throw runtime_error("Could not found user!");
        }
        if (!anyFound) {
            cout << "There is no task!" << endl;
        }
    }
};
