#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include <QLineEdit>
#include <QMessageBox>
#include <QInputDialog>
#include <QRandomGenerator>
#include <QGroupBox>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QTimer>
#include <random>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), lastCardIndex(-1),
    gameCurrentIndex(0), gameScore(0), gameTotal(0), gameTimeLeft(10) {

    setWindowTitle("Флеш-карточки - Изучение английского");
    resize(1000, 600);

    loadDaysData();

    QWidget* central = new QWidget;
    QHBoxLayout* mainLayout = new QHBoxLayout(central);
    mainLayout->setSpacing(20);

    // Левая панель
    QWidget* leftPanel = new QWidget;
    QVBoxLayout* leftLayout = new QVBoxLayout(leftPanel);

    QLabel* titleLabel = new QLabel("МОИ НАБОРЫ");
    titleLabel->setStyleSheet("font-size: 16px; font-weight: bold;");
    leftLayout->addWidget(titleLabel);

    setList = new QListWidget;
    setList->setMinimumWidth(250);
    setList->setMaximumWidth(300);
    leftLayout->addWidget(setList);

    QPushButton* addSetBtn = new QPushButton("+ ДОБАВИТЬ СВОЙ НАБОР");
    addSetBtn->setStyleSheet("background-color: #3498db; color: white; padding: 10px; font-weight: bold; border-radius: 5px;");
    leftLayout->addWidget(addSetBtn);

    deleteBtn = new QPushButton("- УДАЛИТЬ СВОЙ НАБОР");
    deleteBtn->setStyleSheet("background-color: #9b59b6; color: white; padding: 10px; font-weight: bold; border-radius: 5px;");
    deleteBtn->setEnabled(false);
    leftLayout->addWidget(deleteBtn);

    QPushButton* gameBtn = new QPushButton("ИГРА: БЫСТРЫЙ ПЕРЕВОД");
    gameBtn->setStyleSheet("background-color: #e67e22; color: white; padding: 10px; font-weight: bold; border-radius: 5px; margin-top: 10px;");
    leftLayout->addWidget(gameBtn);

    // Статистика
    QGroupBox* statsGroup = new QGroupBox("");
    QVBoxLayout* statsLayout = new QVBoxLayout(statsGroup);

    daysLabel = new QLabel();
    daysLabel->setStyleSheet("font-size: 14px; font-weight: bold; color: #2c3e50; padding: 5px;");
    statsLayout->addWidget(daysLabel);

    progressLabel = new QLabel("Прогресс:");
    progressLabel->setStyleSheet("font-size: 12px; margin-top: 10px;");
    statsLayout->addWidget(progressLabel);

    progressBar = new QProgressBar;
    progressBar->setMinimum(0);
    progressBar->setMaximum(100);
    progressBar->setValue(0);
    statsLayout->addWidget(progressBar);

    statsLabel = new QLabel("Выберите набор");
    statsLabel->setStyleSheet("font-size: 12px; color: #7f8c8d; margin-top: 5px;");
    statsLayout->addWidget(statsLabel);

    leftLayout->addWidget(statsGroup);
    leftLayout->addStretch();

    // Правая панель (основная)
    rightPanel = new QWidget;
    QVBoxLayout* rightLayout = new QVBoxLayout(rightPanel);

    QGroupBox* cardBox = new QGroupBox("КАРТОЧКА");
    QVBoxLayout* cardLayout = new QVBoxLayout(cardBox);

    questionLabel = new QLabel("Нажмите на набор слева");
    questionLabel->setAlignment(Qt::AlignCenter);
    questionLabel->setWordWrap(true);
    questionLabel->setStyleSheet("font-size: 28px; font-weight: bold; padding: 60px; background-color: #f0f0f0; border-radius: 15px; margin: 10px;");
    cardLayout->addWidget(questionLabel);

    answerInput = new QLineEdit;
    answerInput->setPlaceholderText("Введите ответ здесь...");
    answerInput->setEnabled(false);
    answerInput->setStyleSheet("font-size: 18px; padding: 15px; border: 2px solid #ccc; border-radius: 10px; margin: 10px;");
    cardLayout->addWidget(answerInput);

    QHBoxLayout* btnLayout = new QHBoxLayout;
    btnLayout->setSpacing(15);

    checkBtn = new QPushButton("Проверить");
    dontKnowBtn = new QPushButton("Не знаю");
    finishBtn = new QPushButton("Завершить");

    checkBtn->setStyleSheet("background-color: #27ae60; color: white; padding: 12px; font-weight: bold; border-radius: 8px;");
    dontKnowBtn->setStyleSheet("background-color: #e74c3c; color: white; padding: 12px; font-weight: bold; border-radius: 8px;");
    finishBtn->setStyleSheet("background-color: #95a5a6; color: white; padding: 12px; font-weight: bold; border-radius: 8px;");

    checkBtn->setEnabled(false);
    dontKnowBtn->setEnabled(false);
    finishBtn->setEnabled(false);

    btnLayout->addWidget(checkBtn);
    btnLayout->addWidget(dontKnowBtn);
    btnLayout->addWidget(finishBtn);
    cardLayout->addLayout(btnLayout);

    rightLayout->addWidget(cardBox);

    mainLayout->addWidget(leftPanel, 1);
    mainLayout->addWidget(rightPanel, 3);

    // Создание игры
    gameWidget = new QWidget(this);
    QVBoxLayout* gameLayout = new QVBoxLayout(gameWidget);

    QLabel* gameTitle = new QLabel("ИГРА: БЫСТРЫЙ ПЕРЕВОД");
    gameTitle->setAlignment(Qt::AlignCenter);
    gameTitle->setStyleSheet("font-size: 24px; font-weight: bold; color: #e67e22; margin: 20px;");
    gameLayout->addWidget(gameTitle);

    gameTimerLabel = new QLabel("Время: 10 сек");
    gameTimerLabel->setAlignment(Qt::AlignCenter);
    gameTimerLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #e74c3c;");
    gameLayout->addWidget(gameTimerLabel);

    gameScoreLabel = new QLabel("Счет: 0");
    gameScoreLabel->setAlignment(Qt::AlignCenter);
    gameScoreLabel->setStyleSheet("font-size: 16px;");
    gameLayout->addWidget(gameScoreLabel);

    gameQuestionLabel = new QLabel();
    gameQuestionLabel->setAlignment(Qt::AlignCenter);
    gameQuestionLabel->setStyleSheet("font-size: 28px; font-weight: bold; padding: 40px; background-color: #f0f0f0; border-radius: 15px; margin: 20px;");
    gameQuestionLabel->setWordWrap(true);
    gameLayout->addWidget(gameQuestionLabel);

    gameAnswerInput = new QLineEdit;
    gameAnswerInput->setPlaceholderText("Введите перевод...");
    gameAnswerInput->setStyleSheet("font-size: 18px; padding: 15px; border: 2px solid #ccc; border-radius: 10px; margin: 10px;");
    gameLayout->addWidget(gameAnswerInput);

    QHBoxLayout* gameBtnLayout = new QHBoxLayout;
    gameCheckBtn = new QPushButton("ПРОВЕРИТЬ");
    gameDontKnowBtn = new QPushButton("НЕ ЗНАЮ");
    gameCheckBtn->setStyleSheet("background-color: #27ae60; color: white; padding: 12px; font-weight: bold; font-size: 14px; border-radius: 8px;");
    gameDontKnowBtn->setStyleSheet("background-color: #e74c3c; color: white; padding: 12px; font-weight: bold; font-size: 14px; border-radius: 8px;");
    gameBtnLayout->addWidget(gameCheckBtn);
    gameBtnLayout->addWidget(gameDontKnowBtn);
    gameLayout->addLayout(gameBtnLayout);

    QPushButton* gameCloseBtn = new QPushButton("ЗАКРЫТЬ ИГРУ");
    gameCloseBtn->setStyleSheet("background-color: #95a5a6; color: white; padding: 10px; margin-top: 20px; font-weight: bold; border-radius: 8px;");
    gameLayout->addWidget(gameCloseBtn);

    mainLayout->addWidget(gameWidget);
    gameWidget->hide();

    gameTimer = new QTimer(this);

    setCentralWidget(central);

    // Подключаем сигналы
    connect(setList, &QListWidget::itemClicked, this, &MainWindow::onSetSelected);
    connect(checkBtn, &QPushButton::clicked, this, &MainWindow::onCheckAnswer);
    connect(dontKnowBtn, &QPushButton::clicked, this, &MainWindow::onDontKnow);
    connect(finishBtn, &QPushButton::clicked, this, &MainWindow::onFinish);
    connect(addSetBtn, &QPushButton::clicked, this, &MainWindow::onAddOwnSet);
    connect(deleteBtn, &QPushButton::clicked, this, &MainWindow::onDeleteSet);
    connect(gameBtn, &QPushButton::clicked, this, &MainWindow::startGame);
    connect(gameCheckBtn, &QPushButton::clicked, this, &MainWindow::onGameCheck);
    connect(gameDontKnowBtn, &QPushButton::clicked, this, &MainWindow::onGameDontKnow);
    connect(gameCloseBtn, &QPushButton::clicked, this, &MainWindow::closeGame);
    connect(gameTimer, &QTimer::timeout, this, &MainWindow::updateGameTimer);

    loadEnglishToRussian();
    loadRussianToEnglish();
    loadCustomSetsFromFiles();
    updateDaysCounter();
}

