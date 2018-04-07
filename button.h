#ifndef BUTTON_H
#define BUTTON_H
#include<QToolButton>
#include<QMouseEvent>
#include<QLineEdit>
#include<QLabel>
#include<QEventLoop>


class Button : public QToolButton
{
private:
    bool moveevent=false;
public:
    explicit Button(QWidget *) ;
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
