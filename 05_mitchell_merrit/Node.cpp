#include "Node.h"

Node::Node(int id)
	: id(id), public_label(id), private_label(id){}

void Node::block_with(const std::shared_ptr<Node>& blocker_node)
{
	// Update label & block
	int new_label = std::max(public_label, blocker_node->public_label) + 1;
	public_label = private_label = new_label;
	blocked_by = blocker_node;

	// Report event
	std::cout << "[Blocked] Node " << id << " by Node" << blocker_node->id
		<< " -> new label: " << public_label << "\n";
}

bool Node::update()
{
	if (!blocked_by) 
		return false;

	if (blocked_by->public_label > public_label)
	{
		// Adopt label
		public_label = blocked_by->public_label;

		// Report event
		std::cout << "[Transmit] Node " << id
			<< " adopted label " << public_label
			<< " from Node " << blocked_by->id << "\n";

		return true;
	}

	return false;
}

bool Node::detected_deadlock() const
{
	if (!blocked_by)
		return false;

	if (public_label == private_label && public_label == blocked_by->public_label)
	{
		// Report event
		std::cout << "[Deadlock] Node " << id << " reports deadlock\n";
		return true;
	}

	return false;
}

std::string Node::get_debug_string() const
{
	std::ostringstream out;

	out << "ID: " << id << "\n";
	out << "Public label: " << public_label << "\n";
	out << "Private label: " << private_label << "\n";

	if (blocked_by)
		out << "Blocked by (id): " << blocked_by->id << "\n";
	else 
		out << "Blocked by (id): nullptr\n";

	return out.str();
}