void MainWindow::loadEnglishToRussian() {
    QListWidgetItem* item = new QListWidgetItem("АНГЛИЙСКИЙ -> РУССКИЙ (30 слов)");
    item->setData(Qt::UserRole, "base");
    setList->addItem(item);
}

void MainWindow::loadRussianToEnglish() {
    QListWidgetItem* item = new QListWidgetItem("РУССКИЙ -> АНГЛИЙСКИЙ (30 слов)");
    item->setData(Qt::UserRole, "base");
    setList->addItem(item);
}

void MainWindow::loadCustomSetsFromFiles() {
    QDir dir(".");
    QStringList files = dir.entryList(QStringList() << "*.txt", QDir::Files);

    for (QString file : files) {
        QString setName = file.left(file.length() - 4);
        if (setName != "eng2rus" && setName != "rus2eng" && setName != "days_data") {
            QListWidgetItem* item = new QListWidgetItem(setName);
            item->setData(Qt::UserRole, "custom");
            setList->addItem(item);
        }
    }
}

void MainWindow::addToSetList(QString name) {
    QListWidgetItem* item = new QListWidgetItem(name);
    item->setData(Qt::UserRole, "custom");
    setList->addItem(item);
}

void MainWindow::onSetSelected(QListWidgetItem* item) {
    // Закрываем игру если открыта
    if (gameWidget && gameWidget->isVisible()) {
        closeGame();
    }

    QString selected = item->text();
    QString type = item->data(Qt::UserRole).toString();

    deleteBtn->setEnabled(type == "custom");

    // Если уже открыт этот же набор, ничего не делае
    if (currentSetName == selected && !currentCards.isEmpty()) {
        return;
    }

    currentCards.clear();
    currentSetName = selected;

    if (selected == "АНГЛИЙСКИЙ -> РУССКИЙ (30 слов)") {
        QStringList eng = {"Apple", "Car", "House", "Dog", "Cat", "Book", "Pen", "Table", "Chair", "Window", "Door", "Sun", "Moon", "Star", "Water", "Fire", "Earth", "Sky", "Tree", "Flower", "Bird", "Fish", "Happy", "Sad", "Big", "Small", "Fast", "Slow", "New", "Old"};
        QStringList rus = {"Яблоко", "Машина", "Дом", "Собака", "Кошка", "Книга", "Ручка", "Стол", "Стул", "Окно", "Дверь", "Солнце", "Луна", "Звезда", "Вода", "Огонь", "Земля", "Небо", "Дерево", "Цветок", "Птица", "Рыба", "Счастливый", "Грустный", "Большой", "Маленький", "Быстрый", "Медленный", "Новый", "Старый"};
        for (int i = 0; i < 30; i++) {
            currentCards.append(Card(eng[i], rus[i]));
        }
    }
    else if (selected == "РУССКИЙ -> АНГЛИЙСКИЙ (30 слов)") {
        QStringList rus = {"Яблоко", "Машина", "Дом", "Собака", "Кошка", "Книга", "Ручка", "Стол", "Стул", "Окно", "Дверь", "Солнце", "Луна", "Звезда", "Вода", "Огонь", "Земля", "Небо", "Дерево", "Цветок", "Птица", "Рыба", "Счастливый", "Грустный", "Большой", "Маленький", "Быстрый", "Медленный", "Новый", "Старый"};
        QStringList eng = {"Apple", "Car", "House", "Dog", "Cat", "Book", "Pen", "Table", "Chair", "Window", "Door", "Sun", "Moon", "Star", "Water", "Fire", "Earth", "Sky", "Tree", "Flower", "Bird", "Fish", "Happy", "Sad", "Big", "Small", "Fast", "Slow", "New", "Old"};
        for (int i = 0; i < 30; i++) {
            currentCards.append(Card(rus[i], eng[i]));
        }
    }
    else {
        loadCustomSet(selected);
    }

    lastCardIndex = -1;
    updateActiveCards();
    showCurrentCard();

    answerInput->setEnabled(true);
    checkBtn->setEnabled(true);
    dontKnowBtn->setEnabled(true);
    finishBtn->setEnabled(true);
    answerInput->clear();
    answerInput->setFocus();
}

