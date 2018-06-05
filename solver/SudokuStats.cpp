#include "stdafx.h"
#include "SudokuStats.h"


SudokuStats::SudokuStats()
{
}


SudokuStats::~SudokuStats()
{
}

void SudokuStats::load_txt(const std::string& filename)
{
	std::ifstream in_file(filename);
	std::string line;
	while (std::getline(in_file, line))
		sudokus_to_solve.push_back(line);
	in_file.close();
}

void SudokuStats::solve_all()
{
	for (const auto& sudo_str : sudokus_to_solve) {
		sudoku.load(sudo_str);
		sudoku.solve();
		times_ms.push_back(sudoku.get_solve_duration());
	}
}

void SudokuStats::print_stats()
{
	mean_stdev();
	std::cout << "Stats : \n" <<
		"Number : " << sudokus_to_solve.size() << std::endl <<
		"Mean solving time : "  << mean															<< " ms \n" <<
		"Stdev solving time : " << stdev														<< " ms \n" <<
		"Max solving time : "   << *std::max_element(std::begin(times_ms), std::end(times_ms))	<< " ms \n" <<
		"Min solving time : "   << *std::min_element(std::begin(times_ms), std::end(times_ms))	<< " ms \n";
}

void SudokuStats::get_stats(const std::string& filename)
{
	sudokus_to_solve.clear();
	times_ms.clear();
	load_txt(filename);
	solve_all();
	print_stats();
	std::sort(times_ms.begin(), times_ms.end());
	for (auto i = times_ms.begin(); i != times_ms.end(); ++i)
		std::cout << *i << ' ';
	std::cout << std::endl;
}

void SudokuStats::mean_stdev()
{
	mean = std::accumulate(times_ms.begin(), times_ms.end(), 0.0) / times_ms.size();
	double sum = 0.0;
	std::for_each(times_ms.begin(), times_ms.end(), [&](const double& d) {sum += (d - mean)*(d - mean); });
	stdev = sqrt(sum / (times_ms.size() - 1));
}
