/*
 *
 *    Copyright (c) 2020-2022 Project CHIP Authors
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

/**
 *    @file
 *      CHIP project configuration for python builds on Linux and OS X.
 *
 */
#ifndef CHIPPROJECTCONFIG_H
#define CHIPPROJECTCONFIG_H

#define CHIP_CONFIG_EVENT_LOGGING_NUM_EXTERNAL_CALLBACKS 2

// Uncomment this for a large Tunnel MTU.
// #define CHIP_CONFIG_TUNNEL_INTERFACE_MTU                           (9000)

// Enable support functions for parsing command-line arguments
#define CHIP_CONFIG_ENABLE_ARG_PARSER 1

//  Enable use of test setup parameters for testing purposes only.
//
//    WARNING: This option makes it possible to circumvent basic chip security functionality.
//    Because of this it SHOULD NEVER BE ENABLED IN PRODUCTION BUILDS.
//
#ifndef CHIP_DEVICE_CONFIG_ENABLE_TEST_SETUP_PARAMS
#define CHIP_DEVICE_CONFIG_ENABLE_TEST_SETUP_PARAMS 1
#endif

// Enable reading DRBG seed data from /dev/(u)random.
// This is needed for test applications and the CHIP device manager to function
// properly when CHIP_CONFIG_RNG_IMPLEMENTATION_CHIPDRBG is enabled.
#define CHIP_CONFIG_DEV_RANDOM_DRBG_SEED 1

// For convenience, Chip Security Test Mode can be enabled and the
// requirement for authentication in various protocols can be disabled.
//
//    WARNING: These options make it possible to circumvent basic Chip security functionality,
//    including message encryption. Because of this they MUST NEVER BE ENABLED IN PRODUCTION BUILDS.
//
//    To build with this flag, pass 'treat_warnings_as_errors=false' to gn/ninja.
//
#define CHIP_CONFIG_SECURITY_TEST_MODE 0

#define CHIP_SYSTEM_CONFIG_PACKETBUFFER_POOL_SIZE 0

/* TODO: Ideally, these #defines should be enabled by default for Linux
 AND the python tool would provide runtime options to enable/disable them */
#define CHIP_DEVICE_CONFIG_ENABLE_COMMISSIONER_DISCOVERY 1
#define CHIP_DEVICE_CONFIG_ENABLE_BOTH_COMMISSIONER_AND_COMMISSIONEE 1

#define CONFIG_BUILD_FOR_HOST_UNIT_TEST 1

#endif /* CHIPPROJECTCONFIG_H */
