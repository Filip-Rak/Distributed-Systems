#include "Node.h"

Node::Node(int id, std::vector<int> proc_resources)
	: id(id), proc_required_resources(proc_resources){}

bool Node::update()
{
	if (!proc_required_resources.empty())
	{
		auto res_index = proc_required_resources.back();
		bool reserved = shared_resources[res_index]->reserve(id);

		if (reserved)
		{
			std::cout << "[Request]: Node " << id << " -> Resource: " << res_index << ": SUCCESS\n";
		}
		else
		{
			std::cout << "[Request]: Node " << id << " -> Resource: " << res_index << ": FAILURE\n";
			proc_pending_resources.push_back(res_index);
		}

		// In reality, if this has not been secured already it will never become free
		// Therefore we can just pop it, simplifying things
		proc_required_resources.pop_back();
	}

	return !proc_required_resources.empty();
}

void Node::use_resource(int res_id, int user_id)
{
	used_resources_to_holder[res_id] = user_id;
}

void Node::set_resource_ptr(const std::vector<std::shared_ptr<Resource>>& resources)
{
	shared_resources = resources;
}

std::string Node::get_detailed_string() const
{
	std::ostringstream out;

	out << "ID: " << id << "\n";

	out << "Used resource -> holder: ";
	for (auto [resource, holder] : used_resources_to_holder)
	{
		out << "[" << resource << ", " << holder << "] ";
	}

	out << "\nProc pending resources: ";
	for (int resource : proc_pending_resources)
	{
		out << resource << " ";
	}

	std::cout << "\n";
	return out.str();
}

std::string Node::get_clean_string() const
{
	std::ostringstream out;

	out << "ID: " << id << "\n";
	out << "Needed resources: ";
	for (int resource : proc_required_resources)
	{
		out << resource << " ";
	}

	out << "\n";

	return out.str();
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