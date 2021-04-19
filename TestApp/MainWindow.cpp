#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "MapGraphicsView.h"
#include "MapGraphicsScene.h"
#include "tileSources/GridTileSource.h"
#include "tileSources/OSMTileSource.h"
#include "tileSources/CompositeTileSource.h"
#include "guts/CompositeTileSourceConfigurationWidget.h"
#include "CircleObject.h"
#include "PolygonObject.h"
#include "WeatherManager.h"

#include "smytilesource.h"
#include "sroadtilesource.h"

#include <QSharedPointer>
#include <QtDebug>
#include <QThread>
#include <QImage>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Setup the MapGraphics scene and view
    MapGraphicsScene * scene = new MapGraphicsScene(this);
    MapGraphicsView * view = new MapGraphicsView(scene,this);

    //The view will be our central widget
    this->setCentralWidget(view);



    //Setup some tile sources
    QSharedPointer<OSMTileSource> osmTiles(new OSMTileSource(OSMTileSource::OSMTiles), &QObject::deleteLater);
    QSharedPointer<SMyTileSource> myTiles(new SMyTileSource(SMyTileSource::SMyTiles), &QObject::deleteLater);
    QSharedPointer<SRoadTileSource> roadTiles(new SRoadTileSource(SMyTileSource::SMyTiles), &QObject::deleteLater);
    QSharedPointer<GridTileSource> gridTiles(new GridTileSource(), &QObject::deleteLater);
    QSharedPointer<CompositeTileSource> composite(new CompositeTileSource(), &QObject::deleteLater);

    QSettings* setting = new QSettings(qApp->applicationDirPath()
                                       +qApp->applicationName()+".ini",QSettings::IniFormat);
    setting->deleteLater();

    QString bgHost = setting->value("map/bgHost", "http://localhost:8000/").toString();
    QString bgUri = setting->value("map/bgUri", "/tile/Gansu_jiayuguan&collection=ImgTile&tileKeyField=Key&dataField=Data&dataType=jpg_%1_%2_%3.jpg").toString();
    myTiles->setURL(bgHost, bgUri);

    QString roadHost = setting->value("map/roadHost", "http://localhost:8000/").toString();
    QString roadUri = setting->value("map/roadUri", "/tile/jiayuguan_zhuji&collection=ImgTile&tileKeyField=Key&dataField=Data&dataType=png_%1_%2_%3.jpg").toString();
    double roadAlpha = setting->value("map/roadAlpha", 0.5).toDouble();
    roadTiles->setURL(roadHost, roadUri);

    setting->setValue("map/bgHost", bgHost);
    setting->setValue("map/bgUri", bgUri);
    setting->setValue("map/roadHost", roadHost);
    setting->setValue("map/roadUri", roadUri);
    setting->setValue("map/roadAlpha", roadAlpha);
    setting->sync();

    composite->addSourceBottom(myTiles);
    composite->addSourceTop(roadTiles, roadAlpha);
    composite->addSourceTop(gridTiles);

//    composite->addSourceBottom(osmTiles);
//    composite->addSourceTop(gridTiles);
    view->setTileSource(composite);

    //Create a widget in the dock that lets us configure tile source layers
    CompositeTileSourceConfigurationWidget * tileConfigWidget = new CompositeTileSourceConfigurationWidget(composite.toWeakRef(),
                                                                                         this->ui->dockWidget);
    this->ui->dockWidget->setWidget(tileConfigWidget);
    delete this->ui->dockWidgetContents;

    this->ui->menuWindow->addAction(this->ui->dockWidget->toggleViewAction());
    this->ui->dockWidget->toggleViewAction()->setText("&Layers");

    view->setZoomLevel(12);
    view->centerOn(98.3746, 39.7608);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//private slot
void MainWindow::on_actionExit_triggered()
{
    this->close();
}
