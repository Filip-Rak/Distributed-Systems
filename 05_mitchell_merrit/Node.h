#pragma once

#include <memory>
#include <sstream>
#include <iostream>

class Node
{
	/* Attributes */
	const int id;
	int public_label;
	int private_label;

	std::shared_ptr<Node> blocked_by = nullptr;

public:
	/* Csontructor */
	Node(int id);

	/* Public Methods */
	void block_with(const std::shared_ptr<Node>& blocker_node);
	bool update();

	/* Getter */
	bool detected_deadlock() const;
	std::string get_debug_string() const;
};