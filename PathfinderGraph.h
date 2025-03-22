// PathfinderGraph.h
#pragma once
#include "Graph.h"
#include <optional>
#include <vector>
#include <string>

optional<vector<string>> aStarSearch(const Graph& graph, const string& start, const string& goal);
