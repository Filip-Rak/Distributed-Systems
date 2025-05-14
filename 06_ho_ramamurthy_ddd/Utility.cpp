#include "Utility.h"

std::pair<std::vector<std::shared_ptr<Node>>,
    std::vector<std::shared_ptr<Resource>>> load_from_file(const std::string& filename)
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

    // Load processes
    // Format: [node_id resource resource ... ]
    std::unordered_map<int, std::queue<int>> node_to_process; // <node_id, [resources]>]

    std::string line;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);

        int node_id;
        ss >> node_id;

        int buffer;
        while (ss >> buffer)
        {
            node_to_process[node_id].push(buffer);
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
            nodes.push_back(std::make_shared<Node>(i));
        }
        else
        {
            nodes.push_back(std::make_shared<Node>(i, it->second));
        }
    }

    /* Create Resources */
    std::vector<std::shared_ptr<Resource>> resources;
    resources.reserve(num_resources);

    for (std::size_t i = 0; i < num_resources; i++)
    {
        resources.push_back(std::make_shared<Resource>(i));
    }

    // Assign resources to nodes
    for (auto node_ptr : nodes)
    {
        node_ptr->set_resource_ptr(resources);
    }

    return { nodes, resources };
}

void print_nodes(const std::vector<std::shared_ptr<Node>>& nodes, std::string(Node::*method)() const)
{
    for (auto node_ptr : nodes)
    {
        std::cout << (node_ptr.get()->*method)() << "\n";
    }
}
