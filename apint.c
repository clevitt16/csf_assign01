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
	/* TODO: implement */
	assert(0);
}

// milestone 1
// Casey
int apint_is_zero(const ApInt *ap) {
	assert(0);
	return ap->len == 1U && ap->data[1] == 0UL;
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
	ApInt * negApInt = malloc(sizeof(ApInt));
	uint64_t * negData = malloc(ap->len * sizeof(uint64_t));
	for (uint32_t i = 0; i < ap->len; i++) {
		negData[i] = ap->data[i];
	}
	ApInt apint = {ap->len, 1U, negData};
	*negApInt = apint;
	assert(0);
	return negApInt;
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
	// do we just add the numbers??
	// 2 cases: sum does not need another uint64, and sum does
	// ex: 1111 + 1111 =  11110 >> [1110, 0001]
	//      15  +  15  =  30
	// ex: 11111111 + 11111111 =  111111110 >> [11111110, 0001]
	//      255  +  255  =  610
	// so even if both values are maxed out, the max new place value will be a 1 in the next bit
	// assumes that lengths of both are 1 (use assert!)
	ApInt * sumApInt = malloc(sizeof(ApInt));
	uint64_t sum = a->data[0] + b->data[0];
	if (sum < a->data[0] || sum < b->data[0]) {
		uint64_t * data = malloc(2 * sizeof(uint64_t));
		data[0] = sum;
		data[1] = 1UL;
		ApInt apint = {2, 0, data};
		*sumApInt = apint;
	} else {
		uint64_t * data = malloc(sizeof(uint64_t));
		data[0] = sum;
		ApInt apint = {1, 0, data};
		*sumApInt = apint;
	}
	return sumApInt;
}

ApInt *subtract_magnitudes(const ApInt *a, const ApInt *b) {
	
}