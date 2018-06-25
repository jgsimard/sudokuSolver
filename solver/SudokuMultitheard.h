#pragma once

//#include "QueueThreadSafe.h"
//#include "ThreadPool.h"
#include "sudoku.h"

class SudokuMultitheard : public sudoku
{
public:
	SudokuMultitheard(const std::string& sudoku_string);
	~SudokuMultitheard();

private:
//	ThreadPool _thread_pool;
};

