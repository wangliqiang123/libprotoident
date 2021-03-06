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

static inline bool match_mystery_emule(lpi_data_t *data, lpi_module_t *mod UNUSED) {
	/* These particular patterns occur frequently on port 4672, making
         * me think they're some sort of emule traffic but there is no
         * obvious documentation. The payloads appear to be random, which
         * is unlike all other emule traffic. The flows tend to consist of
         * only one or two packets in each direction.
         */

        if (data->payload_len[0] == 44 && data->payload_len[1] >= 38 &&
                        data->payload_len[1] <= 50)
                return true;
        if (data->payload_len[1] == 44 && data->payload_len[0] >= 38 &&
                        data->payload_len[0] <= 50)
                return true;

        if (data->payload_len[0] == 51 && (data->payload_len[1] == 135 ||
                        data->payload_len[1] == 85 ||
                        data->payload_len[1] == 310))
                return true;
        if (data->payload_len[1] == 51 && (data->payload_len[0] == 135 ||
                        data->payload_len[0] == 85 ||
                        data->payload_len[0] == 310))
                return true;


	return false;
}

static lpi_module_t lpi_mystery_emule = {
	LPI_PROTO_UDP_EMULE_MYSTERY,
	LPI_CATEGORY_P2P,
	"eMule_UDP_Mystery",
	250,
	match_mystery_emule
};

void register_mystery_emule(LPIModuleMap *mod_map) {
	register_protocol(&lpi_mystery_emule, mod_map);
}

