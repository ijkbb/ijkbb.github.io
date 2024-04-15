//[cobalt_hello_cpp

//`[~文件名：[role blue cobalt_hello.cpp]]

#include <boost/cobalt.hpp>
#include <iostream>

namespace cobalt = boost::cobalt;

class rab_pot
{
public:
	cobalt::generator<int> generator() const
	{
		for (int i=0; i<7; ++i)
			co_yield i;
		co_return -1;
	}
	cobalt::promise<int> promise() const
	{
		co_return 9;
	}
};

cobalt::main co_main(int argc, char * argv[])
{
	auto rp = rab_pot{};
	auto g = rp.generator();
	auto p = rp.promise();
	while (g)
		std::cout << co_await g << std::endl;
	std::cout << co_await p << std::endl;
	co_return 0;
}

/*`

[h2 输出：]
[!teletype]
```
0
1
2
3
4
5
6
-1
9
```
*/

//]
