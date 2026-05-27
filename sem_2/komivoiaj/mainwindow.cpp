#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <cstdlib>
#include <ctime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    std::srand(std::time(nullptr));
    ui->spinCities->setValue(5);
    updateTableSize();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// РЕАЛИЗАЦИЯ АЛГОРИТМА КОМИВОЯЖЁРА (прямо в cpp-файле)
TSPResult MainWindow::solveTSP(const std::vector<std::vector<int>>& distances)
{
    TSPResult result;
    result.bestDistance = std::numeric_limits<int>::max();
    result.permutationsCount = 0;

    int n = distances.size();
    if (n == 0) return result;

    // Создаём начальный маршрут: 0, 1, 2, ..., n-1
    std::vector<int> cities(n);
    for (int i = 0; i < n; i++) {
        cities[i] = i;
    }

    // Перебираем все перестановки
    do {
        // Вычисляем длину текущего маршрута
        int currentDistance = 0;
        for (int i = 0; i < n - 1; i++) {
            currentDistance += distances[cities[i]][cities[i+1]];
        }
        // Добавляем расстояние возврата в начальный город
        currentDistance += distances[cities[n-1]][cities[0]];

        result.permutationsCount++;

        // Обновляем лучший маршрут
        if (currentDistance < result.bestDistance) {
            result.bestDistance = currentDistance;
            result.bestPath = cities;
        }

    } while (std::next_permutation(cities.begin() + 1, cities.end()));

    return result;
}

void MainWindow::updateTableSize()
{
    int n = ui->spinCities->value();

    ui->tableDistances->setRowCount(n);
    ui->tableDistances->setColumnCount(n);

    QStringList headers;
    for (int i = 0; i < n; i++) {
        headers << QString("Город %1").arg(i + 1);
    }
    ui->tableDistances->setHorizontalHeaderLabels(headers);
    ui->tableDistances->setVerticalHeaderLabels(headers);

    distances.resize(n);
    for (int i = 0; i < n; i++) {
        distances[i].resize(n);
        for (int j = 0; j < n; j++) {
            if (i == j) {
                distances[i][j] = 0;
            } else if (distances[i][j] == 0) {
                distances[i][j] = 10 + std::rand() % 91;
            }
        }
    }

    updateDistanceMatrix();
}

void MainWindow::updateDistanceMatrix()
{
    int n = ui->spinCities->value();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            QTableWidgetItem *item = new QTableWidgetItem();
            if (i == j) {
                item->setText("0");
                item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            } else {
                item->setText(QString::number(distances[i][j]));
            }
            ui->tableDistances->setItem(i, j, item);
        }
    }

    ui->tableDistances->resizeColumnsToContents();
    ui->tableDistances->resizeRowsToContents();
}

void MainWindow::on_spinCities_valueChanged(int arg1)
{
    Q_UNUSED(arg1);
    updateTableSize();
}

void MainWindow::on_buttonRandom_clicked()
{
    int n = ui->spinCities->value();

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int dist = 10 + std::rand() % 91;
            distances[i][j] = dist;
            distances[j][i] = dist;
        }
    }

    updateDistanceMatrix();
}

void MainWindow::on_buttonClear_clicked()
{
    ui->textResult->clear();
}

void MainWindow::on_buttonSolve_clicked()
{
    int n = ui->spinCities->value();
    std::vector<std::vector<int>> distMatrix(n, std::vector<int>(n));

    // Считываем расстояния из таблицы
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            QTableWidgetItem *item = ui->tableDistances->item(i, j);
            if (item) {
                bool ok;
                int value = item->text().toInt(&ok);
                if (ok && value >= 0) {
                    distMatrix[i][j] = value;
                } else {
                    QMessageBox::warning(this, "Ошибка",
                        QString("Неверное значение в ячейке (%1, %2)").arg(i+1).arg(j+1));
                    return;
                }
            }
        }
    }

    ui->textResult->clear();
    ui->textResult->append("Решаем задачу коммивояжёра...\n");

    TSPResult result = solveTSP(distMatrix);

    // Вывод результата
    ui->textResult->append("=== РЕЗУЛЬТАТ ===");
    ui->textResult->append("");
    ui->textResult->append(QString("Проверено маршрутов: %1").arg(result.permutationsCount));
    ui->textResult->append(QString("Минимальное расстояние: %1").arg(result.bestDistance));
    ui->textResult->append("");
    ui->textResult->append("Оптимальный маршрут:");

    QString path;
    for (size_t i = 0; i < result.bestPath.size(); i++) {
        path += QString("Город %1").arg(result.bestPath[i] + 1);
        if (i < result.bestPath.size() - 1) {
            path += " → ";
        }
    }
    path += QString(" → Город %1").arg(result.bestPath[0] + 1);

    ui->textResult->append(path);
    ui->textResult->append("");

    ui->textResult->append("Детали маршрута:");
    int total = 0;
    for (size_t i = 0; i < result.bestPath.size(); i++) {
        int from = result.bestPath[i];
        int to = (i == result.bestPath.size() - 1) ? result.bestPath[0] : result.bestPath[i + 1];
        int dist = distMatrix[from][to];
        total += dist;
        ui->textResult->append(QString("  %1 → %2: %3")
            .arg(from + 1).arg(to + 1).arg(dist));
    }
    ui->textResult->append(QString("  Итого: %1").arg(total));
}
