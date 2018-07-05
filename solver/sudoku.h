#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include <numeric>
#include <algorithm>
#include <fstream>

#include "AbstractSudoku.h"

namespace sudoku 
{
	using cell_type = int32_t; //using __int8 or short slows the program
	const cell_type size = 9;

	class Sudoku : public AbstractSudoku
	{
	public:
		static int steps;
		Sudoku(const std::string& sudoku_string);
		Sudoku();
		bool solve();
		void load(const std::string& sudoku_string);

	private:
		cell_type grid[size][size];
		cell_type posibilities[size][size];
	
		bool add_works(const cell_type& num, const cell_type& row, const cell_type& col) const;

		bool solve_recursive();
		bool find_nb_possibilities(cell_type& row, cell_type& col, bool& remaining);

		//2x slower don't know why
		bool solve_recursive2();
		bool find_nb_possibilities2(cell_type& row, cell_type& col, bool& remaining, std::vector<cell_type>& pos);

	};
}

