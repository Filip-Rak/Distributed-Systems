#include "Node.h"

Node::Node(int id, int proc_timestamp, std::vector<int> proc_resources)
	: id(id), process_timestamp(proc_timestamp), proc_required_resources(proc_resources){}

bool Node::process(int iteration)
{
	// Ask for resources ONLY once (==)
	if (iteration == process_timestamp)
	{
		attempt_reserving_resources();
	}
}

void Node::attempt_reserving_resources()
{
	for (int res_index : proc_required_resources)
	{
		bool reserved = shared_resources[res_index]->reserve(id);
		if (reserved) proc_held_resources.push_back(res_index);
	}
}
