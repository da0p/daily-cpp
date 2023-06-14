#include <iostream>
#include <string>
#include <cassert>

int main(int argc, char *argv[])
{

	std::string s = "http://path/to/hello-world";
	auto found = s.find_last_of("/");
	if (found != std::string::npos) {
		std::cout << s.substr(found + 1) << std::endl;
	}

	assert(s.substr(found+1) == "hello-world");

	return 0;
}
