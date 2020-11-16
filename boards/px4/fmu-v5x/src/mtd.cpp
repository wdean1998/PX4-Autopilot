/****************************************************************************
 *
 *   Copyright (C) 2020 PX4 Development Team. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

#include <nuttx/spi/spi.h>
#include <px4_platform_common/mtd_config.h>

const px4_mtd_device_t spi5 = {             // FM25V02A on FMUM 32K
	.bus_type = px4_mtd_device_t::SPI,
	.devid    = SPIDEV_FLASH(0)
};
const px4_mtd_device_t i2c3 = {             // 24LC64T on Base  8K
	.bus_type = px4_mtd_device_t::I2C,
	.devid    = PX4_MK_I2C_DEVID(3, 0x51)
};
const px4_mtd_device_t i2c4 = {             // 24LC64T on IMU   8K
	.bus_type =  px4_mtd_device_t::I2C,
	.devid    =  PX4_MK_I2C_DEVID(4, 0x50)
};


const px4_mtd_entry_t fmum_fram = {
	.device = &spi5,
	.npart = 2,
	.partd = {
		{
			.type = MTD_PARAMETERS,
			.path = "/fs/mtd_params",
			.nblocks = 32
		},
		{
			.type = MTD_WAYPOINTS,
			.path = "/fs/mtd_waypoints",
			.nblocks = 32

		}
	},
};

const px4_mtd_entry_t base_eeprom = {
	.device = &i2c3,
	.npart = 2,
	.partd = {
		{
			.type = MTD_MFT,
			.path = "/fs/mtd_mft",
			.nblocks = 15
		},
		{
			.type = MTD_NET,
			.path = "/fs/mtd_net",
			.nblocks = 1

		}
	},
};

const px4_mtd_entry_t imu_eeprom = {
	.device = &i2c4,
	.npart = 2,
	.partd = {
		{
			.type = MTD_MFT,
			.path = "/fs/mtd_caldata",
			.nblocks = 15
		},
		{
			.type = MTD_ID,
			.path = "/fs/mtd_id",
			.nblocks = 1
		}
	},
};

const px4_mtd_config_t board_mtd_config = {
	.nconfigs   = 3,
	.entries = {
		&fmum_fram,
		&base_eeprom,
		&imu_eeprom
	}
};
