#include "stdafx.h"
#include <string>
#include <ctime>

#include "sudoku.h"
#include "SudokuStats.h"
#include "ThreadPool.h"

using namespace std;

int main() {
	string sudoku_easy = "000079065000003002005060093340050106000000000608020059950010600700600000820390000";
	Sudoku sudo_easy = Sudoku(sudoku_easy);
	sudo_easy.solve();

	
	SudokuStats stats;
	stats.get_stats("top95.txt");
	stats.get_stats("hardest.txt");
	
	cout << "\n\n\nPARALLEL" << endl;
	get_ThreadPool();
	std::vector<ThreadPool::TaskFuture<void>> v;
	for (int i = 0; i < 22; ++i)
		v.push_back(submit_job([]() {SudokuStats("top95.txt"); }));
	for (auto& item : v)
		item.get();

	cout << "\n\n\n NOT PARALLEL" << endl;
	SudokuStats("top95.txt");
	

}