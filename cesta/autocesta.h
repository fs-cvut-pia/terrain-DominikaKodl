#include "Path.h"
#include <unordered_map>

class autocesta : public Path {
public:
    autocesta(TerrainMap &m, const Point &startIn, const Point &finishIn);

    bool find() override;

private:
    bool isValid(const Point &referencePoint, const Point &currentPoint);

    std::vector<Point> findNeighbor(const Point &current);

    void reconstructPath(const std::unordered_map<Point, Point> &predecessor);
};

#endif
