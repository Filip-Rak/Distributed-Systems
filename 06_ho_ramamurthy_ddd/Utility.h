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

std::pair<std::vector<std::shared_ptr<Node>>, 
	std::shared_ptr<std::vector<int>>> load_from_file(const std::string& filename);

void print_nodes(const std::vector<std::shared_ptr<Node>>& nodes, std::string (Node::*method)() const);