void MainWindow::updateActiveCards() {
    activeCards.clear();
    for (int i = 0; i < currentCards.size(); i++) {
        if (!currentCards[i].learned) {
            activeCards.append(i);
        }
    }
}

int MainWindow::getNextCard() {
    if (activeCards.isEmpty()) return -1;

    if (activeCards.size() == 1) {
        return activeCards[0];
    }

    QVector<int> weights;
    int totalWeight = 0;

    for (int i = 0; i < activeCards.size(); i++) {
        int idx = activeCards[i];
        int weight = currentCards[idx].errors * 15 + 5;
        if (currentCards[idx].correctCount >= 3) {
            weight = 1;
        }
        if (idx == lastCardIndex) {
            weight = 0;
        }
        weights.append(weight);
        totalWeight += weight;
    }

    if (totalWeight == 0) {
        for (int i = 0; i < activeCards.size(); i++) {
            int idx = activeCards[i];
            if (idx != lastCardIndex) {
                return idx;
            }
        }
        return activeCards[0];
    }

    int random = QRandomGenerator::global()->bounded(totalWeight);
    int sum = 0;
    for (int i = 0; i < weights.size(); i++) {
        sum += weights[i];
        if (random < sum) {
            return activeCards[i];
        }
    }
    return activeCards[0];
}

