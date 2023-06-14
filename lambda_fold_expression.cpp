#include <iostream>

int main(int argc, char *argv[])
{
	const auto sumLambda = [](auto... args) {
		std::cout << "sum of: " << sizeof...(args) << " numbers\n";
		return (args + ... + 0);
	};

	std::cout << sumLambda(1.1, 2.2, 3.3, 4.4);

	const auto printer = [](auto... args) {
		const auto printElem = [](auto elem) {
			std::cout << elem << ", ";
		};
		(printElem(args), ...);
		std::cout << "\n";
	};

	printer(1, 2, 3, "hello", 10.5f);

	const auto printer_2 = [](auto first, auto... args) {
		std::cout << first;
		((std::cout << ", " << args), ...);
		std::cout << "\n";
	};

	printer_2(1, 2, 3, "world", 11.4f);

	return 0;
}
