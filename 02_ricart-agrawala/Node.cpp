#include "Node.h"

Node::Node(int id, const std::queue<int>& jobs, int node_num)
	: id(id), job_timestamps(jobs), received_responses(node_num, false) {}

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

	// Verify if this node can go ahead
	bool allowed_to_go = verify_go_aheads();
	if (allowed_to_go) enter_cs();
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
		if (job_timestamps.front() < sender_timestamp ||
			(job_timestamps.front() == sender_timestamp && id < sender_id))
		{
			// I go first
			defered_requests.push_back(sender_id);
			return;
		}
	}

	send_go_ahead(sender_id);
}

bool Node::verify_go_aheads() const
{
	for (int i = 0; i < received_responses.size(); i++)
	{
		if (i == this->id) continue;
		if (!received_responses[i]) return false;
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
	request_sent = false;

	for (auto it = received_responses.begin(); it != received_responses.end(); it++)
		*it = false;

	// Remove the job
	job_timestamps.pop();

	// Give go ahead to all defered requests
	while (!defered_requests.empty())
	{
		send_go_ahead(defered_requests.front());
		defered_requests.pop_front();
	}
}

void Node::try_job()
{
	// Increase the local clock
	local_clock += 1;

	if (request_sent)
	{
		// The node has already sent the request.
		// Check if there are still nodes which did not approve it
		bool allowed_to_go = verify_go_aheads();
		if (allowed_to_go) enter_cs();
	}
	else
	{
		// The node has not yet send the request.
		// Based on my clock, verify if it's time to do my job
		if (!job_timestamps.empty() && local_clock >= job_timestamps.front())
		{
			request_sent = true;
			send_request_all();
		}
	}
}

bool Node::has_jobs() const
{
	return !job_timestamps.empty();
}

std::string Node::get_data_string() const
{
	std::ostringstream out;

	out << "ID: " << id << "\n";
	out << "Local clock: " << local_clock << "\n";
	// out << "Nodes [id, timestamps.size()]: ";
	out << "Nodes: ";
	for (auto node : *nodes_ptr)
	{
		// out << "[" << node.id << ", " << node.job_timestamps.size() << "] ";
		out << node.id << " ";
	}

	out << "\nJob timestamps: ";
	std::queue<int> job_copy(job_timestamps);

	while (!job_copy.empty())
	{
		out << job_copy.front() << " ";
		job_copy.pop();
	}

	out << "\nResponses: ";
	for (bool val : received_responses)
		out << val << " ";

	out << "\nDeferred: ";
	for (int id : defered_requests)
		out << id << " ";

	out << "\n----------\n";

	return out.str();
}

void Node::set_nodes(const std::shared_ptr<std::vector<Node>>& all_nodes)
{
	this->nodes_ptr = all_nodes;
}