void MainWindow::showCurrentCard() {
    if (activeCards.isEmpty()) {
        questionLabel->setText("ПОЗДРАВЛЯЮ! Вы выучили все слова! Можете выбрать другой набор.");
        answerInput->setEnabled(false);
        checkBtn->setEnabled(false);
        dontKnowBtn->setEnabled(false);
        updateProgress();
        return;
    }

    currentCardIndex = getNextCard();
    lastCardIndex = currentCardIndex;
    questionLabel->setText(currentCards[currentCardIndex].question);
    answerInput->clear();
    answerInput->setFocus();
    updateProgress();
}

void MainWindow::onCheckAnswer() {
    QString userAnswer = answerInput->text().trimmed();
    if (userAnswer.isEmpty()) {
        QMessageBox::warning(this, "Внимание", "Введите ответ!");
        return;
    }

    QString correctAnswer = currentCards[currentCardIndex].answer;

    if (userAnswer.compare(correctAnswer, Qt::CaseInsensitive) == 0) {
        QMessageBox::information(this, "Правильно!", "Верно!");
        currentCards[currentCardIndex].correctCount++;

        if (currentCards[currentCardIndex].correctCount >= 7) {
            currentCards[currentCardIndex].learned = true;
            QMessageBox::information(this, "Отлично!", "Слово выучено!");
        }
        updateActiveCards();
        showCurrentCard();
    } else {
        QMessageBox::information(this, "Ошибка!", "Неправильно! Правильный ответ: " + correctAnswer);
        currentCards[currentCardIndex].errors++;
        currentCards[currentCardIndex].correctCount = 0;
        updateActiveCards();
        showCurrentCard();
    }
}

