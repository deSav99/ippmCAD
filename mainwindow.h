#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QAction>
#include <QToolBar>
#include <QToolBox>
#include <QButtonGroup>
#include <QToolButton>
#include <QStatusBar>
#include <QFile>
#include <QMenuBar>
#include <QFileDialog>
#include <QTextStream>
#include <QGraphicsView>
#include <QGridLayout>
#include <QLabel>

#include "itemcad.h"
#include "scenecad.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void saveRect();
    void openRect();
    void deleteItem();
    void createStatusBar(QPointF mouseCoordinates);
    void buttonGroupClicked(QAbstractButton *button);
    void pointerGroupCliced();
    void insertItem();

signals:
    void typeItem(ItemCAD::TypeItem type);

private:
    void createMenu();
    void createAction();
    void createToolBox();
    void createToolBar();

    QWidget *createCellWidget(const QString &text, ItemCAD::TypeItem type);

    QMenu *fileMenu;

    QToolBox *toolBox;

    QAction *deleteAction;
    QAction *saveAction;
    QAction *openAction;

    QToolBar *pointerToolBar;

    QButtonGroup *buttonGroup;
    QButtonGroup *pointerTypeGroup;

    SceneCAD *scene;
    QGraphicsView *view;

};
#endif // MAINWINDOW_H
