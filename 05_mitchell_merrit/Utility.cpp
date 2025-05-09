#include "Utility.h"

std::pair<int, std::queue<std::pair<int, int>>> load_from_file(const std::string& filename)
{
	std::ifstream file(filename);

	if (!file.is_open())
		throw std::runtime_error("Invalid file name");

	// Load the number of nodes
	int nodes_num;
	file >> nodes_num;
	file.ignore();

	if (nodes_num <= 0)
		throw std::runtime_error("Invalid node count");

	// Load blocks
	std::queue<std::pair<int, int>> blocks;

	std::string line;
	while (std::getline(file, line))
	{
		int blocked, blocker;
		file >> blocked >> blocker;

		if (blocked >= nodes_num && blocker >= nodes_num)
			throw std::runtime_error("Invalid node blocks");

		blocks.push({ blocked, blocker });
	}

	file.close();
}

std::vector<std::shared_ptr<Node>> create_nodes(int num_of_nodes)
{
	std::vector<std::shared_ptr<Node>> nodes;
	nodes.reserve(num_of_nodes);

	for (int i = 0; i < num_of_nodes; i++)
	{
		nodes.push_back(std::make_shared<Node>(i));
	}

	return nodes;
}

void print_loaded_data(int num_nodes, std::queue<std::pair<int, int>> block_queue)
{
	std::cout << "Loaded number of nodes: " << num_nodes << "\n";
	std::cout << "ID range: 0 - " << num_nodes - 1 << "\n";

	while (!block_queue.empty())
	{
		auto [blocked, blocker] = block_queue.front();
		std::cout << blocked << " " << blocker << "\n";
		block_queue.pop();
	}
}

void print_node_state(const std::vector<std::shared_ptr<Node>>& nodes)
{
	for (auto node_ptr : nodes)
		std::cout << node_ptr->get_debug_string() << "\n";
}