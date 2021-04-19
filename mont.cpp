#include "mont.h"
#include "ui_mont.h"

double PI = 3.141592653589793;
double e = 2.718281828459045;
double Normal(double mu, double sigma);
double LogNormal(double mu, double sigma);
double Weibull(double alpha, double beta, double theta);

    int n=0, t1=0, t2=0;
    double a1 = -1, b1=-1, c1=-1;
    double a2 = -1,b2 = -1, c2 = -1;
    //切换radio之后应该参数初始化


Mont::Mont(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Mont)
{
    ui->setupUi(this);
}

Mont::~Mont()
{
    delete ui;
}



void Mont::on_StartButton_clicked()
{

    srand((int)time(NULL));
    int i=0;
    double *X1, *X2;

    int r = 0;

    n =ui->StimuTimesBox->text().toInt();
    if(t1==0||t2 ==0){
        QMessageBox::warning(this,"Warning","请选择分布");
        return;
    }
    if(n==0){
        QMessageBox::warning(this,"Warning","请填写模拟次数");
        return;
    }
    X1 = new double[n];
    X2 = new double[n];
    switch(t1){
        case 1:
            a1 = ui->StrNorPara1->text().toDouble();
            b1 = ui->StrNorPara2->text().toDouble();
            //QMessageBox::warning(this,"Warning",QString::number(a1,'g',16),QString::number(b1,'g',16));

            if(a1==0.00||b1==0.00){
                QMessageBox::warning(this,"Warning","请填写参数");
                return;
            }
            for(i=0;i<n;i++)X1[i] = Normal(a1,b1);
            break;
        case 2:
            a1 = ui->StrLogNorPara1->text().toDouble();
            b1 = ui->StrLogNorPara2->text().toDouble();
            if(a1==0.00||b1==0.00){
                QMessageBox::warning(this,"Warning","请填写参数");
                return;
            }
            for (i = 0; i < n; i++) X1[i] = LogNormal(a1, b1);
            break;
        case 3:
            a1 = ui->StrIndPara->text().toDouble();
            if(a1==-1){
                QMessageBox::warning(this,"Warning","请填写参数");
                return;
            }
            for (i = 0; i < n; i++) X1[i] = Weibull(1.0, 1.0 / a1, 0.0);
            break;
        case 4:
            a1 = ui->StrWeiPara1->text().toDouble();
            b1 = ui->StrWeiPara2->text().toDouble();
            c1 = ui->StrWeiPara3->text().toDouble();
            if(a1==0.00||b1==0.00||c1==0.00){
                QMessageBox::warning(this,"Warning","请填写参数");
                return;
            }
            for (i = 0; i < n; i++) X1[i] = Weibull(a1, b1, c1);
            break;
        default:
            break;
    }
    switch(t2){
        case 1:
            a2 = ui->GthNorPara1->text().toDouble();
            b2 = ui->GthNorPara2->text().toDouble();
            if(a2==-1||b2==-1){
                QMessageBox::warning(this,"Warning","请填写参数");
                return;
            }
            for(i=0;i<n;i++)X2[i] = Normal(a2,b2);
            break;
        case 2:
            a2 = ui->GthLogNorPara1->text().toDouble();
            b2 = ui->GthLogNorPara2->text().toDouble();
            if(a2==-1||b2==-1){
                QMessageBox::warning(this,"Warning","请填写参数");
                return;
            }
            for (i = 0; i < n; i++) X2[i] = LogNormal(a2, b2);
            break;
        case 3:
            a2 = ui->GthIndPara->text().toDouble();
            if(a2==-1){
                QMessageBox::warning(this,"Warning","请填写参数");
                return;
            }
            for (i = 0; i < n; i++) X2[i] = Weibull(1.0, 1.0 / a2, 0.0);
            break;
        case 4:
            a2=ui->GthWeiPara1->text().toDouble();
            b2=ui->GthWeiPara2->text().toDouble();
            c2=ui->GthWeiPara3->text().toDouble();
            if(a2==-1||b2==-1||c2==-1){
                QMessageBox::warning(this,"Warning","请填写参数");
                return;
            }
            for (i = 0; i < n; i++) X2[i] = Weibull(a2, b2, c2);
            break;
        default:
            break;
    }
    for (i = 0; i < n; i++) {
            if (X2[i] > X1[i]) r++;
        }
    double result = double(r)/n;
    ui->ResultLab->setText(QString::number(result,'g',16));
}





double Normal(double mu, double sigma) {
    static double U, V;
    static int phase = 0;
    double Z;

    if (phase == 0) {
        U = rand() / double(RAND_MAX);
        V = rand() / double(RAND_MAX);
        Z = sqrt(-2.0 * log(U)) * sin(2.0 * PI * V);
    } else {
        Z = sqrt(-2.0 * log(U)) * cos(2.0 * PI * V);
    }

    phase = 1 - phase;
    return mu + Z * sigma;
}

double Weibull(double alpha, double beta, double theta) {
    static double U, X;
    U = rand() / double(RAND_MAX);
    U = -log(U);
    X = beta * pow(U, 1.0 / alpha);
    return X + theta;
}

