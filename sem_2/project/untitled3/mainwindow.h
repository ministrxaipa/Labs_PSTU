#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QString>
#include <QListWidgetItem>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QDate>
#include <QProgressBar>
#include <QTimer>

class Card {
public:
    QString question;
    QString answer;
    int errors;
    int correctCount;
    bool learned;

    Card(QString q = "", QString a = "") {
        question = q;
        answer = a;
        errors = 0;
        correctCount = 0;
        learned = false;
    }
};

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void onSetSelected(QListWidgetItem* item);
    void onCheckAnswer();
    void onDontKnow();
    void onFinish();
    void onAddOwnSet();
    void onDeleteSet();
    void startGame();
    void onGameCheck();
    void onGameDontKnow();
    void updateGameTimer();
    void closeGame();

private:
    QVector<Card> currentCards;
    QVector<int> activeCards;
    QString currentSetName;
    int currentCardIndex;
    int lastCardIndex;

    QListWidget* setList;
    QLabel* questionLabel;
    QLineEdit* answerInput;
    QPushButton* checkBtn;
    QPushButton* dontKnowBtn;
    QPushButton* finishBtn;
    QPushButton* deleteBtn;
    QLabel* progressLabel;
    QLabel* statsLabel;
    QLabel* daysLabel;
    QProgressBar* progressBar;
    QWidget* rightPanel;

    // Игра
    QVector<Card> gameCards;
    int gameCurrentIndex;
    int gameScore;
    int gameTotal;
    int gameTimeLeft;
    QTimer* gameTimer;
    QLabel* gameTimerLabel;
    QLabel* gameScoreLabel;
    QLabel* gameQuestionLabel;
    QLineEdit* gameAnswerInput;
    QPushButton* gameCheckBtn;
    QPushButton* gameDontKnowBtn;
    QWidget* gameWidget;

    void loadEnglishToRussian();
    void loadRussianToEnglish();
    void loadCustomSetsFromFiles();
    void updateActiveCards();
    int getNextCard();
    void showCurrentCard();
    void updateProgress();
    void loadCustomSet(QString name);
    void addToSetList(QString name);
    void updateDaysCounter();
    void saveDaysData();
    void loadDaysData();
};

#endif
