#include "mainwindow.h"
#include<cmath>
#include<QMouseEvent>
#include<cstdlib>
#include <QPaintEvent>
#include<QPen>
#include<vector>



mainwindow::mainwindow(QWidget *parent) : QWidget(parent)
{
    //set window size
    setFixedSize(1280, 680);
    setUpdatesEnabled(true);

    //create close button
    close = new QPushButton("Close",this);
    close->setGeometry(10,640,100,30);
    close->show();
    connect(close, SIGNAL(clicked()), QApplication::instance(), SLOT (quit()));

    //create current algorithm name
    l =new QLabel("->Graph Solver<-",this);
    l->show();
    l->setGeometry(640,0,300,35);

    //create dikstra button
    QPushButton* Djikstrabutton=new QPushButton("Solve with Dijkstra" ,this);
    Djikstrabutton->setGeometry(10,20,100,30);
    connect(Djikstrabutton,SIGNAL(clicked()),this,SLOT(SD()));

    //create bellman button
    QPushButton *Bellmanbutton=new QPushButton("Solve with Bellman",this);
    Bellmanbutton->setGeometry(10,70,100,30);
    connect(Bellmanbutton,SIGNAL(clicked()),this,SLOT(SB()));

    //create floyd button
    QPushButton *dagbutton =new QPushButton("Solve with DAG",this);
    dagbutton->setGeometry(10,120,100,30);
    connect(dagbutton,SIGNAL(clicked()),this,SLOT(SDAG()));

    //create reset button
    QPushButton *Resetbutton =new QPushButton("Reset all",this);
    Resetbutton->setGeometry(10,600,100,30);
    connect(Resetbutton,SIGNAL(clicked()),this,SLOT(Resetall()));
}

bool mainwindow::getchecked()
{return checked ;}

Button* mainwindow::getcheckeditem()
{return checkeditem ;}

void mainwindow::setcheckeditem(Button* b)
{
    mainwindow::checkeditem=b;
}

void mainwindow::setifchecked(bool v)
{
    checked=v;
}

void mainwindow::mousePressEvent(QMouseEvent *event)
{
    if (checked==true)
    {
        //uncheck the button
        checkeditem->setChecked(false);
        checked=false;
        checkeditem=NULL;
    }
    else
    {
        if (event->button()==Qt::LeftButton)
        {
            //create a new button
            char* itemn_str= new char[3];
            sprintf(itemn_str,"%d",itemn);
            Button *item = new Button (this) ;
            item->setText(itemn_str);
            item->setGeometry((event->x())-25, (event->y())- 25,50,50);
            item->show();
            itemlist.append(item);
            itemn++;
        }
    }
    repaint();
    return;

}

void mainwindow::paintEvent(QPaintEvent*  )
{
    QPainter *painter = new QPainter(this);
    QPen linepen(Qt::darkGray);
    linepen.setWidth(1);
    QPoint p1,p2,p3,p4;


    linepen.setStyle( Qt::SolidLine );
    painter->setPen(linepen);
    for(int i=0;i<itemlist.size();i++)

    {
        for(int j=0;j<itemrelations[itemlist[i]].size();j++)

        {
            //draw the line
            painter->drawLine(* (itemrelations[itemlist[i]][j].line));

            //draw arrow

            //Arrowhead left
            if(itemrelations[itemlist[i]][j].line->x2()==itemrelations[itemlist[i]][j].item->x()-5)
            { p1.setX(itemrelations[itemlist[i]][j].item->x());
                p1.setY(itemrelations[itemlist[i]][j].item->y()+25);

                p2.setX(p1.x()-5); p2.setY(p1.y()-5);
                p3.setX(p1.x()-5); p3.setY(p1.y()+5);
                painter->drawLine(p2,p1);
                painter->drawLine(p1,p3);
                painter->drawLine(p2,p3);
            }


            //Arrowhead top
            if (itemrelations[itemlist[i]][j].line->y2()==itemrelations[itemlist[i]][j].item->y()-5 )
            {p1.setX(itemrelations[itemlist[i]][j].item->x()+25);
                p1.setY(itemrelations[itemlist[i]][j].item->y());

                p2.setX(p1.x()-5); p2.setY(p1.y()-5);
                p3.setX(p1.x()+5); p3.setY(p1.y()-5);
                painter->drawLine(p2,p1);
                painter->drawLine(p1,p3);
                painter->drawLine(p2,p3);
            }


            //Arrowhead bottom
            if (itemrelations[itemlist[i]][j].line->y2()==itemrelations[itemlist[i]][j].item->y()+55)
            {
                p1.setX(itemrelations[itemlist[i]][j].item->x()+25);
                p1.setY(itemrelations[itemlist[i]][j].item->y()+50);

                p2.setX(p1.x()-5); p2.setY(p1.y()+5);
                p3.setX(p1.x()+5); p3.setY(p1.y()+5);
                painter->drawLine(p2,p1);
                painter->drawLine(p1,p3);
                painter->drawLine(p2,p3);
            }


            //Arrowhead right
            if ( itemrelations[itemlist[i]][j].line->x2()==itemrelations[itemlist[i]][j].item->x()+55)
            {p1.setX(itemrelations[itemlist[i]][j].item->x()+50);
                p1.setY(itemrelations[itemlist[i]][j].item->y()+25);

                p2.setX(p1.x()+5); p2.setY(p1.y()-5);
                p3.setX(p1.x()+5); p3.setY(p1.y()+5);
                painter->drawLine(p2,p1);
                painter->drawLine(p1,p3);
                painter->drawLine(p2,p3);
            }
            update();
        }
    }

    update();
    painter->end();
}