double LogNormal(double mu, double sigma) {
    static double U, V;
    static int phase = 0;
    double Z;

    if (phase == 0) {
        U = rand() / double(RAND_MAX);
        V = rand() / double(RAND_MAX);
        Z = sqrt(-2.0 * log(U)) * sin(2.0 * PI * V);
    } else {
        Z = sqrt(-2.0 * log(U)) * cos(2.0 * PI * V);
    }

    phase = 1 - phase;
    return pow(e, mu + Z * sigma);
}



void Mont::on_StrNorRadio_clicked()
{
    if(ui->StrNorRadio->isChecked()){
        ui->StrNorPara1->setEnabled(1);
        ui->StrNorPara2->setEnabled(1);
        ui->StrWeiPara1->setEnabled(0);
        ui->StrWeiPara2->setEnabled(0);
        ui->StrWeiPara3->setEnabled(0);
        ui->StrLogNorPara1->setEnabled(0);
        ui->StrLogNorPara2->setEnabled(0);
        ui->StrIndPara->setEnabled(0);
        t1 = 1;
    }
}

void Mont::on_StrLogNorRadio_clicked()
{
    if(ui->StrLogNorRadio->isChecked()){
        ui->StrLogNorPara1->setEnabled(1);
        ui->StrLogNorPara2->setEnabled(1);
        ui->StrWeiPara1->setEnabled(0);
        ui->StrWeiPara2->setEnabled(0);
        ui->StrWeiPara3->setEnabled(0);
        ui->StrIndPara->setEnabled(0);
        ui->StrNorPara1->setEnabled(0);
        ui->StrNorPara2->setEnabled(0);
        t1 = 2;
    }
}




void Mont::on_StrIndRadio_clicked()
{
    if(ui->StrIndRadio->isChecked()){
        ui->StrIndPara->setEnabled(1);
        ui->StrWeiPara1->setEnabled(0);
        ui->StrWeiPara2->setEnabled(0);
        ui->StrWeiPara3->setEnabled(0);
        ui->StrLogNorPara1->setEnabled(0);
        ui->StrLogNorPara2->setEnabled(0);
        ui->StrNorPara1->setEnabled(0);
        ui->StrNorPara2->setEnabled(0);
        t1 =3;
    }
}

void Mont::on_StrWeiRadio_clicked()
{
    if(ui->StrWeiRadio->isChecked()){
        ui->StrWeiPara1->setEnabled(1);
        ui->StrWeiPara2->setEnabled(1);
        ui->StrWeiPara3->setEnabled(1);
        ui->StrLogNorPara1->setEnabled(0);
        ui->StrLogNorPara2->setEnabled(0);
        ui->StrNorPara1->setEnabled(0);
        ui->StrNorPara2->setEnabled(0);
        ui->StrIndPara->setEnabled(0);
        t1 =4;
    }
}

void Mont::on_GthNorRadio_clicked()
{
    if(ui->GthNorRadio->isChecked()){
        ui->GthNorPara1->setEnabled(1);
        ui->GthNorPara2->setEnabled(1);
        ui->GthLogNorPara1->setEnabled(0);
        ui->GthLogNorPara2->setEnabled(0);
        ui->GthIndPara->setEnabled(0);
        ui->GthWeiPara1->setEnabled(0);
        ui->GthWeiPara2->setEnabled(0);
        ui->GthWeiPara3->setEnabled(0);
        t2 =1;
    }
}


void Mont::on_GthLogNorRadio_clicked()
{
    if(ui->GthLogNorRadio->isChecked()){
        ui->GthNorPara1->setEnabled(0);
        ui->GthNorPara2->setEnabled(0);
        ui->GthLogNorPara1->setEnabled(1);
        ui->GthLogNorPara2->setEnabled(1);
        ui->GthIndPara->setEnabled(0);
        ui->GthWeiPara1->setEnabled(0);
        ui->GthWeiPara2->setEnabled(0);
        ui->GthWeiPara3->setEnabled(0);
        t2 =2;
    }
}


void Mont::on_GthIndRadio_clicked()
{
    if(ui->GthIndRadio->isChecked()){
        ui->GthNorPara1->setEnabled(0);
        ui->GthNorPara2->setEnabled(0);
        ui->GthLogNorPara1->setEnabled(0);
        ui->GthLogNorPara2->setEnabled(0);
        ui->GthIndPara->setEnabled(1);
        ui->GthWeiPara1->setEnabled(0);
        ui->GthWeiPara2->setEnabled(0);
        ui->GthWeiPara3->setEnabled(0);
        t2=3;
    }
}


void Mont::on_GthWeiRadio_clicked()
{
    if(ui->GthWeiRadio->isChecked()){
        ui->GthNorPara1->setEnabled(0);
        ui->GthNorPara2->setEnabled(0);
        ui->GthLogNorPara1->setEnabled(0);
        ui->GthLogNorPara2->setEnabled(0);
        ui->GthIndPara->setEnabled(0);
        ui->GthWeiPara1->setEnabled(1);
        ui->GthWeiPara2->setEnabled(1);
        ui->GthWeiPara3->setEnabled(1);
        t2 =4;
    }
}

void Mont::on_pushButton_2_clicked()
{
    QApplication::quit();
}
