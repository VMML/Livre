#
# Copyright (c) 2011-2015, EPFL/Blue Brain Project
#                    2015, University of Zurich / VMMLab
#                          Enrique G. Paredes <egparedes@ifi.uzh.ch>
#                          David Steiner <steiner@ifi.uzh.ch>
#                          Ahmet Bilgili <ahmet.bilgili@epfl.ch>
#
# This file is part of Livre <https://github.com/BlueBrain/Livre>
# This file is part of Livre <https://github.com/VMML/Livre>
#
if(NOT ZEQ_FOUND)
  message(STATUS "Not building TFLoader due to missing ZeroEQ dependency")
  return()
endif()

set(LIVRETFLOADER_HEADERS
  types.h
  Controller.h
  TransferFunctionFile.h)

set(LIVRETFLOADER_SOURCES
  Controller.cpp
  TransferFunctionFile.cpp
  main.cpp)

#include(${QT_USE_FILE})
#add_definitions(${QT_DEFINITIONS} "-DBOOST_TT_HAS_OPERATOR_HPP_INCLUDED" )
add_definitions("-DBOOST_TT_HAS_OPERATOR_HPP_INCLUDED" )
set(LIVRETFLOADER_LINK_LIBRARIES LivreCore LivreEq ${QT_LIBRARIES})

common_application(livreTFLoader MACOSX_BUNDLE)
