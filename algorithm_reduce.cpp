#include <iostream>
#include <numeric>
#include <vector>
#include <execution>

double
averageScore(const std::vector<int>& scores)
{
	return std::reduce(
			std::execution::par,
			scores.cbegin(),
			scores.cend(),
			0) / (double) scores.size();
}

int main(int argc, char *argv[])
{

	std::vector<int> scores = {1, 2, 3, 5, 6, 7, 8, 9, 10};
	std::cout << "Average score = " << averageScore(scores) << "\n";

	return 0;
}
