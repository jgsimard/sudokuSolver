#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include <numeric>
#include <algorithm>
#include <fstream>

using cell_type = int; //using __int8 or short slows the program

const int nb_threads = 9;
const cell_type size = 9;

class sudoku
{
public:
	static int steps;
	sudoku(const std::string& sudoku_string);
	sudoku();
	void print() const;
	bool solve();
	void load(const std::string& sudoku_string);
	double get_solve_duration();

private:
	cell_type grid[size][size];
	cell_type posibilities[size][size];
	
	bool add_works(cell_type& num, cell_type& row, cell_type& col) const;

	bool solve_recursive();
	bool find_nb_possibilities(cell_type& row, cell_type& col, bool& remaining);

	//2x slower don't know why
	bool solve_recursive2();
	bool find_nb_possibilities2(cell_type& row, cell_type& col, bool& remaining, std::vector<cell_type>& pos);

	double time_ms;
	std::vector<int*> sq[3][3];
	void square_formation();
	//bool solve_recursive_multithread();
	//std::thread threads[nb_threads];
};



