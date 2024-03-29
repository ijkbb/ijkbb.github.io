//[dp_proxy_pattern_cpp

//`[~文件名：[role blue dp_proxy_pattern.cpp]]

#include <iostream>

namespace wp
{

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

// 巡航导弹代理
class cruise_missile_proxy: virtual public wp::missile
{
protected:
	wp::cruise_missile * missile;
	bool is_ready;
public:
	cruise_missile_proxy():
		missile{new wp::cruise_missile}
	{
	}
	cruise_missile_proxy(const wp::cruise_missile & missile__):
		missile{new wp::cruise_missile{missile__}}
	{
	}
public:
	virtual ~cruise_missile_proxy()
	{
		delete missile;
	}
public:
	void seek() const override
	{
		if (this->ready())
		{
			std::cout << "Cruise missile is ready!" << std::endl;
			missile->seek();
		}
	}

	bool ready() const
	{
		return is_ready;
	}
	void make_ready()
	{
		is_ready = true;
	}
};

class missile_manager
{
public:
	void operator()() const
	{
		auto m1 = wp::cruise_missile{};
		auto m2 = wp::swarm_missile{};
		auto m3 = wp::cruise_missile_proxy{m1};
		
		this->launch(m1);
		this->launch(m2);
		
		m3.make_ready();
		this->launch(m3);
	}
	void launch(wp::missile & missile) const
	{
		missile.seek();
	}
};

}	// namespace wp

int main()
{
	wp::missile_manager mm;
	mm();
}

/*`
[h2 程序输出：]

[!teletype]
```
巡航导弹正在索敌 ...
蜂群导弹正在索敌 ...
Cruise missile is ready!
巡航导弹正在索敌 ...
```
*/
//]

