// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include <assert.h>
#include <openenclave/host.h>
#include <stdio.h>
#include "sample_u.h"

int main(int argc, const char* argv[])
{
    oe_result_t r;
    oe_enclave_t* enclave = NULL;
    const uint32_t flags = OE_ENCLAVE_FLAG_DEBUG;
    const oe_enclave_type_t type = OE_ENCLAVE_TYPE_SGX;

    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s ENCLAVE_PATH TMP_DIR\n", argv[0]);
        return 1;
    }

    const char* enclave_path = argv[1];
    const char* tmp_dir = argv[2];

    r = oe_create_sample_enclave(enclave_path, type, flags, NULL, 0, &enclave);
    assert(r == OE_OK);

    r = test_sample(enclave, tmp_dir);
    assert(r == OE_OK);

    r = oe_terminate_enclave(enclave);
    assert(r == OE_OK);

    printf("=== passed all tests (sample)\n");

    return 0;
}
