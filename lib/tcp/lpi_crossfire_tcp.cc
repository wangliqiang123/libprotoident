/*
 *
 * Copyright (c) 2011-2016 The University of Waikato, Hamilton, New Zealand.
 * All rights reserved.
 *
 * This file is part of libprotoident.
 *
 * This code has been developed by the University of Waikato WAND
 * research group. For further information please see http://www.wand.net.nz/
 *
 * libprotoident is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * libprotoident is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 */

#include <string.h>

#include "libprotoident.h"
#include "proto_manager.h"
#include "proto_common.h"

static inline bool match_cf_tcp(uint32_t payload, uint32_t len) {

        uint32_t hlen = bswap_le_to_host32(payload & 0xffff00) >> 8;

        if (len < 1350 && hlen != len - 7)
                return false;
        if (MATCH(payload, 0xf1, ANY, ANY, 0x01))
                return true;
        if (MATCH(payload, 0xf1, ANY, ANY, 0x00))
                return true;
        return false;
}

static inline bool match_crossfire_tcp(lpi_data_t *data, lpi_module_t *mod UNUSED) {

        if (match_cf_tcp(data->payload[0], data->payload_len[0])) {
                if (match_cf_tcp(data->payload[1], data->payload_len[1])) {
                        return true;
                }
        }

	return false;
}

static lpi_module_t lpi_crossfire_tcp = {
	LPI_PROTO_CROSSFIRE,
	LPI_CATEGORY_GAMING,
	"CrossfireTCP",
	30,
	match_crossfire_tcp
};

void register_crossfire_tcp(LPIModuleMap *mod_map) {
	register_protocol(&lpi_crossfire_tcp, mod_map);
}

