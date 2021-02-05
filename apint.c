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

// could use strtol()
// Peter
ApInt *apint_create_from_hex(const char *hex) {
	ApInt * ptr = malloc(sizeof(ApInt));
	ApInt apint;
	int size = getSize(hex);
	//check if size is 0 
	//check for negative in get size
	// run a loop based on number of hex chars
	//set variable to track cur index , start from len - 1
	//every 16 hex char - decrease index by 1
	//char convert to int 
	//bitwise OR for left shifting by 4

	uint32_t len = ((size - 1)/ 16) + 1;

	apint.len = len;
	apint.flags = 0U;
	uint64_t * data = malloc(sizeof(uint64_t) * len);

	return ptr;
}

//returns size of hex character pointer
int getSize(const char *hex) {
	char * p;
	int size = 0;

	while (*p == '0') {
		p++;
	}

	if (!*p) {
		return 0;
	}

	for (p = hex; *p != '\0'; p++) {
		
		if (*p == '-') {
			continue;
		}
		size++;
	}
	return size;
}

//used to get value from a specific character
int getVal(const char c) {
	
	int val = c - '0';
	
	if (val <= 9) {
		return val;
	}
	else if (val >= 17 && val <= 22) {
		return val - 7;
	}
	else if (val >= 49 && val <= 54) {
		return val - 39;
	}
	else {
		return -1;
	}

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
 * TO DO
 *
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
 * TO DO - Casey
 * 
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
	if (apint_is_zero(left) && apint_is_zero(right)) { // can delete
		return 0;
	}
	int leftSign = apint_is_negative(left);
	int rightSign = apint_is_negative(right);
	if (leftSign != rightSign) { // case that one is positive and the other negative
		return rightSign - leftSign;
	} 
	if (left->len > right->len) { // case of same sign, different lengths
		if (leftSign == 0) {
			return 1;
		}
		return -1;
	}
	else if (right->len > left->len) {
		if (rightSign == 0) {
			return -1;
		}
		return 1;
	}
	
	// apints have the same length and are either both positive or both negative
	// will compare largest place values
	uint32_t index = left->len - 1;
	while (left->data[index] == right->data[index]) {
		if (index == 0U) {
			return 0;
		}
		index--;
	} // most significant values that differ are at index
	if (leftSign == 0) { // positive values:
		if (left->data[index] > right->data[index]) {
			return 1;
		}
		return -1;
	} // negative values:
	if (left->data[index] < right->data[index]){
			return 1;
		}
	return -1;
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
// will change this to add values with any-legnth data arrays
ApInt *add_magnitudes(const ApInt *a, const ApInt *b) {
	ApInt * sumApInt = malloc(sizeof(ApInt));
	uint64_t * sumData;
	uint32_t longerLength;
	if (a->len >= b->len) {
		longerLength = a->len;
	} else {
		longerLength = b->len;
	}
	sumData = malloc((longerLength + 1) * sizeof(uint64_t)); //  can allocate one extra space for overflow, but use length to not access it
	uint64_t carry = 0UL;
	uint32_t index = 0U; // effectively the length
	for (; index < longerLength; index++) {
		uint64_t aVal, bVal;
		if (index >= a->len) {
			aVal = 0UL;
		} else {
			aVal = a->data[i];
		}
		if (index >= b->len) {
			bVal = 0UL;
		} else {
			bVal = b->data[i];
		}
		uint64_t sum = aVal + bVal + carry;
		if (sum < aVal || sum < bVal) { // case that addition of uint64_t values caused overflow
			carry = 1UL;
		} else {
			carry = 0UL;
		} 
		sumData[i] = sum;
	} // at this point, index = longerLength
	if (carry == 1UL) {
		sumData[i] = carry;
		index++;
	}
	ApInt apint = {index, 0U, sumData};
	*sumApInt = apint;
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

/*
*   Assume we have uint4_t values
            val1: 1011 0111
			val2: 1001 1111
*      need to add 1011 + 1001 first, and then if there's overflow, we add 0001 + 0111 + 1111

      1011
	  1001



          1111
		  0011
	 	 10010 

*    assuming we have both positive or both negative values of the same length
*    for each array element:
*         add using add_magnitudes, place sum (the single uint16_t in corresponding value in new ApInt)
*         if the previous sum had overflow, add 0000...01 to the next place
*    if there was overflow on the last sum, add another array element of 0000...01
*
*
*    assuming we have both positive or both negative values of different lengths:
*      compare lengths
*      for each array element in smaller-length ApInt
*          add using add_magnitudes, place sum (the single uint16_t in corresponding value in new ApInt)
*          if the previous sum had overflow, add 0000...01 to the next place
*      for each remaining array value in longer ApInt
*          append to new array
*          *make sure to check if there's overflow from the last actual addition*
*
*
*
*
*
*   Assume we have uint4_t values
            val1: 1011 1111   11 + 240 = 251  
			val2: 1101 0111   13 + 112 = 125       difference should be 126
*      need to subtract 1011 - 1001 
*
*         0*11        ****
*         1101        0111
*         1110        0111        =     14 + 112 = 126
*
*    assuming we have a larger positive value (A) and a smaller negative (B) value of the same length
*       for each array element
*            check which uint64_t value is greater
*                 if the value from A is greater, call subtract magnitudes, put that difference in the new ApInt, continue
                  if the value from B is greater, subtract A value from B value, add most significant bit

				  1101
				  0111
				  0110
*                 
*         
*       
*
*
*/