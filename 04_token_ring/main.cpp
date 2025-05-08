#include <iostream>
#include <memory>
#include <vector>

#include "Node.h"

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
	std::vector<std::shared_ptr<Node>> nodes;
}