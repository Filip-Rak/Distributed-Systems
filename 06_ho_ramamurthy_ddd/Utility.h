#pragma once

#include <utility>
#include <memory>
#include <string>
#include <sstream>
#include <fstream>
#include <stdexcept>
#include <unordered_map>

#include "Node.h"
#include "Resource.h"

std::vector<std::shared_ptr<Node>> load_from_file(const std::string& filename);

void print_nodes(const std::vector<std::shared_ptr<Node>>& nodes);