/*
 * CSF Assignment 1
 * Arbitrary-precision integer data type
 * Function implementations
 */

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "apint.h"
#include <stdio.h>

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
	return ptr;
}


// milestone 2
ApInt *apint_create_from_hex(const char *hex) {
	/* TODO: implement */
	// assert(0);
	return NULL;
}

// milestone 1
// Peter
void apint_destroy(ApInt *ap) {
	free(ap->data);
	free(ap);
}

// milestone 1
// Casey
int apint_is_zero(const ApInt *ap) {
	assert(ap->len >= 1);
	return ap->len == 1U && ap->data[0] == 0UL;
}

// milestone 1
// Peter
int apint_is_negative(const ApInt *ap) {
	// assert(0);
	return ap->flags == 1 && !apint_is_zero(ap);
}

// milestone 1
// if index is out-of-bounds, return 0
// Casey
uint64_t apint_get_bits(const ApInt *ap, unsigned n) {
	assert(ap->len >= 1);
	if (n > ap->len) {
		return 0UL;
	}
	return ap->data[n];
}

// milestone 1 - only first uint64_t val
// Peter
int apint_highest_bit_set(const ApInt *ap) {
	if (apint_is_zero(ap)) {
		return -1;
	}

	if(ap->data[0] == 1UL) {
		return 0;
	}
	 uint64_t bits = ap->data[ap->len - 1];
	 uint64_t size = 64UL;

	//Not sure if this method works with 64-bit
	 /*while (bit >>= 1) {
		 pos++;
	 }*/
	for (uint64_t i = 0; i < size; i++) {
		if (i == 63UL) {
			printf("%ld", bits);
			printf("%ld", 0x7FFFFFF76B48C000 >> i);
		}
		if (((0x7FFFFFF76B48C000 >> i) & bits) != 0) {           // 10000000000      01000000000  00100000000
			return 63 - i;                       //Bit: 00101001111      00101001111  00101001111
		}                                       //00000000000      00000000000  00100000000
	}
	return 0; 
}

// Casey
// milestone 2 - only for first uint64_t val
char *apint_format_as_hex(const ApInt *ap) {
	uint64_t num = ap->data[0];
	// the max hex values needed for a 64-bit value is 16
	char backwardsHex[16 * ap->len];
	uint32_t hexLength = 0;
	while(num > 0) {
		char hexDigit = num % 16;
		if (hexDigit <= 9) {
			backwardsHex[hexLength] = hexDigit + '0';
		}
		else {
			backwardsHex[hexLength] = hexDigit - (char)10 + 'a';
		}
		hexLength++;
		num -= hexDigit;
		num = num/16;
	}
	char * forwardsHex = malloc(hexLength * sizeof(char) + 1);
	for (uint32_t i = 0; i < hexLength; i++) {
		forwardsHex[i] = backwardsHex[hexLength - 1 - i];
	}
	forwardsHex[hexLength] = '\0';
	return forwardsHex;
}

// milestone 1
// Casey
ApInt *apint_negate(const ApInt *ap) {
	ApInt * negApInt = malloc(sizeof(ApInt));
	uint64_t * negData = malloc(ap->len * sizeof(uint64_t));
	for (uint32_t i = 0; i < ap->len; i++) {
		negData[i] = ap->data[i];
	}
	uint32_t sign;
	if (apint_is_zero(ap)) {
		sign = ap->flags;
	} else {
		sign = (unsigned)(!ap->flags);
	}
	ApInt apint = {ap->len, sign, negData};
	*negApInt = apint;
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
		ApInt *sum = add_magnitudes(a, b);
		sum->flags = 1;
		return sum;
	}
	else {
		uint64_t d = (unsigned)a->data[0];
		uint64_t e = (unsigned)b->data[0];
		ApInt *diff;
		if (d > e) { // magnitude of a is greater
			diff = subtract_magnitudes(a, b);
			if (apint_is_negative(a)) {
				diff->flags = 1;
			}
			return diff;
		} else { // magnitude of b is greater
			diff = subtract_magnitudes(b, a);
			if (d == e) {
				return diff;
			}
			if (apint_is_negative(b)) {
				diff->flags = 1;
			}
			return diff;
		}

	}

	// assert(0);
	return NULL;
}

// milestone 1 - only first uint64_t val
// Casey
ApInt *apint_sub(const ApInt *a, const ApInt *b) {
	ApInt *new_b = apint_negate(b);	
	return apint_add(a, new_b);
	
}

// milestone 1 - only first uint64_t val
// Peter
int apint_compare(const ApInt *left, const ApInt *right) {
	int leftSign = apint_is_negative(left);
	int rightSign = apint_is_negative(right);
	if (leftSign != rightSign) { // where one is 0 and the other is 1
		return rightSign - leftSign;
	} 
	// apints have same sign
	if (left->len != right->len) {
		if (leftSign == 0) {
			return left->len - right->len;
		}
		return right->len - left->len;
	}
	// apints have the same length
	return left->data[0] - right->data[0]; // to generalize, can start at most significant val and move down


	
}

// only first uint64_t val
// helpers for add and subtract
ApInt *add_magnitudes(const ApInt *a, const ApInt *b) {
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

// only first uint64_t val
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