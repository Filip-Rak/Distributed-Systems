#include "Node.h"

Node::Node(int id, const std::queue<int>& jobs, int node_num)
	: id(id), job_timestamps(jobs), received_responses(node_num, false) {}

Node::Node()
	: id(-1) {}

void Node::send_request_all()
{
	// Increase the clock by 1
	local_clock += 1;


	// Ask all the nodes for permission
	auto& nodes_vec = *nodes_ptr;
	for (int i = 0; i < nodes_vec.size(); i++)
	{
		if (i == this->id) continue;
		nodes_vec[i].handle_request(this->id, job_timestamps.front());
	}

	// Verify if can go ahead
	bool allowed_to_go = verify_go_aheads();
	if (allowed_to_go)
		enter_cs();
}

void Node::send_go_ahead(int recv_id)
{
	// Update my local clock
	local_clock += 1;

	// Give the node go ahead
	auto& node_vec = *nodes_ptr;
	node_vec[recv_id].received_responses[id] = true;
	
	// Update receiver node's clock
	int recv_clock = node_vec[recv_id].local_clock;
	node_vec[recv_id].local_clock = std::max(recv_clock, local_clock);
}

void Node::handle_request(int sender_id, int sender_timestamp)
{
	// Update my local clock
	local_clock = std::max(local_clock, sender_timestamp) + 1;

	// Check if I want to do my job
	if (!job_timestamps.empty() && local_clock >= job_timestamps.front())
	{
		if (job_timestamps.front() > sender_timestamp ||
			(job_timestamps.front() == sender_timestamp && id < sender_id))
		{
			// This node goes first
			defered_requests.push_back(sender_id);
			return;
		}
	}

	send_go_ahead(sender_id);
}

bool Node::verify_go_aheads()
{
	for (int i = 0; i < received_responses.size(); i++)
	{
		if (i == id) continue;

		if (!received_responses[i])
		{
			return false;
		}
	}

	return true;
}

void Node::enter_cs()
{
	// Increase local clock
	local_clock += 1;

	// Do the job
	std::cout << "CS: "
		<< "\n\tProcess_id: " << id
		<< "\n\tLocal clock: " << local_clock
		<< "\n\tJob's timestamp: " << job_timestamps.front() << "\n";

	// Zero all control variables
	for (auto it = received_responses.begin(); it != received_responses.end(); it++)
	{
		*it = false;
	}
	waiting_for_answers = false;

	// Remove the job
	job_timestamps.pop();

	// Give go ahead to all defered requests
	for (int node_id : defered_requests)
	{
		send_go_ahead(node_id);
	}
}

void Node::try_job()
{
	// Increase the local clock
	local_clock += 1;

	// The node has already send the request.
	// Check if there are still nodes which did not approve it
	if (waiting_for_answers)
	{
		bool allowed_to_go = verify_go_aheads();
		if (allowed_to_go)
			enter_cs();
	}
	else
	{
		// The node has not yet send the request.
		// Based on my clock verify if it's time to do my job
		if (!job_timestamps.empty() && local_clock >= job_timestamps.front())
		{
			waiting_for_answers = true;
			send_request_all();
		}
	}
}

bool Node::has_jobs()
{
	return !job_timestamps.empty();
}

void Node::set_nodes(const std::shared_ptr<std::vector<Node>>& all_nodes)
{
	this->nodes_ptr = all_nodes;
}

void Node::print_data() const
{
	std::cout << "ID: " << id << "\n";
	std::cout << "Local clock: " << local_clock << "\n";
	// std::cout << "Nodes [id, timestamps.size()]: ";
	std::cout << "Nodes: ";
	for (auto node : *nodes_ptr)
	{
		// std::cout << "[" << node.id << ", " << node.job_timestamps.size() << "] ";
		std::cout << node.id << " ";
	}

	std::cout << "\nJob timestamps: ";
	std::queue<int> job_copy(job_timestamps);

	while (!job_copy.empty())
	{
		std::cout << job_copy.front() << " ";
		job_copy.pop();
	}

	std::cout << "\nResponses: ";
	for (bool val : received_responses)
		std::cout << val << " ";

	std::cout << "\nDeferred: ";
	for (int id : defered_requests)
	{
		std::cout << id << " ";
	}

	std::cout << "\n----------\n\n";
}
