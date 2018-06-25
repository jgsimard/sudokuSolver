#include "stdafx.h"
#include "Sudoku.h"
#include <string>

int Sudoku::steps = 0;

Sudoku::Sudoku(const std::string& sudoku_string)
{
	//square_formation();
	load(sudoku_string);
	print();
	if (solve()) {
		std::cout << "Elapsed time (ms): "<< _time_ms << std::endl;
		print();
	}
	else
		std::cout << "Unable to solve" << std::endl;
}
Sudoku::Sudoku() {}// { square_formation(); }

void Sudoku::load(const std::string& sudoku_string) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			int value = sudoku_string[i*size + j] == '.' ? 0 : sudoku_string[i*size + j] - '0';
			grid[i][j] = value;
			posibilities[i][j] = 0;
		}
	}
}


void Sudoku::print() const
{
	std::cout << "print : " << steps << std::endl;
	for (int i = 0; i < size; i++) {
		if (i % 3 == 0 && i != 0)
			std::cout << "----------------------------------\n";
		for (int j = 0; j < size; j++) {
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

double Sudoku::get_solve_duration(){return _time_ms;}

bool Sudoku::solve() 
{
	using namespace std::chrono;
	auto begin = high_resolution_clock::now();
	if (solve_recursive()) {
		_time_ms = (double)duration_cast<microseconds>(high_resolution_clock::now() - begin).count() / 1000;
		return true;
	}
	return false;	
}
bool Sudoku::solve_recursive()
{
	steps++;
	cell_type row, col;
	bool is_grid_complete;
	if (!find_nb_possibilities(row, col, is_grid_complete)) return false;
	if (is_grid_complete) return true;
	for (cell_type i = 1; i <= size; i++) {
		if (add_works(i, row, col)) {
			grid[row][col] = i;
			if (solve_recursive())
				return true;
			else
				grid[row][col] = 0;
		}
	}
	return false;
}
bool Sudoku::solve_recursive2()
{
	steps++;
	cell_type row, col;
	bool remaining;
	std::vector<cell_type> pos;
	if (!find_nb_possibilities2(row, col, remaining, pos)) return false;
	if (!remaining) return true;
	for (const int& i : pos) {
		grid[row][col] = i;
		if (solve_recursive2())
			return true;
		else
			grid[row][col] = 0;
	}
	return false;
}
/*
void Sudoku::square_formation() {
	
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			for (int k = 0; k < 9; ++k) {
				sq[i][j].push_back(&(grid[i + k / 3][j + k % 3]));
			}
		}
	}
}
*/
bool Sudoku::add_works(const cell_type& num, const cell_type& row, const cell_type& col) const
{
	const cell_type s_row = (row / 3) * 3; // 0,1,2 => 0, 3,4,5 => 3, 6,7,8 => 6 
	const cell_type s_col = (col / 3) * 3;
	for (cell_type i = 0; i < size; ++i) {
		if (grid[i][col] == num || //check col
			grid[row][i] == num || //check row
			//*(sq[s_row][s_col][i]) == num)
			grid[s_row + i / 3][s_col + i % 3] == num) //check square
			return false;
	}
	return true;
}
bool Sudoku::find_nb_possibilities(cell_type& row, cell_type& col, bool& is_grid_complete)
{
	int min = 10;
	is_grid_complete = true;
	for (cell_type i = 0; i < size; ++i) {
		for (cell_type j = 0; j < size; ++j) {
			if (grid[i][j] == 0){ //check if the case is populated
				posibilities[i][j] = 0;
				for (cell_type k = 1; k <= size; ++k) { //check if 1 to 9 works
					if (add_works(k,i,j)){
						++posibilities[i][j];
					}
				}
				if (posibilities[i][j] == 0) return false;
				is_grid_complete = false;
				if (posibilities[i][j] < min) {
					min = posibilities[i][j];
					row = i;
					col = j;
					if (posibilities[i][j] == 1) return true;
				}	
			}
		}
	}
	return true;
}
bool Sudoku::find_nb_possibilities2(cell_type& row, cell_type& col, bool& remaining, std::vector<cell_type>&pos)
{
	int min = 10;
	std::vector<cell_type> temp(4);
	remaining = false;
	for (cell_type i = 0; i < size; ++i) {
		for (cell_type j = 0; j < size; ++j) {
			if (grid[i][j] == 0) {
				temp.clear();
				posibilities[i][j] = 0;
				for (cell_type k = 1; k <= size; ++k) {
					if (add_works(k, i, j)) {
						posibilities[i][j]++;
						temp.push_back(k);
					}
					//if (posibilities[i][j] > min) break;
				}
				if (posibilities[i][j] == 0) return false;
				remaining = true;
				if (posibilities[i][j] < min) {
					min = posibilities[i][j];
					row = i;
					col = j;
					pos = temp;
					if (posibilities[i][j] == 1) return true;
				}
			}
		}
	}
	return true;
}