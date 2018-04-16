  //-----------------------------------------//
 //work of Khaled Sellami and Ilyes Yahyaoui//
//-----------------------------------------//

#ifndef BUTTON_H
#define BUTTON_H
#include<QToolButton>
#include<QMouseEvent>
#include<QLineEdit>
#include<QLabel>
#include<QEventLoop>

enum current_algo {none,dijkstra,bellman,DAG};

class Button : public QToolButton
{
private:
    bool moveevent=false;
public:
    explicit Button(QWidget *) ;
    int relationexists(Button*);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);


};

struct relatedbutton
{
    Button* item;
    QLabel* label;
    QLine* line;
    int color=0;
};

#endif // BUTTON_H
