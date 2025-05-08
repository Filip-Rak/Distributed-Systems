#include "Node.h"

void Node::transfer_token()
{
	// Print the state
	std::cout << "[Transfer] " << id << " -> " << neighbor->id << "\n";

	// Transfer the token
	neighbor->token = std::move(token);
}

void Node::pass_requests_to_neighbor()
{
	if (local_requesters.empty()) 
		return;

	// Print the event
	std::cout << "[Request] Node id: " << id << "\n";

	// Append local requests to next node's requests
	while (!local_requesters.empty())
	{
		neighbor->local_requesters.push(local_requesters.front());
		local_requesters.pop();
	}
}

void Node::pass_requests_to_token()
{
	// Append local requests to token's requests
	while (!local_requesters.empty())
	{
		token->requester_ids.push(local_requesters.front());
		local_requesters.pop();
	}
}

void Node::enter_cs()
{
	// Print the state
	if (job_timestamps.empty()) std::cout << "CRITICAL ERROR IN enter_cs() -> Node id: " << id << "\n";
	std::cout << "[CS] Node id: " << id << " | Timestamp: " << job_timestamps.front() << "\n";

	// Clean afterwards
	job_timestamps.pop();
	token->requester_ids.pop();
	task_in_druation = false;
}

void Node::process_has_token(int iteration)
{
	// Pass local requests to token
	pass_requests_to_token();

	if (!token->requester_ids.empty())
	{
		if (token->requester_ids.front() == id)
			enter_cs();
		else
			transfer_token();
	}
}

bool Node::should_self_request(int iteration) const
{
	return (!task_in_druation && !job_timestamps.empty() && iteration >= job_timestamps.front());
}

Node::Node(int id, const std::queue<int>& jobs, bool init_token)
	: id(id), job_timestamps(jobs)
{
	if (init_token)
		token = std::make_unique<Token>();
}

void Node::process(int iteration)
{
	if (should_self_request(iteration))
	{
		local_requesters.push(id);
		task_in_druation = true;
	}

	if (token)
	{
		process_has_token(iteration);
	}
	else
	{
		pass_requests_to_neighbor();
	}
}

bool Node::has_jobs() const
{
	return !job_timestamps.empty();
}

std::string Node::get_debug_string() const
{
	std::ostringstream out;

	out << "ID: " << id << "\n";

	if (token)
	{
		out << "Token holder: ";
		std::queue<int> token_queue(token->requester_ids);
		while (!token_queue.empty())
		{
			out << token_queue.front() << " ";
			token_queue.pop();
		}

		out << "\n";
	}
	else
	{
		out << "Token: nullptr\n";
	}

	if (neighbor)
		out << "Neighbor: " << neighbor << "\n";
	else
		out << "Neighbor: nullptr\n";

	out << "Jobs: ";
	std::queue<int> jobs_copy(job_timestamps);
	while (!jobs_copy.empty())
	{
		out << jobs_copy.front() << " ";
		jobs_copy.pop();
	}

	out << "\n";
	out << "Local requesters: ";
	std::queue<int> local_rq_copy(local_requesters);
	while (!local_rq_copy.empty())
	{
		out << local_rq_copy.front() << "";
		local_rq_copy.pop();
	}

	out << "\n";
	out << "Task in duration: " << task_in_druation << "\n";

	return out.str();
}

void Node::set_neighbor(std::shared_ptr<Node> neighbor)
{
	this->neighbor = neighbor;
}
