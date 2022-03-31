#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , curGuess("")
    , answer("")
    , guess(0)
    , amtGuess(0)
{
    makeAnswer();
    ui->setupUi(this);
    labels = findChildren<QLabel*>();
    this->setWindowTitle("Wordle but numbers wow creative");

    for (int i = 0; i < labels.length(); i++)
        labels[i]->setText("_");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::makeAnswer()
{
    for (int i = 0; i < 6; i++)
    {
        auto rd = std::random_device();
        auto urbg = std::mt19937{rd()};
        auto distr = std::uniform_int_distribution<int>{1,9};
        auto roll = [urbg, distr]() mutable -> int { return distr(urbg); };
        answer.append(QString::number(roll()));
    }
}

void MainWindow::clearColor()
{
    for (int i = 0; i < labels.length(); i++)
    {
        QPalette palette = labels[i]->palette();
        palette.setColor(QPalette::WindowText, Qt::black);
        labels[i]->setPalette(palette);
    }
}

void MainWindow::checkAnswer(const QString &guess, const QString &ans, QLabel *label)
{
    QColor color;
    if (!(ans == guess))
    {
        if (answer.contains(guess))
        {
            color = Qt::yellow;
        }
        else
        {
            color = Qt::red;
        }
    }
    else
    {
        color = Qt::green;
    }

    QPalette palette = label->palette();
    palette.setColor(QPalette::WindowText, color);
    label->setPalette(palette);
}

void MainWindow::reset()
{
    for (int i = 0; i < labels.length(); i++)
        labels[i]->setText("_");
    guess = 0;
    clearColor();
    answer = "";
    makeAnswer();
}

void MainWindow::on_pushButton_clicked()
{
    bool run = true;
    curGuess = ui->lineEdit->text();
    if (curGuess.length() != 6)
    {
            QMessageBox::warning(this, "Input Size Error", "The Size of the Guess must be 6 integers");
            run = false;
    }
    std::string stdGuess = curGuess.toStdString();
    qDebug() << QString::fromStdString(stdGuess);
    bool isDigit = std::all_of(stdGuess.begin(), stdGuess.end(), ::isdigit);
    if (!isDigit)
    {
        QMessageBox::warning(this, "Input must be Integers", "The input of the Guess must be integers");
        run = false;
    }

    if (run)
    {
        amtGuess++;

        for (int i = 0; i < 6; i++)
        {
            checkAnswer(curGuess[i], answer[i], labels[guess]);
            labels[guess]->setText(curGuess[i]);
            guess++;
        }


        if (amtGuess == 5)
        {
            QMessageBox::StandardButton reply = QMessageBox::information(this, "you lost :(", "Good Try! The answer was " + answer + ", would you like to play again?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::No)
               QApplication::quit();
            else
                reset();
        }

        if (curGuess == answer)
        {
            QMessageBox::StandardButton reply = QMessageBox::information(this, "YOU WON", "You correctly guessed the number, would you like to play again?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::No)
                QApplication::quit();
            else
                reset();
        }


    }

}

