#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <cstdlib>
#include <ctime>
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , root(nullptr)
{
    ui->setupUi(this);
    setFixedSize(1200, 700);
    std::srand(std::time(nullptr));

    // Начальное дерево для примера
    root = insertNode(root, 50);
    root = insertNode(root, 30);
    root = insertNode(root, 70);
    root = insertNode(root, 20);
    root = insertNode(root, 40);
    root = insertNode(root, 60);
    root = insertNode(root, 80);

    updateDisplay();
}

MainWindow::~MainWindow()
{
    clearTree(root);
    delete ui;
}

// Вставка узла
std::shared_ptr<TreeNode> MainWindow::insertNode(std::shared_ptr<TreeNode> root, int value)
{
    if (!root) {
        return std::make_shared<TreeNode>(value);
    }

    if (value < root->data) {
        root->left = insertNode(root->left, value);
    } else if (value > root->data) {
        root->right = insertNode(root->right, value);
    }

    return root;
}

// Поиск минимального узла
std::shared_ptr<TreeNode> MainWindow::findMin(std::shared_ptr<TreeNode> root)
{
    while (root && root->left) {
        root = root->left;
    }
    return root;
}

// Удаление узла
std::shared_ptr<TreeNode> MainWindow::deleteNode(std::shared_ptr<TreeNode> root, int value)
{
    if (!root) return nullptr;

    if (value < root->data) {
        root->left = deleteNode(root->left, value);
    } else if (value > root->data) {
        root->right = deleteNode(root->right, value);
    } else {
        // Узел найден
        if (!root->left) {
            return root->right;
        } else if (!root->right) {
            return root->left;
        }

        // Узел с двумя детьми
        auto minNode = findMin(root->right);
        root->data = minNode->data;
        root->right = deleteNode(root->right, minNode->data);
    }

    return root;
}

// Поиск узла
bool MainWindow::findNode(std::shared_ptr<TreeNode> root, int value)
{
    if (!root) return false;
    if (value == root->data) return true;
    if (value < root->data) return findNode(root->left, value);
    return findNode(root->right, value);
}

// Очистка дерева
void MainWindow::clearTree(std::shared_ptr<TreeNode> root)
{
    if (root) {
        clearTree(root->left);
        clearTree(root->right);
        root.reset();
    }
}

// Высота дерева
int MainWindow::getHeight(std::shared_ptr<TreeNode> root)
{
    if (!root) return 0;
    return 1 + std::max(getHeight(root->left), getHeight(root->right));
}

// Симметричный обход (in-order)
void MainWindow::inorderTraversal(std::shared_ptr<TreeNode> root, std::vector<int>& result)
{
    if (root) {
        inorderTraversal(root->left, result);
        result.push_back(root->data);
        inorderTraversal(root->right, result);
    }
}

// Прямой обход (pre-order)
void MainWindow::preorderTraversal(std::shared_ptr<TreeNode> root, std::vector<int>& result)
{
    if (root) {
        result.push_back(root->data);
        preorderTraversal(root->left, result);
        preorderTraversal(root->right, result);
    }
}

// Обратный обход (post-order)
void MainWindow::postorderTraversal(std::shared_ptr<TreeNode> root, std::vector<int>& result)
{
    if (root) {
        postorderTraversal(root->left, result);
        postorderTraversal(root->right, result);
        result.push_back(root->data);
    }
}

