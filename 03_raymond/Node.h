#pragma once

#include <queue>
#include <memory>
#include <iostream>
#include <sstream>

class Node
{
	/* Attributes */
	const int id;
	std::shared_ptr<Node> self_reference;

	bool has_token;
	bool passed_request_up = false;
	bool self_requested = false;

	std::shared_ptr<Node> parent;
	std::queue<std::shared_ptr<Node>> token_requests;
	std::queue<int> jobs;

	/* Private Methods */
	void handle_token();
	void handle_no_token();

	void transfer_token(std::shared_ptr<Node>& receiver);
	void request_token_from_parent();
	void enter_cs();

public:
	/* Constructor */
	Node(int id, std::queue<int> jobs, bool has_token = false);

	/* Public Methods */
	void process(int iteration);

	/* Setters */
	void set_parent(std::shared_ptr<Node>& parent);
	void set_self_reference(std::shared_ptr<Node>& self);

	/* Getters */
	bool has_jobs() const;
	std::string get_debug_string() const;
};