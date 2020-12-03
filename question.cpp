#include "question.h"
#include <QVBoxLayout>
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <string>
#include <QString>
#include <QCheckBox>
#include <QButtonGroup>
#include <QProgressBar>
#include <QMessageBox>


Question::Question(MainWindow *parent, QString text, int n, int ans, QVector<QString> answersList, QVector<QString> answers, QString type, int number, int total) : QWidget(parent)
{
    QVector<QString> constructor;
    this->answersList = constructor;
    for(int i = 0; i < n; i++){
        this->answersList.push_back(answersList[i]);
    }
    this->number = number;
    this->total = total;
    this->answersCount = n;
    for(int i = 0; i < ans; i++)
        this->answersRight.insert(answers[i]);
    if(type == "radio")
    {
        this->answersGroup = new QButtonGroup();

        this->parent = parent;
        QVBoxLayout *layout = new QVBoxLayout();

        QVBoxLayout *questionLayout = new QVBoxLayout();
        QProgressBar *progressBar = new QProgressBar();
        progressBar->setRange(0, this->total);
        progressBar->setValue(this->number + 1);
        progressBar->setAlignment(Qt::AlignLeft);
        progressBar->setFormat("%v/%m");
        progressBar->setFixedHeight(15);
        questionLayout->addWidget(progressBar);
        questionLayout->addWidget(new QLabel(text));
        layout->addLayout(questionLayout);

        QHBoxLayout *buttonsLayout = new QHBoxLayout();
        if(this->total - this->number != this->total)
        {
            QPushButton *prevButton = new QPushButton("Previous");
            connect(prevButton, SIGNAL(clicked()), this, SLOT(switchToPrevious()));
            prevButton->setToolTip(tr("Previous question"));
            buttonsLayout->addWidget(prevButton);
        }
        else {
            QWidget *emptyItem1 = new QWidget();
            buttonsLayout->addWidget(emptyItem1);
        }
        if(this->total - this->number != 1)
        {
            QPushButton *nextButton = new QPushButton("Next");
            connect(nextButton, SIGNAL(clicked()), this, SLOT(switchToNext()));
            nextButton->setToolTip(tr("Next question"));
            buttonsLayout->addWidget(nextButton);
        }
        else{
            QWidget *emptyItem2 = new QWidget();
            buttonsLayout->addWidget(emptyItem2);
        }
        layout->addLayout(buttonsLayout);

        for(int i = 0; i < n; i++){
            QRadioButton *radioButton = new QRadioButton(answersList[i], this);
            this->answersGroup->addButton(radioButton);
            layout->addWidget(radioButton);
        }

        QPushButton *finishButton = new QPushButton("Finish");
        connect(finishButton, SIGNAL(clicked()), this, SLOT(switchToFinish()));
        finishButton->setToolTip(tr("Finish the test"));
        layout->addWidget(finishButton);

        this->setLayout(layout);
    }
    else if(type == "multi")
    {
        this->answersGroup = new QButtonGroup();
        this->answersGroup->setExclusive(false);
        this->parent = parent;
        QVBoxLayout *layout = new QVBoxLayout();

        QVBoxLayout *questionLayout = new QVBoxLayout();
        QProgressBar *progressBar = new QProgressBar();
        progressBar->setRange(0, this->total);
        progressBar->setValue(this->number + 1);
        progressBar->setAlignment(Qt::AlignLeft);
        progressBar->setFormat("%v/%m");
        progressBar->setFixedHeight(15);
        questionLayout->addWidget(progressBar);
        questionLayout->addWidget(new QLabel(text));
        layout->addLayout(questionLayout);

        QHBoxLayout *buttonsLayout = new QHBoxLayout();
        if(this->total - this->number != this->total)
        {
            QPushButton *prevButton = new QPushButton("Previous");
            connect(prevButton, SIGNAL(clicked()), this, SLOT(switchToPrevious()));
            prevButton->setToolTip(tr("Previous question"));
            buttonsLayout->addWidget(prevButton);
        }
        else {
            QWidget *emptyItem1 = new QWidget();
            buttonsLayout->addWidget(emptyItem1);
        }
        if(this->total - this->number != 1)
        {
            QPushButton *nextButton = new QPushButton("Next");
            connect(nextButton, SIGNAL(clicked()), this, SLOT(switchToNext()));
            nextButton->setToolTip(tr("Next question"));
            buttonsLayout->addWidget(nextButton);
        }
        else{
            QWidget *emptyItem2 = new QWidget();
            buttonsLayout->addWidget(emptyItem2);
        }
        layout->addLayout(buttonsLayout);

        for(int i = 0; i < n; i++){
            QCheckBox *checkButton = new QCheckBox(answersList[i], this);
            this->answersGroup->addButton(checkButton);
            layout->addWidget(checkButton);
        }

        QPushButton *finishButton = new QPushButton("Finish");
        connect(finishButton, SIGNAL(clicked()), this, SLOT(switchToFinish()));
        finishButton->setToolTip(tr("Finish the test"));
        layout->addWidget(finishButton);

        this->setLayout(layout);
    }


}

