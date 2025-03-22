#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <unordered_map>
#include <tuple>
#include <optional>

using namespace std;

struct Node {
    int x, y;
    double g, h;
    Node* parent;

    Node(int x, int y, double g, double h, Node* parent = nullptr)
        : x(x), y(y), g(g), h(h), parent(parent) {}

    double f() const { return g + h; }
};

struct Compare {
    bool operator()(const Node* a, const Node* b) const {
        return a->f() > b->f();
    }
};

const vector<pair<int, int>> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

double heuristic(int x, int y, int a, int b) {
    return abs(x - a) + abs(y - b);
}
optional<vector<pair<int, int>>> aStarSearch(const vector<vector<int>>& grid, pair<int, int> start, pair<int, int> des) {
    int row = grid.size(), col = grid[0].size();
    
    priority_queue<Node*, vector<Node*>, Compare> openlist;
    openlist.emplace(new Node(start.first, start.second, 0, heuristic(start.first, start.second, des.first, des.second)));

    // store the shortest path.
    unordered_map<int, unordered_map<int, double>> gCost;
    gCost[start.first][start.second] = 0;

    // store the visited node.
    unordered_map<int, unordered_map<int, bool>> closedSet;

    while (!openlist.empty()) {
        Node* current = openlist.top();
        openlist.pop();

        if (closedSet[current->x][current->y]) continue;
        closedSet[current->x][current->y] = true;

        // judge  the destination
        if (current->x == des.first && current->y == des.second) {
            vector<pair<int, int>> path;
            while (current) {
                path.emplace_back(current->x, current->y);
                current = current->parent;
            }
            reverse(path.begin(), path.end());
            return path;
        }

        // directions
        for (auto [dx, dy] : directions) {
            int nx = current->x + dx, ny = current->y + dy;
            if (nx >= 0 && nx < row && ny >= 0 && ny < col && grid[nx][ny] == 1) {
                double newG = current->g + 1;
                if (!gCost.count(nx) || !gCost[nx].count(ny) || newG < gCost[nx][ny]) {
                    gCost[nx][ny] = newG;
                    openlist.emplace(new Node(nx, ny, newG, heuristic(nx, ny, des.first, des.second), current));
                }
            }
        }
    }
    return nullopt;
}

void showpath(const optional<vector<pair<int, int>>>& path) {
    if (!path.has_value()) {
        cout << "Error01, no legal value found." << endl;
        return;
    }
    cout << "Path:" << endl;
    for (const auto& [x, y] : *path) {
        cout << "(" << x << "," << y << ") -> ";
    }
    cout << "Goal\n";
}

