#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QDebug>
#include <QTime>
#include <QVector>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QCommandLineParser parser;

    QCommandLineOption sizeOption(QStringList() << "s" << "size",
                                  "<размер> генеруемой матрицы",
                                  "размер", "5");
    parser.addOption(sizeOption);

    QCommandLineOption outputFile(QStringList() << "o" << "output",
                                  "Записать результат в <файл>",
                                  "файл", "output.txt");
    parser.addOption(outputFile);

    parser.process(a);

    QString sizeString = parser.value(sizeOption);
    bool ok;
    int size = sizeString.toInt(&ok);
    if(!ok)
    {
        qCritical() << "аргумент <файл> не корректен";
        a.exit(1);
    }
    QString saveFileName = parser.value(outputFile);

    QFile saveFile(saveFileName);
    if(!saveFile.open(QIODevice::WriteOnly))
    {
        qCritical() << QString("файл %1 не может быть открыт на запись").arg(saveFileName);
        a.exit(2);
    }

    QTextStream out(&saveFile);
    out << size << endl;

    qsrand(QDateTime::currentDateTime().toMSecsSinceEpoch());

    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            if(i == j)
                out << 0 << "\t";
            else
                out << qrand() % 51 << "\t";
        }
        out << endl;
    }
    out.flush();
    saveFile.close();

    return 0;
}
