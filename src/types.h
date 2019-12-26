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

#ifndef TWAINPP_TYPES_H
#define TWAINPP_TYPES_H

#include "precompiled.h"

namespace kitsune::twain {
    typedef TW_HANDLE handle;

    typedef TW_UINT16 (dsm_entry)(pTW_IDENTITY, pTW_IDENTITY, TW_UINT32, TW_UINT16, TW_UINT16, TW_MEMREF);
}

#endif
