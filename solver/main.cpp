#include "stdafx.h"
#include <string>
#include <ctime>

#include "sudoku.h"
#include "Stats.h"
#include "ThreadPool.h"

using namespace std;
using namespace sudoku;

int main() {
	Sudoku sudo_easy = Sudoku("000079065000003002005060093340050106000000000608020059950010600700600000820390000");
	sudo_easy.solve();
	
	Stats stats;
	stats.get_stats("top95.txt");
	stats.get_stats("hardest.txt");
	
	cout << "\n\n\nPARALLEL" << endl;
	get_ThreadPool();
	std::vector<ThreadPool::TaskFuture<void>> v;
	for (int i = 0; i < 22; ++i)
		v.push_back(submit_job([]() {Stats("top95.txt"); }));
	for (auto& item : v)
		item.get();

	cout << "\n\n\nNOT PARALLEL" << endl;
	Stats("top95.txt");
}