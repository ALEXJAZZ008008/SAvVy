#include "display_container_raster.h"

#include <QSettings>

Display_container_raster::Display_container_raster(int dims, QWidget *parent)
    : Display_container(dims,parent)
{
    QSettings settings;

    d_spectrogram = new QwtPlotSpectrogram();
    d_spectrogram->setRenderThreadCount(1);
    d_spectrogram->setCachePolicy(QwtPlotRasterItem::CachePolicy::NoCache);
    this->setAxisAutoScale(Qt::XAxis);
    this->setAxisAutoScale(Qt::YAxis);

//    if(settings.contains("defaultColorMap"))
//        myColorMap = new display::ColorMap(settings.value("defaultColorMap").toInt());
//    else
//        myColorMap = new display::ColorMap();

//    d_spectrogram->setColorMap(myColorMap);

    //    d_rescaler = new QwtPlotRescaler(this->canvas(),QwtPlot::yLeft, QwtPlotRescaler::Fitting);
    //    d_rescaler->setExpandingDirection(QwtPlot::xBottom, QwtPlotRescaler::ExpandBoth);
//    this->setCanvasBackground(QBrush(myColorMap->get_background()));

    if(settings.contains("showAxisDefault"))
    {
        bool state = settings.value("showAxisDefault").toBool();
        this->enableAxis(QwtPlot::xBottom, state);
        this->enableAxis(QwtPlot::yLeft, state);
    }

    p_raster = new QwtMatrixRasterData();

    d_spectrogram->attach(this);
}


Display_container_raster::~Display_container_raster()
{
    // N.E: We cannot call this because colormaps will be deleted, too.
//    delete d_spectrogram;
}

size_t Display_container_raster::get_x_axis_size() const
{
    return row_size;
}
