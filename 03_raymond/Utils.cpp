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

	file.close();

	/* Create Nodes */
	// Create all nodes and store them by ID
	std::unordered_map<int, std::shared_ptr<Node>> id_to_node;

	// Root node
	id_to_node[root_node_id] = std::make_shared<Node>(root_node_id, std::move(node_to_jobs[root_node_id]), true);
	id_to_node[root_node_id]->set_self_reference(id_to_node[root_node_id]);


	// Other nodes
	for (const auto& [node_id, _] : node_to_parent)
	{
		auto& jobs = node_to_jobs[node_id];
		id_to_node[node_id] = std::make_shared<Node>(node_id, std::move(jobs));
		id_to_node[node_id]->set_self_reference(id_to_node[node_id]);
	}

	// Assign parents
	for (const auto& [node_id, parent_id] : node_to_parent)
		id_to_node[node_id]->set_parent(id_to_node[parent_id]);

	// Convert to vector
	std::vector<std::shared_ptr<Node>> nodes;
	for (auto& [_, node] : id_to_node)
		nodes.push_back(node);

	return nodes;
}

void print_node_info(const std::vector<std::shared_ptr<Node>>& nodes)
{
	for (auto node_ptr : nodes)
		std::cout << node_ptr->get_debug_string() << "\n";
}