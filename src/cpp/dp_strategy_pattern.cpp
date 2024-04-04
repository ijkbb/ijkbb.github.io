//[dp_strategy_pattern_cpp

//`[~文件名：[role blue dp_strategy_pattern.cpp]]

#include <iostream>

namespace pattern
{

class strategy
{
public:
	virtual ~strategy() = default;
public:
	virtual void solve_equation() = 0;
};

class method_1: virtual public pattern::strategy
{
public:
	void solve_equation() override
	{
		std::cout << "用方法1" << std::endl;
	}
};

class method_2: virtual public pattern::strategy
{
public:
	void solve_equation() override
	{
		std::cout << "用方法2" << std::endl;
	}
};

class solution_context
{
public:
	virtual ~solution_context() = default;
protected:
	pattern::strategy & strategy;
public:
	solution_context(pattern::strategy & s__):
		strategy(s__)
	{
	}
public:
	virtual void solve_equation()
	{
		strategy.solve_equation();
	}
};

}	// namespace pattern

int main()
{
	pattern::method_1 m1;
	pattern::method_2 m2;
	pattern::solution_context s1{m1};
	pattern::solution_context s2{m2};
	std::cout << "解方程：" << std::endl;
	s1.solve_equation();
	std::cout << "解方程：" << std::endl;
	s2.solve_equation();
}

/*`
[h2 程序输出]

[!teletype]
```
解方程：
用方法1
解方程：
用方法2
```
*/

//]

