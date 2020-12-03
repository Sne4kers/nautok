#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QVector>
#include <QLabel>

struct structQuestion{
    QString type = "";
    QString questionText = "";
    int correctAnswers = 0;
    int answers = 0;
    QVector <QString> answersList;
    QVector <QString> correctAnswersList;
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void switchWidget(QWidget *widget);

public slots:
    void chooseFile();
    void switchToFirstWidget();

private:
    QWidget questions[100];
    QVector<structQuestion> questionList;
    QWidget *mainWidget;
    QWidget *welcomeWidget;
};

#endif // MAINWINDOW_H
