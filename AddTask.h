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
    Task(const string& taskName, const string& description, const string& priority, const string& date, const string& time,bool completed)
        : _taskName(taskName), _description(description), _priority(priority), _date(date), _time(time),_completed(completed) {
    }

    Task() = default;

   
    string gettaskName() const { return _taskName; }
    string getDescription() const { return _description; }
    string getPriority() const { return _priority; }
    string getDate() const { return _date; }
    string getTime() const { return _time; }
    bool getCompleted()const {return _completed; }
   
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


    void addTask(const string& username) {
        ifstream inFile("users.json");
        if (!inFile.is_open()) {
            throw runtime_error("users.json acilmadi");
        }

        json users;
        inFile >> users;
        inFile.close();

        bool userFound = false;
        for (auto& user : users) {
            if (user["username"] == username) {
                userFound = true;

               
                string taskName, priority, description, date, time;

                cout << "Task Name: ";
                cin.ignore();
                getline(cin, taskName);

                cout << "Prioritet (Low/Medium/High): ";
                getline(cin, priority);

                cout << "Description: ";
                getline(cin, description);

                cout << "Time (YYYY-MM-DD): ";
                getline(cin, date);

                cout << "clock (HH:MM): ";
                getline(cin, time);
                cout << "completed?";
                char completedChar;
                bool completed;

                cout << "completed? (Y/N): ";
                cin >> completedChar;

                if (completedChar == 'Y' || completedChar == 'y') {
                    completed = true;
                }
                else {
                    completed = false;
                }

                settaskName(taskName);
                setPriority(priority);
                setDescription(description);
                setDate(date);
                setTime(time);
                setCompleted(completed);

              
                json newTask = {
                    {"taskName", gettaskName()},
                    {"priority", getPriority()},
                    {"description", getDescription()},
                    {"date", getDate()},
                    {"time", getTime()},
                    {"completed", getCompleted()}
                };

                if (!user.contains("tasks")) {
                    user["tasks"] = json::array();
                }

                user["tasks"].push_back(newTask);
                break;
            }
        }

        if (!userFound) {
            throw runtime_error("user cannot found!");
        }
        ofstream outFile("users.json");
        if (!outFile.is_open()) {
            throw runtime_error("users.json cannot opened!");
        }
        outFile << users.dump(4);
        outFile.close();
    }


    void showTasks(const string& username) {
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

                cout << "User Tasks:\n";
                for (auto& task : user["tasks"]) {
                    cout << "Task name: " << task["taskName"] << endl;
                    cout << "Priorityt: " << task["priority"] << endl;
                    cout << "description: " << task["description"] << endl;
                    cout << "Date: " << task["date"] << endl;
                    cout << "time: " << task["time"] << endl;
                    if (task.contains("completed") && task["completed"].is_boolean()) {
                        cout << "completed: " << (task["completed"] ? "Bəli" : "Xeyr") << endl;
                    }
                    else {
                        cout << "Completed: Məlumat yoxdur" << endl;
                    }
                    cout << "----------------------------\n";
                }
                break;
            }
        }

        if (!userFound) {
            throw runtime_error("User could not found!");
        }
    }



};
