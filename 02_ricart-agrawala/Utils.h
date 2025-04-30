#pragma once

#include <unordered_map>
#include <functional>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <memory>
#include <queue>

#include "Node.h"

/**
 * @brief Loads the file contents and fully initializes nodes with them
 *
 * @param filename: Name of the file with extension.
 * @return an std::vector<Node> of fully initialized nodes.
 * @throws std::runtime_error if it fails to open the file.
 */
std::shared_ptr<std::vector<Node>> load_nodes(const std::string& filename);

void print_nodes_state(const std::shared_ptr<std::vector<Node>>& nodes);