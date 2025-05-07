/*
 *	Assignment: Raymond's Algorithm
 *	Author: Filip Rak
 *
 *	Description:
 *		The program simulates nodes competing for acces to the Critical Section
 *		using the Raymond's Algorithm.
 *
 *	Input format
 *		- Name of the file followed by it's extension.
 *
 *	Example: input1.txt
 *
 *	Example file format:
 *	Line 1:
 *		<number_of_nodes>
 *			the number of nodes to be simulated.
 *	Line 2:
 *		<root_node_id>
 *			the number by which the root node (initial token holder) will be idetified.
 *
 *	Subsequent <number_of_nodes> lines:
 *		<node_id> <parent_id>
 *		- Each line defines a process and it's parent.
 *		- The first number is the process ID - whichever number you assign.
 *		- The following number is the ID of the parent.
 *		- The order of lines within this section is irrelevant. 
 *		- A parent has to be declared at some point within this section.
 * 
 *	Subsequent lines:
 *		<node_id>
 *		- The id of the node to request the critical section.
 *		- Each node will internally be assigned a timestamp at which it will request the critical section. 
 *		- The order of these requests is based on the input order.
 *		- A <node_id> has to be declared in the prior section.
 *		- Distinct <node_id> can appear multiple times within this section.
 *		- Multiple appearences will be considered separate jobs assigned different timestamps. 
 *
 *	Example:
 *		4		<- The number of nodes to be simulated.
 *		0		<- The ID of the root node.
 *		1 0		<- Node ID followed by the parent's ID.
 *		2 0		<- Node ID followed by the parent's ID.
 *		3 1		<- Node ID followed by the parent's ID.
 *		3		<- Node of ID 3 will request CS during the first time interval.
 *		1		<- Node of ID 1 will request CS during the second time interval.
 *		3		<- Node of ID 3 will request CS once again in the third time interval.
 *
 *	Output:
 *		- Initial state of loaded nodes prior to simulation.
 *		- Requests, token transfers and critical section entries.
 */

#include <iostream>
#include <memory>
#include <vector>

#include "Node.h"
#include "Utils.h"

void main_loop(std::vector<std::shared_ptr<Node>>& nodes)
{
	int iteration = 0;
	while (true)
	{
		/*if (iteration > 20)
		{
			std::cout << "Failed to finish within time limit. Terminating main loop...\n";
			break;
		}*/

		// Check if there are jobs left
		bool jobs_left = false;
		for (const auto& node_ptr : nodes)
		{
			if (node_ptr->has_jobs())
			{
				jobs_left = true;
				break;
			}
		}

		// Exit if no job
		if (!jobs_left)
		{
			std::cout << "No jobs left. Exitting main loop...\n";
			break;
		}

		// Process each node
		for (auto& node_ptr : nodes)
			node_ptr->process(iteration);

		// std::cout << "-------------\n";
		// print_node_info(nodes);

		iteration += 1;
	}
}

int main()
{
	std::vector<std::shared_ptr<Node>> nodes;
	std::string filename = "input.txt";

	try
	{
		nodes = load_nodes_from_file(filename);
	}
	catch (std::exception ex)
	{
		std::cout << "Exception: " << ex.what() << "\n";
		return 0;
	}

	// Print initial state of the nodes
	std::cout << "-- Nodes on initialization --\n";
	print_node_info(nodes);

	// Start the main loop
	main_loop(nodes);

	// Print the final state of the nodes
	std::cout << "-- Nodes after exit --\n";
	print_node_info(nodes);
}