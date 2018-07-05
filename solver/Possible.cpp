#include "stdafx.h"
#include "Possible.h"
namespace sudoku
{
	Possible::Possible() : _b(9, true)
	{}

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
	void Possible::update(int& i, const bool& value)
	{
		_b[i - 1] = value;
	}

	void Possible::keep(int & i)
	{
		_keep = _b;
		std::fill(_b.begin(), _b.end(), false);
		_b[i - 1] = true;
	}

	void Possible::keep_back()
	{
		_b = _keep;
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
}

