#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include<QMap>
#include<button.h>
#include<QVector>

class mainwindow : public QWidget
{
    Q_OBJECT
    int itemn=0 ;
    bool checked=false ;
    Button* checkeditem=NULL ;

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
    QLine* drawlink(Button*,Button*);
    //QLine MinimumSideDistance(Button* , Button*);



signals:

public slots:
};

#endif // MAINWINDOW_H
