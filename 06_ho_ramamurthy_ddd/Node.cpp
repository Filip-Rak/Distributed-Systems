#include "Node.h"

Node::Node(int id, int proc_timestamp, std::vector<int> proc_resources)
	: id(id), proc_time_entry(proc_timestamp), proc_required_resources(proc_resources){}

bool Node::process(int iteration)
{
	// Ask for resources ONLY once (==)
	if (iteration >= proc_time_entry)
	{
		try_reserve_resource();

		if (proc_pending_resources.size() < proc_required_resources.size())
		{
			is_blocked = true;
		}

		return true;
	}

	return false;
}

void Node::use_resource(int res_id, int user_id)
{
	used_resources_to_holder[res_id] = user_id;
}

void Node::set_resource_ptr(const std::vector<std::shared_ptr<Resource>>& resources)
{
	shared_resources = resources;
}

std::string Node::get_debug_string() const
{
	std::ostringstream out;

	out << "ID: " << id << "\n";
	out << "Shared resources size: " << shared_resources.size() << "\n";

	out << "Used resource to holder: ";
	for (auto [resource, holder] : used_resources_to_holder)
	{
		out << "[" << resource << ", " << holder << "] ";
	}

	out << "\nProc time entry: " << proc_time_entry << "\n";

	out << "Proc required resources: ";
	for (int resource : proc_required_resources)
	{
		out << resource << " ";
	}

	out << "\nProc held resources: ";
	for (int resource : proc_pending_resources)
	{
		out << resource << " ";
	}

	return out.str();
}

bool Node::get_is_blocked() const
{
	return is_blocked;
}

std::vector<int> Node::get_pending_nodes() const
{
	return proc_pending_resources;
}

int Node::get_blocker_of_res(int res_id) const
{
	return used_resources_to_holder.find(res_id)->second;
}

int Node::get_id() const
{
	return id;
}

void Node::try_reserve_resource()
{
	/*for (int res_index : proc_required_resources)
	{
		bool reserved = shared_resources[res_index]->reserve(id);
		if (!reserved) proc_pending_resources.push_back(res_index);
	}*/

	if (!proc_required_resources.empty())
	{
		auto res_index = proc_required_resources.back();
		proc_required_resources.pop_back();

		bool reserved = shared_resources[res_index]->reserve(id);
		if (!reserved) proc_pending_resources.push_back(res_index);
	}
}