void MainWindow::onDontKnow() {
    QString correctAnswer = currentCards[currentCardIndex].answer;
    QMessageBox::information(this, "Правильный ответ", "Правильный ответ: " + correctAnswer + " Слово будет повторяться чаще!");
    currentCards[currentCardIndex].errors++;
    currentCards[currentCardIndex].correctCount = 0;
    updateActiveCards();
    showCurrentCard();
}

void MainWindow::onFinish() {
    QMessageBox msgBox;
    msgBox.setWindowTitle("Завершить");
    msgBox.setText("Завершить обучение?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setButtonText(QMessageBox::Yes, "Да");
    msgBox.setButtonText(QMessageBox::No, "Нет");

    int reply = msgBox.exec();

    if (reply == QMessageBox::Yes) {
        questionLabel->setText("Выберите набор для изучения");
        answerInput->setEnabled(false);
        checkBtn->setEnabled(false);
        dontKnowBtn->setEnabled(false);
        finishBtn->setEnabled(false);
        deleteBtn->setEnabled(false);
        currentCards.clear();
        activeCards.clear();
        currentSetName = "";
        lastCardIndex = -1;
        updateProgress();
    }
}

void MainWindow::onAddOwnSet() {
    bool ok;
    QString setName = QInputDialog::getText(this, "Новый набор", "Введите название набора (до 50 карточек):", QLineEdit::Normal, "", &ok);

    if (!ok || setName.isEmpty()) return;

    QVector<Card> newCards;
    int cardCount = 0;

    while (cardCount < 50) {
        QString question = QInputDialog::getText(this, QString("Карточка %1 из 50").arg(cardCount + 1), "Введите слово или вопрос (Cancel - закончить):", QLineEdit::Normal, "", &ok);
        if (!ok || question.isEmpty()) break;

        QString answer = QInputDialog::getText(this, "Ответ", "Введите перевод или ответ:", QLineEdit::Normal, "", &ok);
        if (!ok || answer.isEmpty()) {
            QMessageBox::warning(this, "Ошибка", "Ответ не может быть пустым!");
            continue;
        }

        newCards.append(Card(question, answer));
        cardCount++;
    }

    if (newCards.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Набор не может быть пустым!");
        return;
    }

    QFile file(setName + ".txt");
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream out(&file);
        out << newCards.size() << "\n";
        for (int i = 0; i < newCards.size(); i++) {
            out << newCards[i].question << "\n";
            out << newCards[i].answer << "\n";
            out << "0\n";
            out << "0\n";
            out << "0\n";
        }
        file.close();
    }

    QListWidgetItem* item = new QListWidgetItem(setName);
    item->setData(Qt::UserRole, "custom");
    setList->addItem(item);

    QMessageBox::information(this, "Успех", QString("Набор '%1' создан! Добавлено карточек: %2").arg(setName).arg(cardCount));
}

void MainWindow::onDeleteSet() {
    if (currentSetName.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Выберите набор для удаления!");
        return;
    }

    if (currentSetName == "АНГЛИЙСКИЙ -> РУССКИЙ (30 слов)" || currentSetName == "РУССКИЙ -> АНГЛИЙСКИЙ (30 слов)") {
        QMessageBox::warning(this, "Ошибка", "Нельзя удалить базовый набор!");
        return;
    }

    QMessageBox msgBox;
    msgBox.setWindowTitle("Удалить набор");
    msgBox.setText(QString("Вы уверены, что хотите удалить набор '%1'?").arg(currentSetName));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setButtonText(QMessageBox::Yes, "Да");
    msgBox.setButtonText(QMessageBox::No, "Нет");

    int reply = msgBox.exec();

    if (reply == QMessageBox::Yes) {
        QFile::remove(currentSetName + ".txt");

        for (int i = 0; i < setList->count(); i++) {
            QListWidgetItem* item = setList->item(i);
            if (item->text() == currentSetName) {
                delete setList->takeItem(i);
                break;
            }
        }

        currentCards.clear();
        activeCards.clear();
        currentSetName = "";
        lastCardIndex = -1;
        questionLabel->setText("Выберите набор для изучения");
        answerInput->setEnabled(false);
        checkBtn->setEnabled(false);
        dontKnowBtn->setEnabled(false);
        finishBtn->setEnabled(false);
        deleteBtn->setEnabled(false);
        updateProgress();
        QMessageBox::information(this, "Успех", "Набор удален!");
    }
}

