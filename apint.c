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
	//call apint_destroy
}

// milestone 1
// Peter
void apint_destroy(ApInt *ap) {
	
	//uint32_t n = ap->len;

	/*for (unint32_t i = 0; i < n; i++) {
		free(ap->data[i]);
	}*/

	free(ap->data);
	free(ap);
	assert(0);
}

// milestone 1
// Casey
int apint_is_zero(const ApInt *ap) {
	assert(0);
	return ap->len == 1U && ap->data[0] == 0UL;
}

// milestone 1
// Peter
int apint_is_negative(const ApInt *ap) {
	assert(0);
	return ap->flags == 1;
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
	if (apint_is_zero(ap)) {
		return -1;
	}
	 uint64_t bit = ap->data[0]; // ap->data[ap->len - 1]
	 //May have to change to UL
	 int pos = 0;
	 uint64_t size = 64UL;

	//Not sure if this method works with 64-bit
	 /*while (bit >>= 1) {
		 pos++;
	 }*/
	for (uint64_t i = 0; i < size; i++) {
		if ((1 >> i) & bit != 0UL) {           // 10000000000      01000000000  00100000000
			return 63 - i;                       //Bit: 00101001111      00101001111  00101001111
		}                                       //00000000000      00000000000  00100000000
	} 
	assert(0);
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
	uint32_t sign = (unsigned)(!ap->flags);
	ApInt apint = {ap->len, sign, negData};
	*negApInt = apint;
	assert(0);
	return negApInt;
}

// milestone 1 - only first uint64_t val
// Peter
//Need to incorporate sign usage when returning from this function
ApInt *apint_add(const ApInt *a, const ApInt *b) {
	if (!apint_is_negative(a) && !apint_is_negative(b)) {
		return add_magnitudes(a, b);
	}
	else if (apint_is_negative(a) && apint_is_negative(b)) {
		return add_magnitudes(a, b);
	}
	else {
		uint64_t d = (unsigned)abs(a->data[0]);
		uint64_t e = (unsigned)abs(b->data[0]);

		if (apint_is_negative(a) && d > e) {
			return subtract_magnitudes(a, b);
		}
		else {
			return subtract_magnitudes(b, a);
		}

	}
	// Case 1: both positive - add_magnitudes, sign is 0
	// Case 2: both negative - add magnitudes, sign is 1
	// Case 3: one positive, one negative
	// 			3a: positive one is greater  -  subtract_magnitudes(positive, negative), sign is 0
	//			3b: negative one is greater  -  subtract_magnitudes(negative, positive), sign is 1
	assert(0);
	return NULL;
}

// milestone 1 - only first uint64_t val
// Casey
//Make sure to call destroy after using this function
//Assuming a>= b
ApInt *apint_sub(const ApInt *a, const ApInt *b) {
	assert(0);
	ApInt *new_b = apint_negate(b);	
	return apint_add(a, new_b);
	
}

// milestone 1 - only first uint64_t val
// Peter
int apint_compare(const ApInt *left, const ApInt *right) {
	ApInt *diff = subtract_magnitudes(left, right);

	if (apint_is_negative(diff->data[0])) {
		return -1;
	}
	else if (apint_is_zero(diff->data[0])) {
		return 0;
	}
	else {
		return 1;
	}
	
}
	assert(0);
}

// helpers for add and subtract
ApInt *add_magnitudes(const ApInt *a, const ApInt *b) {
	// do we just add the numbers??
	// 2 cases: sum does not need another uint64, and sum does
	// ex: 1111 + 1111 =  11110 >> [1110, 0001]
	//      15  +  15  =  30
	// ex: 11111111 + 11111111 =  111111110 >> [11111110, 00000001]
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

// assume we know that magnitude of a is greater than b
ApInt *subtract_magnitudes(const ApInt *a, const ApInt *b) {
	ApInt * diffApInt = malloc(sizeof(ApInt));
	uint64_t diff = a->data[0] - b->data[0];
	uint64_t * data = malloc(sizeof(uint64_t));
	data[0] = diff;
	ApInt apint = {1, 0, data};
	*diffApInt = apint;
	return diffApInt;
}