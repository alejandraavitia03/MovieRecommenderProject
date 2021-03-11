#pragma once
#include <string>
#include <set>
using namespace std;
struct Entry
{
	string title;
	string director;
	string actor1;
	string actor2;
	string actor3;
	set<string> genre; // set of genres
	string rating;
	int year;
	int score;
};

class Strategy {
public:
	virtual bool operator() (Entry e1, Entry e2) = 0;
};

class CompareByScoreAscending : public Strategy {
public:
	bool operator() (Entry e1, Entry e2) override{
		return e1.score < e2.score;
	}
};

class CompareByScoreDescending : public Strategy {
public:
	bool operator() (Entry e1, Entry e2) override {
		return e1.score > e2.score;
	}
};

class CompareByYearAscending : public Strategy {
public:
	bool operator() (Entry e1, Entry e2) override {
		return e1.year < e2.year;
	}
};

class CompareByYearDescending : public Strategy {
public:
	bool operator() (Entry e1, Entry e2) override {
		return e1.year > e2.year;
	}
};

class CompareByTitleAscending : public Strategy {
public:
	bool operator() (Entry e1, Entry e2) override {
		return e1.title < e2.title;
	}
};

class CompareByTitleDescending : public Strategy {
public:
	bool operator() (Entry e1, Entry e2) override {
		return e1.title > e2.title;
	}
};