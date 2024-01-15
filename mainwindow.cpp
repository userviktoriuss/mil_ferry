#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "qDebug"

using std::to_string;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupScreen();
    setupGraphicsView();
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
    if (scene) {
        delete scene;
        scene = nullptr;
    }
}

void MainWindow::drawGrid() {
    // Create new scene.
    scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);

    auto width = ui->graphicsView->width();
    auto height = ui->graphicsView->height();
    scene->setSceneRect(0, 0, width, height);

    // Draw grid.
    auto dw = width / 11.0;
    auto dh = height / 11.0;

    auto markw = dw / 10;
    auto markh = dh / 10;


    // Pen for drawing the lines.
    QPen linesPen = QPen(Qt::gray, 2);

    // Draw horizontal.
    for (int i = 1; i <= 10; ++i) {
        auto x1 = dw - markw;
        auto x2 = 10 * dw + markw;
        auto y = i * dh;

        scene->addLine(x1, y, x2, y, linesPen);
    }

    // Draw vertical.
    for (int i = 1; i <= 10; ++i) {
        auto y1 = dh - markh;
        auto y2 = 10 * dh + markh;
        auto x = i * dw;

        scene->addLine(x, y1, x, y2, linesPen);
    }
}

string MainWindow::toString(const double &x) {
    int num = std::round(x * 10);
    auto res = to_string(num / 10) + "." + to_string(num % 10);
    return res;
}

void MainWindow::drawData() {
    if (cars.empty())
        return;

    double maxX = 0;
    double maxY = 0;
    for (auto &car : cars) {
        maxX = std::max(maxX, car.X + car.width / 100.0);
        maxY = std::max(maxY, car.Y + car.length / 100.0);
    }
    ++maxX;
    ++maxY;

    // Create labels.
    auto width = scene->width();
    auto height = scene->height();
    auto dw = width / 11.0;
    auto dh = height / 11.0;
    auto markw = dw / 10;
    auto markh = dh / 10;

    // For ordinate.
    for (int i = 1; i <= 10; ++i) {
        auto text = toString((10 - i) / 9.0 * maxY);
        auto label = scene->addText(text.c_str());
        auto x = dw - 9 * markw;
        auto y = i * dh - 15;
        label->setPos(x, y);
    }
    // For abscissa.
    for (int i = 1; i <= 10; ++i) {
        auto text = toString((i - 1) / 9.0 * maxX);
        auto label = scene->addText(text.c_str());
        auto x = i * dw - 15;
        auto y = height - dh + markh;
        label->setPos(x, y);
    }

    auto carPen = QPen(Qt::red);
    auto carBrush = QBrush(Qt::red);

    auto mapXCoords = [dw, maxX](double x) {
        return x / maxX * 9 * dw;
    };
    auto mapYCoords = [dh, maxY](double y) {
        return y / maxY * 9 * dh;
    };

    //qInfo() << "reload:";
    for (auto & car : cars) {
        auto x = dw + mapXCoords(car.X);
        auto y = height - dh - mapYCoords(car.Y);
        auto w = mapXCoords(car.width / 100.0);
        auto h = mapYCoords(car.length / 100.0);
        y -= h; // Because the coordinates of a Rect are at its top left.
        //qInfo() << x << " " << y << "; w/h: " << w << " " << h;
        scene->addRect(x, y, w, h, carPen, carBrush);
    }
}

void MainWindow::setupGraphicsView() {
    // TODO: Set size if needed

    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
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
    this->setFixedWidth(this->width());

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

    QStandardItem* row[6];

    // Fill data.
    for (int i = 0; i < cars.size(); ++i) {
        auto & car = cars[i];
        auto str = [](double &x) {
            auto s = to_string(x);
            int pos = s.find('.');
            return s.substr(0, pos + 1 + 2);
        };

        row[0] = new QStandardItem(car.call.c_str()); // Sorry about that, I'm too lazy now.
        row[1] = new QStandardItem(str(car.X).c_str());
        row[2] = new QStandardItem(str(car.Y).c_str());
        row[3] = new QStandardItem(str(car.width).c_str());
        row[4] = new QStandardItem(str(car.length).c_str());
        row[5] = new QStandardItem(car.position.c_str());

        for (int j = 0; j < 6; ++j) {
            row[j]->setEditable(false);
            model->setItem(i, j, row[j]);
        }
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
    double width = ui->widthLineEdit->text().replace(',', '.').toDouble();
    double length = ui->lengthLineEdit->text().replace(',', '.').toDouble();
    double xCoord = ui->xCoordLineEdit->text().replace(',', '.').toDouble();
    double yCoord = ui->yCoordLineEdit->text().replace(',', '.').toDouble();

    //qInfo() << "w/l: " << width << " " << length << "; x/y: " << xCoord << " " << yCoord;

    bool sameCall = false;
    bool intersects = false;

    for (auto & car : cars) {
        if (car.call == call)
            sameCall = true;

        auto left = std::max(xCoord, car.X);
        auto right = std::min(xCoord + width / 100.0, car.X + car.width / 100.0);
        auto bottom = std::max(yCoord, car.Y);
        auto top = std::min(yCoord + length / 100.0, car.Y + car.length / 100.0);

        //qInfo() << left << " " << right << " " << bottom << " " << top;

        if (left <= right || bottom <= top)
            intersects = true;
    }

    if (!sameCall && !intersects) {
        cars.push_back(Car(call, xCoord, yCoord, width, length));
        reloadUI();
    } else {
        // Send message;
        if (sameCall) {
            QMessageBox msgBox;
            msgBox.setText("Такая запись уже существует!");
            msgBox.setWindowTitle("Оповещение");
            msgBox.exec();
        } else {
            QMessageBox msgBox;
            msgBox.setText("Пересечения запрещены!");
            msgBox.setWindowTitle("Оповещение");
            msgBox.exec();
        }
    }
}


void MainWindow::on_ferryLengthLineEdit_editingFinished()
{
    ui->setFerryLengthPushButton->setEnabled(true);
}


void MainWindow::on_ferryLengthLineEdit_textChanged(const QString &arg1)
{
    ui->setFerryLengthPushButton->setEnabled(false);
}

