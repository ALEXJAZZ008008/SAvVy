#ifndef SAVVY_H
#define SAVVY_H

#include <QVector>
#include <QProgressDialog>

#include "stir/common.h"
#include "stir/Array.h"
#include "stir/VoxelsOnCartesianGrid.h"
#include "stir/is_null_ptr.h"

class savvy
{
public:
    template<class T>
    static int copy_QVector(const QVector<T> &in, QVector<T> &out, T &min, T &max)
    {
        assert(in.size() > 0);

        int row_num = in.size();

        if(out.size() != row_num)
        {
            out.resize(row_num);
        }

        for(int i = 0; i < row_num; ++i)
        {
            if(in[i] != 0.0)
            {
                out[i] = in[i];

                if (in[i] >  max)
                {
                    max = in[i];
                }
                else
                {
                    if(in[i]<  min)
                    {
                        min = in[i];
                    }
                }
            }
        }

        return 1;
    }

    template<class T>
    static int serialize_QVector(const QVector<QVector<T>> &in, QVector<T> &out, T &min, T &max)
    {
        assert(in.size() > 0);
        assert(in[0].size() > 0);

        int row_num = in.size();
        int row_size = in[0].size();

        if(out.size() == 0)
        {
            out.resize(row_num * row_size);
        }

        for(int i = 0; i < row_num; ++i)
        {
            for(int j = 0; j < row_size; ++j)
            {
                if(in[i][j] != 0.0)
                {
                    out[(row_size * i) + j] = in[i][j];

                    if (in[i][j] > max)
                    {
                        max = in[i][j];
                    }
                    else
                    {
                        if(in[i][j] < min)
                        {
                            min = in[i][j];
                        }
                    }
                }
            }
        }

        return 1;
    }

    template<class T>
    static int serialize_QVector(const QVector<QVector<T>> &in, QVector<QVector<T>> &out, QVector<T> &min, QVector<T> &max)
    {
        assert(in.size() > 0);
        assert(in[0].size() > 0);

        int row_num  = in.size();
        int row_size = in[0].size();

        if(out.size() == 0)
        {
            out.resize(row_num * row_size);
        }

        for(int i = 0; i < row_num; ++i)
        {
            for(int j =  0; j <  row_size; ++j)
            {
                if (in[i][j] != 0.0)
                {
                    out[0][(row_size * i) + j] = in[i][j];

                    if (in[i][j] > max[0])
                    {
                        max[0] = in[i][j];
                    }
                    else
                    {
                        if(in[i][j]< min[0])
                        {
                            min[0] = in[i][j];
                        }
                    }
                }
            }
        }

        return 1;
    }

    template<class T>
    static int serialize_QVector(const QVector<QVector<QVector<T>>> &in, QVector<T> &out, T &min, T &max)
    {
        assert(in.size() > 0);
        assert(in[0].size() > 0);
        assert(in[0][0].size() > 0);

        int data_num  = in.size();
        int row_num  = in[0].size();
        int row_size = in[0][0].size();

        if(out.size() == 0)
        {
            out.resize(row_num * row_size * data_num);
        }

        for(int i =  0; i <  data_num; ++i)
        {
            for(int j = 0; j < row_num; ++j)
            {
                for(int k = 0; k < row_size; ++k)
                {
                    if (in[i][j][k] != 0.0)
                    {
                        out[(row_size * j) + k] = in[i][j][k];

                        if (in[i][j][k] >max)
                        {
                            max = in[i][j][k];
                        }
                        else
                        {
                            if(in[i][j][k] < min)
                            {
                                min = in[i][j][k];
                            }
                        }
                    }
                }
            }
        }

        return 1;
    }

    template<class T>
    static int serialize_QVector(const QVector<QVector<QVector<T>>> &in, QVector<QVector<T>> &out, QVector<T> &min, QVector<T> &max)
    {
        assert(in.size() > 0);
        assert(in[0].size() > 0);
        assert(in[0][0].size() > 0);

        assert(out.size() == in.size());

        int data_num  = in.size();
        int row_num  = in[0].size();
        int row_size = in[0][0].size();

        for(int i = 0; i < data_num; ++i)
        {
            for(int j = 0; j < row_num; ++j)
            {
                for(int k = 0; k < row_size; ++k)
                {
                    if (in[i][j][k] != 0.0)
                    {
                        out[i][(row_size * j) + k] = in[i][j][k];

                        if (in[i][j][k] >max[i])
                        {
                            max[i] = in[i][j][k];
                        }
                        else
                        {
                            if(in[i][j][k] < min[i])
                            {
                                min[i] = in[i][j][k];
                            }
                        }
                    }
                }
            }
        }

        return 1;
    }