void MainWindow::loadCustomSet(QString name) {
    currentCards.clear();
    QFile file(name + ".txt");

    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        int size = in.readLine().toInt();
        for (int i = 0; i < size; i++) {
            QString q = in.readLine();
            if (q.isEmpty()) break;
            QString a = in.readLine();
            int err = in.readLine().toInt();
            int corr = in.readLine().toInt();
            bool learned = (in.readLine() == "1");

            Card c(q, a);
            c.errors = err;
            c.correctCount = corr;
            c.learned = learned;
            currentCards.append(c);
        }
        file.close();
    }
}

void MainWindow::updateProgress() {
    if (currentCards.isEmpty()) {
        progressBar->setValue(0);
        statsLabel->setText("Выберите набор");
        return;
    }

    int total = currentCards.size();
    int learned = 0;
    for (int i = 0; i < total; i++) {
        if (currentCards[i].learned) learned++;
    }

    int percent = (total > 0) ? (learned * 100 / total) : 0;
    progressBar->setValue(percent);
    statsLabel->setText(QString("Выучено: %1 из %2 слов (%3%)").arg(learned).arg(total).arg(percent));
}

void MainWindow::updateDaysCounter() {
    loadDaysData();

    int totalDays = 0;
    QFile file("days_data.txt");
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        if (!in.atEnd()) {
            totalDays = in.readLine().toInt();
        }
        file.close();
    }

    daysLabel->setText(QString("Дней занятий: %1").arg(totalDays));
}

void MainWindow::saveDaysData() {
    QDate today = QDate::currentDate();
    QString lastDateStr;
    int currentDays = 0;

    QFile file("days_data.txt");
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        if (!in.atEnd()) {
            currentDays = in.readLine().toInt();
        }
        if (!in.atEnd()) {
            lastDateStr = in.readLine();
        }
        file.close();
    }

    QDate lastDate = QDate::fromString(lastDateStr, Qt::ISODate);

    if (lastDate != today) {
        currentDays++;

        if (file.open(QIODevice::WriteOnly)) {
            QTextStream out(&file);
            out << currentDays << "\n";
            out << today.toString(Qt::ISODate) << "\n";
            file.close();
        }
    }
}

void MainWindow::loadDaysData() {
    QFile file("days_data.txt");
    if (!file.exists()) {
        if (file.open(QIODevice::WriteOnly)) {
            QTextStream out(&file);
            out << "0\n";
            out << QDate::currentDate().toString(Qt::ISODate) << "\n";
            file.close();
        }
    }
}

// ИГРА: БЫСТРЫЙ ПЕРЕВОД

void MainWindow::startGame() {
    if (currentCards.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Сначала выберите набор для изучения!");
        return;
    }

    bool ok;
    int wordCount = QInputDialog::getInt(this, "Настройки игры",
        "Сколько слов вы хотите перевести? (Максимум: " + QString::number(currentCards.size()) + ")",
        5, 1, currentCards.size(), 1, &ok);

    if (!ok) return;

    gameCards.clear();
    QVector<int> indices;
    for (int i = 0; i < currentCards.size(); i++) {
        indices.append(i);
    }
    std::shuffle(indices.begin(), indices.end(), std::mt19937(std::random_device()()));

    for (int i = 0; i < wordCount; i++) {
        gameCards.append(currentCards[indices[i]]);
    }

    gameCurrentIndex = 0;
    gameScore = 0;
    gameTotal = gameCards.size();
    gameTimeLeft = 10;

    gameScoreLabel->setText(QString("Счет: 0 / %1").arg(gameTotal));
    gameTimerLabel->setText("Время: 10 сек");
    gameQuestionLabel->setText(gameCards[0].question);
    gameAnswerInput->clear();
    gameAnswerInput->setEnabled(true);
    gameCheckBtn->setEnabled(true);
    gameDontKnowBtn->setEnabled(true);

    rightPanel->hide();
    gameWidget->show();
    gameTimer->start(1000);
}

