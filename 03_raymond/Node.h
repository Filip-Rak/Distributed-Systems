#pragma once

#include <queue>
#include <memory>
#include <iostream>

class Node
{
	/* Attributes */
	const int id;

	bool has_token;
	bool request_in_progress = false;

	std::shared_ptr<Node> parent;
	std::queue<std::shared_ptr<Node>> token_requests;
	std::queue<int> jobs;

	/* Private Methods */
	void transfer_token(std::shared_ptr<Node>& receiver);
	void request_token_from_parent();

	void enter_cs();

public:
	/* Constructor */
	Node(int id, std::queue<int> jobs, std::shared_ptr<Node> parent = nullptr, bool has_token = false);

	/* Public Methods */
	void process(int iteration);

	/* Getters */
	bool has_jobs() const;
};