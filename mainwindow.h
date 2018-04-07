#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include<QMap>
#include<button.h>
#include<QVector>
#include <QPainter>
#include<QPushButton>
#include <QApplication>

class mainwindow : public QWidget
{
    Q_OBJECT
private:
    int itemn=0;
    bool checked=false ;
    Button* checkeditem=NULL ;
    QPushButton* close=NULL ;

protected:

public:

    QMap<Button*,QVector<relatedbutton>> itemrelations ;

    QVector<Button*> itemlist ;

    explicit mainwindow(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *event);
    bool getchecked();
    void setifchecked(bool);
    Button* getcheckeditem();
    void setcheckeditem(Button*);
    void paintEvent(QPaintEvent *event  );



signals:

public slots:
};

#endif // MAINWINDOW_H
