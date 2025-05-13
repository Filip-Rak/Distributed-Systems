#include "Resource.h"

Resource::Resource(const std::shared_ptr<Node>& parent)
	: parent(parent){}

bool Resource::reserve(int requester_id)
{
	if (taken) return false;

	taken = true;

	// Update parent's table.

	return true;
}
