/* Copyright (c) 2011-2015, EPFL/Blue Brain Project
 *                    2015, University of Zurich / VMMLab
 *                          Enrique G. Paredes <egparedes@ifi.uzh.ch>
 *                          Stefan.Eilemann@epfl.ch
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

#include "Controller.h"
#include "TransferFunctionFile.h"

#include <iostream>
#include <thread>
#include <chrono>

int main( int argc, char *argv[] )
{
    if (argc < 2)
    {
        std::cout << "ERROR: missing TF filename!!" << std::endl;
        return 1;
    }

    std::string tfFileName(argv[1]);
    livre::Controller controller(tfFileName);

    std::this_thread::sleep_for (std::chrono::seconds(2));

    controller.publishTransferFunction();

    return 0;
}
