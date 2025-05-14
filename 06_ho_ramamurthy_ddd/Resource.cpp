#include "Resource.h"

Resource::Resource(int id)
	: id(id){}

bool Resource::reserve(int requester_id)
{
	if (taken) return false;

	// Update parent's table.
	taken = true;
	taker_id = requester_id;

	return true;
}

int Resource::get_taker_id()
{
	return taker_id;
}

