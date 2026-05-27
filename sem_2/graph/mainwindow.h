#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QPoint>
#include <QPainter>
#include <vector>
#include <algorithm>
#include <limits>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// Структура города
struct City {
    QPoint position;  // Позиция на экране
    int id;           // Номер города
};

// Результат решения
struct TSPResult {
    std::vector<int> bestPath;  // Лучший маршрут
    int bestDistance;           // Минимальное расстояние
    int permutationsCount;      // Количество проверенных маршрутов
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event) override;  // Отрисовка графа
    void mousePressEvent(QMouseEvent *event) override;  // Добавление городов кликом

private slots:
    void on_solveButton_clicked();      // Решить задачу
    void on_clearButton_clicked();      // Очистить все
    void on_randomButton_clicked();     // Случайные города
    void on_removeLastButton_clicked(); // Удалить последний город

private:
    Ui::MainWindow *ui;

    // Методы
    void updateGraph();                          // Перерисовать граф
    double calculateDistance(const City& c1, const City& c2);  // Расстояние между городами
    TSPResult solveTSP();                        // Решение задачи коммивояжёра
    void drawCity(QPainter& painter, const City& city, bool isSelected);  // Отрисовка города

    // Данные
    QVector<City> cities;        // Список городов
    std::vector<int> bestPath;   // Лучший найденный путь
    bool showBestPath;           // Показывать ли лучший путь
    int minDistance;             // Минимальная найденная дистанция
};

#endif // MAINWINDOW_H
