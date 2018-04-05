#ifndef BUTTON_H
#define BUTTON_H
#include<QToolButton>
#include<QMouseEvent>
#include<QLineEdit>
#include<QLabel>
#include<QEventLoop>

class Button : public QToolButton
{
public:
    explicit Button(QWidget *) ;//parent);
    void mousePressEvent(QMouseEvent *event);
};

struct relatedbutton
{
    Button* item;
    QLabel* label;
    QLine* line;
};

#endif // BUTTON_H
