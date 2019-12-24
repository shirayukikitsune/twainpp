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

#include "error_condition.h"

namespace kitsune::twain {
    class condition_category : public std::error_category {
    public:
        const char *name() const noexcept final
        {
            return "TWAIN";
        }

        std::string message(int c) const final
        {
            using namespace std::literals;
            switch (static_cast<error_condition>(c)) {
                case error_condition::bummer:
                    return "bummer"s;
                case error_condition::low_memory:
                    return "low memory"s;
                case error_condition::no_ds:
                    return "no ds"s;
                case error_condition::max_connections:
                    return "max connections"s;
                case error_condition::operation_error:
                    return "operation error"s;
                case error_condition::bad_capability:
                    return "bad capability"s;
                case error_condition::bad_protocol:
                    return "bad protocol"s;
                case error_condition::bad_value:
                    return "bad value"s;
                case error_condition::sequence_error:
                    return "sequence error"s;
                case error_condition::bad_destination:
                    return "bad destination"s;
                case error_condition::unsupported_capability:
                    return "unsupported capability"s;
                case error_condition::capability_bad_operation:
                    return "bad operation for capability"s;
                case error_condition::capability_sequence_error:
                    return "sequence error for capability"s;
                case error_condition::denied:
                    return "denied"s;
                case error_condition::file_exists:
                    return "file exists"s;
                case error_condition::file_not_found:
                    return "file not found"s;
                case error_condition::not_empty:
                    return "not empty"s;
                case error_condition::paper_jam:
                    return "paper jam"s;
                case error_condition::paper_double_feed:
                    return "paper double feed"s;
                case error_condition::file_write_error:
                    return "file write error"s;
                case error_condition::check_device_online:
                    return "check device online"s;
                case error_condition::interlock:
                    return "interlock"s;
                case error_condition::damaged_corner:
                    return "damaged corner"s;
                case error_condition::focus_error:
                    return "focus error"s;
                case error_condition::document_too_bright:
                    return "document too bright"s;
                case error_condition::document_too_dark:
                    return "document too dark"s;
                case error_condition::no_media:
                    return "no media"s;
                default:
                    return "unknown condition"s;
            }
        }
    };

    static const condition_category& category()
    {
        static condition_category category;
        return category;
    }

    std::error_code make_error_code(error_condition ec)
    {
        return { static_cast<int>(ec), category() };
    }
}
