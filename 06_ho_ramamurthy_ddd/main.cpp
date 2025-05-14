#include <iostream>
#include <string>
#include <memory>
#include <stdexcept>

#include "Node.h"
#include "Utility.h"

int main()
{
	std::string filename = "input1.txt";

	std::vector<std::shared_ptr<Node>> nodes;
	try
	{
		nodes = load_from_file(filename);
	}
	catch (std::exception ex)
	{
		std::cout << "Exception: " << ex.what() << "\n";
		return 1;
	}

	print_nodes(nodes);
}