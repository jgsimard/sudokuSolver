#pragma once
#include <string>
#include <iostream>

namespace sudoku
{
	class AbstractSudoku
	{
	public:		
		AbstractSudoku(const std::string& sudoku_string);
		AbstractSudoku();
		virtual ~AbstractSudoku() = 0;
		virtual bool solve() = 0;
		virtual void load(const std::string& sudoku_string) = 0;
		double get_solve_duration();

	protected:
		static int steps;
		double _time_ms;
	};

	//useful function
	void print(const int grid[][9]);
}