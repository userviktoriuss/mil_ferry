#include "mainwindow.h"
#include "./ui_mainwindow.h"

using std::to_string;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupScreen();
    // Reloads all widets data
    reloadApp();
}

void MainWindow::clearApp() {
    clearCar();
    //clearFerry();
    clearTable();
}

void MainWindow::reloadApp() {
    reloadTable();
    reloadCar();
}

// Set the desired size and screen-mode type.
void MainWindow::setupScreen() {
    QScreen *screen = QGuiApplication::primaryScreen ();
    QRect geom = screen->availableGeometry() ;
    int screenWidth = geom.width();
    int screenHeight = geom.height();
    this->setFixedHeight(screenHeight);
    this->setFixedWidth(screenWidth);
}

// Update table according to the stored data.
void MainWindow::reloadTable() {
    QStandardItemModel *model = new QStandardItemModel;

    // Create header.
    QStringList horizontalHeader;
    horizontalHeader.append("Позывной");
    horizontalHeader.append("X");
    horizontalHeader.append("Y");
    horizontalHeader.append("Ширина");
    horizontalHeader.append("Длина");
    horizontalHeader.append("Положение");

    model->setHorizontalHeaderLabels(horizontalHeader);

    // Fill data.
    for (int i = 0; i < cars.size(); ++i) {
        auto & car = cars[i];
        auto str = [](double &x) {
            auto s = to_string(x);
            int pos = s.find('.');
            return s.substr(0, pos + 1 + 2);
        };

        model->setItem(i, 0, new QStandardItem(car.call.c_str())); // Sorry about that, I'm too lazy now.
        model->setItem(i, 1, new QStandardItem(str(car.X).c_str()));
        model->setItem(i, 2, new QStandardItem(str(car.Y).c_str()));
        model->setItem(i, 3, new QStandardItem(str(car.width).c_str()));
        model->setItem(i, 4, new QStandardItem(str(car.length).c_str()));
        model->setItem(i, 5, new QStandardItem(car.position.c_str()));
    }

    // Pass the data to table.
    ui->tableView->setModel(model);
    ui->tableView->verticalHeader()->setVisible(false); // Hide numerations of rows.
    ui->tableView->resizeRowsToContents();
    ui->tableView->resizeColumnsToContents();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_clearCarPushButton_clicked()
{
    ui->callLineEdit->clear();
    ui->widthLineEdit->clear();
    ui->lengthLineEdit->clear();
    ui->xCoordLineEdit->clear();
    ui->yCoordLineEdit->clear();
}

