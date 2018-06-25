#include "stdafx.h"
#include "Sudoku2.h"


Sudoku2::Sudoku2()
{
}


Sudoku2::~Sudoku2()
{
}

Possible::Possible() : _b(9, true) {}
bool Possible::is_on(int& i) const
{
	return _b[i - 1];
}
int Possible::count() const
{
	return std::count(_b.begin(), _b.end(), true);
}
void Possible::eliminate(int& i)
{	
	_b[i - 1] = false;
}
int Possible::val() const
{
	auto it = find(_b.begin(), _b.end(), true);
	return it != _b.end() ? it - _b.begin() + 1 : -1;
}
std::string Possible::str(int& w) const
{
	std::string s(w, ' ');
	int k = 0;
	for (int i = 1; i <= 9; ++i)
		if (is_on(i))
			s[k++] = '0' + i;
	return s;
}

bool Sudoku2::is_solved() const {
	for (const Possible& cell : _cells)
		if (cell.count() > 1)
			return false;
	return true;
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
			v.push_back(&_cells[s_val + (int)(k/3) + (int)(k%3)*9]);
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
		if (cell->val == num)
			return false;
	return true;
}

void