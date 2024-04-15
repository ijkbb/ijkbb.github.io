//[cobalt_race_cpp

//`[~文件名：[role blue cobalt_race.cpp]]

#include <boost/cobalt.hpp>
#include <iostream>

namespace cobalt = boost::cobalt;

class generator_set
{
public:
	cobalt::generator<int> source_1() const
	{
		for (int i=0; i<10; ++i)
			co_yield i;
		co_return 100;
	}
	cobalt::generator<double> source_2() const
	{
		for (double i=0.7; i<10.7; ++i)
			co_yield i;
		co_return 1000.7;
	}
};

cobalt::main co_main(int argc, char * argv[])
{
	auto gs = generator_set{};
	auto src1 = gs.source_1();
	auto src2 = gs.source_2();
	while (src1 && src2)
	{
		switch (auto res = co_await cobalt::race(src1, src2); res.index())
		{
		case 0:
			std::cout << "取出了整形值：" << boost::variant2::get<0>(res) << std::endl;
			break;
		case 1:
			std::cout << "取出了浮点值：" << boost::variant2::get<1>(res) << std::endl;
			break;
		}
	}
	co_return 0;
}

/*`
[h2 输出：]

[!teletype]
```
取出了整形值：0
取出了浮点值：0.7
取出了整形值：1
取出了浮点值：1.7
取出了整形值：2
取出了浮点值：2.7
取出了整形值：3
取出了浮点值：3.7
取出了整形值：4
取出了浮点值：4.7
取出了整形值：5
取出了浮点值：5.7
取出了整形值：6
取出了浮点值：6.7
取出了整形值：7
取出了浮点值：7.7
取出了整形值：8
取出了浮点值：8.7
取出了整形值：9
取出了浮点值：9.7
取出了整形值：100
```
*/

//]
