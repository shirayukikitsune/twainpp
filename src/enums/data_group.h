/*
    twain++: a modernization of the TWAIN library
    Copyright (C) 2019 Bruno Ferreira

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef TWAINPP_DATA_GROUP_H
#define TWAINPP_DATA_GROUP_H

#include "../precompiled.h"

namespace kitsune::twain {

    enum data_group : uint32_t {
        ///! Message that should be used to control the DS or the DSM
        control = DG_CONTROL,
        ///! Message that should be used to handle an image from a DS
        image = DG_IMAGE,
        ///! Message that should be used to handle an audio from a DS
        audio = DG_AUDIO,
        ///! Data flag indicating that this is a TWAIN 2.0+ connection to the DSM
        dsm_twain2 = DF_DSM2,
        ///! Data flag indicating that the application is TWAIN 2.0+ compatible
        app_twain2 = DF_APP2,
        ///! Data flag indicating that the DS is TWAIN 2.0+ compatible
        ds_twain2 = DF_DS2,
    };

}

#endif
