/*
 *	Assignment: Token-Based Algorithm on Ring Topology
 *	Author: Filip Rak
 *
 *  Description:
 *		This program simulates a distributed system of nodes arranged in a ring topology.
 *      Nodes compete for access to a Critical Section (CS) using a token-passing algorithm.
 *      A single token circulates through the ring, granting exclusive CS access to requesting nodes.
 *
 *	Input:
 *		- Single file name with extension.
 * 
 *  Input Format (from file):
 *		Line 1:
 *			<number_of_nodes>
 *				- Total number of nodes in the simulation.
 *
 *      Subsequent lines:
 *          <node_id>
 *              - ID of a node that should request access to the CS at a specific time step.
 *              - The first ID corresponds to time step 0, the second to time step 1, and so on.
 *              - IDs can appear multiple times to simulate repeated requests from the same node.
 *
 *  Example Input:
 *      5       <- Total number of nodes
 *      1       <- At time 0, Node 1 requests the CS
 *      2       <- At time 1, Node 2 requests the CS
 *      1       <- At time 2, Node 1 requests the CS again
 *
 *  Output:
 *      - Initial state of all nodes
 *      - Event log including:
 *          * Critical Section entries
 *          * Token transfers
 *          * Request propagations
 */

#include <iostream>
#include <memory>
#include <vector>

#include "Node.h"
#include "Utility.h"

void main_loop(std::vector<std::shared_ptr<Node>>& nodes)
{
	int iteration = 0;
	while (true)
	{
		bool jobs_left = false;
		for (auto node_ptr : nodes)
		{
			if (node_ptr->has_jobs())
			{
				jobs_left = true;
				break;
			}
		}

		if (!jobs_left)
		{
			std::cout << "No jobs left. Exiting main loop...\n";
			break;
		}

		for (auto node_ptr : nodes)
			node_ptr->process(iteration);

		iteration += 1;
	}
}

int main()
{	
	std::string filename = "input1.txt";
	std::cout << "File name with extension: ";
	std::cin >> filename;

	std::vector<std::shared_ptr<Node>> nodes;

	try
	{
		nodes = load_from_file(filename);
	}
	catch (std::exception ex)
	{
		std::cerr << "Exception: " << ex.what() << "\n";
		return 1;
	}

	// Print the state of the nodes
	std::cout << "--- Initial Node State ---\n\n";
	print_nodes(nodes);

	std::cout << "Ring order: ";
	for (int i = 0; i < nodes.size(); i++)
		std::cout << "<- " << i << " ";

	std::cout << "<-\n\n";

	// Run main loop
	std::cout << "--- Within Main Loop ---\n";
	main_loop(nodes);

	// Print the final state
	// std::cout << "\n--- Final Node State ---\n";
	// print_nodes(nodes);
}