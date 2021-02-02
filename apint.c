/*
 * CSF Assignment 1
 * Arbitrary-precision integer data type operations
 * Function implementations
 * Casey Levitt and Peter Novello
 * clevitt1@jhu.edu and pnovell1@jhu.edu
 */

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "apint.h"
#include <stdio.h>

/*
 * Creates an and allocates a ApInt object that represents
 * the given uint64_t value
 * 
 * Parameters:
 * 	val - the uint64_t value to be represented
 * 
 * Returns:
 *  pointer to the dynamically allocated ApInt object
 */
ApInt *apint_create_from_u64(uint64_t val) {
	ApInt * ptr = malloc(sizeof(ApInt));
	ApInt apint;
	apint.len = 1U;
	apint.flags = 0U;
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


/*
 * Frees any allocated memory associated with an ApInt object
 * 
 * Parameters:
 * 	ap - a pointer to an ApInt object
 * 
 */
void apint_destroy(ApInt *ap) {
	free(ap->data);
	free(ap);
}


/*
 * Determines whether the given ApInt object represents the value 0
 * 
 * Parameters:
 * 	ap - a pointer to an ApInt object
 * 
 * Returns:
 *  0 - if the value is not 0
 *  1 - if the value is 0
 * 
 */
int apint_is_zero(const ApInt *ap) {
	assert(ap->len >= 1);
	return ap->len == 1U && ap->data[0] == 0UL;
}


/*
 * Determines whether or not an ApInt object represents a negative value,
 * which is useful when performing arithmetic operations such as addition
 * and subtraction
 * 
 * Parameters:
 * 	ap - a pointer to an ApInt object
 * 
 * Returns:
 * 	0 - if the value is not negative
 *  1 - if the value is negative
 * 
 */
int apint_is_negative(const ApInt *ap) {
	return ap->flags == 1 && !apint_is_zero(ap);
}


/*
 * Gets 64 bits of the value represented by the ApInt ap,
 * as determined by the value n
 * n = 0: bits 0-63
 * n = 1: bits 64-127
 * etc.
 * 
 * Parameters:
 * 	ap - a pointer to an ApInt object
 *  n  - an unsigned int indicating which bits to return
 * 
 * Returns:
 * 	a uint64_t value containing the 64 bits
 */
uint64_t apint_get_bits(const ApInt *ap, unsigned n) {
	assert(ap->len >= 1UL);
	if (n >= ap->len) {
		return 0UL;
	}
	return ap->data[n];
}


/*
 * Determines the highest bit set in the represntation of the 64-bit
 * value stored in the first element of the data field for an ApInt
 * object.
 * 
 * Parameters:
 * 	ap - a pointer to an ApInt object
 * 
 * Returns:
 * 	An integer representing the power of the highest bit set to represent
 * 	the first element of the ApInt object's data array
 * 
 */
int apint_highest_bit_set(const ApInt *ap) {
	if (apint_is_zero(ap)) {
		return -1;
	}
	 uint64_t bits = ap->data[ap->len - 1];
	 uint64_t size = 64UL;
	for (uint64_t i = 0; i < size; i++) {
		if (((0x8000000000000000 >> i) & bits) != 0) {   
			return 63 - i;                                       
		}           
	}
	return 0; 
}


/*
 * Finds the hexadecimal representation of the value of the ApInt 
 * instance pointed to by ap, returns it as a dynamically allocated
 * character string
 * 
 * Parameters:
 * 	ap - a pointer to the ApInt object to be represented in hex
 * 
 * Returns:
 * 	a pointer to the character string of hexadecimal digits
 */
char *apint_format_as_hex(const ApInt *ap) {
	if (apint_is_zero(ap)) {
		char * zeroString = malloc(2 * sizeof(char));
		zeroString[0] = '0';
		zeroString[1] = '\0';
		return zeroString;
	}
	char backwardsHex[16 * ap->len + 1]; // 64-bit value needs 16 hex digits, plus sign character
	uint32_t hexLength = 0U;
	for (uint32_t i = 0; i < ap->len; i++) {
		uint64_t num = ap->data[i];
		if (num == 0UL) {
			for (int j = 0; j < 16; j++) {
				backwardsHex[hexLength] = '0';
				hexLength++;
			}
			continue;
		}
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
	}
	if (apint_is_negative(ap)) {
		backwardsHex[hexLength] = '-';
		hexLength++;
	} // hex digits are calculated in reverse order - need to flip them
	char * forwardsHex = malloc(hexLength * sizeof(char) + 1);
	for (uint32_t i = 0; i < hexLength; i++) {
		forwardsHex[i] = backwardsHex[hexLength - 1 - i];
	}
	forwardsHex[hexLength] = '\0';
	return forwardsHex;
}

/*
 * Creates and allocates a new ApInt object that represents the
 * negation of the value in the given ApInt instance
 * 
 * Parameters:
 * 	ap - a pointer to the ApInt object to be negated
 * 
 * Returns:
 * 	a pointer to the negated ApInt object
 */
ApInt *apint_negate(const ApInt *ap) {
	ApInt * negApInt = malloc(sizeof(ApInt));
	uint64_t * negData = malloc(ap->len * sizeof(uint64_t));
	for (uint32_t i = 0; i < ap->len; i++) { // deep copy of uint64_t data array
		negData[i] = ap->data[i];
	}
	uint32_t sign;
	if (ap->flags == 0U && !apint_is_zero(ap)) { 
		sign = 1U;
	}
	else {
		sign = 0U;
	}
	ApInt apint = {ap->len, sign, negData};
	*negApInt = apint;
	return negApInt;
}

/*
 * Computes the sum of the first elements from the data array in 
 * two separate Apint objects. The function uses the add_magnitudes 
 * and subtract_magnitudes helper functions to handle the appropriate 
 * calculations, which is dependent on whether or not the values
 * being added are positive or negative
 * 
 * Parameters:
 * a - a pointer to an ApInt object
 * b - a ponter to an ApInt object
 * 
 * Returns:
 *  a pointer to the new dynamically allocated ApInt instance
 *  representing the sum a + b
 * 
 */
ApInt *apint_add(const ApInt *a, const ApInt *b) {
	if (!apint_is_negative(a) && !apint_is_negative(b)) {
		return add_magnitudes(a, b);
	}
	else if (apint_is_negative(a) && apint_is_negative(b)) {
		ApInt *sum = add_magnitudes(a, b);
		sum->flags = 1UL;
		return sum;
	} // case that one is positive, one is negative
	uint64_t d = a->data[0];
	uint64_t e = b->data[0];
	ApInt *diff;
	if (d > e) { // magnitude of a is greater
		diff = subtract_magnitudes(a, b);
		if (apint_is_negative(a)) {
			diff->flags = 1UL;
		}
		return diff;
	}  // magnitude of b is greater
	diff = subtract_magnitudes(b, a);
	if (apint_is_negative(b) && d != e) {
		diff->flags = 1UL;
	}
	return diff;
}

/*
 * Computes the difference between the values represented by the given 
 * Apint objects. Specifically, it subtracts the value represented by b
 * from the value represented by a, and returns a new ApInt instance
 * containing this difference
 * 
 * Parameters:
 * a - a pointer to the ApInt object to subtract b from
 * b - a ponter to the ApInt object to subtract from a
 * 
 * Returns:
 *  a pointer to the new dynamically allocated ApInt instance
 *  representing the difference a - b
 * 
 */
ApInt *apint_sub(const ApInt *a, const ApInt *b) {
	ApInt *new_b = apint_negate(b);	
	ApInt *diff = apint_add(a, new_b);
	apint_destroy(new_b);
	return diff;
}

/*
 * Compares the values represented by the given ApInt instances. Returns
 * a positive value if left is greater and a negative value if right is
 * greater
 * 
 * Parameters:
 * left - a pointer to an ApInt object
 * right - a ponter to an ApInt object
 * 
 * Returns:
 *  an int indicating which ApInt value is greater
 * 
 */
int apint_compare(const ApInt *left, const ApInt *right) {
	int leftSign = apint_is_negative(left);
	int rightSign = apint_is_negative(right);
	if (leftSign != rightSign) { // case that one is positive and the other negative
		return rightSign - leftSign;
	} 
	if (left->len != right->len) { // case that the lengths are different
		if (leftSign == 0) {
			return left->len - right->len;
		}
		return right->len - left->len;
	}
	// apints have the same length
	return left->data[0] - right->data[0];
}

/* 
 * Helper function for apint_add and apint_sub, computes the sum of the magnitudes
 * represented by two different pointers to ApInt objects. Returns a new ApInt
 * object representing the positive sum of the magnitudes
 * 
 * Parameters:
 *  a - a pointer to an ApInt object
 *  b - a pointer to an Apint object
 * 
 * Returns:
 * 	sumApInt- a pointer to an ApInt object holding the magnitude
 * 	sum of the values represented by a and b
 * 
 */
ApInt *add_magnitudes(const ApInt *a, const ApInt *b) {
	ApInt * sumApInt = malloc(sizeof(ApInt));
	uint64_t sum = a->data[0] + b->data[0];
	if (sum < a->data[0] || sum < b->data[0]) { // case that addition of uint64_t values caused overflow
		uint64_t * data = malloc(2 * sizeof(uint64_t));
		data[0] = sum;
		data[1] = 1UL;
		ApInt apint = {2U, 0U, data};
		*sumApInt = apint;
	} else { // cast that there was no overflow
		uint64_t * data = malloc(sizeof(uint64_t));
		data[0] = sum;
		ApInt apint = {1U, 0U, data};
		*sumApInt = apint;
	}
	return sumApInt;
}

/* 
 * Helper function for apint_add and apint_sub, computes the difference between
 * the magnitudes represented by two ApInt objects. Returns a new ApInt
 * object representing the positive difference of the magnitudes
 * 
 * Parameters:
 *  a - a pointer to an ApInt object with a magnitude greater than b
 *  b - a pointer to an Apint object with a magnitude less than a
 * 
 * Returns:
 * 	a pointer to an ApInt object holding the difference between the magnitudes
 * 	of the values represented by a and b
 */
ApInt *subtract_magnitudes(const ApInt *a, const ApInt *b) {
	ApInt * diffApInt = malloc(sizeof(ApInt));
	uint64_t diff = a->data[0] - b->data[0];
	uint64_t * data = malloc(sizeof(uint64_t));
	data[0] = diff;
	ApInt apint = {1, 0, data};
	*diffApInt = apint;
	return diffApInt;
}