void mainwindow::SD()
{
    //rename all types needed later
    typedef float Weight;
    typedef boost::property<boost::edge_weight_t, Weight> WeightProperty;
    typedef boost::property<boost::vertex_name_t, std::string> NameProperty;
    typedef boost::adjacency_list < boost::listS, boost::vecS, boost::directedS,NameProperty, WeightProperty > Graph;
    typedef boost::graph_traits < Graph >::vertex_descriptor Vertex;
    typedef boost::property_map < Graph, boost::vertex_index_t >::type IndexMap;
    //typedef boost::property_map < Graph, boost::vertex_name_t >::type NameMap;
    typedef boost::iterator_property_map < Vertex*, IndexMap, Vertex, Vertex& > PredecessorMap;
    typedef boost::iterator_property_map < Weight*, IndexMap, Weight, Weight& > DistanceMap;
    //initialise the variiables needed later
    QMap<Button*,Vertex> boostitemlist;
    l->setText("Solution with Dijkstra's algorithm :");
    algo=dijkstra;
    pathpair=new Button*[2];
    Graph g;
    bool negativeweight=false;
    //translate the graph into the boost graph variable
    for(int i=0;(i<itemlist.size());i++)
    {
        Vertex v =boost::add_vertex(itemlist[i]->text().toStdString(),g);
        boostitemlist[itemlist[i]]=v;
    }
    for(int i=0;((i<itemlist.size())&&(negativeweight==false));i++)
    {
        for(int k=0;(k<itemrelations[itemlist[i]].size())&&(negativeweight==false);k++)
        {
            bool* ok=new bool;
            Weight j=itemrelations[itemlist[i]][k].label->text().toFloat(ok);
            if (j<0)
                negativeweight=true;
            boost::add_edge(boostitemlist[itemlist[i]],boostitemlist[itemrelations[itemlist[i]][k].item], j, g);
        }
    }
    if (negativeweight)
        //alert the user and exit the algorithm
        l->setText("error : this graph contains a negative weight");
    else
    {
        std::vector<Vertex> predecessors(boost::num_vertices(g));
        std::vector<Weight> distances(boost::num_vertices(g));
        l->setText("Solution with Dijkstra's algorithm :\n  choose the source vertex");
        //wait for user the pick the source and destination
        loop.exec();
        //initialise the needed containers for the algorithm output
        IndexMap indexMap = boost::get(boost::vertex_index, g);
        PredecessorMap predecessorMap(&predecessors[0], indexMap);
        DistanceMap distanceMap(&distances[0], indexMap);
        //call dijkstra's algorithm function
        boost::dijkstra_shortest_paths(g,boostitemlist[pathpair[0]], boost::distance_map(distanceMap).predecessor_map(predecessorMap));
        //show the shortest path if it exists
        if (predecessorMap[boostitemlist[pathpair[1]]]==boostitemlist[pathpair[1]])
            l->setText("there's no path from this source to this destination");
        else
        {QString s="Solution with Dijkstra's algorithm :\nthe minimum distance is : ";
            s+=QString::number(distanceMap[boostitemlist[pathpair[1]]]);
            l->setText(s);}
    }
    algo=none;
    delete[] pathpair;
}

