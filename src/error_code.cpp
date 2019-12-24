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

#include "error_code.h"

namespace kitsune::twain {

    class twain_category : public std::error_category {
    public:
        const char *name() const noexcept final
        {
            return "TWAIN";
        }

        std::string message(int c) const final
        {
            using namespace std::literals;
            switch (static_cast<error_code>(c)) {
                case error_code::generic_failure:
                    return "generic failure"s;
                case error_code::check_status:
                    return "check status"s;
                case error_code::cancelled:
                    return "cancelled"s;
                case error_code::ds_event:
                    return "ds event"s;
                case error_code::not_ds_event:
                    return "not ds event"s;
                case error_code::transfer_done:
                    return "transfer completed"s;
                case error_code::end_of_list:
                    return "end of list"s;
                case error_code::info_not_supported:
                    return "info not supported"s;
                case error_code::data_not_available:
                    return "data not available"s;
                case error_code::busy:
                    return "busy"s;
                case error_code::scanner_locked:
                    return "scanner locked"s;
                case error_code::invalid_state:
                    return "invalid state"s;
                default:
                    return "unknown error"s;
            }
        }
    };

    static const twain_category& category()
    {
        static twain_category category;
        return category;
    }

    std::error_code make_error_code(error_code ec)
    {
        return { static_cast<int>(ec), category() };
    }
}
