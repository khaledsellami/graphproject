#ifndef BUTTON_H
#define BUTTON_H
#include<QToolButton>
#include<QMouseEvent>
#include<QLineEdit>
#include<QLabel>
#include<QEventLoop>

 enum current_algo {none,dijkstra};

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
};

#endif // BUTTON_H
