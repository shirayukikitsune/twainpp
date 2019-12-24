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

#include "precompiled.h"

namespace kitsune::twain {

    enum class error_condition {
        bummer  = TWCC_BUMMER,
        low_memory = TWCC_LOWMEMORY,
        no_ds = TWCC_NODS,
        max_connections = TWCC_MAXCONNECTIONS,
        operation_error = TWCC_OPERATIONERROR,
        bad_capability = TWCC_BADCAP,
        bad_protocol = TWCC_BADPROTOCOL,
        bad_value = TWCC_BADVALUE,
        sequence_error = TWCC_SEQERROR,
        bad_destination = TWCC_BADDEST,
        unsupported_capability = TWCC_CAPUNSUPPORTED,
        capability_bad_operation = TWCC_CAPBADOPERATION,
        capability_sequence_error = TWCC_CAPSEQERROR,
        denied = TWCC_DENIED,
        file_exists = TWCC_FILEEXISTS,
        file_not_found = TWCC_FILENOTFOUND,
        not_empty = TWCC_NOTEMPTY,
        paper_jam = TWCC_PAPERJAM,
        paper_double_feed = TWCC_PAPERDOUBLEFEED,
        file_write_error = TWCC_FILEWRITEERROR,
        check_device_online = TWCC_CHECKDEVICEONLINE,
        interlock = TWCC_INTERLOCK,
        damaged_corner = TWCC_DAMAGEDCORNER,
        focus_error = TWCC_FOCUSERROR,
        document_too_bright = TWCC_DOCTOOLIGHT,
        document_too_dark = TWCC_DOCTOODARK,
        no_media = TWCC_NOMEDIA,
    };

    std::error_condition make_error_condition(error_condition ec);

}

namespace std {
    template <>
    struct is_error_condition_enum<kitsune::twain::error_condition> : true_type {};
}
