#include <iostream>
#include <string>
#include <memory>
#include <stdexcept>

#include "Node.h"
#include "Utility.h"
#include "Controller.h"

void main_loop(const std::vector<std::shared_ptr<Node>>& nodes, Controller& controller)
{
	int iteration = 0;
	while (true)
	{
		bool state_change = false;
		for (auto node_ptr : nodes)
		{
			if (node_ptr->process(iteration))
				state_change = true;
		}

		if (!state_change)
		{
			std::cout << "Stabilised. Exitting main loop...\n";
			break;
		}

		controller.update(nodes);

		if (controller.detect_cycles())
		{
			std::cout << "Deadlock detected. Exitting main loop...\n";
			break;
		}

		iteration++;
	}
}

int main()
{
	std::string filename = "input1.txt";

	std::pair<std::vector<std::shared_ptr<Node>>, std::vector<std::shared_ptr<Resource>>> loaded_data;
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
	print_nodes(nodes);

	// Enter main loop
	std::cout << "--- Within Main Loop ---\n";
	main_loop(nodes, controller);

	// Print final state
	std::cout << "--- Final Node State ---\n";
	print_nodes(nodes);
}