/* Copyright (c) 2011-2015, EPFL/Blue Brain Project
 *                    2015, University of Zurich / VMMLab
 *                          Enrique G. Paredes <egparedes@ifi.uzh.ch>
 *                          Stefan.Eilemann@epfl.ch
 *
 * Adapted from:
 *
 * ivs - interactive volume splatter
 *       by @author Philipp Schlegel (schlegel@ifi.uzh.ch)
 *
 * This file is part of Livre <https://github.com/BlueBrain/Livre>
 * This file is part of Livre <https://github.com/VMML/Livre>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3.0 as published
 * by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */


#include "TransferFunctionFile.h"

#include <iostream>
#include <fstream>

#include <boost/foreach.hpp>

namespace livre
{

TransferFunctionFile::TransferFunctionFile(const std::string& _filename, Mode _mode):
    filename_(_filename),
    mode_(_mode)
{}

TransferFunctionFile::~TransferFunctionFile()
{}

bool TransferFunctionFile::exists()
{
    file_.exceptions(std::ios::goodbit);
    file_.open(filename_.c_str(), std::ios::in);

    if (file_.is_open())
    {
        file_.close();
        return true;
    }
    file_.close();
    return false;
}

void TransferFunctionFile::open()
{
    try
    {
        file_.exceptions(std::ios::failbit | std::ios::badbit);

        if ((mode_ & READ) == READ)
            file_.open(filename_.c_str(), std::ios::binary | std::ios::in);
        else if ((mode_ & WRITE) == WRITE)
            file_.open(filename_.c_str(), std::ios::binary | std::ios::out);
    }
    catch (std::ios_base::failure &_f)
    {
        throw _f.what();//GET_ERROR_MESSAGE(_f.what());
    }
}

void TransferFunctionFile::close()
{
    if (file_.is_open())
        file_.close();
}

TransferFunctionFile::ItemVector TransferFunctionFile::readTransferFunction()
{
    ItemVector data;
    float s, d, am;

    if (file_.is_open())
    {
        try
        {
            Item item;
            file_.seekg(0, std::ios_base::beg);
            file_ >> item.r >> item.g >> item.b >> item.a;  // >> item.s >> item.d >> item.am;
            file_ >> s >> d >> am;
            while (file_.good())
            {
                data.push_back(item);
                file_ >> item.r >> item.g >> item.b >> item.a; // >> item.s >> item.d >> item.am;
                file_ >> s >> d >> am;
            }
        }
        catch (std::ios_base::failure &_f)
        {
            if (!file_.eof())
                throw _f.what(); //GET_ERROR_MESSAGE(ERR_READ_TRANSFER_FUNCTION) + _f.what();
        }
        catch (std::string &_s)
        {
            throw _s; //GET_ERROR_MESSAGE(ERR_READ_TRANSFER_FUNCTION) + _s;
        }
    }

    return data;
}

void TransferFunctionFile::writeTransferFunction(const ItemVector &_data)
{
    if (file_.is_open())
    {
        try
        {
            file_.seekg(0, std::ios_base::beg);

            BOOST_FOREACH(const Item & item, _data)
            {
                file_ << item.r << " " << item.g << " " << item.b << " " << item.a << std::endl; //<< " " << item.s << " " << item.d << " " << item.am << std::endl;
            }
        }
        catch (std::ios_base::failure &_f)
        {
            throw _f.what(); // GET_ERROR_MESSAGE(ERR_WRITE_TRANSFER_FUNCTION) + _f.what();
        }
        catch (std::string &_s)
        {
            throw _s; //GET_ERROR_MESSAGE(ERR_WRITE_TRANSFER_FUNCTION) + _s;
        }
    }
}

} // namespace
