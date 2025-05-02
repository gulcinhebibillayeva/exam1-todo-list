#pragma once
struct Date {
	int day;
	int month;
	int year;

};
struct Time {
	int hour;
	int minute;
};
class Task {
private:
	int _id;
	string _taskName;
	int _priority;
	string _description;
	 Date _date;
	Time _time;
	bool _completed;
public:
	Task();
	Task(int id, int priority, string taskName, string description, Date date, Time time, bool completed) {

	}


};