void MainWindow::onGameCheck() {
    QString userAnswer = gameAnswerInput->text().trimmed();
    if (userAnswer.isEmpty()) {
        QMessageBox::warning(this, "Внимание", "Введите ответ!");
        return;
    }

    QString correctAnswer = gameCards[gameCurrentIndex].answer;

    if (userAnswer.compare(correctAnswer, Qt::CaseInsensitive) == 0) {
        gameScore++;
        gameScoreLabel->setText(QString("Счет: %1 / %2").arg(gameScore).arg(gameTotal));
        QMessageBox::information(this, "Правильно!", "Верно!");
    } else {
        QMessageBox::information(this, "Ошибка!", "Неправильно! Правильный ответ: " + correctAnswer);
    }

    gameCurrentIndex++;

    if (gameCurrentIndex >= gameTotal) {
        gameTimer->stop();
        QMessageBox::information(this, "Игра окончена",
            QString("Игра завершена! Правильных ответов: %1 из %2 Процент: %3%")
            .arg(gameScore).arg(gameTotal).arg(gameScore * 100 / gameTotal));
        closeGame();
    } else {
        gameTimeLeft = 10;
        gameTimerLabel->setText("Время: 10 сек");
        gameQuestionLabel->setText(gameCards[gameCurrentIndex].question);
        gameAnswerInput->clear();
        gameAnswerInput->setEnabled(true);
        gameCheckBtn->setEnabled(true);
        gameDontKnowBtn->setEnabled(true);
        gameTimer->start(1000);
    }
}

void MainWindow::onGameDontKnow() {
    QString correctAnswer = gameCards[gameCurrentIndex].answer;
    QMessageBox::information(this, "Правильный ответ", "Правильный ответ: " + correctAnswer);

    gameCurrentIndex++;

    if (gameCurrentIndex >= gameTotal) {
        gameTimer->stop();
        QMessageBox::information(this, "Игра окончена",
            QString("Игра завершена! Правильных ответов: %1 из %2 Процент: %3%")
            .arg(gameScore).arg(gameTotal).arg(gameScore * 100 / gameTotal));
        closeGame();
    } else {
        gameTimeLeft = 10;
        gameTimerLabel->setText("Время: 10 сек");
        gameQuestionLabel->setText(gameCards[gameCurrentIndex].question);
        gameAnswerInput->clear();
        gameAnswerInput->setEnabled(true);
        gameCheckBtn->setEnabled(true);
        gameDontKnowBtn->setEnabled(true);
        gameTimer->start(1000);
    }
}

void MainWindow::updateGameTimer() {
    gameTimeLeft--;
    gameTimerLabel->setText(QString("Время: %1 сек").arg(gameTimeLeft));

    if (gameTimeLeft <= 0) {
        gameTimer->stop();

        QMessageBox::information(this, "Время вышло!",
            "Время на ответ истекло! Правильный ответ: " + gameCards[gameCurrentIndex].answer);

        gameCurrentIndex++;

        if (gameCurrentIndex >= gameTotal) {
            QMessageBox::information(this, "Игра окончена",
                QString("Игра завершена! Правильных ответов: %1 из %2 Процент: %3%")
                .arg(gameScore).arg(gameTotal).arg(gameScore * 100 / gameTotal));
            closeGame();
        } else {
            gameTimeLeft = 10;
            gameTimerLabel->setText("Время: 10 сек");
            gameQuestionLabel->setText(gameCards[gameCurrentIndex].question);
            gameAnswerInput->clear();
            gameAnswerInput->setEnabled(true);
            gameCheckBtn->setEnabled(true);
            gameDontKnowBtn->setEnabled(true);
            gameTimer->start(1000);
        }
    }
}

void MainWindow::closeGame() {
    gameWidget->hide();
    gameTimer->stop();
    rightPanel->show();
}
