#include "Controller.h"

Controller::Controller(const std::vector<std::shared_ptr<Resource>>& resources)
	: resources(resources){}

bool Controller::check_deadlock(const std::vector<std::shared_ptr<Node>>& nodes)
{
	graph.clear();
	build_graph(nodes);

	// Print the graph
	std::cout << "/* Graph */\n";
	for (auto& [key, neighbors] : graph)
	{
		std::cout << key << ": ";
		for (int neighbor : neighbors)
		{
			std::cout << neighbor << " ";
		}

		std::cout << "\n";
	}

	return detect_cycles();
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

void Controller::build_graph(const std::vector<std::shared_ptr<Node>>& nodes)
{
	for (auto node_ptr : nodes)
	{
		if (node_ptr->get_is_blocked() || true)
		{
			auto pending_resource_vec = node_ptr->get_pending_nodes();
			for (int res_id : pending_resource_vec)
			{
				auto blocker_node_id = resources[res_id]->get_parent()->get_blocker_of_res(res_id);
				graph[node_ptr->get_id()].push_back(blocker_node_id);
			}
		}
	}
}
