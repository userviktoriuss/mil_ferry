#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScreen>
#include <qDebug>
#include "QStandardItemModel"
#include "QStandardItem"
#include <vector>
#include "car.h"
#include <QRegularExpression>

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

    void on_widthLineEdit_editingFinished();

    void on_widthLineEdit_textChanged(const QString &arg1);

    void on_lengthLineEdit_editingFinished();

    void on_lengthLineEdit_textChanged(const QString &arg1);

    void on_xCoordLineEdit_editingFinished();

    void on_xCoordLineEdit_textChanged(const QString &arg1);

    void on_yCoordLineEdit_editingFinished();

    void on_yCoordLineEdit_textChanged(const QString &arg1);

    void on_callLineEdit_editingFinished();

    void on_callLineEdit_textChanged(const QString &arg1);

    void on_addCarPushButton_clicked();

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

    // Validators utils -------------------

    // True, if lineEdits are formatted properly.

    bool callLineEditOk = false;
    bool widthLineEditOk = false;
    bool lengthLineEditOk = false;
    bool xCoordLineEditOk = false;
    bool yCoordLineEditOk = false;

    // Checks that car parameters are ok. If so, enables addCarPushButton. Otherwise, disables it.
    void checkCarParametersOk();

    // End Validators utils ---------------

    // Setups screen size and it's changeing policy.
    void setupScreen();
    // Setups text validators for LineEdits
    void setupValidators();

    // Clears and redraws the UI.
    void reloadUI();
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
