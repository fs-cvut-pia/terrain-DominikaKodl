#include "Path.h"
#include <map>

class lod : public Path {
public:
    lod(TerrainMap &m, const Point &startIn, const Point &finishIn);

    bool find() override;

private:
    bool isValid(const Point &referencePoint);

    std::vector<Point> findNeighbor(const Point &current);

    void reconstructPath(const std::unordered_map<Point, Point> &predecessor);
};

#endif
