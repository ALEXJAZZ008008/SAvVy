#ifndef DISPLAY_CONTAINER_1D_H
#define DISPLAY_CONTAINER_1D_H

#include <QWidget>

#include "src/display/display_container.h"

#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>

//!
//! \brief The display class for 1D graphs
//!

class Display_container_1d : public Display_container
{
    Q_OBJECT
public:
    explicit Display_container_1d(int, QWidget *parent = nullptr);

    /** \addtogroup Setters
     *  @{
     */
    //! Set the data array and initialise x_data by pointer
    virtual void set_array(QVector<double>* , int _offset = 0);
    //! Set the data array and initialise x_data by reference
    virtual void set_array(const QVector<double>&, int _offset = 0 );
    //! Set the data array, initialise x_data and update() display, by pointer
    virtual void set_display(QVector<double> * , int _offset = 0 );
    //! Set the data array, initialise x_data and update() display, by reference
    virtual void set_display(const QVector<double>& , int _offset = 0 );
    //! Set the physical dimentions of the x axis
    void set_sizes(float _min_x = 0.f, float  _min_y = 0.f);
    //! Set the the array to display and calibrate the x axis to the physical dimensions.
    void set_physical_display(const QVector<double>& , int offset = 0, float _min_x = 0.f, float  _max_x= 0.f);
    /** @}*/

    //! Update the display contents
    //! \details Try to keep this as minimal as possible
    virtual void update_scene();

    //! Clear the data and x_data
    void clear();

    /** \addtogroup Members to get access to the data
     *  @{
     */
    //! Get value at position. The offset is taken into account
    double at(int) const;
    /** @}*/

private:
    //! QVector of y data
    QVector<double> data;
    //! QVector of x data
    QVector<double> x_data;
    //! Offset of the x axis
    int data_offset;

    QwtPlotCurve* curve;
    //! The minimum x value in physical dimensions
    double min_x;
    //! The maximum x value in physical dimensions
    double max_x;
    //! The incremental step along the x axis
    double inc_x;

};

#endif // DISPLAY_CONTAINER_H
