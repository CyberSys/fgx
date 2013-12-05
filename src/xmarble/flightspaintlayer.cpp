
#include <QtDebug>
#include <QKeyEvent>

#include "flightspaintlayer.h"

// This stuff is verbatim as a start from
// http://techbase.kde.org/Projects/Marble/LayerInterface

FlightsPaintLayer::FlightsPaintLayer(MarbleWidget* widget) : m_widget(widget), m_index(0)
{
    // nothing to do
    this->flightsModel = 0;
}

void FlightsPaintLayer::register_flights_model(FlightsModel *fmod)
{
    this->flightsModel = fmod;
}


QStringList FlightsPaintLayer::renderPosition() const
{
    // We will paint in exactly one of the following layers.
    // The current one can be changed by pressing the '+' key
    QStringList layers = QStringList() << "SURFACE" << "HOVERS_ABOVE_SURFACE";
    //layers << "ORBIT" << "USER_TOOLS" << "STARS";

    int index = m_index % layers.size();
    //qDebug() << QStringList() << layers.at(index);
    return QStringList() << layers.at(index);
}

bool FlightsPaintLayer::eventFilter(QObject *obj, QEvent *event)
{
    // Adjust the current layer when '+' is pressed
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Plus) {
            ++m_index;
            return true;
        }
    }

    return false;
}



bool FlightsPaintLayer::render( GeoPainter *painter, ViewportParams *viewport,
    const QString& renderPos, GeoSceneLayer * layer )
{
    // Have window title reflect the current paint layer
    //qDebug() << renderPosition().first();
    //m_widget->setWindowTitle(renderPosition().first());
    //GeoDataCoordinates home(8.4, 48.0, 0.0, GeoDataCoordinates::Degree);
    //QTime now = QTime::currentTime();

    painter->setRenderHint(QPainter::Antialiasing, true);

    // Large circle built by 60 small circles
    painter->setPen( QPen(QBrush(QColor::fromRgb(255,0,0,200)), 3.0, Qt::SolidLine, Qt::RoundCap ) );

    //== Draw Radar Widgets
    for(int idx=0; idx < this->flightsModel->rowCount(); idx++)
    {

        // Yes,, LON, LAT is order !!
        Marble::GeoDataCoordinates blip(this->flightsModel->item(idx, FlightsModel::C_LON)->text().toFloat(),
                                        this->flightsModel->item(idx, FlightsModel::C_LAT)->text().toFloat(),
                                        0.0, //this->flightsModel->item(idx, FlightsModel::C_ALTITUDE)->text().toInt() * 10, << mad idea to make flights at 100 * 10 and exagerated position
                                        Marble::GeoDataCoordinates::Degree
                        );
        painter->drawEllipse(blip, 5, 5);

        QString callsign = this->flightsModel->item(idx, FlightsModel::C_CALLSIGN)->text();
        QList <GeoDataCoordinates> trails = this->flightsModel->flightPositions[callsign]->blips;
        qDebug() << callsign << trails.length();
        for(int tidx = 0; tidx < trails.length(); tidx++){

            Marble::GeoDataCoordinates t_blip  = trails.at( tidx );
            painter->drawEllipse(t_blip, 5, 5);
        }
    }


    // hour, minute, second hand
    //painter->drawLine(home, approximate(home, M_PI * now.minute() / 30.0, 0.75));
    //painter->drawLine(home, approximate(home, M_PI * now.hour() / 6.0, 0.5));
    //painter->setPen(QPen(QBrush(Qt::red), 4.0, Qt::SolidLine, Qt::RoundCap ));
    //painter->drawLine(home, approximate(home, M_PI * now.second() / 30.0, 1.0));

    return true;
}