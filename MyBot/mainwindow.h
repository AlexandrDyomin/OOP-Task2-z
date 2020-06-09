#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QString history = "history.txt";
    QString userName;
    QFile fileSettings;
    void writeString();
    void setSettings();
    void readSettings();
    void speakBot();
    double calculator(int operation, QList<double> lst);
    double calculator(QStringList str);
    QTime time();
    void check(QString str);
    QList<double> separate(QString str);
    QStringList separate2(QString str);
    void modul(int x, QString str);
    void printHistory();
};
#endif // MAINWINDOW_H
