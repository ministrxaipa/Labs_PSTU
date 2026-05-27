#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QVector>
#include <vector>
#include <algorithm>
#include <limits>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// Структура для хранения результата (добавлена прямо в заголовочный файл)
struct TSPResult {
    std::vector<int> bestPath;  // Лучший маршрут (индексы городов)
    int bestDistance;           // Минимальное расстояние
    int permutationsCount;      // Количество проверенных перестановок
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_buttonSolve_clicked();
    void on_buttonRandom_clicked();
    void on_buttonClear_clicked();
    void on_spinCities_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;

    // Методы
    void updateTableSize();
    void updateDistanceMatrix();
    void displayResult(const TSPResult& result);
    TSPResult solveTSP(const std::vector<std::vector<int>>& distances); // Алгоритм внутри класса

    // Данные
    QVector<QVector<int>> distances;
};

#endif // MAINWINDOW_H
