/**
 * Boolean Operations Visualizer - GUI Implementation
 * 
 * A Qt-based interface for visualizing Boolean operations on polygons using CGAL
 */

#include <QApplication>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPolygonItem>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QMessageBox>
#include "../include/BooleanOperations.h"

class BooleanOperationsWindow : public QMainWindow {
    Q_OBJECT
    
public:
    BooleanOperationsWindow(QWidget* parent = nullptr) : QMainWindow(parent) {
        setWindowTitle("CGAL Boolean Operations");
        resize(800, 600);
        
        // Create central widget and layout
        QWidget* centralWidget = new QWidget(this);
        QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
        
        // Create graphics scene and view
        scene = new QGraphicsScene(this);
        view = new QGraphicsView(scene, this);
        view->setRenderHint(QPainter::Antialiasing);
        view->setDragMode(QGraphicsView::ScrollHandDrag);
        view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        
        // Create control panel
        QHBoxLayout* controlLayout = new QHBoxLayout();
        
        // Operation selector
        QLabel* opLabel = new QLabel("Operation:", this);
        operationCombo = new QComboBox(this);
        operationCombo->addItem("Union");
        operationCombo->addItem("Intersection");
        operationCombo->addItem("Difference");
        operationCombo->addItem("Symmetric Difference");
        
        // Execute button
        QPushButton* executeButton = new QPushButton("Execute", this);
        connect(executeButton, &QPushButton::clicked, this, &BooleanOperationsWindow::executeOperation);
        
        // Reset button
        QPushButton* resetButton = new QPushButton("Reset", this);
        connect(resetButton, &QPushButton::clicked, this, &BooleanOperationsWindow::resetScene);
        
        // Add widgets to control layout
        controlLayout->addWidget(opLabel);
        controlLayout->addWidget(operationCombo);
        controlLayout->addWidget(executeButton);
        controlLayout->addWidget(resetButton);
        controlLayout->addStretch();
        
        // Add widgets to main layout
        mainLayout->addWidget(view);
        mainLayout->addLayout(controlLayout);
        
        setCentralWidget(centralWidget);
        
        // Initialize scene with sample polygons
        initializeScene();
    }
    
private slots:
    void executeOperation() {
        // Clear previous results
        if (resultItem) {
            scene->removeItem(resultItem);
            delete resultItem;
            resultItem = nullptr;
        }
        
        std::list<Polygon_with_holes_2> result;
        QString operationName = operationCombo->currentText();
        
        // Perform the selected operation
        if (operationName == "Union") {
            result = BooleanOperations::performUnion(poly1, poly2);
        } else if (operationName == "Intersection") {
            result = BooleanOperations::performIntersection(poly1, poly2);
        } else if (operationName == "Difference") {
            result = BooleanOperations::performDifference(poly1, poly2);
        } else if (operationName == "Symmetric Difference") {
            result = BooleanOperations::performSymmetricDifference(poly1, poly2);
        }
        
        // Display results
        if (!result.empty()) {
            QColor resultColor;
            if (operationName == "Union")
                resultColor = Qt::green;
            else if (operationName == "Intersection")
                resultColor = Qt::magenta;
            else if (operationName == "Difference")
                resultColor = Qt::cyan;
            else if (operationName == "Symmetric Difference")
                resultColor = Qt::yellow;
            
            // Display all resulting polygons
            for (const auto& poly : result) {
                displayPolygonWithHoles(poly, resultColor);
            }
        } else {
            QMessageBox::information(this, "Result", 
                                    "The operation resulted in an empty set.");
        }
    }
    
    void resetScene() {
        // Remove all items
        scene->clear();
        
        // Reinitialize scene
        initializeScene();
    }
    
private:
    void initializeScene() {
        // Create first polygon (square)
        std::vector<Point_2> vertices1 = {
            Point_2(0, 0),
            Point_2(200, 0),
            Point_2(200, 200),
            Point_2(0, 200)
        };
        poly1 = BooleanOperations::createPolygon(vertices1);
        
        // Create second polygon (overlapping square)
        std::vector<Point_2> vertices2 = {
            Point_2(100, 100),
            Point_2(300, 100),
            Point_2(300, 300),
            Point_2(100, 300)
        };
        poly2 = BooleanOperations::createPolygon(vertices2);
        
        // Display polygons
        displayPolygon(poly1, Qt::blue);
        displayPolygon(poly2, Qt::red);
        
        // Reset result item pointer
        resultItem = nullptr;
    }
    
    void displayPolygon(const Polygon_2& poly, const QColor& color) {
        QPolygonF qpoly;
        
        // Convert CGAL polygon to Qt polygon
        for (auto it = poly.vertices_begin(); it != poly.vertices_end(); ++it) {
            qpoly << QPointF(CGAL::to_double(it->x()), CGAL::to_double(it->y()));
        }
        
        // Create graphics item
        QGraphicsPolygonItem* item = new QGraphicsPolygonItem(qpoly);
        item->setPen(QPen(color, 2));
        item->setBrush(QBrush(color, Qt::BDiagPattern));
        
        // Add to scene
        scene->addItem(item);
    }
    
    void displayPolygonWithHoles(const Polygon_with_holes_2& poly, const QColor& color) {
        QPainterPath path;
        
        // Convert outer boundary
        QPolygonF qpoly;
        for (auto it = poly.outer_boundary().vertices_begin(); 
             it != poly.outer_boundary().vertices_end(); ++it) {
            qpoly << QPointF(CGAL::to_double(it->x()), CGAL::to_double(it->y()));
        }
        
        path.addPolygon(qpoly);
        
        // Add holes (subtract from path)
        for (auto hit = poly.holes_begin(); hit != poly.holes_end(); ++hit) {
            QPolygonF qhole;
            for (auto it = hit->vertices_begin(); it != hit->vertices_end(); ++it) {
                qhole << QPointF(CGAL::to_double(it->x()), CGAL::to_double(it->y()));
            }
            path.addPolygon(qhole);
        }
        
        // Create graphics item from path
        QGraphicsPathItem* item = new QGraphicsPathItem(path);
        item->setPen(QPen(color, 2));
        item->setBrush(QBrush(color, Qt::Dense4Pattern));
        
        // Add to scene
        scene->addItem(item);
        resultItem = item;
    }
    
    QGraphicsScene* scene;
    QGraphicsView* view;
    QComboBox* operationCombo;
    QGraphicsItem* resultItem = nullptr;
    
    Polygon_2 poly1;
    Polygon_2 poly2;
};

/**
 * Main application entry point
 */
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    BooleanOperationsWindow window;
    window.show();
    
    return app.exec();
}

#include "BooleanOperationsGUI.moc"