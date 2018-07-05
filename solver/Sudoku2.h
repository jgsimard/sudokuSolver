#pragma once
#include <vector>
#include <numeric>
#include <algorithm>
#include <fstream>
#include <string>

#include "Possible.h"
#include "Sudoku.h"
namespace sudoku
{
	const int nb_cell = 81;

	class Sudoku2 : public Sudoku
	{
	public:
		Sudoku2();
		~Sudoku2();

	protected:
		int lowest_count_cell();
		void update_group(int& index, const bool& value);
		bool solve_recursive();
		bool find_possibilities();
		bool is_solved() const;
		void make_groups();
		bool add_works(const int & num, const int & index) const;

		bool update_possibilities();
		
		std::vector<Possible> _cells;
		std::vector<std::vector<Possible*>> _groups;
	};
}