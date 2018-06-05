#include "stdafx.h"
#include "Sudoku2.h"


Sudoku2::Sudoku2()
{
}


Sudoku2::~Sudoku2()
{
}

//Version 2

Possible::Possible() :b_(9, true) {}
bool Possible::is_on(int& i) const{	return b_[i - 1];}
int Possible::count() const{	return std::count(b_.begin(), b_.end(), true);}
void Possible::eliminate(int& i){	b_[i - 1] = false;}
int Possible::val() const
{
	auto it = find(b_.begin(), b_.end(), true);
	return it != b_.end() ? it - b_.begin() + 1 : -1;
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

bool Sudoku::is_solved() const {
	for (int k = 0; k < cells_.size(); k++)
		if (cells_[k].count() != 1)
			return false;
	return true;
}

void Sudoku::write(std::ostream& o) const {
	int width = 1;
	for (int k = 0; k < cells_.size(); k++)
		width = std::max(width, 1 + cells_[k].count());

	const std::string sep(3 * width, '-');
	for (int i = 0; i < 9; i++) {
		if (i == 3 || i == 6)
			o << sep << "+-" << sep << "+" << sep << std::endl;
		for (int j = 0; j < 9; j++) {
			if (j == 3 || j == 6) o << "| ";
			o << cells_[i * 9 + j].str(width);
		}
		o << std::endl;
	}
}
std::vector<std::vector<int>>Sudoku::group_(27);
std::vector<std::vector<int>>Sudoku::neighbors_(27);
std::vector<std::vector<int>>Sudoku::groups_of(27);

void Sudoku::init() {
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			const int k = i * 9 + j;
			const int x[3] = { i, 9 + j, 18 + (i / 3) * 3 + j / 3 };
			for (int g = 0; g < 3; ++g) {
				group_[x[g]].push_back(k);
				groups_of[k].push_back(x[g]);
			}
		}
	}
	for (int k = 0; k < neighbors_.size(); k++) {
		for (int x = 0; x < groups_of[k].size(); x++) {
			for (int j = 0; j < 9; j++) {
				int k2 = group_[groups_of[k][x]][j];
				if (k2 != k) neighbors_[k].push_back(k2);
			}
		}
	}
}
bool Sudoku::assign(int k, int val) {
	for (int i = 1; i <= 9; i++)
		if (i != val)
			if (!eliminate(k, i))
				return false;
	return true;
}
bool Sudoku::eliminate(int k, int val) {
	if (!cells_[k].is_on(val)) {
		return true;
	}
	cells_[k].eliminate(val);
	const int N = cells_[k].count();
	if (N == 0) return false;
	else if (N == 1) {
		const int v = cells_[k].val();
		for (int i = 0; i < neighbors_[k].size(); i++) {
			if (!eliminate(neighbors_[k][i], v)) return false;
		}
	}
	for (int i = 0; i < groups_of[k].size(); i++) {
		const int x = groups_of[k][i];
		int n = 0, ks;
		for (int j = 0; j < 9; j++) {
			const int p = group_[x][j];
			if (cells_[p].is_on(val)) {
				n++, ks = p;
			}
		}
		if (n == 0)return false;

		else if (n == 1) {
			if (!assign(ks, val)) return false;

		}
	}
	return true;
}