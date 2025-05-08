#include "Utility.h"

std::vector<std::shared_ptr<Node>> load_from_file(const std::string& filename)
{
	return std::vector<std::shared_ptr<Node>>();
}

void print_nodes(const std::vector<std::shared_ptr<Node>>& nodes)
{
	for (auto node_ptr : nodes)
	{
		std::cout << node_ptr->get_debug_string() << "\n";
	}
}