void Question::switchToPrevious()
{
    if(this->prevQuestion != nullptr){
        this->parent->switchWidget(prevQuestion);
    }
}

void Question::switchToNext()
{
    if(this->nextQuestion != nullptr){
        this->parent->switchWidget(nextQuestion);
    }
    else{
        switchToFinish();
    }
}

void Question::switchToFinish()
{
    QMessageBox msgBox;
    msgBox.setText("Test is completed");
    msgBox.setInformativeText("Do you want to verify your answers?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    int ret = QMessageBox::warning(this, "Finish the test", "Do you want to finish the test?", QMessageBox::Yes | QMessageBox::No);
    if(ret == QMessageBox::Yes)
    {
        this->parent->centralWidget()->setParent(nullptr);
        QVBoxLayout *finishWidgetLayout = new QVBoxLayout;
        QLabel *finishText = new QLabel("Test has been finished.\nYour result: " + QString::number(countAnswers()) + "%");
        finishText->setAlignment(Qt::AlignCenter);
        finishWidgetLayout->addWidget(finishText);


        QWidget *finishWidget = new QWidget;
        finishWidget->setLayout(finishWidgetLayout);
        this->parent->setCentralWidget(finishWidget);
    }

}

int Question::countAnswers()
{
    Question *nextIterator = this->nextQuestion;
    Question *prevIterator = this->prevQuestion;
    int result = 0;
    int n = 1;
    bool counts = true;
    int buttonID = 0;
    foreach(const QString &temp, this->answersRight){
        buttonID = 0;
        while(this->answersList[buttonID] != temp)
            buttonID++;
        buttonID = (buttonID + 1)*(-1) - 1;
        if(!this->answersGroup->button(buttonID)->isChecked()){
           counts = false;
        }
    }
    for(int i = -2; i > -(this->answersCount) - 2; i--)
    {

        if(this->answersGroup->button(i)->isChecked() && !this->answersRight.contains(this->answersList[(i + 1)*(-1) - 1])){
           counts = false;
        }
    }
    result += counts * 1;
    while(nextIterator != nullptr){
        n++;
        bool counts = true;
        int buttonID = 0;
        foreach(const QString &temp, nextIterator->answersRight){
            buttonID = 0;
            while(nextIterator->answersList[buttonID] != temp)
                buttonID++;
            buttonID = (buttonID + 1)*(-1) - 1;
            if(!nextIterator->answersGroup->button(buttonID)->isChecked()){
               counts = false;
            }
        }
        for(int i = -2; i > -(nextIterator->answersCount) - 2 ; i--)
        {
            if(nextIterator->answersGroup->button(i)->isChecked() && !nextIterator->answersRight.contains(nextIterator->answersList[(i + 1)*(-1) - 1])){
               counts = false;
            }
        }
        result += counts * 1;
        nextIterator = nextIterator->nextQuestion;
    }
    while(prevIterator != nullptr){
        n++;
        bool counts = true;
        int buttonID = 0;
        foreach(const QString &temp, prevIterator->answersRight){
            buttonID = 0;
            while(prevIterator->answersList[buttonID] != temp)
                buttonID++;
            buttonID = (buttonID + 1)*(-1) - 1;
            if(!prevIterator->answersGroup->button(buttonID)->isChecked()){
               counts = false;
            }
        }
        for(int i = -2; i > -(prevIterator->answersCount) - 2 ; i--)
        {
            if(prevIterator->answersGroup->button(i)->isChecked() && !prevIterator->answersRight.contains(prevIterator->answersList[(i + 1)*(-1) - 1])){
               counts = false;
            }
        }
        result += counts * 1;
        prevIterator = prevIterator->prevQuestion;

    }
    int answer = double(result)/double(n)*100;
    return answer;
}

