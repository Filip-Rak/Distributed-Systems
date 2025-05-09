#include "Node.h"

Node::Node(int id)
	: id(id), public_label(id), private_label(id){}

void Node::block_with(const std::shared_ptr<Node>& blocker_node)
{
	blocked_by = blocker_node;

	int new_label = std::max(public_label, blocker_node->public_label) + 1;
	public_label = private_label = new_label;
}

bool Node::update()
{
	if (!blocked_by) 
		return false;

	if (blocked_by->public_label > public_label)
	{
		public_label = blocked_by->public_label;
		return true;
	}

	return false;
}

bool Node::detected_deadlock() const
{
	if (!blocked_by)
		return false;

	return (public_label == private_label && public_label == blocked_by->public_label);
}

int Node::get_id() const
{
	return id;
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
