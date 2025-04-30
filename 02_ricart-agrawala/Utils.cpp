#include "Utils.h"

std::shared_ptr<std::vector<Node>> load_nodes(const std::string& filename)
{
	std::ifstream file(filename);

	if (!file.good())
		throw std::runtime_error("Failed to open: " + filename);

	// Load first row number
	int num_nodes;
	file >> num_nodes;
	file.ignore();

	// Load following rows
	std::unordered_map<int, std::priority_queue<int, std::vector<int>, std::greater<int>>> node_job_map;

	std::string line;
	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		int node_id;
		ss >> node_id;

		int job_buffer;
		while (ss >> job_buffer)
		{
			node_job_map[node_id].push(job_buffer);
		}
	}

	file.close();

	// Fill the nodes with input
	auto nodes_ptr = std::make_shared<std::vector<Node>>();
	nodes_ptr->reserve(num_nodes);
	for (int i = 0; i < num_nodes; i++)
	{
		auto pq = node_job_map[i];
		std::queue<int> job_queue;

		while (!pq.empty())
		{
			job_queue.push(pq.top());
			pq.pop();
		}

		nodes_ptr->emplace_back(i, job_queue, num_nodes);
	}

	for (auto& node : *nodes_ptr)
		node.set_nodes(nodes_ptr);

	return nodes_ptr;
}

void print_nodes_state(const std::shared_ptr<std::vector<Node>>& nodes)
{
	for (Node node : *nodes)
		node.print_data();
}