// Отрисовка дерева
void MainWindow::drawTree(QPainter& painter, std::shared_ptr<TreeNode> node,
                          int x, int y, int xOffset, int level)
{
    if (!node) return;

    // Рисуем круг с числом
    int radius = 25;
    painter.setBrush(QBrush(Qt::cyan));
    painter.setPen(QPen(Qt::black, 2));
    painter.drawEllipse(x - radius, y - radius, 2 * radius, 2 * radius);

    painter.setPen(QPen(Qt::black, 2));
    painter.setFont(QFont("Arial", 12, QFont::Bold));
    painter.drawText(x - 10, y + 6, QString::number(node->data));

    // Рисуем линии к детям
    if (node->left) {
        int childX = x - xOffset;
        int childY = y + 80;
        painter.setPen(QPen(Qt::red, 2));
        painter.drawLine(x, y + radius, childX, childY - radius);
        drawTree(painter, node->left, childX, childY, xOffset / 2, level + 1);
    }

    if (node->right) {
        int childX = x + xOffset;
        int childY = y + 80;
        painter.setPen(QPen(Qt::blue, 2));
        painter.drawLine(x, y + radius, childX, childY - radius);
        drawTree(painter, node->right, childX, childY, xOffset / 2, level + 1);
    }
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(rect(), Qt::white);

    if (root) {
        int startX = width() / 2;
        int startY = 80;
        int initialOffset = 200;

        drawTree(painter, root, startX, startY, initialOffset, 0);

        // Информация о дереве
        painter.setPen(QPen(Qt::black, 1));
        painter.setFont(QFont("Arial", 10));
        painter.drawText(10, 30, QString("Высота дерева: %1").arg(getHeight(root)));
        painter.drawText(10, 50, QString("Количество узлов: %1").arg(
            [this](){ int c=0; std::function<void(std::shared_ptr<TreeNode>)> count=[&](std::shared_ptr<TreeNode> n){
                if(!n) return; c++; count(n->left); count(n->right);
            }; count(root); return c; }()));

        // Результаты обхода
        if (!traversalResult.empty()) {
            painter.setPen(QPen(Qt::darkBlue, 1));
            painter.drawText(10, height() - 80,
                            QString("%1 обход: ").arg(currentTraversal));

            QString resultStr;
            for (int val : traversalResult) {
                resultStr += QString::number(val) + " ";
            }
            painter.drawText(10, height() - 55, resultStr);
        }
    } else {
        painter.drawText(width()/2 - 100, height()/2, "Дерево пусто");
    }

    // Легенда
    painter.setPen(QPen(Qt::black, 1));
    painter.drawText(10, height() - 25, "Красные линии - левые связи | Синие линии - правые связи");
}

void MainWindow::updateDisplay()
{
    update();  // Перерисовываем
}

// Слоты для кнопок
void MainWindow::on_addButton_clicked()
{
    bool ok;
    int value = ui->lineEdit->text().toInt(&ok);

    if (!ok) {
        QMessageBox::warning(this, "Ошибка", "Введите целое число!");
        return;
    }

    if (findNode(root, value)) {
        QMessageBox::information(this, "Информация",
                                QString("Число %1 уже есть в дереве!").arg(value));
        return;
    }

    root = insertNode(root, value);
    traversalResult.clear();
    updateDisplay();
    ui->lineEdit->clear();
}

void MainWindow::on_removeButton_clicked()
{
    bool ok;
    int value = ui->lineEdit->text().toInt(&ok);

    if (!ok) {
        QMessageBox::warning(this, "Ошибка", "Введите целое число!");
        return;
    }

    if (!findNode(root, value)) {
        QMessageBox::information(this, "Информация",
                                QString("Число %1 не найдено в дереве!").arg(value));
        return;
    }

    root = deleteNode(root, value);
    traversalResult.clear();
    updateDisplay();
    ui->lineEdit->clear();
}

void MainWindow::on_findButton_clicked()
{
    bool ok;
    int value = ui->lineEdit->text().toInt(&ok);

    if (!ok) {
        QMessageBox::warning(this, "Ошибка", "Введите целое число!");
        return;
    }

    if (findNode(root, value)) {
        QMessageBox::information(this, "Результат",
                                QString("Число %1 найдено в дереве!").arg(value));
    } else {
        QMessageBox::information(this, "Результат",
                                QString("Число %1 не найдено в дереве!").arg(value));
    }
}

void MainWindow::on_clearButton_clicked()
{
    clearTree(root);
    root = nullptr;
    traversalResult.clear();
    updateDisplay();
}

void MainWindow::on_randomButton_clicked()
{
    clearTree(root);
    root = nullptr;

    int numNodes = 7 + std::rand() % 8;  // 7-15 узлов

    for (int i = 0; i < numNodes; i++) {
        int value = std::rand() % 100;
        root = insertNode(root, value);
    }

    traversalResult.clear();
    updateDisplay();
}

void MainWindow::on_inorderButton_clicked()
{
    traversalResult.clear();
    inorderTraversal(root, traversalResult);
    currentTraversal = "Симметричный (in-order)";
    updateDisplay();

    QString resultStr;
    for (int val : traversalResult) {
        resultStr += QString::number(val) + " ";
    }
    ui->textEdit->setText(resultStr);
}

void MainWindow::on_preorderButton_clicked()
{
    traversalResult.clear();
    preorderTraversal(root, traversalResult);
    currentTraversal = "Прямой (pre-order)";
    updateDisplay();

    QString resultStr;
    for (int val : traversalResult) {
        resultStr += QString::number(val) + " ";
    }
    ui->textEdit->setText(resultStr);
}

void MainWindow::on_postorderButton_clicked()
{
    traversalResult.clear();
    postorderTraversal(root, traversalResult);
    currentTraversal = "Обратный (post-order)";
    updateDisplay();

    QString resultStr;
    for (int val : traversalResult) {
        resultStr += QString::number(val) + " ";
    }
    ui->textEdit->setText(resultStr);
}
