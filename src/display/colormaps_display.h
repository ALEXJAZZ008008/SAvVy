#ifndef COLORMAPS_DISPLAY_H
#define COLORMAPS_DISPLAY_H

#include <qwt_color_map.h>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QDirIterator>
#include <QSharedPointer>

#include <memory>
#include <array>

//! Colormaps. Defaults at BW grayscale.
class ColorMap
{
public:
    explicit ColorMap(QString plugin_colormaps = "",
                             QString default_colormap = ""):
        _plugin_colormaps(plugin_colormaps),
        _default_colormap(default_colormap)
    {
        set_BW();
        set_WB();
        set_qwt();
        set_JET();

        my_list << "BW" << "WB" << "QWT" << "Jet";

        if (!_plugin_colormaps.isEmpty())
            load_plugins();

        if(!_default_colormap.isEmpty())
        {
            index_of_default_colormap = my_list.indexOf(_default_colormap);
        }

    }

    explicit ColorMap(int set,
                             QString plugin_colormaps = "",
                             QString default_colormap = ""):
        ColorMap(plugin_colormaps, default_colormap)
    {
        getColorMap(set);
    }

    ~ColorMap() = default;

    //! Get the list with all the available options
    QStringList getColormapList()
    {
        return my_list;
    }

    //! Set the active ColorMap by name
    const QSharedPointer<QwtLinearColorMap> getColorMap(QString const & name) const
    {
        int index = my_list.indexOf(name);

        return getColorMap(index);
    }

    const QSharedPointer<QwtLinearColorMap> getDefaultColorMap() const
    {
        return get_ColorMap(index_of_default_colormap);
    }

    //! Set the active ColorMap by index
    const QSharedPointer<QwtLinearColorMap> getColorMap(int index) const
    {
        switch (index)
        {
        case 0:

            return this->get_BW();

        case 1:

            return this->get_WB();

        case 2:

            return this->get_qwt();

        case 3:

            return this->get_JET();

        default:

            return this->get_ColorMap(index);
        }

    }

    int load_plugins()
    {

        QStringList filter;
        QDirIterator it(_plugin_colormaps, filter,
                        QDir::AllEntries | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);

        while (it.hasNext())
        {
            QFile file(it.next());
            if (!file.exists())
                continue;
            QFileInfo info(file);

            if(info.suffix() != "csv")
                continue;

            QTextStream file_text_stream(&file);

            if(file.open(QIODevice::ReadOnly))
            {
                QSharedPointer<QwtLinearColorMap> tmp( new QwtLinearColorMap());

                QColor firstC;
                QColor lastC;

                int ind = 0;

                while(!file_text_stream.atEnd())
                {
                    QString line = file_text_stream.readLine();
                    QStringList split = line.split(',');

                    if (ind == 1)
                    {
                        firstC.setRgb(split[1].toInt(), split[2].toInt(), split[3].toInt());
                    }

                    if (ind == 256)
                    {
                        lastC.setRgb(split[1].toInt(), split[2].toInt(), split[3].toInt());
                    }

                    ++ind;
                }

                file.close();
                tmp->setColorInterval(firstC, lastC);

                file.open(QIODevice::ReadOnly);
                ind = 0;
                while(!file_text_stream.atEnd())
                {
                    QString line = file_text_stream.readLine();
                    QStringList split = line.split(',');

                    if(ind > 0 && ind < 256)
                    {
                        QColor clr(static_cast<unsigned char>(split[1].toInt()),
                                static_cast<unsigned char>(split[2].toInt()),
                                static_cast<unsigned char>(split[3].toInt()));

                        tmp->addColorStop(split[0].toDouble(), clr);
                    }
                    ++ind;
                }

                file.close();

                my_list << info.fileName();
                _data_pool.append(tmp);
            }
        }
        return 1;
    }

    //! Set Black - White grayscale
    void set_BW()
    {
        QSharedPointer<QwtLinearColorMap> tmp( new QwtLinearColorMap(Qt::black,
                                                                     Qt::white));

        _data_pool.append(tmp);
    }

    const QSharedPointer<QwtLinearColorMap> get_BW() const
    {
        return _data_pool[0];
    }

    //! Set White - Black grayscale
    void set_WB()
    {
        QSharedPointer<QwtLinearColorMap> tmp( new QwtLinearColorMap(Qt::white,
                                                                     Qt::black));

        _data_pool.append(tmp);
    }
    const QSharedPointer<QwtLinearColorMap> get_WB() const
    {
        return _data_pool[1];
    }
    //! Set Jet, popular by old Matlab
    void set_JET()
    {
        QSharedPointer<QwtLinearColorMap> tmp( new QwtLinearColorMap(Qt::blue,
                                                                     Qt::red));

        tmp->addColorStop( 0.35, Qt::cyan );
        tmp->addColorStop( 0.5, Qt::green );
        tmp->addColorStop( 0.75, Qt::yellow );

        _data_pool.append(tmp);
    }

    const QSharedPointer<QwtLinearColorMap> get_JET() const
    {
        return _data_pool.at(3);
    }
    //! Set QWT default ColorMap
    void set_qwt()
    {
        QSharedPointer<QwtLinearColorMap> tmp( new QwtLinearColorMap(Qt::darkCyan,
                                                                     Qt::red));

        tmp->addColorStop( 0.1, Qt::cyan );
        tmp->addColorStop( 0.6, Qt::green );
        tmp->addColorStop( 0.95, Qt::yellow );

        _data_pool.append(tmp);
    }

    QSharedPointer<QwtLinearColorMap> get_qwt() const
    {
        return _data_pool.at(2);
    }

    //! Set Extended Black Body ColorMap
    QSharedPointer<QwtLinearColorMap> get_ColorMap(int index) const
    {
        if (index < _data_pool.size() &&
                index >=0)
        {
            return _data_pool.at(index);
        }

        return nullptr;
    }

    //    //! Returns the first Color of the ColorMap
    //    QColor get_background() const
    //    { return background; }
    //    //! Returns the last Color of the ColorMap
    //    QColor get_peak_color() const
    //    { return peak; }

private:

    QString _plugin_colormaps;

    QString _default_colormap;

    int index_of_default_colormap;

    QVector < QSharedPointer<QwtLinearColorMap> > _data_pool;

    //    QColor background;
    //    QColor peak;

    QStringList my_list;
};

#endif // COLORMAPS_DISPLAY_H
