#ifndef BOOLEAN_OPERATIONS_GUI_H
#define BOOLEAN_OPERATIONS_GUI_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QComboBox>
#include "BooleanOperations.h"

class BooleanOperationsWindow : public QMainWindow {
    Q_OBJECT
    
public:
    BooleanOperationsWindow(QWidget* parent = nullptr);
    
private slots:
    void executeOperation();
    void resetScene();
    
private:
    void initializeScene();
    void displayPolygon(const Polygon_2& poly, const QColor& color);
    void displayPolygonWithHoles(const Polygon_with_holes_2& poly, const QColor& color);
    
    QGraphicsScene* scene;
    QGraphicsView* view;
    QComboBox* operationCombo;
    QGraphicsItem* resultItem = nullptr;
    
    Polygon_2 poly1;
    Polygon_2 poly2;
};

#endif // BOOLEAN_OPERATIONS_GUI_H