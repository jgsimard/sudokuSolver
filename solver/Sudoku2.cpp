#include "stdafx.h"
#include "Sudoku2.h"

namespace sudoku
{
	Sudoku2::Sudoku2()
	{
	}


	Sudoku2::~Sudoku2()
	{
	}

	bool Sudoku2::find_possibilities()
	{
		for (int i = 0; i < nb_cell; ++i) {
			for (int j = 1; j <= 9; ++j) {
				for (auto& cell_in_group : _groups[i]) {

				}
			}
		}
		return true;
	}

	bool Sudoku2::update_possibilities()
	{
		return false;
	}

	bool Sudoku2::is_solved() const {
		for (const Possible& cell : _cells)
			if (cell.count() > 1)
				return false;
		return true;
	}

	int Sudoku2::lowest_count_cell()
	{
		int n = 10;
		int pos = -1;
		for (int i = 0; i < nb_cell; ++i) {
			int c = _cells[i].count();
			if (c == 0)	return -1;
			if (c < n) {
				if (c == 2)	return i;
				n = c;
				pos = i;
			}
		}
		return pos;
	}

	void Sudoku2::update_group(int & index,const bool & value)
	{
		for (auto& pcell : _groups[index])
			pcell->update(index, value);
	}

	bool Sudoku2::solve_recursive()
	{
		steps++;
		if (is_solved()) return true;
		int index_lowest_count_cell = lowest_count_cell();
		if (index_lowest_count_cell == -1) return false;
		for (int i = 1 ; i <= 9; ++i) {
			if (_cells[index_lowest_count_cell].is_on(i)) {
				_cells[index_lowest_count_cell].keep(i);
				update_group(index_lowest_count_cell, false);
				if(!solve_recursive()){
					_cells[index_lowest_count_cell].update(i, true);
					}

			}
				
		}
		return false;
	}

	void Sudoku2::make_groups()
	{
		std::vector<Possible*> bob;
		for (int i = 0; i < nb_cell; ++i) {
			std::vector<Possible*> v;
			int row = i / 9;
			int col = i % 9;
			int s_row = (row / 3) * 3;
			int s_col = (col / 3) * 3;
			int s_val = s_col + 9 * s_row;

			for (int k = 0; k < 9; ++k) {
				v.push_back(&_cells[row * 9 + k]);
				v.push_back(&_cells[col + 9 * k]);
				v.push_back(&_cells[s_val + (int)(k / 3) + (int)(k % 3) * 9]);
			}
			v.erase(std::remove(v.begin(), v.end(), &_cells[i]), v.end());
			std::sort(v.begin(), v.end());
			auto last = std::unique(v.begin(), v.end());
			v.erase(last, bob.end());

			_groups[i] = v;
		}
	}

	bool Sudoku2::add_works(const int & num, const int & index) const
	{
		for (const auto& cell : _groups[index])
			if (cell->val() == num)
				return false;
		return true;
	}
}