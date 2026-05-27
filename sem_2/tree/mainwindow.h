#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <memory>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// Узел бинарного дерева
struct TreeNode {
    int data;
    std::shared_ptr<TreeNode> left;
    std::shared_ptr<TreeNode> right;

    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void on_addButton_clicked();        // Добавить элемент
    void on_removeButton_clicked();     // Удалить элемент
    void on_findButton_clicked();       // Найти элемент
    void on_clearButton_clicked();      // Очистить дерево
    void on_randomButton_clicked();     // Случайное дерево
    void on_inorderButton_clicked();    // Симметричный обход
    void on_preorderButton_clicked();   // Прямой обход
    void on_postorderButton_clicked();  // Обратный обход

private:
    Ui::MainWindow *ui;

    // Методы работы с деревом
    std::shared_ptr<TreeNode> insertNode(std::shared_ptr<TreeNode> root, int value);
    std::shared_ptr<TreeNode> deleteNode(std::shared_ptr<TreeNode> root, int value);
    std::shared_ptr<TreeNode> findMin(std::shared_ptr<TreeNode> root);
    bool findNode(std::shared_ptr<TreeNode> root, int value);
    void clearTree(std::shared_ptr<TreeNode> root);
    int getHeight(std::shared_ptr<TreeNode> root);

    // Обходы дерева
    void inorderTraversal(std::shared_ptr<TreeNode> root, std::vector<int>& result);
    void preorderTraversal(std::shared_ptr<TreeNode> root, std::vector<int>& result);
    void postorderTraversal(std::shared_ptr<TreeNode> root, std::vector<int>& result);

    // Отрисовка дерева
    void drawTree(QPainter& painter, std::shared_ptr<TreeNode> node, int x, int y, int xOffset, int level);
    void updateDisplay();

    // Данные
    std::shared_ptr<TreeNode> root;
    std::vector<int> traversalResult;
    QString currentTraversal;
};

#endif // MAINWINDOW_H
