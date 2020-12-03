#ifndef QUESTION_H
#define QUESTION_H

#include <QWidget>
#include <QButtonGroup>
#include <QVector>
#include <QSet>
#include "mainwindow.h"
#include "mainwindow.h"

class Question : public QWidget
{
    Q_OBJECT
public:
    explicit Question(MainWindow *parent, QString text, int n, int ans, QVector<QString>  answersList, QVector<QString> answers, QString type, int number, int total);
    Question *nextQuestion = nullptr;
    Question *prevQuestion = nullptr;
    int answersCount;
    int number = 0;
    int total = 0;
    QString type;
    QSet <QString> answersRight;
    QVector<QString> answersList;
    QButtonGroup *answersGroup;
    int countAnswers();
signals:

public slots:
    void switchToPrevious();
    void switchToNext();
    void switchToFinish();

private:
    MainWindow *parent;

};

#endif // QUESTIONS_H
