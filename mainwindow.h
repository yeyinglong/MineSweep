#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QPushButton"
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QToolBar>
#include <QTimer>
#include "MineMap.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    CMineMap mineMap;
    int offsetx,offsety;
    QTimer *rumtime;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *);
protected:
    void mousePressEvent(QMouseEvent *event);
   // void mouseMoveEvent(QMouseEvent *event);

private slots:

    void on_actionRestart_triggered();
    void on_actionExit_triggered();

    void on_actionEasy_triggered();

    void on_actionIntermediate_triggered();

    void on_actionAdvanced_triggered();

    void on_sectime();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
