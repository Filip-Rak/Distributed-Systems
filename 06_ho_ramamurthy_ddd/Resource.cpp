#include "Resource.h"

Resource::Resource(int id, const std::shared_ptr<Node>& parent)
	: id(id), parent(parent){}

bool Resource::reserve(int requester_id)
{
	if (taken) return false;

	// Update parent's table.
	parent->use_resource(id, requester_id);
	taken = true;

	return true;
}

std::shared_ptr<Node> Resource::get_parent()
{
	return parent;
}
