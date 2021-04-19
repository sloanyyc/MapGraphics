#ifndef SROADTILESOURCE_H
#define SROADTILESOURCE_H

#include "smytilesource.h"

class SRoadTileSource : public SMyTileSource
{
    Q_OBJECT
public:
    explicit SRoadTileSource(SMyTileSource::SMyTileType type = SMyTiles);
    virtual ~SRoadTileSource();
    virtual QString name() const {
        return "Road Tiles";
    }
protected:
    virtual QString urlFormat() {
        return "/jiayuguan_zhuji&collection=ImgTile&tileKeyField=Key&dataField=Data&dataType=png_%1_%2_%3.jpg";
    }
};

//#include "MapTileSource.h"
//#include "MapGraphics_global.h"
//#include <QSet>
//#include <QHash>

////Forward declaration so that projects that import us as a library don't necessarily have to use QT += network
//class QNetworkReply;

//class SRoadTileSource : public MapTileSource
//{
//    Q_OBJECT
//public:
//    enum RoadTileType
//    {
//        RoadTiles
//    };

//public:
//    explicit SRoadTileSource(SRoadTileSource::RoadTileType tileType = RoadTiles);
//    virtual ~SRoadTileSource();

//    virtual QPointF ll2qgs(const QPointF& ll, quint8 zoomLevel) const;

//    virtual QPointF qgs2ll(const QPointF& qgs, quint8 zoomLevel) const;

//    virtual quint64 tilesOnZoomLevel(quint8 zoomLevel) const;

//    virtual quint16 tileSize() const;

//    virtual quint8 minZoomLevel(QPointF ll);

//    virtual quint8 maxZoomLevel(QPointF ll);

//    virtual QString name() const;

//    virtual QString tileFileExtension() const;

//protected:
//    virtual QString urlFormat();
//    virtual void fetchTile(quint32 x,
//                           quint32 y,
//                           quint8 z);

//    SRoadTileSource::RoadTileType _tileType;
//private:

//    //Set used to ensure a tile with a certain cacheID isn't requested twice
//    QSet<QString> _pendingRequests;

//    //Hash used to keep track of what cacheID goes with what reply
//    QHash<QNetworkReply *, QString> _pendingReplies;

//signals:

//public slots:

//private slots:
//    void handleNetworkRequestFinished();
//};


#endif // SROADTILESOURCE_H
