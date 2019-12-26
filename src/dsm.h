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
         * Open a connection to the DSM
         *
         * This may throw an exception if there was a failure
         *
         * @param client_identity The identity to register with the DSM
         * @param parent_window A reference to the parent window
         * @remarks The parent_window must be nullptr when the target OS is not Windows
         */
        void open(identity* client_identity, TW_MEMREF parent_window);

        /**
         * Open a connection to the DSM
         * @param client_identity
         * @param parent_window
         * @param ec
         */
        void open(identity* client_identity, TW_MEMREF parent_window, std::error_code& ec) noexcept;

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
        void operator()(identity* origin,
                identity* destination,
                data_group DG,
                uint16_t DAT,
                uint16_t MSG,
                TW_MEMREF data);

        /**
         * @brief Post an operation to the DSM
         *
         * This method throws nothing in case of any failure.
         *
         * @param origin The source of the message
         * @param destination The message recipient
         * @param DG The message Data Group
         * @param DAT The message Data Argument Type
         * @param MSG The message to be posted
         * @param data The data content
         * @param ec Error code to be set in case of failure
         */
        void operator()(identity* origin,
                identity* destination,
                data_group DG,
                uint16_t DAT,
                uint16_t MSG,
                TW_MEMREF data,
                std::error_code& ec) noexcept;

    private:
        enum state state_ = state::disconnected;
        std::function<dsm_entry> entry_;
        TW_ENTRYPOINT entrypoint_{};

        void clear_entrypoint();
        void request_entrypoint(identity* identity);
    };

}

#endif
