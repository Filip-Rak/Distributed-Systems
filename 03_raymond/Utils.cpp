#include "Utils.h"

std::vector<std::shared_ptr<Node>> load_nodes_from_file(const std::string& filename)
{
	std::ifstream file(filename);

	if (!file.is_open()) 
		throw "Invalid file name";

	// Load the number of nodes
	int nodes_num;
	file >> nodes_num;

	if (nodes_num <= 0)
		throw "Invalid file format";

	// Load root node
	int root_node_id;
	file >> root_node_id;

	// Load tree structure - map nodes to their parents
	std::unordered_map<int, int> node_to_parent;
	for (int i = 1; i < nodes_num; i++)
	{
		int node_id, parent;
		file >> node_id >> parent;
		node_to_parent[node_id] = parent;
	}

	// Load jobs
	std::unordered_map<int, std::queue<int>> node_to_jobs;

	int node_id, timestamp = 0;
	while (file >> node_id)
		node_to_jobs[node_id].push(timestamp++);

	/* Create Nodes */
	std::vector<std::shared_ptr<Node>> nodes;

	// Root node
	nodes.emplace_back(std::make_shared<Node>(root_node_id, node_to_jobs[root_node_id]));

	// Other nodes
	for (auto [node_id, parent] : node_to_parent)
	{
		auto& jobs = node_to_jobs[node_id];
		nodes.emplace_back(std::make_shared<Node>(node_id, jobs, parent));
	}

	file.close();

	return nodes;
}
