#pragma once

#include <queue>
#include <memory>
#include <iostream>
#include <sstream>
#include <iomanip>

class Node
{
	/* Types */
	struct Token
	{
		std::queue<int> requester_ids;
	};

	/* Attributes */
	const int id;

	std::unique_ptr<Token> token = nullptr;		// Pointer to the token. nullptr when not the holder.
	std::shared_ptr<Node> neighbor = nullptr;	// Pointer to next Node in the ring.		
	std::queue<int> job_timestamps;				// Times at which a Node is scheduled to request token.
	std::queue<int> local_requesters;			// Storing requests before they can be passed further.
	bool task_in_druation = false;				// When a node started a task & it still hasn't finished.

	/* Private Methods */
	void transfer_token();
	void pass_requests_to_neighbor();
	void pass_requests_to_token();
	void enter_cs();

	void process_has_token(int iteration);
	bool should_self_request(int iteration) const;

public:
	/* Constructor */
	Node(int id, const std::queue<int>& jobs, bool init_token = false);

	/* Public Methods */
	void process(int iteration);

	/* Getters */
	bool has_jobs() const;
	std::string get_debug_string() const;
	std::string get_clean_string() const;

	/* Setters */
	void set_neighbor(std::shared_ptr<Node> neighbor);
};