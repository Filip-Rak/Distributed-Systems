/*
 *	Assignment: Ho-Ramamurthy Centralized Deadlock Detection Algorithm
 *	Author: Filip Rak
 *
 *  Description:
 *		This program simulates a distributed system of nodes requesting access to shared resources.
 *      It implements the centralized deadlock detection algorithm, where a controller monitors the system
 *      to detect circular wait conditions using a Wait-For Graph (WFG).
 *
 *		Each node attempts to acquire a list of required resources, one at a time. If a requested resource
 *		is already held by another node, the requesting node becomes blocked. The controller periodically
 *		collects the current system state, constructs a WFG, and checks for cycles. A detected cycle
 *		indicates a deadlock.
 *
 *	Input:
 *		- Single file name with extension.
 *
 *  Input Format (from file):
 *		Line 1:
 *			<number_of_nodes> <number_of_resources>
 *				- Total number of nodes and resources in the system.
 *
 *		Next lines:
 *          <node_id> <resource_id_1> <resource_id_2> ...
 *              - Describes which resources are needed by the job assigned to that node.
 *				- Each node has exactly one job.
 *
 *  Example Input:
 *      4 5			<- Nodes: 4, Resources 5
 *      0 0 1		<- Node 0 needs resources 0 and 1
 *      1 1 2       <- Node 1 needs resources 1 and 2
 *      2 2 3       <- Node 2 needs resources 2 and 3
 *					<- Node 3 will not seek any resources
 *
 *  Output:
 *      - Initial state of all nodes
 *      - Resource acquisition attempts per time step
 *      - Wait-For Graph (WFG) construction log
 *      - Deadlock detection results
 *      - If no deadlock is detected, the simulation exits on stabilization
 */


#include <iostream>
#include <string>
#include <memory>
#include <stdexcept>

#include "Node.h"
#include "Utility.h"
#include "Controller.h"

void main_loop(const std::vector<std::shared_ptr<Node>>& nodes, Controller& controller)
{
	while (true)
	{
		// Update nodes. Record if a change has happened
		bool state_change = false;
		for (auto node_ptr : nodes)
		{
			if (node_ptr->update())
				state_change = true;
		}

		// Deadlock happened -> Stop
		if (controller.check_deadlock(nodes))
		{
			std::cout << "Deadlock detected. Exitting main loop...\n";
			break;
		}

		// None of the nodes did anything -> Stop
		if (!state_change)
		{
			std::cout << "Stabilized. Exitting main loop...\n";
			break;
		}
	}
}

int main()
{
	std::string filename = "input1.txt";

	std::cout << "File name with extension: ";
	std::cin >> filename;

	std::pair<std::vector<std::shared_ptr<Node>>, std::shared_ptr<std::vector<int>>> loaded_data;
	try
	{
		loaded_data = load_from_file(filename);
	}
	catch (std::exception ex)
	{
		std::cout << "Exception: " << ex.what() << "\n";
		return 1;
	}

	// Map loaded data to components
	auto [nodes, resources] = loaded_data;

	// Initialize Controller
	Controller controller(resources);

	// Print inputted data
	std::cout << "--- Initial Node State ---\n";
	print_nodes(nodes, &Node::get_in_string);

	// Enter main loop
	std::cout << "--- Within Main Loop ---\n";
	main_loop(nodes, controller);

	// Print final state
	std::cout << "\n--- Final Node State ---";
	print_nodes(nodes, &Node::get_out_string);
}