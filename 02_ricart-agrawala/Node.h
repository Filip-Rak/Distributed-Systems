#pragma once

#include <list>
#include <queue>
#include <vector>
#include <memory>
#include <sstream>
#include <iostream>

class Node
{
	/* Attributes */
	const int id;
	int local_clock = 0;
	bool request_sent = false;

	std::shared_ptr<std::vector<Node>> nodes_ptr;	// Reference to all nodes. Includes self reference.

	std::queue<int> job_timestamps;			// Times at which the job is scheduled to execute. Sorted min to max
	std::vector<bool> received_responses;	// Nodes that responded with green light to the request.
	std::list<int> defered_requests;		// Requests that for now have been unaswered.

	/* Private Methods */
	void send_request_all();
	void send_go_ahead(int recv_id);

	void handle_request(int sender_id, int sender_timestamp);
	bool verify_go_aheads() const;
	void enter_cs();

public:
	/* Constructor */
	Node(int id, const std::queue<int>& jobs, int node_num);

	/* Public Methods */
	void try_job();

	/* Getters */
	bool has_jobs() const;
	std::string get_data_string() const;

	/* Setters */
	void set_nodes(const std::shared_ptr<std::vector<Node>>& all_nodes);
};