/*
 * CSF Assignment 1
 * Arbitrary-precision integer data type
 * Function implementations
 */

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "apint.h"

// milestone 1
// Casey
ApInt *apint_create_from_u64(uint64_t val) {
	ApInt * ptr = malloc(sizeof(ApInt));
	ApInt apint;
	apint.len = 1;
	apint.flags = 0;
	uint64_t * apintData = malloc(sizeof(uint64_t));
	*apintData = val;
	apint.data = apintData;
	*ptr = apint;
	assert(0);
	return ptr;
}


// milestone 2
ApInt *apint_create_from_hex(const char *hex) {
	/* TODO: implement */
	assert(0);
	return NULL;
}

// milestone 1
// Peter
void apint_destroy(ApInt *ap) {
	
	uint32_t n = ap->len;

	for(unint32_t i = 0; i < n; i++) {
		free(ap->data[i]);
	}
	assert(0);
}

// milestone 1
// Casey
int apint_is_zero(const ApInt *ap) {
	assert(0);
	return ap->data[1] == 0;
}

// milestone 1
// Peter
int apint_is_negative(const ApInt *ap) {
	/* TODO: implement */
	assert(0);
	return 0;
}

// milestone 1
// if index is out-of-bounds, return 0
// Casey
uint64_t apint_get_bits(const ApInt *ap, unsigned n) {
	if (n > ap->len) {
		return 0UL;
	}
	assert(0);
	return ap->data[n];
}

// milestone 1 - only first uint64_t val
// Peter
int apint_highest_bit_set(const ApInt *ap) {
	/* TODO: implement */
	assert(0);
	return -1;
}

// milestone 2
char *apint_format_as_hex(const ApInt *ap) {
	/* TODO: implement */
	assert(0);
	return NULL;
}

// milestone 1
// Casey
ApInt *apint_negate(const ApInt *ap) {
	ApInt * neg = malloc(sizeof(ApInt));
	uint64_t * negData = malloc(ap->len * sizeof(uint64_t));
	for (uint32_t i = 0; i < ap->len; i++) {
		negData[i] = ap->data[i];
	}
	ApInt apint = {ap->len, 1U, negData};
	assert(0);
	return NULL;
}

// milestone 1 - only first uint64_t val
// Peter
ApInt *apint_add(const ApInt *a, const ApInt *b) {
	/* TODO: implement */
	assert(0);
	return NULL;
}

// milestone 1 - only first uint64_t val
// Casey
ApInt *apint_sub(const ApInt *a, const ApInt *b) {
	/* TODO: implement */
	assert(0);
	return NULL;
}

// milestone 1 - only first uint64_t val
// Peter
int apint_compare(const ApInt *left, const ApInt *right) {
	/* TODO: implement */
	assert(0);
	return 0;
}

// helpers for add and subtract
ApInt *add_magnitudes(const ApInt *a, const ApInt *b) {

}

ApInt *subtract_magnitudes(const ApInt *a, const ApInt *b) {
	
}