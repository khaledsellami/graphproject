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

    bool checked=false ;
    Button* checkeditem=NULL ;
    QPushButton* close=NULL ;
    QLabel *l=NULL;
     QPushButton* Djikstrabutton=NULL;


protected:
int itemn=0;


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
    void Resetall()
        {

        for(int i=0;i<itemlist.size();i++)

        {
            for(int j=0;j<itemrelations[itemlist[i]].size();j++)
               { delete itemrelations[itemlist[i]][j].line;
                 delete itemrelations[itemlist[i]][j].label;
            }
            itemrelations[itemlist[i]].clear();
            delete itemlist[i] ;


          }
        itemlist.clear();
        itemrelations.clear();
         }

    void SD()
    {l->setText("Solution with Djikstra's algorithm...");};

    void SB()
    {l->setText("Solution with Bellman's algorithm...");};

    void SF()
    {l->setText("Solution with Floyd's algorithm...");};















};





#endif // MAINWINDOW_H
