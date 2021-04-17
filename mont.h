#ifndef MONT_H
#define MONT_H

#include <QMainWindow>
#include <cmath>
#include <ctime>
#include <stdlib.h>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class Mont; }
QT_END_NAMESPACE

class Mont : public QMainWindow
{
    Q_OBJECT

public:
    Mont(QWidget *parent = nullptr);
    ~Mont();

private slots:


    void on_StartButton_clicked();

    void on_StrNorRadio_clicked();

    void on_StrLogNorRadio_clicked();

    void on_StrIndRadio_clicked();

    void on_StrWeiRadio_clicked();

    void on_GthNorRadio_clicked();

    void on_GthLogNorRadio_clicked();

    void on_GthIndRadio_clicked();

    void on_GthWeiRadio_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Mont *ui;

};
#endif // MONT_H
