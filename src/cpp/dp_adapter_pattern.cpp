//[dp_adapter_pattern_cpp

//`[~文件名：[role blue dp_adapter_pattern.cpp]]

#include <iostream>

namespace wp
{

// 导弹
class missile
{
public:
	virtual ~missile() = default;
public:
	virtual void seek() const
	{
		std::cout << "导弹正在索敌 ..." << std::endl;
	}
};

// 加农炮
class cannon
{
public:
	virtual ~cannon() = default;
public:
	virtual void fire() const = 0;
};

// 导弹大炮适配器：让大炮具有了导弹的功能，但是继续保持大炮的接口不变
class missile_cannon_adapter: virtual private wp::missile, virtual public wp::cannon
{
public:
	// 大炮的接口（开火），导弹的功能（索敌）
	void fire() const override
	{
		std::cout << "导弹到大炮的适配器被调用了：";
		this->seek();
	}
};

}	// namespace wp

int main()
{
	wp::cannon * cannon = new wp::missile_cannon_adapter{};
	cannon->fire();
	delete cannon;
	
	// 正确：适配器类引用可以转化成加农炮类引用
	static_assert(std::convertible_to<wp::missile_cannon_adapter &, wp::cannon &>);
	
	// 正确：适配器类引用不可以转化成导弹类引用
	static_assert(! std::convertible_to<wp::missile_cannon_adapter &, wp::missile &>);
}

/*`
[h2 程序输出]

[!teletype]
```
导弹到大炮的适配器被调用了：导弹正在索敌 ...
```
*/

//]

