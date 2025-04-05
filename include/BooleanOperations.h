#ifndef BOOLEAN_OPERATIONS_H
#define BOOLEAN_OPERATIONS_H

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Boolean_set_operations_2.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/Polygon_with_holes_2.h>
#include <list>
#include <vector>
#include <iostream>

// Define the kernel for exact geometric predicates and constructions
typedef CGAL::Exact_predicates_exact_constructions_kernel Kernel;
typedef Kernel::Point_2 Point_2;
typedef CGAL::Polygon_2<Kernel> Polygon_2;
typedef CGAL::Polygon_with_holes_2<Kernel> Polygon_with_holes_2;

namespace BooleanOperations {
    /**
     * Performs a union operation on two 2D polygons
     * @param poly1 First polygon
     * @param poly2 Second polygon
     * @return A list containing the resulting polygon(s) with holes
     */
    std::list<Polygon_with_holes_2> performUnion(const Polygon_2& poly1, const Polygon_2& poly2);
    
    /**
     * Performs an intersection operation on two 2D polygons
     * @param poly1 First polygon
     * @param poly2 Second polygon
     * @return A list containing the resulting polygon(s) with holes
     */
    std::list<Polygon_with_holes_2> performIntersection(const Polygon_2& poly1, const Polygon_2& poly2);
    
    /**
     * Performs a difference operation on two 2D polygons
     * @param poly1 First polygon
     * @param poly2 Second polygon
     * @return A list containing the resulting polygon(s) with holes
     */
    std::list<Polygon_with_holes_2> performDifference(const Polygon_2& poly1, const Polygon_2& poly2);
    
    /**
     * Performs a symmetric difference operation on two 2D polygons
     * @param poly1 First polygon
     * @param poly2 Second polygon
     * @return A list containing the resulting polygon(s) with holes
     */
    std::list<Polygon_with_holes_2> performSymmetricDifference(const Polygon_2& poly1, const Polygon_2& poly2);
    
    /**
     * Creates a sample polygon for testing
     * @param vertices Vector of points defining the polygon vertices
     * @return A polygon constructed from the given vertices
     */
    Polygon_2 createPolygon(const std::vector<Point_2>& vertices);
    
    /**
     * Prints a polygon with holes, showing the outer boundary and any holes
     * @param poly The polygon with holes to print
     */
    void printPolygonWithHoles(const Polygon_with_holes_2& poly);
    
    /**
     * Prints all polygons in a list of polygons with holes
     * @param polys The list of polygons with holes
     */
    void printPolygonList(const std::list<Polygon_with_holes_2>& polys);
}

#endif // BOOLEAN_OPERATIONS_H