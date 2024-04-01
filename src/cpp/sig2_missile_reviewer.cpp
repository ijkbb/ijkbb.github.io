//[sig2_missile_reviewer_cpp

//`[~文件名：[role blue sig2_missile_reviewer.cpp]]

#include <boost/signals2.hpp>
#include <iostream>
#include <iomanip>		// std::quoted

namespace sig2 = boost::signals2;

using signal_type = sig2::signal<void(std::string)>;	// 函数对象类型 void(std::string)
using slot_type = signal_type::slot_type;
using connection_type = sig2::connection;

using std::placeholders::_1;

namespace wp
{

// 导弹类
class missile
{
protected:
	signal_type sig;
public:
	virtual ~missile() {}
public:
	connection_type connect(const slot_type & slot)
	{
		return sig.connect(slot);
	}
public:
	void launch() const
	{
		std::cout << "发射导弹 ..." << std::endl;
		sig("发送信息：导弹被发射了");
	}
};

}	// namespace wp

namespace viewer
{

// 审查员
class reviewer
{
protected:
	wp::missile & missile;
	connection_type connection;
public:
	reviewer(wp::missile & missile__):
		missile{missile__}
	{
		connection = missile.connect(boost::bind(&viewer::reviewer::receive, this, _1));
	}
public:
	void receive(const std::string & msg) const
	{
		std::cout << "收到信息：" << std::quoted(msg) << std::endl;
	}
};

}	// namespace viewer

int main()
{
	wp::missile missile;		// 声明一枚导弹
	viewer::reviewer reviewer{missile};		// 声明一名审查员
	missile.launch();		// 发射导弹，你猜会发生什么？
}

/*`
[h2 输出：]

[!teletype]
```
发射导弹 ...
收到信息："发送信息：导弹被发射了"
```
*/

//]
