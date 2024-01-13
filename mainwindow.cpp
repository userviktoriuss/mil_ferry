#include "mainwindow.h"
#include "./ui_mainwindow.h"

using std::to_string;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupScreen();
    setupValidators();
    // Reloads all widets data
    reloadApp();
}

// TODO:

void MainWindow::setupValidators() {
    // callLineEdit.
    QRegularExpression regexp("^[а-яА-Я]([а-яА-Я0-9]){0,14}$");  // TODO: set pattern
    auto callValidator = new QRegularExpressionValidator(regexp);
    callValidator->setRegularExpression(regexp);
    ui->callLineEdit->setValidator(callValidator);
}

void MainWindow::reloadApp() {
    // Clear all the data.
    clearData();
    clearFerry();

    // Clear UI
    clearCarLineEdits();
    clearFerryLineEdit();
    clearGraph();

    // Redraw UI
    reloadTable();
    drawGrid();
    drawData();
}

void MainWindow::clearGraph() {

}

void MainWindow::drawGrid() {

}

void MainWindow::drawData() {

}

// END TODO

void MainWindow::clearFerryLineEdit() {
    ui->ferryLengthLineEdit->clear();
}

void MainWindow::clearFerry() {
    ferryLength = 0;
}

void MainWindow::clearData() {
    center.setX(0);
    center.setY(0);
    radius = 0;
    cars.clear();
}

void MainWindow::clearCarLineEdits() {
    ui->callLineEdit->clear();
    ui->widthLineEdit->clear();
    ui->lengthLineEdit->clear();
    ui->xCoordLineEdit->clear();
    ui->yCoordLineEdit->clear();
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

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_clearCarPushButton_clicked() {
    clearCarLineEdits();
}


void MainWindow::on_clearTablePushButton_clicked()
{
    reloadApp();
}


void MainWindow::on_callLineEdit_textChanged(const QString &newText)
{
    auto text = newText;
    int pos = 0;
    ui->callLineEdit->setText(newText);
    auto res = ui->callLineEdit->validator()->validate(text, pos);
    callLineEditOk = res == QValidator::Acceptable;

    checkCarParametersOk(); // TODO: impl.
}

