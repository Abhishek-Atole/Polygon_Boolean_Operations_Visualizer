#include "include/BooleanOperations.h"

int main() {
    // Create first polygon (square with vertices at (0,0), (2,0), (2,2), (0,2))
    std::vector<Point_2> vertices1 = {
        Point_2(0, 0),
        Point_2(2, 0),
        Point_2(2, 2),
        Point_2(0, 2)
    };
    Polygon_2 poly1 = BooleanOperations::createPolygon(vertices1);
    
    // Create second polygon (square with vertices at (1,1), (3,1), (3,3), (1,3))
    std::vector<Point_2> vertices2 = {
        Point_2(1, 1),
        Point_2(3, 1),
        Point_2(3, 3),
        Point_2(1, 3)
    };
    Polygon_2 poly2 = BooleanOperations::createPolygon(vertices2);
    
    std::cout << "Computing union of two overlapping squares..." << std::endl;
    
    // Perform union operation
    std::list<Polygon_with_holes_2> result = BooleanOperations::performUnion(poly1, poly2);
    
    // Print result
    BooleanOperations::printPolygonList(result);
    
    return 0;
}