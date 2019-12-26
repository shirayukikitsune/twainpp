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

#ifndef TWAINPP_DSM_H
#define TWAINPP_DSM_H

#include "precompiled.h"
#include "types.h"

namespace kitsune::twain {

    ///! This class describes a connection to the TWAIN DSM
    class dsm {
    public:
        ///! Describe the state of the DSM connection
        enum struct state {
            ///! The DSM connection is inactive
            disconnected,
            ///! The DSM connection is active
            ready
        };

        /**
         * Construct a new instance of the DSM connection
         * @param dsm_entry The DSM_Entry function pointer
         */
        explicit dsm(std::function<dsm_entry> dsm_entry);

        ///! Return the current state of the DSM connection
        enum state state();
        ///! Set the current state of the DSM connection
        void state(enum state new_state);

        /**
         * Allocate memory that can be shared with the DSM and DS
         * @param size How much memory to allocate
         * @return A handle to the allocated memory or nullptr if failed to allocate
         */
        handle alloc(uint32_t size);

        /**
         * Free a memory handle previously allocated using {@see alloc(uint32_t)}
         * @param handle The handle to the allocated memory
         */
        void free(handle handle);

        /**
         * @brief Post an operation to the DSM
         *
         * This method throws in case of any failure.
         *
         * @param origin The source of the message
         * @param destination The message recipient
         * @param DG The message Data Group
         * @param DAT The message Data Argument Type
         * @param MSG The message to be posted
         * @param data The data content
         * @throws std::error_code on any failure
         */
        void operator()(pTW_IDENTITY origin,
                             pTW_IDENTITY destination,
                             TW_UINT32 DG,
                             TW_UINT16 DAT,
                             TW_UINT16 MSG,
                             TW_MEMREF data);

        /**
         * @brief Post an operation to the DSM
         *
         * This method throws nothing in case of any failure.
         *
         * @param origin The source of the message
         * @param dest The message recipient
         * @param DG The message Data Group
         * @param DAT The message Data Argument Type
         * @param MSG The message to be posted
         * @param data The data content
         * @param ec Error code to be set in case of failure
         */
        void operator()(pTW_IDENTITY origin,
                             pTW_IDENTITY dest,
                             TW_UINT32 DG,
                             TW_UINT16 DAT,
                             TW_UINT16 MSG,
                             TW_MEMREF data,
                             std::error_code& ec);

    private:
        enum state state_ = state::disconnected;
        std::function<dsm_entry> entry_;
        TW_ENTRYPOINT entrypoint_{};
    };

}

#endif
