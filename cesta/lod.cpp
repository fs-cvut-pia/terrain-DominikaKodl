#include "lod.h"
#include <iostream>
#include <queue>
#include <set>
#include <map>

lod::lod(TerrainMap &m, const Point &startIn, const Point &finishIn)
    : Path(m, "Lod", startIn, finishIn) {}

bool lod::find() {
    std::queue<Point> queue;
    std::unordered_set<Point> visited;
    std::unordered_map<Point, Point> predecessor;

    queue.push(start);
    visited.insert(start);

    while (!queue.empty()) {
        Point current = queue.front();
        queue.pop();

        for (const auto &neighbor : findNeighbor(current)) {
            if (visited.find(neighbor) == visited.end()) {
                queue.push(neighbor);
                visited.insert(neighbor);
                predecessor[neighbor] = current;

                if (neighbor == finish) {
                    reconstructPath(predecessor);
                    return true;
                }
            }
        }
    }

    return false;
}

std::vector<Point> lod::findNeighbor(const Point &current) {
    std::vector<Point> neighbors;

    for (int j = -1; j < 2; ++j) {
        for (int i = -1; i < 2; ++i) {
            auto neighbor = Point(current.x + i, current.y + j);
            if (isValid(neighbor)) {
                neighbors.push_back(neighbor);
            }
        }
    }

    return neighbors;
}

bool lod::isValid(const Point &referencePoint) {
    return map.validCoords(referencePoint) &&
           (map.alt(referencePoint) < 0 || referencePoint == finish);
}

void lod::reconstructPath(const std::unordered_map<Point, Point> &predecessor) {
    Point current = finish;

    while (current != start) {
        path.push_back(current);
        current = predecessor.at(current);
    }

    path.push_back(current);
    std::reverse(path.begin(), path.end());
