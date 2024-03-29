//[dp_bridge_pattern_cpp

//`[~文件名：[role blue dp_bridge_pattern.cpp]]

#include <iostream>

namespace wp
{

// 导弹基
class missile
{
public:
	virtual ~missile() = default;
	virtual void seek() const = 0;
};

// 巡航导弹
class cruise_missile: virtual public wp::missile
{
public:
	void seek() const override
	{
		std::cout << "巡航导弹正在索敌 ..." << std::endl;
	}
};

// 蜂群导弹

class swarm_missile: virtual public wp::missile
{
public:
	void seek() const override
	{
		std::cout << "蜂群导弹正在索敌 ..." << std::endl;
	}
};

// 武器
class weapon
{
protected:
	wp::missile & missile;
public:
	virtual ~weapon() = default;
public:
	weapon(wp::missile & missile__):
		missile{missile__}
	{
	}
public:
	void attack() const
	{
		std::cout << "武器桥接到导弹了：";
		missile.seek();
	}
};

// 制导武器
class guided_weapon: virtual public wp::weapon
{
public:
	guided_weapon(wp::missile & missile__):
		wp::weapon{missile__}
	{
	}
	void attack() const
	{
		std::cout << "制导武器桥接到导弹了：";
		this->missile.seek();
	}
};

}	// namespace wp

int main()
{
	auto m1 = wp::cruise_missile{};
	auto m2 = wp::swarm_missile{};

	auto w1 = wp::weapon{m1};
	auto w2 = wp::weapon{m2};

	auto w3 = wp::guided_weapon{m1};
	auto w4 = wp::guided_weapon{m2};

	std::cout << "==========" << "导弹即将发射 ...\n";
	m1.seek();
	m2.seek();

	std::cout << "\n==========" << "武器即将发射 ...\n";
	w1.attack();
	w2.attack();

	std::cout << "\n==========" << "武器即将发射 ...\n";
	w3.attack();
	w4.attack();
}

/*`
[h2 程序输出：]
[!teletype]
```
==========导弹即将发射 ...
巡航导弹正在索敌 ...
蜂群导弹正在索敌 ...
   
==========武器即将发射 ...
武器桥接到导弹了：巡航导弹正在索敌 ...
武器桥接到导弹了：蜂群导弹正在索敌 ...

==========武器即将发射 ...
制导武器桥接到导弹了：巡航导弹正在索敌 ...
制导武器桥接到导弹了：蜂群导弹正在索敌 ...
```
*/
//]

