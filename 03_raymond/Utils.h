#pragma once

#include <vector>
#include <memory>

#include "Node.h"

std::vector<std::shared_ptr<Node>> load_nodes_from_file(const std::string& filename);