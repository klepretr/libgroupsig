/* 
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#ifndef _PS16_SIGNATURE_H
#define _PS16_SIGNATURE_H

#include <stdint.h>
#include "include/signature.h"
#include "ps16.h"
#include "shim/pbc_ext.h"

/**
 * @struct ps16_signature_t
 * @brief Defines the structure of a PS16 signature.
 */
typedef struct {
  uint8_t scheme; /**< Metainformation: the gs scheme this key belongs to. */
  pbcext_element_G1_t *sigma1;
  pbcext_element_G1_t *sigma2;
  pbcext_element_Fr_t *c;
  pbcext_element_Fr_t *s;
} ps16_signature_t;

/** 
 * @fn groupsig_signature_t* ps16_signature_init()
 * @brief Initializes the fields of a PS16 signature.
 * 
 * @return A pointer to the allocated signature, or NULL if error.
 */
groupsig_signature_t* ps16_signature_init();

/** 
 * @fn int ps16_signature_free(groupsig_signature_t *sig)
 * @brief Frees the alloc'ed fields of the given PS16 signature.
 *
 * @param[in,out] sig The signature to free.
 * 
 * @return IOK or IERROR
 */
int ps16_signature_free(groupsig_signature_t *sig);

/** 
 * @fn int ps16_signature_copy(groupsig_signature_t *dst, 
 *                              groupsig_signature_t *src)
 * @brief Copies the given source signature into the destination signature.
 *
 * @param[in,out] dst The destination signature. Initialized by the caller.
 * @param[in] src The signature to copy. 
 * 
 * @return IOK or IERROR.
 */
int ps16_signature_copy(groupsig_signature_t *dst, groupsig_signature_t *src);

/** 
 * @fn int ps16_signature_to_string(groupsig_signature_t *sig)
 * @brief Returns a printable string representing the current signature.
 *
 * @param[in] sig The signature o convert.
 * 
 * @return A pointer to the created string or NULL if error.
 */
char* ps16_signature_to_string(groupsig_signature_t *sig);

/** 
 * @fn int ps16_signature_get_size(groupsig_signature_t *sig)
 * Returns the number of bytes needed to store the signature in an array
 * of bytes.
 *
 * @param[in] sig The signature.
 * 
 * @return -1 if error. Else, the number of bytes to represent the signature.
 */
int ps16_signature_get_size(groupsig_signature_t *sig);

/**
 * @fn int ps16_signature_export(byte_t **bytes, uint32_t *size, groupsig_key_t *key)
 * @brief Writes a bytearray representation of the given signature, with format:
 *
 * | PS16_CODE | size_sigma1 | sigma1 | size_sigma2 | sigma2 | size_c | c | 
 *   size_s | s |
 *
 * @param[in,out] bytes A pointer to the array that will contain the exported
 *  signature. If <i>*bytes</i> is NULL, memory will be internally allocated.
 * @param[in,out] size Will be set to the number of bytes written in <i>*bytes</i>.
 * @param[in] sig The signature to export.
 *
 * @return IOK or IERROR
 */
int ps16_signature_export(byte_t **bytes,
			  uint32_t *size,
			  groupsig_signature_t *signature);

/** 
 * @fn groupsig_signature_t* ps16_signature_import(byte_t *source, uint32_t size)
 * @brief Imports a signature.
 *
 * Imports a PS16 signature from the specified array of bytes.
 * 
 * @param[in] source The array of bytes containing the signature to import.
 * @param[in] size The number of bytes in <i>source</i>.
 * 
 * @return A pointer to the imported signature, or NULL if error.
 */
groupsig_signature_t* ps16_signature_import(byte_t *source, uint32_t size);

/**
 * @var ps16_signature_handle
 * @brief Set of functions for managing PS16 signatures.
 */
static const groupsig_signature_handle_t ps16_signature_handle = {
  .scheme = GROUPSIG_PS16_CODE, /**< The scheme code. */
  .init = &ps16_signature_init,  /**< Initializes signatures. */
  .free = &ps16_signature_free, /**< Frees signatures. */
  .copy = &ps16_signature_copy, /**< Copies signatures. */
  .get_size = &ps16_signature_get_size, /**< Gets the size in bytes of a 
					   signature. */
  .gexport = &ps16_signature_export, /**< Exports signatures. */
  .gimport = &ps16_signature_import, /**< Imports signatures. */
  .to_string = &ps16_signature_to_string, /**< Converts signatures to 
					     printable strings. */
};

#endif

/* signature.h ends here */
