#pragma once
#include <vector>
#include <algorithm>
namespace sudoku
{
	class Possible
	{
	public:
		Possible();
		~Possible();
	};

	class Possible
	{
	public:
		Possible();
		bool is_on(int& i) const;
		int count() const;
		void eliminate(int& i);
		void update(int& i, const bool& value);
		void keep(int& i);
		void keep_back();
		int val() const;
		std::string str(int& w) const;
	private:
		std::vector<bool> _b;
		std::vector<bool> _keep;
		//int _i;
	};
}