void mainwindow::SB()
{
    //rename all types needed later
    typedef float Weight;
    typedef boost::property<boost::edge_weight_t, Weight> WeightProperty;
    typedef boost::property<boost::vertex_name_t, std::string> NameProperty;
    typedef boost::adjacency_list < boost::listS, boost::vecS, boost::directedS,NameProperty, WeightProperty > Graph;
    typedef boost::graph_traits < Graph >::vertex_descriptor Vertex;
    typedef boost::property_map < Graph, boost::vertex_index_t >::type IndexMap;
    //typedef boost::property_map < Graph, boost::vertex_name_t >::type NameMap;
    typedef boost::iterator_property_map < Vertex*, IndexMap, Vertex, Vertex& > PredecessorMap;
    typedef boost::iterator_property_map < Weight*, IndexMap, Weight, Weight& > DistanceMap;
    //initialise the variiables needed later
    QMap<Button*,Vertex> boostitemlist;
    l->setText("Solution with Bellman's algorithm...");
    algo=bellman;
    pathpair=new Button*[2];
    Graph g;
    //translate the graph into the boost graph variable
    for(int i=0;(i<itemlist.size());i++)
    {
        Vertex v =boost::add_vertex(itemlist[i]->text().toStdString(),g);
        boostitemlist[itemlist[i]]=v;
    }
    for(int i=0;(i<itemlist.size());i++)
    {
        for(int k=0;k<itemrelations[itemlist[i]].size();k++)
        {
            bool* ok=new bool;
            Weight j=itemrelations[itemlist[i]][k].label->text().toFloat(ok);
            boost::add_edge(boostitemlist[itemlist[i]],boostitemlist[itemrelations[itemlist[i]][k].item], j, g);
        }
    }
    std::vector<Vertex> predecessors(boost::num_vertices(g));
    std::vector<Weight> distances(boost::num_vertices(g));
    l->setText("Solution with Bellman's algorithm :\n  choose the source vertex");
    //wait for user the pick the source and destination
    loop.exec();
    //initialise the needed containers for the algorithm output
    IndexMap indexMap = boost::get(boost::vertex_index, g);
    PredecessorMap predecessorMap(&predecessors[0], indexMap);
    DistanceMap distanceMap(&distances[0], indexMap);
    boost::property_map<Graph, boost::edge_weight_t>::type weights = get(boost::edge_weight_t(), g);
    //call bellman's algorithm function
    bool r = boost::bellman_ford_shortest_paths(g,num_vertices(g), boost::weight_map(weights).distance_map(distanceMap).predecessor_map(predecessorMap).root_vertex(boostitemlist[pathpair[0]]));
    //show the shortest path if it exists
    if (r)
    {
        if (predecessorMap[boostitemlist[pathpair[1]]]==boostitemlist[pathpair[1]])
            l->setText("there's no path from this source to this destination");
        else
        {
            QString s="Solution with Bellman's algorithm :\nthe minimum distance is : ";
            s+=QString::number(distanceMap[boostitemlist[pathpair[1]]]);
            l->setText(s);
        }
    }
    else
        l->setText("error : there's a negative cycle");




    algo=none;
    delete[] pathpair;
}

void mainwindow::SDAG()
{
    //rename all types needed later
    typedef float Weight;
    typedef boost::property<boost::edge_weight_t, Weight> WeightProperty;
    typedef boost::property<boost::vertex_name_t, std::string> NameProperty;
    typedef boost::adjacency_list < boost::listS, boost::vecS, boost::directedS,NameProperty, WeightProperty > Graph;
    typedef boost::graph_traits < Graph >::vertex_descriptor Vertex;
    typedef boost::property_map < Graph, boost::vertex_index_t >::type IndexMap;
    //typedef boost::property_map < Graph, boost::vertex_name_t >::type NameMap;
    typedef boost::iterator_property_map < Vertex*, IndexMap, Vertex, Vertex& > PredecessorMap;
    typedef boost::iterator_property_map < Weight*, IndexMap, Weight, Weight& > DistanceMap;
    //initialise the variiables needed later
    QMap<Button*,Vertex> boostitemlist;
    l->setText("Solution with DAG's algorithm :");
    algo=DAG;
    pathpair=new Button*[2];
    Graph g;
    bool notdirected=false;
    //translate the graph into the boost graph variable
    for(int i=0;(i<itemlist.size());i++)
    {
        Vertex v =boost::add_vertex(itemlist[i]->text().toStdString(),g);
        boostitemlist[itemlist[i]]=v;
    }
    for(int i=0;((i<itemlist.size())&&(notdirected==false));i++)
    {
        for(int k=0;(k<itemrelations[itemlist[i]].size())&&(notdirected==false);k++)
        {
            bool* ok=new bool;
            Weight j=itemrelations[itemlist[i]][k].label->text().toFloat(ok);
            int t=itemrelations[itemlist[i]][k].item->relationexists(itemlist[i]);
            if (t!=-1)
                notdirected=true;
            boost::add_edge(boostitemlist[itemlist[i]],boostitemlist[itemrelations[itemlist[i]][k].item], j, g);
        }
    }
    if (notdirected)
        l->setText("error : this graph isn't directed");
    else
    {
        std::vector<Vertex> predecessors(boost::num_vertices(g));
        std::vector<Weight> distances(boost::num_vertices(g));
        l->setText("Solution with DAG's algorithm :\n  choose the source vertex");
        //wait for user the pick the source and destination
        loop.exec();
        //initialise the needed containers for the algorithm output
        IndexMap indexMap = boost::get(boost::vertex_index, g);
        PredecessorMap predecessorMap(&predecessors[0], indexMap);
        DistanceMap distanceMap(&distances[0], indexMap);
        //call DAG's algorithm function
        boost::dag_shortest_paths(g,boostitemlist[pathpair[0]], boost::distance_map(distanceMap).predecessor_map(predecessorMap));
        //show the shortest path if it exists
        if (predecessorMap[boostitemlist[pathpair[1]]]==boostitemlist[pathpair[1]])
            l->setText("there's no path from this source to this destination");
        else
        {
            QString s="Solution with DAG's algorithm :\nthe minimum distance is : ";
            s+=QString::number(distanceMap[boostitemlist[pathpair[1]]]);
            l->setText(s);
        }
    }
    algo=none;
    delete[] pathpair;
}








