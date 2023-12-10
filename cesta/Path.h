#include <map>
#include "Path.h"

class PlanePath : public Path {
public:
    PlanePath(TerrainMap &m, const Point &startIn, const Point &finishIn);

    bool find() override;

private:
    bool isValid(const Point &referencePoint);
    std::vector<std::pair<Point, double>> findNeighbor(const Point &current);
    void reconstructPath(const std::map<Point, Point> &predecessor);
};

#endif

