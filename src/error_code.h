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

#pragma once

#include <system_error>
#include "external/twain.h"

namespace kitsune::twain {
    enum class error_code {
        /// Any failure
        generic_failure = TWRC_FAILURE,
        /// Check DS or DSM status
        check_status = TWRC_CHECKSTATUS,
        /// Operation was cancelled
        cancelled = TWRC_CANCEL,
        /// The event was a DS event
        ds_event = TWRC_DSEVENT,
        /// The event was not a DS event
        not_ds_event = TWRC_NOTDSEVENT,
        /// The data transfer is completed
        transfer_done = TWRC_XFERDONE,
        /// The list has reached its end
        end_of_list = TWRC_ENDOFLIST,
        info_not_supported = TWRC_INFONOTSUPPORTED,
        data_not_available = TWRC_DATANOTAVAILABLE,
        busy = TWRC_BUSY,
        scanner_locked = TWRC_SCANNERLOCKED,
        /// The DS or DSM state is invalid for the requested operation
        invalid_state = TWRC_CUSTOMBASE + 1,
    };

    namespace detail {
        class twain_category : public std::error_category {
        public:
            const char *name() const noexcept final {
                return "TWAIN";
            }

            std::string message(int c) const final;
        };
    }

    extern inline const detail::twain_category& twain_category() {
        static detail::twain_category category;
        return category;
    }

    inline std::error_code make_error_code(error_code ec) {
        return { static_cast<int>(ec), twain_category() };
    }
}

namespace std {
    template<>
    struct is_error_code_enum<kitsune::twain::error_code> : std::true_type {};
}

namespace kitsune::twain {

    class twain_error : public std::system_error {
    public:
        explicit twain_error(error_code e) : std::system_error(make_error_code(e)) {}
    };

}
