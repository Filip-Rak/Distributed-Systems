#include "Node.h"

void Node::transfer_token(std::shared_ptr<Node>& receiver)
{
	this->has_token = false;
	this->parent = receiver;
	receiver->has_token = true;
	receiver->parent = nullptr;

	passed_request_up = false;

	std::cout << "[Transfer] " << this->id << " -> " << receiver->id << "\n";
}

void Node::request_token_from_parent()
{
	parent->token_requests.push(self_reference);
	std::cout << "[Request] " << this->id << " -> " << parent->id << "\n";
}

void Node::enter_cs()
{
	// Print the state
	std::cout << "[CS] Node ID: " << id << " | Job's timestamp: " << jobs.front() << "\n";

	// Clean after CS
	jobs.pop();
	self_requested = false;
}

void Node::handle_token()
{
	if (token_requests.empty()) 
		return;
	
	if (token_requests.front() == self_reference)
	{
		enter_cs();
	}
	else
	{
		transfer_token(token_requests.front());
	}

	token_requests.pop();
}

void Node::handle_no_token()
{
	if (!passed_request_up && !token_requests.empty())
	{
		request_token_from_parent();
		passed_request_up = true;
	}
}

Node::Node(int id, std::queue<int> jobs, bool has_token)
	: id(id), jobs(jobs), parent(nullptr), has_token(has_token) {}

void Node::process(int iteration)
{
	if (!self_requested && !jobs.empty() && jobs.front() >= iteration)
	{
		token_requests.push(self_reference);
		self_requested = true;
	}

	if (has_token)
	{
		handle_token();
	}
	else
	{
		handle_no_token();
	}
}

void Node::set_parent(std::shared_ptr<Node>& parent)
{
	this->parent = parent;
}

void Node::set_self_reference(std::shared_ptr<Node>& self)
{
	self_reference = self;
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
	out << "request_in_progress: " << self_requested << "\n";
	if (parent)
		out << "parent id: " << parent->id << "\n";
	else
		out << "parent id: none (token holder)\n";

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
