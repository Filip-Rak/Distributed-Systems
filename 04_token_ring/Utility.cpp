#include "Utility.h"

std::vector<std::shared_ptr<Node>> load_from_file(const std::string& filename)
{
	/* Load From File */
	std::ifstream file(filename);

	if (!file.is_open())
		throw std::exception("Invalid file name");

	int nodes_num;
	file >> nodes_num;
	file.ignore();

	if (nodes_num <= 0)
		throw std::exception("Invalid number of nodes");

	std::unordered_map<int, std::queue<int>> node_to_jobs;

	std::string line;
	int time = 0;
	while (std::getline(file, line))
	{
		int node_id = stoi(line);
		node_to_jobs[node_id].push(time);
		
		time += 1;
	}

	file.close();

	/* Create Nodes */
	std::vector<std::shared_ptr<Node>> nodes;
	nodes.reserve(nodes_num);

	// Create the root node
	nodes.push_back(std::make_shared<Node>(0, node_to_jobs[0], true));
	
	// Create the rest of the nodes
	for (int i = 1; i < nodes_num; i++)
	{
		nodes.push_back(std::make_shared<Node>(i, node_to_jobs[i]));
		nodes[i]->set_neighbor(nodes[i - 1]);
	}

	nodes.front()->set_neighbor(nodes.back());
	return nodes;
}

void print_nodes(const std::vector<std::shared_ptr<Node>>& nodes)
{
	for (auto node_ptr : nodes)
	{
		std::cout << node_ptr->get_debug_string() << "\n";
	}
}
