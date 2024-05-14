//[sycl_group_barrier_cpp

//`[~文件名：[role blue sycl_group_barrier.cpp]]

#include <sycl/sycl.hpp>
#include <numeric>
#include <iomanip>

int main()
{
	sycl::queue queue{sycl::cpu_selector_v};
	
	constexpr int xsize = 8;
	constexpr int ysize = 9;
	constexpr int size = xsize*ysize;
	constexpr int lxsize = 4;
	constexpr int lysize = 3;
	
	float * v0 = sycl::malloc_shared<float>(size, queue);
	float * v1 = sycl::malloc_shared<float>(size, queue);
	float * result = sycl::malloc_device<float>(size, queue);
	std::iota(v0, v0+size, 1.5f);
	std::iota(v1, v1+size, -100.44f);
	
	constexpr int lm_offset = 10;
	
	queue.submit(
		[&] (sycl::handler & handler)
		{
			sycl::local_accessor<float, 2> lm{sycl::range<2>{lysize, lxsize*lm_offset}, handler};
			handler.parallel_for<class kname1>(
				sycl::nd_range<2>{
					sycl::range<2>{ysize, xsize},
					sycl::range<2>{lysize, lxsize}
				},
				[=] (sycl::nd_item<2> item)
				{
					sycl::id<1> gidy = item.get_global_id(0);
					sycl::id<1> gidx = item.get_global_id(1);
					sycl::id<1> lidy = item.get_local_id(0);
					sycl::id<1> lidx = item.get_local_id(1);
					
					float & lm0 = lm[lidy][lidx*lm_offset+0];
					float & lm1 = lm[lidy][lidx*lm_offset+1];
					float & lm2 = lm[lidy][lidx*lm_offset+2];
					
					lm0 = v0[gidy*xsize+gidx];
					lm1 = v1[gidy*xsize+gidx];
					lm2 = 0.0f;
					
					sycl::group_barrier(item.get_group(), sycl::memory_scope::work_group);
					
					lm2 = lm0 + lm1;
					sycl::group_barrier(item.get_group(), sycl::memory_scope::work_group);
					
					result[gidy*xsize + gidx] = lm2;
				}
			);
		}
	);
	queue.wait();
	
	float * host_result = new float[size];
	queue.copy(result, host_result, size);
	
	auto print = [&] (const std::string & label, float * data)
	{
		std::cout << label << std::endl;
		for (int j=0; j<ysize; ++j)
		{
			for (int i=0; i<xsize; ++i)
			{
				std::cout << std::setprecision(3) << data[j*xsize+i] << ' ';
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	};
	
	print("v0:", v0);
	print("v1:", v1);
	print("host_result:", host_result);
	
	sycl::free(v0, queue);
	sycl::free(v1, queue);
	sycl::free(result, queue);
	delete [] host_result;
}

/*`
[h2 输出：]

```
v0:
1.5 2.5 3.5 4.5 5.5 6.5 7.5 8.5 
9.5 10.5 11.5 12.5 13.5 14.5 15.5 16.5 
17.5 18.5 19.5 20.5 21.5 22.5 23.5 24.5 
25.5 26.5 27.5 28.5 29.5 30.5 31.5 32.5 
33.5 34.5 35.5 36.5 37.5 38.5 39.5 40.5 
41.5 42.5 43.5 44.5 45.5 46.5 47.5 48.5 
49.5 50.5 51.5 52.5 53.5 54.5 55.5 56.5 
57.5 58.5 59.5 60.5 61.5 62.5 63.5 64.5 
65.5 66.5 67.5 68.5 69.5 70.5 71.5 72.5 

v1:
-100 -99.4 -98.4 -97.4 -96.4 -95.4 -94.4 -93.4 
-92.4 -91.4 -90.4 -89.4 -88.4 -87.4 -86.4 -85.4 
-84.4 -83.4 -82.4 -81.4 -80.4 -79.4 -78.4 -77.4 
-76.4 -75.4 -74.4 -73.4 -72.4 -71.4 -70.4 -69.4 
-68.4 -67.4 -66.4 -65.4 -64.4 -63.4 -62.4 -61.4 
-60.4 -59.4 -58.4 -57.4 -56.4 -55.4 -54.4 -53.4 
-52.4 -51.4 -50.4 -49.4 -48.4 -47.4 -46.4 -45.4 
-44.4 -43.4 -42.4 -41.4 -40.4 -39.4 -38.4 -37.4 
-36.4 -35.4 -34.4 -33.4 -32.4 -31.4 -30.4 -29.4 

host_result:
-98.9 -96.9 -94.9 -92.9 -90.9 -88.9 -86.9 -84.9 
-82.9 -80.9 -78.9 -76.9 -74.9 -72.9 -70.9 -68.9 
-66.9 -64.9 -62.9 -60.9 -58.9 -56.9 -54.9 -52.9 
-50.9 -48.9 -46.9 -44.9 -42.9 -40.9 -38.9 -36.9 
-34.9 -32.9 -30.9 -28.9 -26.9 -24.9 -22.9 -20.9 
-18.9 -16.9 -14.9 -12.9 -10.9 -8.94 -6.94 -4.94 
-2.94 -0.94 1.06 3.06 5.06 7.06 9.06 11.1 
13.1 15.1 17.1 19.1 21.1 23.1 25.1 27.1 
29.1 31.1 33.1 35.1 37.1 39.1 41.1 43.1 
```
*/

//]

