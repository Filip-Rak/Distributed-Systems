#pragma once

#include <vector>
#include <memory>
#include <queue>
#include <string>
#include <iostream>
#include <fstream>

#include "Node.h"

std::pair<int, std::queue<std::pair<int, int>>> load_from_file(const std::string& filename);
std::vector<std::shared_ptr<Node>> create_nodes(int num_of_nodes);

void print_loaded_data(int num_nodes, std::queue<std::pair<int, int>> block_queue);
void print_node_state(const std::vector<std::shared_ptr<Node>>& nodes);