    //!
    //! \brief deserialize_QVector
    //! \param in
    //! \param out
    //! \warning Be carefull that [X * Y] = size_row_vector
    //!
    template<class T>
    static int deserialize_QVector(const QVector<T> &in, QVector<QVector<T>> &out)
    {
        assert(in.size() > 0);

        int size = in.size();
        int size_sqrt = static_cast<int>(sqrt(size));

        if(out.size() == 0)
        {
            out.resize(size_sqrt);

            for(int i = 0; i < size_sqrt; ++i)
            {
                out[i].resize(size_sqrt);
            }
        }

        for(int i = 0; i < size_sqrt; ++i)
        {
            for(int j = 0; j < size_sqrt; ++j)
            {
                out[i][j] = in[(size_sqrt * i) + j];
            }
        }

        return 1;
    }

    static int decompose_Array1D_to_QVectors_XY(const stir::Array<1, float> &input, QVector<double> &x_values, QVector<double> &y_values)
    {
        if (input.size() > static_cast<unsigned long>(x_values.size()))
        {
            x_values.resize(static_cast<int>(input.size()));
        }

        if(input.size() > static_cast<size_t>(y_values.size()))
        {
            y_values.resize(static_cast<int>(input.size()));
        }

        double x_spacing = static_cast<double>(input.get_max_index() - input.get_min_index()) / static_cast<double>(input.size());

        for(unsigned long i = 0; i < input.size(); ++i)
        {
            x_values[static_cast<int>(i)] = static_cast<double>(input.get_min_index()) + (x_spacing * static_cast<double>(i));
            y_values[static_cast<int>(i)] = static_cast<double>(input[input.get_min_index() + static_cast<int>(i)]);
        }

        return 1;
    }


    static int Array_QVector1D(const stir::ArrayInterface &input, QVector<double> &output, double &min, double &max,
                               int min_pos = -1, int pos_range = -1)
    {
        {
            const stir::Array<1, float>* t = dynamic_cast<const stir::Array<1, float>* >(&input);

            if (!stir::is_null_ptr(t))
            {
                output.resize(static_cast<int>(t->size_all()));
                return Array1D_QVector1D(*t, output, min, max,
                                         min_pos, pos_range);
            }
        }
        {
            const stir::Array<2, float>* t = dynamic_cast<const stir::Array<2, float>* >(&input);

            if (!stir::is_null_ptr(t))
            {
                output.resize(static_cast<int>(t->size_all()));
                return Array2D_QVector1D(*t, output, min, max,
                                         min_pos, pos_range);
            }
        }
        {
            const stir::Array<3, float>* t = dynamic_cast<const stir::Array<3, float>* >(&input);

            if (!stir::is_null_ptr(t))
            {
                output.resize(static_cast<int>(t->size_all()));
                return Array3D_QVector1D(*t, output, min, max,
                                         min_pos, pos_range);
            }
        }

        return -1;
    }

    static int Array1D_QVector1D(const stir::Array<1, float> &input, QVector<double> &output, double &_min, double &_max,
                                 int min_pos = -1, int pos_range = -1)
    {
        if(output.size() == 0)
            return -1;

        if(min_pos == -1)
            min_pos = 0;

        if(pos_range == -1)
            pos_range = static_cast<int>(input.size());

        for(unsigned long i = static_cast<unsigned long>(min_pos); i < static_cast<unsigned long>(pos_range); ++i)
        {
            if(static_cast<double>(input[input.get_min_index() + static_cast<int>(i)]) != 0.0)
            {
                output[static_cast<int>(i)] = static_cast<double>(input[input.get_min_index() + static_cast<int>(i)]);

                if (static_cast<double>(input[input.get_min_index() + static_cast<int>(i)]) > _max)
                {
                    _max = static_cast<double>(input[input.get_min_index() + static_cast<int>(i)]);
                }
                else
                {
                    if(static_cast<double>(input[input.get_min_index() + static_cast<int>(i)])<  _min)
                    {
                        _min = static_cast<double>(input[input.get_min_index() + static_cast<int>(i)]) ;
                    }
                }
            }
        }

        return 1;
    }

