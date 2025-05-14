#include "Node.h"

Node::Node(int id, std::queue<int> proc_resources)
	: id(id), proc_required_resources(proc_resources){}

bool Node::update()
{
	// Attempt reserving the first resource in the queue
	if (!proc_required_resources.empty())
	{
		auto res_index = proc_required_resources.front();
		bool free = (*shared_resources)[res_index] == -1;

		if (free)
		{
			std::cout << "[Request]: Node " << id << " -> Resource: " << res_index << ": SUCCESS\n";
			(*shared_resources)[res_index] = id;
		}
		else
		{
			std::cout << "[Request]: Node " << id << " -> Resource: " << res_index << ": FAILURE\n";
			proc_pending_resources.push_back(res_index);
		}

		// In reality, if this has not been secured already it will never become free
		// Therefore we can just pop it, simplifying things
		proc_required_resources.pop();
	}

	return !proc_required_resources.empty();
}

void Node::set_resource_ptr(const std::shared_ptr<std::vector<int>>& resources)
{
	shared_resources = resources;
}

std::string Node::get_detailed_string() const
{
	std::ostringstream out;

	out << "ID: " << id << "\n";
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

	std::queue<int> nr_cp(proc_required_resources);
	while (!nr_cp.empty())
	{
		out << nr_cp.front() << " ";
		nr_cp.pop();
	}

	out << "\n";

	return out.str();
}

std::vector<int> Node::get_pending_nodes() const
{
	return proc_pending_resources;
}

int Node::get_id() const
{
	return id;
}