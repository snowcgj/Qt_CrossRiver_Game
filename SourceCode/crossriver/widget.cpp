#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QKeyEvent>
#include <QTimerEvent>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
     ui->setupUi(this);
     QPixmap bgImages("001.jpg");
     QPalette bgPalette = this->palette();
     bgPalette.setBrush(QPalette::Background,bgImages);
     this->setPalette(bgPalette);
     setMask(bgImages.mask());

    s.append(lev, 'A'); s.append(1, ' '); s.append(lev, 'B');
    yuan.append(lev, 'B'); yuan.append(1, ' '); yuan.append(lev, 'A');
    s1 = s;
    //ui->lineEdit_2->setText("");
    ui->lineEdit->setText("The 1ed level");
    t1=this->startTimer(500);
}
Widget::~Widget()
{
    delete ui;
}
void Widget::Find(int& m, int& n, int& t, int& state1, int& state2)
    {
        int a, b, c;
        q = m, w = n, e = t;//保留原来的状态
        a = s.find(' ', 0);
        b = s.find('B', a);
        c = s.rfind('A', a);
        m = b, n = c, t = a;
        if (fabs(a - b) > 2 || (b == s.string::npos))
        {
            state1 = 0; m = q;
        }//意味着不能将“↑”继续向上移动了
        if (fabs(a - c) > 2 || (c == s.string::npos))
        {
            state2 = 0; n = w;
        }//意味着不能将“↓”继续向下移动了
    }
void Widget::swapb()
    {
        s[t] = 'B';
        s[m] = ' ';
    }
void Widget::swapa()
    {
        s[t] = 'A';
        s[n] = ' ';
    }
void Widget::check_d()
{
        if (s == yuan)
        {
            ++lev;
            QString sss;
            sss.sprintf("%d",lev);
            QString y1;
            string y;
            y="The "+qstr2cstr(sss) +"ed level";
            sss=cstr2qstr(y);
            ui->lineEdit->setText(sss);
            //cout << "第" << lev << "关开始了" << endl;
            m = lev +1, n = lev-1, t = lev;
            string s2, y2;
            s2.append(lev, 'A'); s2.append(1, ' '); s2.append(lev, 'B');
            y2.append(lev, 'B'); y2.append(1, ' '); y2.append(lev, 'A');
            s=s2;yuan=y2;s1 = s;
        }
}
void Widget::draw()
{
    for(int g=0;g<2*lev +1;++g)
    {
        if(s[g]=='A')
        {
            QPainter paint(this);
            QPen pen(QColor(113,123,133));
            QBrush brush(QColor(242,156,13));
            paint.setPen(pen);
            paint.setBrush(brush);
            paint.drawEllipse(200,70+20*g,20,20);
        }
        else if(s[g]=='B')
        {
            QPainter paint1(this);
            QPen pen1(QColor(113,123,133));
            QBrush brush1(QColor(169,255,34));
            paint1.setPen(pen1);
            paint1.setBrush(brush1);
            paint1.drawEllipse(200,70+20*g,20,20);
        }
        else
        {
            QPainter paint1(this);
            QPen pen1(QColor(113,123,133));
            QBrush brush1(QColor(255,255,255));
            paint1.setPen(pen1);
            paint1.setBrush(brush1);
            paint1.drawEllipse(200,70+20*g,20,20);
        }
   }
}
void Widget:: paintEvent(QPaintEvent *ev)
{
    draw();
    check_d();
}
void Widget::erase()
    {
        for (int i = 0; i < lev * 2 + 1; ++i)
        {
            QPainter paint1(this);
            QPen pen1(QColor(113,123,133));
            QBrush brush1(QColor(255,255,255));
            paint1.setPen(pen1);
            paint1.setBrush(brush1);
            for(int g=0;g<2*lev +1;++g)
            {
                paint1.drawEllipse(100,70+20*g,20,20);
           }
        }
    }
void Widget:: keyPressEvent (QKeyEvent *ev)
{
        state1 = 1, state2 = 1;
        Find(m, n, t,state1,state2);
        switch(ev->key())
        {
        case Qt::Key_Up:
                  if(state1)
                      swapb();
                  break;
        case Qt::Key_Down:
            if(state2)
                swapa();
               break;
        case Qt::Key_5:
            //cout << "sorry,you fail" << endl;
            exit(0);
               break;
        case Qt::Key_0:
            s = s1;
            m = lev - 1, n = lev+1, t = lev;
            q = m, w = n, e = t;
            state1 = 1, state2 = 1;;
               break;
        }
        update();
}
void  Widget::timerEvent(QTimerEvent*ev)
 {
     if(ev->timerId()==t1)
         ;
     update();
}
string Widget::qstr2cstr(QString qs)
{
    QByteArray cdata = qs.toLocal8Bit();
    return string(cdata);
}
QString Widget::cstr2qstr(string cs)
{
    return QString::fromLocal8Bit(cs.data());
}
void Widget::on_pushButton_clicked()
{
    s = s1;
    m = lev - 1, n = lev+1, t = lev;
    q = m, w = n, e = t;
    state1 = 1, state2 = 1;
}


void Widget::on_pushButton_2_clicked()
{
    lev=1;
    QString sss;
    sss.sprintf("%d",lev);
    QString y1;
    string y;
    y="The "+qstr2cstr(sss) +"ed level";
    sss=cstr2qstr(y);
    ui->lineEdit->setText(sss);
    //cout << "第" << lev << "关开始了" << endl;
    m = lev +1, n = lev-1, t = lev;
    string s2, y2;
    s2.append(lev, 'A'); s2.append(1, ' '); s2.append(lev, 'B');
    y2.append(lev, 'B'); y2.append(1, ' '); y2.append(lev, 'A');
    s=s2;yuan=y2;s1 = s;
}

void Widget::on_pushButton_3_clicked()
{
    lev=10;
    QString sss;
    sss.sprintf("%d",lev);
    QString y1;
    string y;
    y="The "+qstr2cstr(sss) +"ed level";
    sss=cstr2qstr(y);
    ui->lineEdit->setText(sss);
    //cout << "第" << lev << "关开始了" << endl;
    m = lev +1, n = lev-1, t = lev;
    string s2, y2;
    s2.append(lev, 'A'); s2.append(1, ' '); s2.append(lev, 'B');
    y2.append(lev, 'B'); y2.append(1, ' '); y2.append(lev, 'A');
    s=s2;yuan=y2;s1 = s;
}

void Widget::on_pushButton_4_clicked()
{
    lev=20;
    QString sss;
    sss.sprintf("%d",lev);
    QString y1;
    string y;
    y="The "+qstr2cstr(sss) +"ed level";
    sss=cstr2qstr(y);
    ui->lineEdit->setText(sss);
    m = lev +1, n = lev-1, t = lev;
    string s2, y2;
    s2.append(lev, 'A'); s2.append(1, ' '); s2.append(lev, 'B');
    y2.append(lev, 'B'); y2.append(1, ' '); y2.append(lev, 'A');
    s=s2;yuan=y2;s1 = s;
}
