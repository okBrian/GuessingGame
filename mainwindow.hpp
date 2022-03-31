#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QMessageBox>
#include <QList>
#include <QLabel>
#include <QString>
#include <QDebug>

#include <random>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void makeAnswer();
    void clearColor();
    void checkAnswer(const QString &guess, const QString &answer, QLabel *label);
    void reset();
private slots:
    void on_pushButton_clicked();

private:
    QList<QLabel*> labels;
    Ui::MainWindow *ui;
    QString curGuess;
    QString answer;
    int guess;
    int amtGuess;
    bool isWon;
};
#endif // MAINWINDOW_H
