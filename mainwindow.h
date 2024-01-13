#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScreen>
#include <qDebug>
#include "QStandardItemModel"
#include "QStandardItem"
#include <vector>
#include "car.h"

using std::vector;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_clearCarPushButton_clicked();

    void on_clearTablePushButton_clicked();

private:
    Ui::MainWindow *ui;

    // Data about cars.
    vector<Car> cars;
    // Circle center.
    QPointF center;
    // Circle radius.
    double radius = 0;
    // Ferry length.
    double ferryLength = 0;

    void setupScreen();

    // Set up to initial state.
    void reloadApp();
    // Load data from cars to the table.
    void reloadTable();


    // Clear LineEdits for car parameters group.
    void clearCarLineEdits();
    // Clear LineEdit for ferry.
    void clearFerryLineEdit();
    // Clears ferry's length
    void clearFerry();
    // Clears container 'cars' and the circle data.
    void clearData();
    // Clears the grid.
    void clearGraph();

    // Draws the grid.
    void drawGrid();
    // Draws cars and circle.
    void drawData();

};
#endif // MAINWINDOW_H
