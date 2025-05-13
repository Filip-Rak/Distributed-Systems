#include "Node.h"

Node::Node(int id, int proc_timestamp, std::vector<int> proc_resources)
	: id(id), proc_time_entry(proc_timestamp), proc_required_resources(proc_resources){}

bool Node::process(int iteration)
{
	// Ask for resources ONLY once (==)
	if (iteration == proc_time_entry)
	{
		try_reserve_resource();
	}
}

void Node::use_resource(int res_id, int user_id)
{
	used_resources_to_holder[res_id] = user_id;
}

void Node::try_reserve_resource()
{
	for (int res_index : proc_required_resources)
	{
		bool reserved = shared_resources[res_index]->reserve(id);
		if (reserved) proc_held_resources.push_back(res_index);
	}
}
