#include "Node.h"

void Node::transfer_token(std::shared_ptr<Node>& receiver)
{
	// Transfer the token & update parents
	this->has_token = false;
	this->parent = receiver;
	receiver->has_token = true;
	receiver->parent = nullptr;

	// Current parent has not received my request
	passed_request_up = false;

	// Print the state
	std::cout << std::left <<"[Transfer] " << this->id << " -> " << receiver->id << "\n";
}

void Node::request_token_from_parent()
{
	// Push self reference to parent's token requests & print
	parent->token_requests.push(shared_from_this());
	std::cout << "[Request ] " << this->id << " -> " << parent->id << "\n";
}

void Node::enter_cs()
{
	// Print the state
	std::cout << "[   CS   ] id = " << id << " | order = " << jobs.front() << "\n";
	// std::cout << "[CSECTION] id = " << id << " | timestamp = " << jobs.front() << "\n";

	// Clean after CS
	jobs.pop();
	self_requested = false;
}

void Node::handle_token()
{
	// Nothing to do if there is no requests
	if (token_requests.empty()) 
		return;
	
	// If the first requester in the queue is me -> go ahead and enter the CS
	if (token_requests.front() == shared_from_this())
	{
		enter_cs();
	}
	else  // I am not first in the queue -> transfer the token
	{
		transfer_token(token_requests.front());
	}

	// A request has been handled
	token_requests.pop();
}

void Node::handle_no_token()
{
	// Pass the request to parent if has requests left & have not done so already
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
	// Push another request to myself if it's time
	if (!self_requested && !jobs.empty() && jobs.front() <= iteration)
	{
		token_requests.push(shared_from_this());
		self_requested = true;
	}

	// Process frame based on token ownership
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

std::string Node::get_clean_string() const
{
	std::ostringstream out;

	out << "ID: " << id << "\n";
	if (parent)
		out << "parent id: " << parent->id << "\n";
	else
		out << "parent id: none (token holder)\n";

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
