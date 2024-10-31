#ifndef WIDGET_H
#define WIDGET_H
#include<QObject>
#include <string.h>
#include <fstream>
#include <QPixmap>
#include <QPalette>
#include <QBitmap>

using namespace std;
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    string s, yuan, s1;
    int m = lev - 1, n = lev, t = lev * 2;
    clock_t t1, t2;
    int q=m, w=n, e=t;
    int state1 = 1, state2 = 1;
    int lev=1;
    void draw();
protected:
    void Find (int& m, int& n, int& t, int& state1, int& state2);
    void swapa();
    void swapb();
    void check_d();
    void paintEvent(QPaintEvent *ev);
    virtual void keyPressEvent (QKeyEvent *ev);
    virtual void timerEvent(QTimerEvent*ev);
    void erase();
    void move();
    string qstr2cstr(QString qs);
    QString cstr2qstr(string cs);
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
};
#endif // WIDGET_H
