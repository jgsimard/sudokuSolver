#pragma once
#include <vector>
#include <numeric>
#include <algorithm>
#include <fstream>
#include <string>

#include "Sudoku.h"

const int nb_cell = 81;

class Sudoku2 : public Sudoku 
{
public:
	Sudoku2();
	~Sudoku2();

	bool is_solved() const;

	std::vector<Possible> _cells;
	std::vector<std::vector<Possible*>> _groups;

	void make_groups();

	bool add_works(const int & num, const int & index) const;

};

class Possible {
	
public:
	Possible();
	bool is_on(int& i) const;
	int count() const;
	void eliminate(int& i);
	int val() const;
	std::string str(int& w) const;
private:
	std::vector<bool> _b;
	
};

