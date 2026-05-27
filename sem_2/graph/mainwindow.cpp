#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
#include <QDebug>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <QPen>
#include <QBrush>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , showBestPath(false)
    , minDistance(0)
{
    ui->setupUi(this);

    // Устанавливаем размер окна для рисования
    setFixedSize(900, 700);

    // Инициализация генератора случайных чисел
    std::srand(std::time(nullptr));

    // Создаём несколько тестовых городов для примера
    cities.append({{200, 200}, 0});
    cities.append({{400, 150}, 1});
    cities.append({{600, 250}, 2});
    cities.append({{550, 450}, 3});
    cities.append({{350, 500}, 4});
    cities.append({{250, 400}, 5});

    updateGraph();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Заливаем фон
    painter.fillRect(rect(), Qt::white);

    // Рисуем сетку для удобства
    painter.setPen(QPen(Qt::lightGray, 1, Qt::DotLine));
    for (int i = 0; i < width(); i += 50) {
        painter.drawLine(i, 0, i, height());
        painter.drawLine(0, i, width(), i);
    }

    // Если есть лучший путь - рисуем его красными линиями
    if (showBestPath && bestPath.size() >= 2) {
        painter.setPen(QPen(Qt::red, 3, Qt::SolidLine));
        for (size_t i = 0; i < bestPath.size(); i++) {
            int from = bestPath[i];
            int to = (i == bestPath.size() - 1) ? bestPath[0] : bestPath[i + 1];

            QPoint p1 = cities[from].position;
            QPoint p2 = cities[to].position;
            painter.drawLine(p1, p2);
        }
    }

    // Рисуем все рёбра между городами (серые линии)
    painter.setPen(QPen(Qt::gray, 1, Qt::SolidLine));
    for (int i = 0; i < cities.size(); i++) {
        for (int j = i + 1; j < cities.size(); j++) {
            painter.drawLine(cities[i].position, cities[j].position);

            // Рисуем расстояние над ребром
            double dist = calculateDistance(cities[i], cities[j]);
            QPoint midPoint = (cities[i].position + cities[j].position) / 2;
            painter.setPen(QPen(Qt::darkGray, 1));
            painter.drawText(midPoint, QString::number((int)dist));
        }
    }

    // Рисуем города
    for (int i = 0; i < cities.size(); i++) {
        bool isInBestPath = false;
        if (showBestPath) {
            for (int cityId : bestPath) {
                if (cityId == i) {
                    isInBestPath = true;
                    break;
                }
            }
        }
        drawCity(painter, cities[i], isInBestPath);

        // Рисуем номер города
        painter.setPen(QPen(Qt::white, 2));
        painter.setFont(QFont("Arial", 12, QFont::Bold));
        painter.drawText(cities[i].position.x() - 8, cities[i].position.y() + 5,
                        QString::number(i + 1));
    }

    // Выводим информацию
    painter.setPen(QPen(Qt::black, 2));
    painter.setFont(QFont("Arial", 10));
    painter.drawText(10, 30, QString("Городов: %1").arg(cities.size()));

    if (showBestPath && minDistance > 0) {
        painter.setPen(QPen(Qt::red, 2));
        painter.drawText(10, 55, QString("Минимальный маршрут: %1").arg(minDistance));

        // Рисуем путь текстом
        QString pathText = "Путь: ";
        for (size_t i = 0; i < bestPath.size(); i++) {
            pathText += QString::number(bestPath[i] + 1);
            if (i < bestPath.size() - 1) pathText += " → ";
        }
        pathText += " → " + QString::number(bestPath[0] + 1);
        painter.drawText(10, 80, pathText);
    } else if (cities.size() >= 3) {
        painter.setPen(QPen(Qt::gray, 2));
        painter.drawText(10, 55, "Нажмите 'Решить задачу'");
    }

    // Инструкция
    painter.setPen(QPen(Qt::darkBlue, 1));
    painter.setFont(QFont("Arial", 9));
    painter.drawText(10, height() - 30,
                    "Инструкция: Кликните мышкой для добавления города | Для 3-8 городов");
}