    static int Array2D_QVector1D(const stir::Array<2, float> &input, QVector<double> &output, double &min, double &max,
                                 int min_pos = -1, int pos_range = -1)
    {
        if(output.size() == 0)
            return -1;

        if(min_pos == -1)
            min_pos = 0;

        if(pos_range == -1)
            pos_range = static_cast<int>(input.size());

        for(unsigned long i = static_cast<unsigned long>(min_pos); i < static_cast<unsigned long>(pos_range); ++i)
        {
            for(unsigned long j = 0; j < input[input.get_min_index() + static_cast<int>(i)].size(); ++j)
            {
                if(static_cast<double>(input[input.get_min_index() + static_cast<int>(i)][input[input.get_min_index() + static_cast<int>(i)].get_min_index() + static_cast<int>(j)]) != 0.0)
                {
                    output[(static_cast<int>(input[input.get_min_index() + static_cast<int>(i)].size()) * static_cast<int>(i)) + static_cast<int>(j)] =
                            static_cast<double>(input[input.get_min_index() + static_cast<int>(i)][input[input.get_min_index() + static_cast<int>(i)].get_min_index() + static_cast<int>(j)]);

                    if (static_cast<double>(input[input.get_min_index() + static_cast<int>(i)][input[input.get_min_index() + static_cast<int>(i)].get_min_index() + static_cast<int>(j)]) > max)
                    {
                        max = static_cast<double>(input[input.get_min_index() + static_cast<int>(i)][input[input.get_min_index() + static_cast<int>(i)].get_min_index() + static_cast<int>(j)]);
                    }
                    else
                    {
                        if(static_cast<double>(input[input.get_min_index() + static_cast<int>(i)][input[input.get_min_index() + static_cast<int>(i)].get_min_index() + static_cast<int>(j)]) <
                                min)
                        {
                            min = static_cast<double>(input[input.get_min_index() +
                                    static_cast<int>(i)][input[input.get_min_index() +
                                    static_cast<int>(i)].get_min_index() +
                                    static_cast<int>(j)]);
                        }
                    }
                }
            }
        }

        return 1;
    }

    //!\todo montage
    static int Array3D_QVector1D(const stir::Array<3, float> &input, QVector<double> &output, double &min, double &max,
                                 int min_pos = -1, int pos_range = -1)
    {
        if(output.size() == 0 )
            return -1;

        if(min_pos == -1)
            min_pos = 0;

        if(pos_range == -1)
            pos_range = static_cast<int>(input.size());

        for(unsigned long i = static_cast<unsigned long>(min_pos); i < static_cast<unsigned long>(pos_range); ++i)
        {
            for(unsigned long j = 0; j < input[input.get_min_index() + static_cast<int>(i)].size(); ++j)
            {
                for(unsigned long k = 0; k < input[input.get_min_index() + static_cast<int>(i)][input[input.get_min_index() + static_cast<int>(i)].get_min_index() + static_cast<int>(j)].size(); ++k)
                {
                    if(static_cast<double>(input[input.get_min_index() + static_cast<int>(i)][input[input.get_min_index() + static_cast<int>(i)].get_min_index() + static_cast<int>(j)]
                                           [input[input.get_min_index() + static_cast<int>(i)][input[input.get_min_index() + static_cast<int>(i)].get_min_index() + static_cast<int>(j)].get_min_index() + static_cast<int>(k)] ) != 0.0)
                    {

                        output[(static_cast<int>(input[input.get_min_index() + static_cast<int>(i)].size()) * static_cast<int>(i)) + static_cast<int>(j)] =
                                static_cast<double>(input[input.get_min_index() + static_cast<int>(i)][input[input.get_min_index() + static_cast<int>(i)].get_min_index() + static_cast<int>(j)]
                                [ input[input.get_min_index() + static_cast<int>(i)][input[input.get_min_index() + static_cast<int>(i)].get_min_index() + static_cast<int>(j)].get_min_index() + static_cast<int>(k)]);

                        if (output[(static_cast<int>(input[input.get_min_index() + static_cast<int>(i)].size()) * static_cast<int>(i)) + static_cast<int>(j)] > max)
                        {
                            max = output[(static_cast<int>(input[input.get_min_index() + static_cast<int>(i)].size()) * static_cast<int>(i)) + static_cast<int>(j)];
                        }
                        else
                        {
                            if(output[(static_cast<int>(input[input.get_min_index() + static_cast<int>(i)].size()) * static_cast<int>(i)) + static_cast<int>(j)] <
                                    min)
                            {
                                min = output[(static_cast<int>(input[input.get_min_index() + static_cast<int>(i)].size()) * static_cast<int>(i)) + static_cast<int>(j)];
                            }
                        }
                    }
                }
            }
        }

        return 1;
    }

