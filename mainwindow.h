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

private:
    Ui::MainWindow *ui;

    vector<Car> cars;

    void setupScreen();

    // Reload - display latest data.
    void reloadApp();
    void reloadTable();
    void reloadCar();


    // Clear - set data to default values.
    void clearApp();
    void clearCar();
    void clearTable();

};
#endif // MAINWINDOW_H
