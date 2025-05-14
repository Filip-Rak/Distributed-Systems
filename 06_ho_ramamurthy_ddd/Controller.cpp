#include "Controller.h"

Controller::Controller(const std::shared_ptr<std::vector<int>>& resources)
	: resources(resources){}

bool Controller::check_deadlock(const std::vector<std::shared_ptr<Node>>& nodes)
{
	std::cout << "[Controller]: Trying to build WFG graph\n";
	rebuild_graph(nodes);

	print_graph();

	// Cycle == deadlock
	bool deadlock = detect_cycles();
	if (deadlock)
		std::cout << "[Controller]: Reporting deadlock\n";
	else
		std::cout << "[Controller]: Nothing to report\n";

	return deadlock;
}

void Controller::print_graph()
{
	if (graph.empty())
		return;

	std::cout << "[Controller]: Print graph\n=== START GRAPH\n";
	for (auto& [key, neighbors] : graph)
	{
		std::cout << "=== " << key << ": ";
		for (int neighbor : neighbors)
		{
			std::cout << neighbor << " ";
		}

		std::cout << "\n";
	}

	std::cout << "=== END GRAPH\n";
}

void Controller::rebuild_graph(const std::vector<std::shared_ptr<Node>>& nodes)
{
	graph.clear();

	for (auto node_ptr : nodes)
	{
		auto pending_resource_vec = node_ptr->get_pending_nodes();
		for (int res_id : pending_resource_vec)
		{
			auto blocker_node_id = (*resources)[res_id];
			graph[node_ptr->get_id()].push_back(blocker_node_id);
		}
	}
}

bool Controller::detect_cycles()
{
	for (const auto& [node, _] : graph)
	{
		std::stack<std::pair<int, std::unordered_set<int>>> stack; // <node, path = [node, node ... ]>
		stack.push({ node, {} });

		while (!stack.empty())
		{
			auto [current_node, current_path] = stack.top();
			stack.pop();

			// Add to path
			bool inserted = current_path.insert(current_node).second;
			if (!inserted) return true;

			// Explore enighbors
			for (int neighbor_node : graph[current_node])
			{
				stack.push({ neighbor_node, current_path });
			}
		}
	}

	return false;
}