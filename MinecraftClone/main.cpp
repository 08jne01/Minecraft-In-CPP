#include "Header.h"
#include "Program.h"

int main()

{
	std::string s;
	std::cout << "Seed(type anything): ";
	std::cin >> s;

	std::vector<int> nums;
	for (int i = 0; i < 10; i++)

	{
		nums.push_back(1 * i);
	}

	nums.erase(nums.begin() + 4);
	nums.shrink_to_fit();
	for (int i = 0; i < nums.size(); i++)

	{
		std::cout << nums[i] << std::endl;
	}

	Program program(1000, 1000, s);
	//std::cout << sizeof(Chunk) << std::endl;
	return program.mainLoop();
}