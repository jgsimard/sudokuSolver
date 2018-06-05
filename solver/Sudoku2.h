#pragma once
#include <vector>
#include <numeric>
#include <algorithm>
#include <fstream>
#include <string>
class Sudoku2
{
public:
	Sudoku2();
	~Sudoku2();
};

class Possible {
	std::vector<bool> b_;
public:
	Possible();
	bool is_on(int& i) const;
	int count() const;
	void eliminate(int& i);
	int val() const;
	std::string str(int& w) const;
private:
};

class Sudoku {
	std::vector<Possible> cells_;
	static std::vector<std::vector<int>> group_, neighbors_, groups_of;

	bool     eliminate(int k, int val);
public:
	Sudoku(std::string s);
	static void init();

	Possible possible(int k) const { return cells_[k]; }
	bool     is_solved() const;
	bool     assign(int k, int val);
	int      least_count() const;
	void     write(std::ostream& o) const;
};