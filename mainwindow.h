  //-----------------------------------------//
 //work of Khaled Sellami and Ilyes Yahyaoui//
//-----------------------------------------//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <boost/config.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include<boost/graph/bellman_ford_shortest_paths.hpp>
#include<boost/graph/dag_shortest_paths.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/iteration_macros.hpp>
#include <boost/graph/properties.hpp>
#include <boost/property_map/property_map.hpp>

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


protected:
     int itemn=0;
     QLabel *l=NULL;
     Button** pathpair;
     QMap<Button*,QVector<relatedbutton>> itemrelations ;
     QVector<Button*> itemlist ;
     QEventLoop loop;
     current_algo algo=none;


public:


    explicit mainwindow(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *event);
    bool getchecked();
    void setifchecked(bool);
    Button* getcheckeditem();
    void setcheckeditem(Button*);
    void paintEvent(QPaintEvent *event  );
    friend class Button;



signals:

public slots:
    void Deleteall();

    void Reset();

    void SD();

    void SB();

    void SDAG();















};





#endif // MAINWINDOW_H
