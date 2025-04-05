/**
 * Implementation of Boolean operations on polygons using CGAL
 * 
 * This file contains implementations for:
 * - Union (join) of two polygons
 * - Intersection of two polygons
 * - Difference between two polygons
 * - Symmetric difference of two polygons
 * - Utility functions for polygon creation and output
 */

#include <CGAL/Boolean_set_operations_2.h>
#include "../include/BooleanOperations.h"

/**
 * Performs a union operation between two polygons
 */
std::list<Polygon_with_holes_2> BooleanOperations::performUnion(const Polygon_2& poly1, const Polygon_2& poly2) {
    std::list<Polygon_with_holes_2> result;
    
    // Create a temporary result object
    Polygon_with_holes_2 temp_result;
    
    // Perform the join operation
    bool success = CGAL::join(poly1, poly2, temp_result);
    
    // If successful, add to the result list
    if (success) {
        result.push_back(temp_result);
    }
    
    return result;
}

/**
 * Performs an intersection operation between two polygons
 */
std::list<Polygon_with_holes_2> BooleanOperations::performIntersection(const Polygon_2& poly1, const Polygon_2& poly2) {
    std::list<Polygon_with_holes_2> result;
    
    // Perform the intersection operation
    CGAL::intersection(poly1, poly2, std::back_inserter(result));
    
    return result;
}

/**
 * Performs a difference operation between two polygons (poly1 - poly2)
 */
std::list<Polygon_with_holes_2> BooleanOperations::performDifference(const Polygon_2& poly1, const Polygon_2& poly2) {
    std::list<Polygon_with_holes_2> result;
    
    // Perform the difference operation (poly1 - poly2)
    CGAL::difference(poly1, poly2, std::back_inserter(result));
    
    return result;
}

/**
 * Performs a symmetric difference operation between two polygons
 */
std::list<Polygon_with_holes_2> BooleanOperations::performSymmetricDifference(const Polygon_2& poly1, const Polygon_2& poly2) {
    std::list<Polygon_with_holes_2> result;
    
    // Perform the symmetric difference operation
    CGAL::symmetric_difference(poly1, poly2, std::back_inserter(result));
    
    return result;
}

/**
 * Creates a polygon from a vector of points
 */
Polygon_2 BooleanOperations::createPolygon(const std::vector<Point_2>& vertices) {
    Polygon_2 poly;
    
    // Add each vertex to the polygon
    for (const auto& vertex : vertices) {
        poly.push_back(vertex);
    }
    
    return poly;
}

/**
 * Prints information about a polygon with holes
 */
void BooleanOperations::printPolygonWithHoles(const Polygon_with_holes_2& poly) {
    std::cout << "Polygon with " << poly.number_of_holes() << " holes" << std::endl;
}

/**
 * Prints information about a list of polygons with holes
 */
void BooleanOperations::printPolygonList(const std::list<Polygon_with_holes_2>& polys) {
    std::cout << "List contains " << polys.size() << " polygon(s) with holes" << std::endl;
    
    int index = 0;
    for (const auto& poly : polys) {
        std::cout << "  Polygon " << ++index << ": ";
        printPolygonWithHoles(poly);
    }
}