    //!
    //! \brief Array3D_QVector2Ds
    //! \param input
    //! \param output
    //! \param _min
    //! \param _max
    //! Transform a 3D Vector to a Vector 2D for dipslay
    static int Array3D_QVector2Ds(const stir::Array<3, float> &input, QVector<QVector<double>> &output, QVector<double> &min, QVector<double> &max)
    {
        if(output.size() == 0 )
            return -1;

        for(int i = 0; input.get_min_index() + i <= input.get_max_index(); ++i)
        {
            for(int j = input[input.get_min_index() + i].get_min_index(), idx = 0; j <= input[input.get_min_index() + i].get_max_index(); ++j)
            {
                for(int k = input[input.get_min_index() + i][j].get_min_index(); k <= input[input.get_min_index() + i][j].get_max_index(); ++k, ++idx)
                {
                    double val =static_cast<double>(input[input.get_min_index() + i][j][k]);

                    if(val != 0.0)
                    {
                        output[i][idx] = val;

                        if (val > max[i])
                        {
                            max[i] = val;
                        }
                        else
                        {
                            if(val < min[i])
                            {
                                min[i] = val;
                            }
                        }
                    }
                }
            }
        }

        return 1;
    }

    static int Array2D_QVector2D(const stir::Array<2, float> &input, QVector<QVector<double>> &output)
    {
        if(output.size() == 0)
        {
            output.resize(static_cast<int>(input.size()));

            for(unsigned long i = 0; i < input.size(); ++i)
            {
                output[static_cast<int>(i)].resize(static_cast<int>(input[0].size()));
            }
        }

        assert(input.size() == static_cast<unsigned long>(output.size()));

        int ii = 0, ij = 0;

        for(int i = input.get_min_index(); i <= input.get_max_index(); ++i, ++ii)
        {
            for(int j = input[i].get_min_index(); j <= input[i].get_max_index(); ++j, ++ij)
            {
                output[ii][ij] = static_cast<double>(input[i][j]);
            }

            ij = 0;
        }

        return 1;
    }

    static int Array3D_QVector3D(const stir::Array<3, float> &input, QVector<QVector<QVector<double>>> &output)
    {
        if(output.size() == 0)
        {
            output.resize(static_cast<int>(input.size()));

            for(unsigned long i = 0; i < input.size(); ++i)
            {
                output[static_cast<int>(i)].resize(static_cast<int>(input[0].size()));

                for(unsigned long j = 0; j < input[0][0].size(); ++j)
                {
                    output[static_cast<int>(i)][static_cast<int>(j)].resize(static_cast<int>(input[0][0].size()));
                }
            }
        }

        assert(input.size() == static_cast<unsigned long>(output.size()));

        int ii = 0, ij = 0, ik = 0;

        for(int i = input.get_min_index(); i <= input.get_max_index(); ++i, ++ii)
        {
            for (int j = input[i].get_min_index(); j <= input[i].get_max_index(); ++j, ++ij)
            {
                for( int k = input[i][j].get_min_index(); k <= input[i][j].get_max_index(); ++k, ++ik)
                {
                    output[ii][ij][ik] = static_cast<double>(input[i][j][k]);
                }

                ik = 0;
            }

            ij = 0;
        }

        return 1;
    }
};

#endif //SAVVY_H
