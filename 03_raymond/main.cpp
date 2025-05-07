/*
 *  Assignment: Raymond's Algorithm
 *  Author: Filip Rak
 *
 *  Description:
 *      This program simulates a distributed system of nodes competing
 *      for access to a Critical Section using Raymond's Algorithm.
 *
 *  Input Format:
 *      - A text file name (e.g., "input1.txt").
 *
 *  File Structure:
 *
 *  Line 1:
 *      <number_of_nodes>
 *          - Total number of nodes in the simulation.
 *
 *  Line 2:
 *      <root_node_id>
 *          - ID of the root node (the initial token holder).
 *
 *  Next <number_of_nodes> lines:
 *      <node_id> <parent_id>
 *          - Defines each node and its parent.
 *          - <node_id> is the process ID (can be any integer).
 *          - <parent_id> must reference another declared node.
 *          - Order of these lines is irrelevant.
 *
 *  Remaining lines:
 *      <node_id>
 *          - Indicates that this node will request the critical section.
 *          - Each line adds a new "job" to that node, assigned an internal timestamp.
 *          - Node IDs can appear multiple times (to simulate multiple requests).
 *
 *  Example Input:
 *      4       <- Number of nodes
 *      0       <- ID of the root node
 *      1 0     <- Node 1's parent is Node 0
 *      2 0     <- Node 2's parent is Node 0
 *      3 1     <- Node 3's parent is Node 1
 *      3       <- Node 3 will request the CS (first job)
 *      1       <- Node 1 will request the CS (second job)
 *      3       <- Node 3 will request the CS again (third job)
 *
 *  Output:
 *      - Initial state of all nodes before simulation begins.
 *      - Step-by-step log of:
 *          * Requests for the critical section
 *          * Token transfers
 *          * CS entries
 *      - A message when all jobs are completed and simulation ends.
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

		// Exit if no more jobs
		if (!jobs_left)
		{
			std::cout << "No jobs left. Exitting main loop...\n";
			break;
		}

		// Process each node
		for (auto& node_ptr : nodes)
			node_ptr->process(iteration);

		iteration += 1;
	}
}

int main()
{
	std::cout << "Input file name with extension: ";
	std::string filename;
	std::cin >> filename;

	std::vector<std::shared_ptr<Node>> nodes;

	// Load the data
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
	std::cout << "-- Within the Main Loop --\n";
	main_loop(nodes);

	// Print the final state of the nodes
	/*std::cout << "\n-- Nodes after exit --\n";
	print_node_info(nodes);*/
}