#include "mainwindow.h"
#include "question.h"
#include <QDebug>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include <algorithm>
#include <QVector>
#include <QFileDialog>
#include <iostream>
#include <fstream>
#include <QMessageBox>


class Questions
{
public:
    int questionsN = 1;
    QVector<QVector <QString>> answersListFull;
    QVector <QString> answersListRight;
    QVector <QButtonGroup> groupListFull;
    void push(Question *question){
        if(firstQuestion == nullptr)
        {
            firstQuestion = question;
            lastQuestion = question;
            question->number = this->questionsN;
            question->total = 1;
        }
        else
        {
            lastQuestion->nextQuestion = question;
            question->prevQuestion = lastQuestion;
            question->number = this->questionsN;
            lastQuestion = question;
        }
        updateTotal(this->questionsN);
        answersListFull.push_back(question->answersList);
        this->questionsN += 1;
    }
    void updateTotal(int total){
        Question *iterator = this->firstQuestion;
        while(iterator != nullptr){
            iterator->total = total;
            iterator = iterator->nextQuestion;
        }
    }
    Question *begin(){
        return firstQuestion;
    }
    Question *firstQuestion = nullptr;
    Question *lastQuestion = nullptr;

private:

};


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{

    QVBoxLayout *welcomeWidgetLayout = new QVBoxLayout;
    QLabel *welcomeText = new QLabel("Вітаємо у программі тестування.\nНатисніть кнопку, щоб розпочати тест.");
    welcomeText->setAlignment(Qt::AlignCenter);
    welcomeWidgetLayout->addWidget(welcomeText);

    QHBoxLayout *browseLayout = new QHBoxLayout;
    QLabel *browseText = new QLabel("Обрано тест:");
    browseText->setAlignment(Qt::AlignLeft);
    browseLayout->addWidget(browseText);

    QLabel *filenameLabel = new QLabel("");
    filenameLabel->setAlignment(Qt::AlignLeft);
    browseLayout->addWidget(filenameLabel);

    QPushButton *browseButton = new QPushButton("Browse");
    connect(browseButton, SIGNAL(clicked()), SLOT(chooseFile()));
    browseLayout->addWidget(browseButton);

    welcomeWidgetLayout->addLayout(browseLayout);

    /*
    QPushButton *startButton = new QPushButton("Розпочати тест");
    connect(startButton, SIGNAL(clicked()), this, SLOT(switchToFirstWidget()));
    startButton->setToolTip(tr("Розпочати тест"));
    welcomeWidgetLayout->addWidget(startButton);
    */
    welcomeWidget = new QWidget;
    welcomeWidget->setLayout(welcomeWidgetLayout);
    this->setCentralWidget(welcomeWidget);
}

void MainWindow::switchWidget(QWidget *widget){
    if (this->centralWidget())
    {
        this->centralWidget()->setParent(nullptr);
    }
    this->setCentralWidget(widget);
}

int myrandom (int i) { return std::time(nullptr)%i;}

void MainWindow::switchToFirstWidget()
{
    Questions questions;
    std::random_shuffle(questionList.begin(), questionList.end(), myrandom);
    for(int i = 0; i < questionList.size(); i++)
    {
        std::random_shuffle(questionList[i].answersList.begin(), questionList[i].answersList.end(), myrandom);
        questions.push(new Question(this, questionList[i].questionText, questionList[i].answers, questionList[i].correctAnswers,questionList[i].answersList, questionList[i].correctAnswersList, questionList[i].type, i, questionList.size()));
    }
    switchWidget(questions.begin());
}

structQuestion format(QString S)
{
    structQuestion result;
    QString type = "";
    type += S[0];
    type += S[1];
    type += S[2];
    type += S[3];
    type += S[4];
    result.type = type;
    QString temp = "";
    int i = 7;
    while(i < S.length() && S[i] != 34 )
    {
        temp += S[i];
        i++;
    }
    qDebug() << temp;
    result.questionText = temp;
    temp = "";
    i += 2;
    while(i < S.length() && S[i] != ' '){
        temp += S[i];
        i++;
    }
    qDebug() << temp;
    result.correctAnswers = temp.toInt();
    i++;
    temp = "";
    while(i < S.length() && S[i] != ' '){
        temp += S[i];
        i++;

    }
    qDebug() << temp;
    result.answers = temp.toInt();
    temp = "";
    i--;
    for(int j = 0; j < result.correctAnswers; j++)
    {
        temp = "";
        i += 3;
        while(i < S.length() && S[i] != 34)
        {
            temp += S[i];
            i++;
        }
        qDebug() << temp;
        result.correctAnswersList.push_back(temp);
        result.answersList.push_back(temp);
    }
    temp = "";
    for(int j = 0; j < result.answers - result.correctAnswers; j++)
    {
        temp = "";
        i += 3;
        while(i < S.length() && S[i] != 34)
        {
            temp += S[i];
            i++;
        }
        qDebug() << temp;
        result.answersList.push_back(temp);
    }
    return result;
}


void MainWindow::chooseFile()
{
    structQuestion tempQuestion;

    QString testFileWay = QFileDialog::getOpenFileName(this, tr("Open test file"), "/home", tr("Test Files (*.test)"));
    int i  = testFileWay.length() - 1;
    QString editedFileName = "";
    while(i >= 0 && testFileWay[i] != '/'){
          editedFileName = testFileWay[i] + editedFileName;
          i--;
    }

    QFile testFile(testFileWay);
    if (!testFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox msgBox;
        msgBox.setText("The test file wasn`t successfully opened.");
        msgBox.exec();
        return;
    }

    questionList.clear();
    while (!testFile.atEnd()) {
        QString line = testFile.readLine();
        tempQuestion = format(line);
        questionList.push_back(tempQuestion);
    }
    testFile.close();


    QVBoxLayout *welcomeWidgetLayout = new QVBoxLayout;
    QLabel *welcomeText = new QLabel("Вітаємо у программі тестування.\nНатисніть кнопку, щоб розпочати тест.");
    welcomeText->setAlignment(Qt::AlignCenter);
    welcomeWidgetLayout->addWidget(welcomeText);

    QHBoxLayout *browseLayout = new QHBoxLayout;
    QLabel *browseText = new QLabel("Обрано тест:");
    browseText->setAlignment(Qt::AlignLeft);
    browseLayout->addWidget(browseText);

    QLabel *filenameLabel = new QLabel(editedFileName);
    filenameLabel->setAlignment(Qt::AlignLeft);
    browseLayout->addWidget(filenameLabel);

    QPushButton *browseButton = new QPushButton("Browse");
    connect(browseButton, SIGNAL(clicked()), SLOT(chooseFile()));
    browseLayout->addWidget(browseButton);

    welcomeWidgetLayout->addLayout(browseLayout);


    QPushButton *startButton = new QPushButton("Розпочати тест");
    connect(startButton, SIGNAL(clicked()), SLOT(switchToFirstWidget()));
    startButton->setToolTip(tr("Розпочати тест"));
    welcomeWidgetLayout->addWidget(startButton);

    welcomeWidget = new QWidget;
    welcomeWidget->setLayout(welcomeWidgetLayout);
    this->setCentralWidget(welcomeWidget);
}


MainWindow::~MainWindow()
{

}

