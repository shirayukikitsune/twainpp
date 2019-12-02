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

namespace kitsune::twain::detail {
    std::string twain_category::message(int c) const {
        switch (static_cast<error_code>(c)) {
        case error_code::generic_failure:
            return "generic failure";
        case error_code::check_status:
            return "check status";
        case error_code::cancelled:
            return "cancelled";
        case error_code::ds_event:
            return "ds event";
        case error_code::not_ds_event:
            return "not ds event";
        case error_code::transfer_done:
            return "transfer completed";
        case error_code::end_of_list:
            return "end of list";
        case error_code::info_not_supported:
            return "info not supported";
        case error_code::data_not_available:
            return "data not available";
        case error_code::busy:
            return "busy";
        case error_code::scanner_locked:
            return "scanner locked";
        case error_code::invalid_state:
            return "invalid state";
        default:
            return "unknown error";
        }
    }
}
