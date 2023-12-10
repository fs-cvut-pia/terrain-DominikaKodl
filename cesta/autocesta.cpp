#include "autocesta.h"
#include <queue>
#include <set>
#include <cmath>

autocesta::autocesta(TerrainMap &m, const Point &startIn, const Point &finishIn)
    : Path(m, "Auto", startIn, finishIn) {}

bool autocesta::find() {
    std::queue<Point> queue;
    std::set<Point> visited;
    std::map<Point, Point> predecessor;

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

std::vector<Point> autocesta::findNeighbor(const Point &current) {
    std::vector<Point> neighbors;

    for (int j = -1; j < 2; ++j) {
        for (int i = -1; i < 2; ++i) {
            auto neighbor = Point(current.x + i, current.y + j);

            if (isValid(neighbor, current)) {
                neighbors.push_back(neighbor);
            }
        }
    }

    return neighbors;
}

bool autocesta::isValid(const Point &referencePoint, const Point &currentPoint) {
    if (map.validCoords(referencePoint)) {
        if (map.alt(referencePoint) > 0 || referencePoint == finish) {
            if (std::abs((map.alt(referencePoint) - map.alt(currentPoint)) / map.alt(currentPoint)) <= 0.006 || referencePoint == finish) {
                return true;
            }
        }
    }

    return false;
}

void autocesta::reconstructPath(const std::map<Point, Point> &predecessor) {
    Point current = finish;

    while (current != start) {
        path.push_back(current);
        current = predecessor.at(current);
    }

    path.push_back(current);
    std::reverse(path.begin(), path.end());
}
