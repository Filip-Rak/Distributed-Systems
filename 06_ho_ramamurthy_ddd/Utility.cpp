#include "Utility.h"

std::vector<std::shared_ptr<Node>> load_from_file(const std::string& filename)
{
    /* Load Data */
    std::ifstream file(filename);

    if (!file.is_open())
        throw std::runtime_error("Failed to open file");

    // Load number of nodes and number of resources
    // Format: [num_nodes num_resources]
    int num_nodes, num_resources;
    file >> num_nodes >> num_resources;

    if (num_nodes <= 0 || num_resources <= 0)
        throw std::runtime_error("Invalid file format");

    // Load resources
    // Format [node_index res res ...]
    file.ignore();

    std::unordered_map<int, int> resource_to_node;
    for (int i = 0; i < num_nodes; i++)
    {
        std::string line;
        std::getline(file, line);
        std::stringstream ss(line);

        int node_id;
        ss >> node_id;

        int buffer;
        while (ss >> buffer)
        {
            resource_to_node[buffer] = node_id;
        }
    }

    // Load processes
    std::unordered_map<int, std::pair<int, std::vector<int>>> node_to_process; // <node_id, <process_timestsamp, [resources]>]

    std::string line;
    int timestamp = 0;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);

        int node_id;
        ss >> node_id;

        node_to_process[node_id].first = timestamp++;

        int buffer;
        while (ss >> buffer)
        {
            node_to_process[node_id].second.push_back(buffer);
        }
    }

    file.close();

    /* Create Nodes */
    std::vector<std::shared_ptr<Node>> nodes;
    nodes.reserve(num_nodes);

    for (int i = 0; i < num_nodes; i++)
    {
        auto it = node_to_process.find(i);
        if (it == node_to_process.end())
        {
            nodes.push_back(std::make_shared<Node>(i, -1));
        }
        else
        {
            nodes.push_back(std::make_shared<Node>(i, it->first, it->second));
        }
    }

    /* Create Resources */
    std::vector<std::shared_ptr<Resource>> resources;
    resources.reserve(num_resources);

    for (std::size_t i = 0; i < num_resources; i++)
    {
        std::shared_ptr<Node> parent = nodes[resource_to_node[i]];
        resources.push_back(std::make_shared<Resource>(i, parent));
    }

    // Assign resources to nodes
    for (auto node_ptr : nodes)
    {
        node_ptr->set_resource_ptr(resources);
    }

    return nodes;
}
