// Task.h
#pragma once
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
        newTask["id"] = "T" + to_string(rand() % 100000);
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
            throw runtime_error("users.json could not opened!");
        }

        json users;
        inFile >> users;
        inFile.close();

        bool userFound = false;
        for (auto& user : users) {
            if (user["username"] == username) {
                userFound = true;

                if (!user.contains("tasks") || user["tasks"].empty()) {
                    cout << "There is no any task.\n";
                    return;
                }

                cout << "Tasks:\n";
                for (size_t i = 0; i < user["tasks"].size(); ++i) {
                    cout << i + 1 << ". " << user["tasks"][i]["taskName"] << endl;
                }

                size_t index;
                cout << "Enter number of task you want to update: ";
                cin >> index;
                if (index < 1 || index > user["tasks"].size()) {
                    cout << "wrong choice.\n";
                    return;
                }

                json& task = user["tasks"][index - 1];
                cin.ignore();

                string taskName, priority, description, date, time;
                char completedChar;
                bool completed;

                cout << "new task name (" << task["taskName"] << "): ";
                getline(cin, taskName);
                cout << "newprioritet prioritet (" << task["priority"] << "): ";
                getline(cin, priority);
                cout << "new description (" << task["description"] << "): ";
                getline(cin, description);
                cout << "new Date(" << task["date"] << "): ";
                getline(cin, date);
                cout << "new Time (" << task["time"] << "): ";
                getline(cin, time);
                cout << "completd or not (Y/N): ";
                cin >> completedChar;
                completed = (completedChar == 'Y' || completedChar == 'y');


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
            throw runtime_error("users.json açıla bilmədi!");
        }

        json users;
        inFile >> users;
        inFile.close();

        bool userFound = false;

        for (auto& user : users) {
            if (user["username"] == username) {
                userFound = true;

                if (!user.contains("tasks") || user["tasks"].empty()) {
                    cout << "There is no any task!" << endl;
                    return;
                }

                cout << "Tasks:\n";
                int index = 0;
                for (const auto& task : user["tasks"]) {
                    cout << index + 1 << ". " << task["taskName"] << endl;
                    index++;
                }

                cout << "Enter number of task: ";
                int delIndex;
                cin >> delIndex;

                if (delIndex < 1 || delIndex > user["tasks"].size()) {
                    cout << "Wrong index!" << endl;
                    return;
                }

                user["tasks"].erase(user["tasks"].begin() + (delIndex - 1));

                ofstream outFile("users.json");
                if (!outFile.is_open()) {
                    throw runtime_error("users.json Failed to write!");
                }

                outFile << users.dump(4);
                outFile.close();

                cout << "Task deleted succesfully!" << endl;
                PlaySound(TEXT("delete-success.wav"), NULL, SND_FILENAME | SND_ASYNC);
                return;
            }
        }

        if (!userFound) {
            throw runtime_error("could not found user!");
        }
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
