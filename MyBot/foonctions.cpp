#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow:: writeString(){ // Записывает ответы в файл history
    QFile file(history);

    if (file.open(QIODevice::Append)){
        QTextStream stream;
        stream.setDevice(&file);
        for (int i = 0; i < ui->listWidget->count(); i++) {
            QListWidgetItem* item = ui->listWidget->item(i);
            stream << item->text();
            stream << '\n';
        }
    }
    file.close();
}


void MainWindow::printHistory() // Печатает историю сообщений
{
    QFile file(history);

    if (file.open(QIODevice::ReadOnly)){
        QTextStream stream;
        stream.setDevice(&file);
        while (!stream.atEnd()){
            ui->listWidgetHistory->addItem(stream.readLine());
        }
    }
}


void MainWindow::on_pushButton_clicked()
{
    QString str;
    str = ui->lineEdit->text();
    ui->listWidget->addItem(userName+":");
    ui->listWidget->addItem(str);
    if (userName == "no name"){
        userName = str;
        setSettings();
        speakBot();
    }
    check(str);
    writeString();
}


void MainWindow::setSettings(){ // Создание файла настроек. Файл содержит имя пользователя
    QSettings* settings = new QSettings("settings.conf", QSettings::NativeFormat);
    settings->setValue("user/name", userName);
    settings->sync();
}


void MainWindow::readSettings(){ // Считывает имя пользователя.
    QSettings* settings = new QSettings("settings.conf", QSettings::NativeFormat);
    userName = settings->value("user/name", "no name").toString();
}


void MainWindow::speakBot()
{
    ui->listWidget->addItem("Bot:");
    ui->listWidget->addItem("Привет, " + userName + ", чем могу помочь?");
    ui->listWidget->addItem("Bot:");
    ui->listWidget->addItem("Я умею считать и могу сказать который час");
}


double MainWindow::calculator(int operation, QList<double> lst)
{
    double result = lst[0];
    switch (operation){
        case 0:
            for (int i = 1; i < lst.count(); i++){
            result += lst[i];
            }
            break;
        case 1:
            for (int i = 1; i < lst.count(); i++){
            result -= lst[i];
            }
            break;
        case 2:
            for (int i = 1; i < lst.count(); i++){
            result /= lst[i];
            }
            break;
        case 3:
            for (int i = 1; i < lst.count(); i++){
            result *= lst[i];
            }
            break;
    }
    return result;
}


double MainWindow::calculator(QStringList lst)
{
    double result = lst[0].toDouble();

    for (int i = 1; i < lst.count(); i+=2){
        if (lst[i] == "+"){
            result += lst[i+1].toDouble();         
        }else{
            if (lst[i] == "-"){
                result -= lst[i+1].toDouble();
            }else{
                if (lst[i] == "*"){
                    qDebug() << lst[i+1];
                    result *= lst[i+1].toDouble();
                }else{
                    if (lst[i] == "/"){
                        result /= lst[i+1].toDouble();
                    }
                }
            }
        }
    }
    return result;
}


QTime MainWindow::time() // возвращает текущее время
{
    QTime tm;
    return tm.currentTime();
}


void MainWindow::check(QString str)
{
    if (str.contains("сложи", Qt::CaseInsensitive)){
        modul(0,str);
    }else{
        if (str.contains("вычти", Qt::CaseInsensitive)){
            modul(1,str);
        }else{
            if (str.contains("раздели", Qt::CaseInsensitive)){
                modul(2,str);
            }else{
                if (str.contains("умнож", Qt::CaseInsensitive)){
                    modul(3,str);
                }else{
                    if (str.contains("погода",Qt::CaseInsensitive)){
                        ui->listWidget->addItem("Bot:");
                        ui->listWidget->addItem("Я пока не умею узнавать погоду:(");
                    }else{
                        if (str.contains("время", Qt::CaseInsensitive)){
                            ui->listWidget->addItem("Bot:");
                            ui->listWidget->addItem(time().toString());
                        }else{
                            QRegExp reg("[0-9][-+*/]");
                            if(str.contains(reg)){

                                QStringList lst = separate2(str);
                                double result = calculator(lst);
                                ui->listWidget->addItem("Bot:");
                                ui->listWidget->addItem(QString::number(result));
                            }else{
                                ui->listWidget->addItem("Bot:");
                                ui->listWidget->addItem("Я и не знаю что на это ответить");
                            }
                        }
                    }
                }
            }
        }
    }
}


QList<double> MainWindow::separate(QString str) // возвращает все цифры из строки
{
    QRegExp reg("\\s");
    QRegExp reg2("[0-9]");
    QStringList l = str.split(reg);
    QList <double> operands;
    foreach (QString var, l) {
        if (var.contains(reg2)){   
            operands.append(var.toDouble());
        }
    }
    return operands;
}


void MainWindow::modul(int x, QString str)
{
    QList<double> operands = separate(str);
    double result = calculator(x, operands);
    ui->listWidget->addItem("Bot:");
    ui->listWidget->addItem(QString::number(result));
}


QStringList MainWindow::separate2(QString str) // возвращает все цифры из строки
{
    QStringList lst;
    int i;
    QString s;

    if(str[0] == "-"){
        s = str.mid(0,1); i = 1;
    }else{
        i = 0;
    }

    for (i; i <str.count(); i++){
        s += str[i];
        if ((not str[i].isDigit()) and str[i-1].isDigit() and str[i+1].isDigit()){
            lst.append(s);
            s.clear();}
        if (str[i+1].isDigit()){
            continue;
        }else{
            lst.append(s);
            s.clear();
        }
    }
    return lst;
}
