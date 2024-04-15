//[cobalt_awaitable_cpp

//`[~文件名：[role blue cobalt_awaitable.cpp]]

#include <boost/cobalt.hpp>
#include <iostream>

namespace cobalt = boost::cobalt;

template <cobalt::awaitable type_t>
class test
{
};

cobalt::main co_main(int argc, char * argv[])
{
	test<cobalt::promise<int>>{};
	test<cobalt::generator<float>>{};
	std::cout << "欢迎收看，谢谢！" << std::endl;
	co_return 0;
}

//]

