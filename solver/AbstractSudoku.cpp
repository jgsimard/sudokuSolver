#include "stdafx.h"
#include "AbstractSudoku.h"

namespace sudoku
{
	AbstractSudoku::AbstractSudoku(const std::string & sudoku_string)
	{
	}
	AbstractSudoku::AbstractSudoku()
	{
	}
	AbstractSudoku::~AbstractSudoku()
	{
	}
	double sudoku::AbstractSudoku::get_solve_duration()
	{
		return _time_ms;
	}

	void print(const int grid[][9])
	{
		for (int i = 0; i < 9; i++) {
			if (i % 3 == 0 && i != 0)
				std::cout << "----------------------------------\n";
			for (int j = 0; j < 9; j++) {
				if (j % 3 == 0 && j != 0)
					std::cout << " | ";

				if (grid[i][j] == 0)
					std::cout << " ? ";
				else
					std::cout << " " << grid[i][j] << " ";
			}
			std::cout << "\n";
		}
		std::cout << "\n";
	}
}