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

    // widthLineEdit.
    ui->widthLineEdit->setMaxLength(9);
    ui->widthLineEdit->setValidator(new QDoubleValidator());

    // lengthLineEdit.
    ui->lengthLineEdit->setMaxLength(9);
    ui->lengthLineEdit->setValidator(new QDoubleValidator());

    // xCoordLineEdit.
    ui->xCoordLineEdit->setMaxLength(9);
    ui->xCoordLineEdit->setValidator(new QDoubleValidator());

    // yCoordLineEdit.
    ui->yCoordLineEdit->setMaxLength(9);
    ui->yCoordLineEdit->setValidator(new QDoubleValidator());

    // ferryLengthLineEdit.
    ui->yCoordLineEdit->setMaxLength(9);
    ui->yCoordLineEdit->setValidator(new QDoubleValidator());
}

void MainWindow::reloadApp() {
    // Clear all the data.
    clearData();
    clearFerry();

    // Reload UI
    reloadUI();
}

void MainWindow::reloadUI() {
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
    // this->setFixedWidth(screenWidth);

    // Place window in the center of the screen.
    move((screenWidth - this->width()) / 2,(screenHeight - this->height()) / 2);

    // setup placePushButton
    ui->placePushButton->setStyleSheet("background-color: rgba(0, 127, 255, 0.5)");
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

    // Set header color.
    ui->tableView->setStyleSheet("QHeaderView::section { background-color: rgb(169, 169, 169) }");

    // Pass the data to table.
    ui->tableView->setModel(model);
    ui->tableView->verticalHeader()->setVisible(false); // Hide numerations of rows.
    ui->tableView->resizeRowsToContents();
    ui->tableView->resizeColumnsToContents();

    // Set enabled for placePushButton and transportPushButton
    ui->placePushButton->setEnabled(cars.size() >= 1);
    ui->transportPushButton->setEnabled(cars.size() >= 1);
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


/*
void MainWindow::on_callLineEdit_textChanged(const QString &newText)
{
    auto text = newText;
    int pos = 0;
    ui->callLineEdit->setText(newText);
    auto res = ui->callLineEdit->validator()->validate(text, pos);
    callLineEditOk = res == QValidator::Acceptable;

    checkCarParametersOk(); // TODO: impl.
}
*/

void MainWindow::checkCarParametersOk() {
    bool enabled = callLineEditOk &&
                   widthLineEditOk &&
                   lengthLineEditOk &&
                   xCoordLineEditOk &&
                   yCoordLineEditOk;
    ui->addCarPushButton->setEnabled(enabled);
}

void MainWindow::on_widthLineEdit_editingFinished()
{
    widthLineEditOk = true;
    checkCarParametersOk();
}


void MainWindow::on_widthLineEdit_textChanged(const QString &arg1)
{
    widthLineEditOk = false;
    checkCarParametersOk();
}


void MainWindow::on_lengthLineEdit_editingFinished()
{
    lengthLineEditOk = true;
    checkCarParametersOk();
}


void MainWindow::on_lengthLineEdit_textChanged(const QString &arg1)
{
    lengthLineEditOk = false;
    checkCarParametersOk();
}


void MainWindow::on_xCoordLineEdit_editingFinished()
{
    xCoordLineEditOk = true;
    checkCarParametersOk();
}


void MainWindow::on_xCoordLineEdit_textChanged(const QString &arg1)
{
    xCoordLineEditOk = false;
    checkCarParametersOk();
}


void MainWindow::on_yCoordLineEdit_editingFinished()
{
    yCoordLineEditOk = true;
    checkCarParametersOk();
}


void MainWindow::on_yCoordLineEdit_textChanged(const QString &arg1)
{
    yCoordLineEditOk = false;
    checkCarParametersOk();
}


void MainWindow::on_callLineEdit_editingFinished()
{
    callLineEditOk = true;
    checkCarParametersOk();
}


void MainWindow::on_callLineEdit_textChanged(const QString &arg1)
{
    callLineEditOk = false;
    checkCarParametersOk();
}


void MainWindow::on_addCarPushButton_clicked()
{
    string call = ui->callLineEdit->text().toStdString();
    double width = ui->widthLineEdit->text().toDouble();
    double length = ui->lengthLineEdit->text().toDouble();
    double xCoord = ui->xCoordLineEdit->text().toDouble();
    double yCoord = ui->yCoordLineEdit->text().toDouble();

    cars.push_back(Car(call, xCoord, yCoord, width, length));
    reloadUI();
}


void MainWindow::on_ferryLengthLineEdit_editingFinished()
{
    ui->setFerryLengthPushButton->setEnabled(true);
}


void MainWindow::on_ferryLengthLineEdit_textChanged(const QString &arg1)
{
    ui->setFerryLengthPushButton->setEnabled(false);
}

