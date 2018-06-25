#pragma once
#include <string>
#include <vector>
#include <fstream>

#include "sudoku.h"
#include "Sudoku2.h"

class SudokuStats
{
public:
	SudokuStats();
	SudokuStats(const std::string& filename);
	void get_stats(const std::string& filename);
	~SudokuStats();

private:
	void load_txt(const std::string& filename);
	void solve_all();
	void print_stats();

	double mean, stdev;
	void mean_stdev();
	std::vector<double> times_ms;
	std::vector<std::string> sudokus_to_solve;

	sudoku sudoku;
};

