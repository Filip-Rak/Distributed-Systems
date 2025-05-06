#include "Node.h"

void Node::transfer_token(std::shared_ptr<Node>& receiver)
{
	this->has_token = false;
	receiver->has_token = true;
	this->parent = receiver;
}

void Node::request_token_from_parent()
{
	auto self_ptr = std::make_shared<Node>(this);
	parent->token_requests.push(self_ptr);
	token_requests.push(self_ptr);

	std::cout << "[Request] ID: " << id << "\n";
}

void Node::enter_cs()
{
	// Print the state
	std::cout << "[CS] ID: " << id << "\n";

	// Zero the state
	jobs.pop();
	request_in_progress = false;
}

Node::Node(int id, std::queue<int> jobs, bool has_token)
	: id(id), jobs(jobs), parent(nullptr), has_token(has_token){}

void Node::process(int iteration)
{
	if (has_token)
	{
		if (!token_requests.empty())
		{
			if (token_requests.front()->id == this->id)
				enter_cs();
			else
				transfer_token(token_requests.front());

			token_requests.pop();
		}
	}
	else
	{
		if (!request_in_progress)
		{
			if (jobs.empty() && jobs.front() >= iteration)
			{
				request_token_from_parent();
				request_in_progress = true;
			}
		}
	}
}

void Node::set_parent(std::shared_ptr<Node>& parent)
{
	this->parent = parent;
}

bool Node::has_jobs() const
{
	return !jobs.empty();
}

std::string Node::get_debug_string() const
{
	std::ostringstream out;
	
	out << "ID: " << id << "\n";
	out << "has_token: " << has_token << "\n";
	out << "request_in_progress: " << request_in_progress << "\n";
	out << "parent id: " << parent->id << "\n";

	std::queue<std::shared_ptr<Node>> token_requests_copy(token_requests);
	
	out << "token requests (IDs): ";
	while (!token_requests_copy.empty())
	{
		out << token_requests_copy.front()->id << " ";
		token_requests_copy.pop();
	}

	out << "\n";

	std::queue<int> jobs_copy(jobs);

	out << "jobs: ";
	while (!jobs_copy.empty())
	{
		out << jobs_copy.front() << " ";
		jobs_copy.pop();
	}

	out << "\n";

	return out.str();
}
