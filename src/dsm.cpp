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

void dsm::open(identity *client_identity, TW_MEMREF parent_window)
{
    if (state_ == state::ready) {
        return;
    }

    (*this)(client_identity, nullptr, data_group::control, DAT_PARENT, MSG_OPENDSM, parent_window);

    request_entrypoint(client_identity);
    state(state::ready);
}

void dsm::open(identity *client_identity, TW_MEMREF parent_window, std::error_code &ec) noexcept
{
    try {
        open(client_identity, parent_window);
    } catch (const std::system_error& e) {
        ec = e.code();
    }
}

handle dsm::alloc(uint32_t size)
{
    if (entrypoint_.DSM_MemAllocate) {
        return entrypoint_.DSM_MemAllocate(size);
    }

#ifdef TWH_CMP_MSC
    auto memory = ::GlobalAlloc(GPTR, size);
#else
    auto memory = ::malloc(size);
#endif

    return reinterpret_cast<handle>(memory);
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

void dsm::operator()(identity* origin, identity* destination, data_group DG, uint16_t DAT, uint16_t MSG, TW_MEMREF data)
{
    if (!entry_) {
        throw twain_error(error_code::dsm_not_ready);
    }

    auto return_code = entry_(origin, destination, static_cast<uint32_t>(DG), DAT, MSG, data);
    if (return_code != TWRC_SUCCESS) {
        throw twain_error(static_cast<error_code>(return_code));
    }
}

void dsm::operator()(identity* origin, identity* destination, data_group DG, uint16_t DAT, uint16_t MSG, TW_MEMREF data, std::error_code& ec) noexcept
{
    try {
        (*this)(origin, destination, DG, DAT, MSG, data);
    } catch (const std::system_error& e) {
        ec = e.code();
    }
}

void dsm::clear_entrypoint()
{
    std::fill_n((char*)&entrypoint_, sizeof(TW_ENTRYPOINT), 0);
    entrypoint_.Size = sizeof(TW_ENTRYPOINT);
}

void dsm::request_entrypoint(identity* identity)
{
    clear_entrypoint();

    // The entrypoint is available only when requesting a TWAIN 2.0+ connection
    if ((identity->SupportedGroups & (uint32_t)DF_DSM2) == 0) {
        return;
    }

    (*this)(identity, nullptr, data_group::control, DAT_ENTRYPOINT, MSG_GET, reinterpret_cast<TW_MEMREF>(&entrypoint_));
}
