#include "button.h"
#include"mainwindow.h"

Button::Button(QWidget* parent):QToolButton(parent)
{
    setCheckable(true);
};
void Button::mousePressEvent(QMouseEvent* event)
{
    mainwindow* parent=(mainwindow*)parentWidget();
    int i,j;
    if (event->button()==Qt::LeftButton)
        if (parent->getchecked()==false)
        {//checking clicked button
            nextCheckState();
            parent->setcheckeditem(this);
            parent->setifchecked(true);
        }
        else
        {//create a link ,add link to containers and uncheck buttons
            if (parent->getcheckeditem()==this)//uncheck if already checked
            {
                this->setChecked(false);
                parent->setifchecked(false);
                parent->setcheckeditem(NULL);
            }
            else
            {
                //create label and temporary lineEdit
                this->setChecked(true);
                QLine* line ;
                line=parent->drawlink(parent->getcheckeditem(),this);//drawing the line
                QLabel* label =new QLabel(parent);
                QLineEdit* lineed =new QLineEdit(parent) ;
                lineed->setGeometry(line->center().x() ,line->center().y() ,30,30);
                lineed->setFocus();
                lineed->show();
                //wait for the user input
                connect(lineed,SIGNAL(textEdited(QString)),label,SLOT(setText(QString)) );
                QEventLoop loop;
                QObject::connect(lineed, SIGNAL(returnPressed()), &loop, SLOT(quit()));//wait for the user input
                loop.exec();
                //delete lineEdit and show label instead
                delete lineed ;
                label->setGeometry(line->center().x() ,line->center().y(),30,30);
                label->show();
                //update data containers
                relatedbutton rb;
                rb.item=this;
                rb.label=label;
                rb.line=line;
                parent->itemrelations[parent->getcheckeditem()].append(rb);
                //reset checked states to default
                this->setChecked(false);
                parent->getcheckeditem()->setChecked(false);
                parent->setcheckeditem(NULL);
                parent->setifchecked(false);
                return;
            }


        }
    else
        if (event->button()==Qt::RightButton)
        {

            for (i=0;i< parent->itemlist.size();i++)//delete links from other buttons to this one
                if (parent->itemlist[i]!=this)
                {
                    bool x=true;
                    QVector<relatedbutton> &v1=parent->itemrelations[parent->itemlist[i]];
                    for(j=0;j<v1.size()&&x;j++)
                        x=v1[j].item!=this;
                    if (!x)
                    {
                        delete v1[j-1].label;
                        delete v1[j-1].line;
                        //deleteline(line);
                        v1.remove(j-1);
                    }
                }
            //delete links from this button to others
            QVector<relatedbutton> &v=parent->itemrelations[this];
            for (i=0;i<v.size();i++)
            {
                delete v[i].label;
                delete v[i].line;
                //deleteline(line);
           }
            //delete this button
            parent->itemrelations.remove(this);
            delete this ;
        }

};



