/* Copyright (c) 2011-2015, EPFL/Blue Brain Project
 *                    2015, University of Zurich / VMMLab
 *                          Enrique G. Paredes <egparedes@ifi.uzh.ch>
 *                          Stefan.Eilemann@epfl.ch
 *
 * Adapted from:
 *
 * ivs - interactive volume splatter
 *       by @author Philipp Schlegel (schlegel@ifi.uzh.ch)

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


#ifndef TRANSFER_FUNCTION_FILE_H
#define TRANSFER_FUNCTION_FILE_H

#include <string>
#include <vector>
#include <fstream>

namespace livre
{

/**
 * Transfer function file.
 **/
class TransferFunctionFile
{
public:
    enum Mode
    {
        READ  = 1,
        WRITE = 2
    };

    struct Item
    {
        float r, g, b, a; //, s, d, am;
    };

    typedef std::vector<Item> ItemVector;


    TransferFunctionFile(const std::string& _filename, Mode _mode = READ);

    virtual ~TransferFunctionFile();

    // returns the filename
    virtual const std::string &getFilename() const;

    // True if the file exists, false else.
    virtual bool exists();

    // Open the file. Throw an exception in case of failure.
    virtual void open();

    // Close the file. No status is returned.
    virtual void close();

    ItemVector readTransferFunction();
    void writeTransferFunction(const ItemVector &_data);

protected:
    // filename
    std::string filename_;

    // mode
    Mode mode_;

    // file
    std::fstream file_;
};

inline const std::string &TransferFunctionFile::getFilename() const
{
    return filename_;
}


} // namespace

#endif
