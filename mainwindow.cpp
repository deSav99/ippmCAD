#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createAction();
    createMenu();
    createToolBox();
    createToolBar();

    scene = new SceneCAD(QRectF(0,0,3000,2000));

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(toolBox);

    view = new QGraphicsView(scene);

    view->resize(scene->width(), scene->height());
    view->setMouseTracking(true);
    view->setDragMode(QGraphicsView::RubberBandDrag);
    layout->addWidget(view);

    connect(scene, &SceneCAD::mouseMove, this, &MainWindow::createStatusBar);
    connect(scene, &SceneCAD::insertItem, this, &MainWindow::insertItem);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);
    resize(1500,900);

    setCentralWidget(widget);

}

void MainWindow::createMenu()
{
    fileMenu = menuBar()->addMenu("&File");

    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
}

void MainWindow::createAction()
{
    openAction = new QAction(QIcon(":/images/Open.png"),"Open file", this);
    openAction->setShortcut(tr("CTRL+O"));
    connect(openAction, &QAction::triggered, this, &MainWindow::openRect);

    saveAction= new QAction(QIcon(":/images/Save.png"),"Save open", this);
    saveAction->setShortcut(tr("CTRL+S"));
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveRect);

    deleteAction = new QAction(QIcon(":/images/Delete.png"), "Delete item", this);
    deleteAction->setShortcut(tr("Delete"));
    connect(deleteAction, &QAction::triggered, this, &MainWindow::deleteItem);
}

void MainWindow::createToolBar()
{
    QToolButton *pointerButton = new QToolButton;
    pointerButton->setIcon(QIcon(":/images/Pointer.png"));
    pointerButton->setCheckable(true);
    pointerButton->setChecked(true);

    QToolButton *wireButton = new QToolButton;
    wireButton->setIcon(QIcon(":/images/Wire.png"));
    wireButton->setCheckable(true);

    pointerTypeGroup = new QButtonGroup;
    pointerTypeGroup->addButton(pointerButton, int(SceneCAD:: MoveItem));
    pointerTypeGroup->addButton(wireButton, int(SceneCAD::InsertWire));

    connect(pointerTypeGroup, QOverload<QAbstractButton *> ::of(&QButtonGroup::buttonClicked),
            this, &MainWindow::pointerGroupCliced);

    pointerToolBar = new QToolBar;
    pointerToolBar = addToolBar("");
    pointerToolBar->addWidget(pointerButton);
    pointerToolBar->addWidget(wireButton);
    pointerToolBar->addSeparator();
    pointerToolBar->addAction(deleteAction);

}

void MainWindow::createStatusBar(QPointF mouseCoordinates)
{
     statusBar()->showMessage(QString("X:%1 Y:%2").arg(mouseCoordinates.x()).arg(mouseCoordinates.y()));
}

void MainWindow::createToolBox()
{
    buttonGroup = new QButtonGroup;

    connect(buttonGroup, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),
            this, &MainWindow::buttonGroupClicked);

    QVBoxLayout *layout = new QVBoxLayout;

    layout->addWidget(createCellWidget( "Element", ItemCAD::Element));
    layout->addWidget(createCellWidget( "In", ItemCAD::In));
    layout->addStretch(1);

    QWidget *itemWidget = new QWidget;
    itemWidget->setLayout(layout);

    toolBox = new QToolBox;

    toolBox->setMinimumWidth(itemWidget->sizeHint().width());
    toolBox->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored));
    toolBox->addItem(itemWidget, "Modules");


}

QWidget *MainWindow::createCellWidget(const QString &text, ItemCAD::TypeItem type)
{
    ItemCAD item(type);
    QIcon icon(item.image());

    QToolButton *button = new QToolButton;
    button->setIcon(icon);
    button->setIconSize(QSize(50,50));

    buttonGroup->addButton(button, int(type));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(button);
    layout->addWidget(new QLabel(text));

    layout->stretch(1);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    return widget;
}

void MainWindow::buttonGroupClicked(QAbstractButton *button)
{
    scene->setItemType(ItemCAD::TypeItem(buttonGroup->id(button)));
    scene->setMode(SceneCAD::InsertItem);
}

void MainWindow::pointerGroupCliced()
{
    scene->setMode(SceneCAD::Mode(pointerTypeGroup->checkedId()));
}

void MainWindow::insertItem()
{
    pointerTypeGroup->button(int(SceneCAD::MoveItem))->setChecked(true);
    scene->setMode(SceneCAD::Mode(pointerTypeGroup->checkedId()));
}

void MainWindow::deleteItem()
{
    QList <QGraphicsItem*> listSelectItems = scene->selectedItems();
    for(QGraphicsItem *item : listSelectItems)
        scene->removeItem(item);
}

void MainWindow::saveRect()
{
    QString filename = "Rects.txt";
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream out(&file);
//        foreach(QRect rect, mypaint->rects)
//            out << rect.x() << " " <<rect.y() << "\n";
    }
    else
        qWarning("Could not open file");
}

void MainWindow::openRect()
{
    QList <QString> rects;
    QString filename = QFileDialog::getOpenFileName();
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Cannot open file for reading"); // если файл не найден, то выводим предупреждение и завершаем выполнение программы
        return;
      }
    QTextStream in(&file);
    while(!in.atEnd())
    {
        rects << in.readLine().split(" ");
//        mypaint->rects.append(QRect(QPoint(rects.takeLast().toInt(),rects.takeLast().toInt()),QSize(100,100)));
    }
}

MainWindow::~MainWindow()
{
}

