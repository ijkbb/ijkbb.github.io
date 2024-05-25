//[math_dft_cpp
/*`
c++ 标准库 std::complex 对复数的各种运算都支持的很好，可拿来直接使用

c++ 输出用 std::cout

std::vector 也非常出色的用于离散傅里叶变换里的数列系列，数学理论中的函数在计算中以离散的数列形式实现，为 std::vector
*/
//`[~文件名：[role blue math_dft.cpp]]
//` 2024-05-25

#include <iostream>
#include <vector>
#include <complex>

constexpr auto im = std::complex{0.0, 1.0};	// 声明单位虚数，方便后续使用
using std::numbers::pi;

class dft_class
{
public:
	using real_value_type = double;
	using value_type = std::complex<real_value_type>;
	using array_type = std::vector<value_type>;
public:
	virtual ~dft_class() = default;
protected:
	array_type input;	// 向量里每个值都是一个复数 std::complex
	array_type output;
	const unsigned long int N;	// N 为总项数
public:
	dft_class(const std::initializer_list<value_type> & list):
		input{list},
		N{input.size()}
	{
		this->dft();
	}
protected:
	value_type dft_k(unsigned int k)	// 计算变换后的第 k 项
	{
		value_type sum{0};
		for (unsigned int n=0u; n<N; ++n)
		{
			sum += input[n] * std::exp(im*(-2.0 * pi * k*n/N));
		}
		return sum;
	}
	void dft()
	{
		for (unsigned int k=0; k<N; ++k)
		{
			output.push_back(this->dft_k(k));
		}
	}
public:
	const array_type & get_dft() const
	{
		return output;
	}
	const array_type & get_input() const
	{
		return input;
	}
};

int main()
{
	std::cout << "Hello c++ DFT!" << std::endl;
	dft_class dft{
		{3},
		{1,2},
		{-2,1},
		{1,3},
		{0,2},
		{2,5},
		{-2,3},
		{-4,-1}
	};

	std::cout << "输入为：" << std::endl;
	for (const auto & item: dft.get_input())
		std::cout << item << std::endl;
	std::cout << std::endl;

	std::cout << "DFT 输出为：" << std::endl;
	for (const auto & item: dft.get_dft())
		std::cout << item << std::endl;
	std::cout << std::endl;
}

/*`
[h2 程序输出：]

注意每一项都是一个复数

[!teletype]
```
Hello c++ DFT!
输入为：
(3,0)
(1,2)
(-2,1)
(1,3)
(0,2)
(2,5)
(-2,3)
(-4,-1)

DFT 输出为：
(-1,15)
(-2.53553,-9.77817)
(12,-8)
(9.94975,0.12132)
(-1,-3)
(4.53553,5.77817)
(2,4)
(0.0502525,-4.12132)
```
*/

//]

