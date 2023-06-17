#include <iostream>
#include <vector>
#include <numeric>

int main(int argc, char *argv[])
{
	std::vector<int> scores = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	std::cout << std::accumulate(
			scores.cbegin(), 
			scores.cend(), 
			1, 
			std::multiplies<int>()
	) << std::endl;

	return 0;
}
