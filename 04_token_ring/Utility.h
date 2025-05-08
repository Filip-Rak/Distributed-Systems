#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Node.h"

std::vector<std::shared_ptr<Node>> load_from_file(const std::string& filename);

void print_nodes(const std::vector<std::shared_ptr<Node>>& nodes);