void MainWindow::drawCity(QPainter& painter, const City& city, bool isSelected)
{
    // Выбираем цвет города
    QColor cityColor = isSelected ? Qt::red : Qt::blue;

    // Рисуем круг города
    painter.setBrush(QBrush(cityColor));
    painter.setPen(QPen(Qt::black, 2));
    painter.drawEllipse(city.position.x() - 15, city.position.y() - 15, 30, 30);

    // Добавляем свечение для выбранных городов
    if (isSelected) {
        painter.setBrush(QBrush(QColor(255, 0, 0, 50)));
        painter.drawEllipse(city.position.x() - 20, city.position.y() - 20, 40, 40);
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    // Добавляем новый город по клику (не больше 8 городов)
    if (cities.size() < 8) {
        City newCity;
        newCity.position = event->pos();
        newCity.id = cities.size();
        cities.append(newCity);

        showBestPath = false;  // Скрываем старый путь
        updateGraph();
    } else {
        QMessageBox::information(this, "Лимит городов",
                                "Максимум 8 городов для быстрого расчёта!");
    }
}

void MainWindow::updateGraph()
{
    update();  // Перерисовываем окно
}

double MainWindow::calculateDistance(const City& c1, const City& c2)
{
    int dx = c1.position.x() - c2.position.x();
    int dy = c1.position.y() - c2.position.y();
    return std::sqrt(dx*dx + dy*dy);
}

TSPResult MainWindow::solveTSP()
{
    TSPResult result;
    result.bestDistance = std::numeric_limits<int>::max();
    result.permutationsCount = 0;

    int n = cities.size();
    if (n < 2) return result;

    // Создаём матрицу расстояний
    std::vector<std::vector<int>> distances(n, std::vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                distances[i][j] = 0;
            } else {
                distances[i][j] = (int)calculateDistance(cities[i], cities[j]);
            }
        }
    }

    // Создаём начальный маршрут
    std::vector<int> cities_order(n);
    for (int i = 0; i < n; i++) {
        cities_order[i] = i;
    }

    // Полный перебор всех перестановок
    do {
        int currentDistance = 0;
        for (int i = 0; i < n - 1; i++) {
            currentDistance += distances[cities_order[i]][cities_order[i+1]];
        }
        currentDistance += distances[cities_order[n-1]][cities_order[0]];

        result.permutationsCount++;

        if (currentDistance < result.bestDistance) {
            result.bestDistance = currentDistance;
            result.bestPath = cities_order;
        }

    } while (std::next_permutation(cities_order.begin() + 1, cities_order.end()));

    return result;
}

void MainWindow::on_solveButton_clicked()
{
    if (cities.size() < 3) {
        QMessageBox::warning(this, "Мало городов",
                            "Добавьте хотя бы 3 города для решения задачи!");
        return;
    }

    if (cities.size() > 9) {
        QMessageBox::warning(this, "Слишком много городов",
                            "Для 9+ городов расчёт будет очень долгим!\n"
                            "Рекомендуется 3-8 городов.");
        return;
    }

    // Решаем задачу
    TSPResult result = solveTSP();

    // Сохраняем результат
    bestPath = result.bestPath;
    minDistance = result.bestDistance;
    showBestPath = true;

    // Выводим информацию в консоль
    qDebug() << "========== РЕЗУЛЬТАТ ==========";
    qDebug() << "Проверено маршрутов:" << result.permutationsCount;
    qDebug() << "Минимальное расстояние:" << result.bestDistance;
    qDebug() << "Лучший маршрут:";
    for (int city : bestPath) {
        qDebug() << "Город" << (city + 1);
    }
    qDebug() << "================================";

    // Показываем сообщение
    QMessageBox::information(this, "Задача решена!",
                            QString("Найден оптимальный маршрут!\n"
                                    "Количество проверенных маршрутов: %1\n"
                                    "Минимальное расстояние: %2")
                            .arg(result.permutationsCount)
                            .arg(result.bestDistance));

    updateGraph();  // Перерисовываем с красным маршрутом
}

void MainWindow::on_clearButton_clicked()
{
    cities.clear();
    showBestPath = false;
    minDistance = 0;
    bestPath.clear();
    updateGraph();
}

void MainWindow::on_randomButton_clicked()
{
    // Генерируем случайные города (5-7 городов)
    int numCities = 5 + std::rand() % 3;
    cities.clear();

    for (int i = 0; i < numCities; i++) {
        City newCity;
        // Случайные координаты с отступами от краёв
        newCity.position.setX(50 + std::rand() % (width() - 100));
        newCity.position.setY(50 + std::rand() % (height() - 150));
        newCity.id = i;
        cities.append(newCity);
    }

    showBestPath = false;
    updateGraph();
}

void MainWindow::on_removeLastButton_clicked()
{
    if (!cities.isEmpty()) {
        cities.removeLast();
        showBestPath = false;
        updateGraph();
    }
}
