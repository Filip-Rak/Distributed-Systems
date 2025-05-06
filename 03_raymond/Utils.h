#pragma once

#include <vector>
#include <memory>
#include <fstream>
#include <unordered_map>
#include <string>
#include <queue>

#include "Node.h"

std::vector<std::shared_ptr<Node>> load_nodes_from_file(const std::string& filename);

void print_node_info(const std::vector<std::shared_ptr<Node>>& nodes);