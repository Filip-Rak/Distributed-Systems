#include <iostream>
#include <memory>
#include <vector>

#include "Node.h"

void main_loop(std::vector<std::shared_ptr<Node>>& nodes)
{
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
	}
}

int main()
{
	std::vector<std::shared_ptr<Node>> nodes;
}