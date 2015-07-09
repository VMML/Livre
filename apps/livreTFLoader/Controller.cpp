/* Copyright (c) 2011-2015, EPFL/Blue Brain Project
 *                          Ahmet Bilgili <ahmet.bilgili@epfl.ch>
 *                          Maxim Makhinya <maxmah@gmail.com>
 *                          David Steiner  <steiner@ifi.uzh.ch>
 *                          Enrique G. Paredes <egparedes@ifi.uzh.ch>
 *                          Fatih Erol
 *
 * This file is part of Livre <https://github.com/BlueBrain/Livre>
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


#include "Controller.h"
#include <zeq/hbp/hbp.h>

#include "TransferFunctionFile.h"

namespace livre
{

Controller::Controller( )
    : _transferFunction( new TransferFunction1Df )
    , _publisher( lunchbox::URI( "hbp://" ))
{}

Controller::Controller(const std::string& tfFileName)
    : _transferFunction( new TransferFunction1Df )
    , _publisher( lunchbox::URI( "hbp://" ))
{
    std::cout << "Loading TF file '" << tfFileName <<  "'..." << std::endl;
    livre::TransferFunctionFile tfFile(tfFileName);
    tfFile.open();
    livre::TransferFunctionFile::ItemVector itemVector = tfFile.readTransferFunction();
    std::cout << itemVector.size() <<  " items loaded!" << std::endl;

    const unsigned int NumChannels = _transferFunction->getNumChannels();
    FloatVector& rgbaf = _transferFunction->getData();

    rgbaf.resize(itemVector.size() * NumChannels);
    for (unsigned int i=0; i < itemVector.size(); ++i)
    {
        rgbaf[NumChannels * i + 0] = itemVector[i].r;
        rgbaf[NumChannels * i + 1] = itemVector[i].g;
        rgbaf[NumChannels * i + 2] = itemVector[i].b;
        rgbaf[NumChannels * i + 3] = itemVector[i].a;;

/*        std::cout << "TF rgba[" << i << "] = \t"
                  << rgbaf[NumChannels * i + 0] << "  "
                  << rgbaf[NumChannels * i + 1] << "  "
                  << rgbaf[NumChannels * i + 2] << "  "
                  << rgbaf[NumChannels * i + 3] << std::endl;
*/
    }
}

Controller::~Controller( )
{}

bool Controller::connect( const std::string& /*hostname*/,
                          const uint16_t /*port*/ )
{
    LBUNIMPLEMENTED;
    return false;
}

void Controller::publishTransferFunction( )
{
    UInt8Vector rgbai;
    const FloatVector& rgbaf = _transferFunction->getData();
    rgbai.resize( rgbaf.size(), 0 );

    for( uint32_t i = 0; i < rgbaf.size( ); ++i )
    {
        rgbai[ i ] = uint8_t( rgbaf[ i ] *
                              std::numeric_limits< uint8_t >::max( ));
    }

    _publisher.publish( zeq::hbp::serializeLookupTable1D( rgbai ));
}

TransferFunction1DfPtr Controller::getTransferFunction() const
{
    return _transferFunction;
}

}
