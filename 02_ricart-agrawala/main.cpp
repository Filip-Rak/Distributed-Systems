#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <queue>
#include <functional>
#include <memory>

#include "Node.h"

/**
 * @brief Loads the file contents and fully initializes nodes with them
 *
 * @param filename: Name of the file with extension.
 * @return an std::vector<Node> of fully initialized nodes.
 * @throws std::runtime_error if it fails to open the file.
 */
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
		int node_id, job_timestamp;
		ss >> node_id >> job_timestamp;

		node_job_map[node_id].push(job_timestamp);
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
	{
		node.set_nodes(nodes_ptr);
	}

	return nodes_ptr;
}

void main_loop(std::shared_ptr<std::vector<Node>> nodes)
{
	while (true)
	{
		// Run the loop as long as there are jobs left
		bool jobs_left = false;
		for (Node node : *nodes)
		{
			// break;
			if (node.has_jobs())
			{
				jobs_left = true;
				break;
			}
		}

		if (!jobs_left) 
			return;

		// Try job
		for (Node& node : *nodes)
		{
			node.try_job();
			// node.print_data();
		}

		// std::cout << "\n###############\n";
	}
}

void print_nodes_state(const std::shared_ptr<std::vector<Node>>& nodes)
{
	for (Node node : *nodes)
	{
		node.print_data();
	}
}

int main()
{
	/* Load the file data */
	std::string input_file = "input.txt";
	std::shared_ptr<std::vector<Node>> nodes;

	try
	{
		nodes = load_nodes(input_file);
	}
	catch (std::exception ex)
	{
		std::cout << "Exception: " << ex.what() << "\n";
		return 0;
	}

	/* Initial State Print */
	std::cout << "---- Intiial State of All Nodes ---\n";
	print_nodes_state(nodes);

	/* Start the sim*/
	main_loop(nodes);

	/* Summary */
	std::cout << "\n---- Final State of All Nodes ---\n";
	print_nodes_state(nodes);
}