#include "stdafx.h"
#include <string>
#include <ctime>

#include "sudoku.h"
#include "SudokuStats.h"

using namespace std;

int main(){	
	SudokuStats stats;
	//stats.get_stats("top95.txt");
	stats.get_stats("hardest.txt");
}
