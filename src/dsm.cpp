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

#include "dsm.h"
#include "error_code.h"

using namespace kitsune::twain;

dsm::dsm(std::function<dsm_entry> dsm_entry)
    : entry_(std::move(dsm_entry))
{
}

enum dsm::state dsm::state()
{
    return state_;
}

void dsm::state(enum dsm::state new_state)
{
    state_ = new_state;
}

handle dsm::alloc(uint32_t size)
{
    if (entrypoint_.DSM_MemAllocate) {
        return entrypoint_.DSM_MemAllocate(size);
    }

#ifdef TWH_CMP_MSC
    return ::GlobalAlloc(GPTR, size);
#else
    return reinterpret_cast<TW_HANDLE>(::malloc(size));
#endif
}

void dsm::free(handle handle)
{
    if(entrypoint_.DSM_MemFree)
    {
        return entrypoint_.DSM_MemFree(handle);
    }

#ifdef TWH_CMP_MSC
    ::GlobalFree(memory);
#else
    ::free(handle);
#endif
}

void dsm::operator()(pTW_IDENTITY origin, pTW_IDENTITY destination, TW_UINT32 DG, TW_UINT16 DAT, TW_UINT16 MSG, TW_MEMREF data)
{
    if (!entry_) {
        throw twain_error(error_code::dsm_not_ready);
    }

    auto return_code = entry_(origin, destination, DG, DAT, MSG, data);
    if (return_code != TWRC_SUCCESS) {
        throw twain_error(static_cast<error_code>(return_code));
    }
}

void dsm::operator()(pTW_IDENTITY origin, pTW_IDENTITY dest, TW_UINT32 DG, TW_UINT16 DAT, TW_UINT16 MSG, TW_MEMREF data, std::error_code& ec)
{
    try {
        (*this)(origin, dest, DG, DAT, MSG, data);
    } catch (const std::system_error& e) {
        ec = e.code();
    }
}
