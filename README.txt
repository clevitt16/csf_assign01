Casey Levitt and Peter Novello
clevitt1@jhu.edu and pnovell1@jhu.edu

Casey:

Worked on apint_create_from_u64, apint_is_zero, apint_get_bits, 
apint_highest_bit_set, apint_format_as_hex, apint_negate, apint_add, 
apint_compare, and add_magnitudes functions. For the unit testing, 
Casey worked on testApintGetBits, testApintIsZero, and test ApintIsNegative.

Peter:

Worked on apint_destroy, apint_is_negative, apint_highest_bit_set, 
apint_negate, apint_add, apint_sub, and subtract_magnitudes. 
For the unit testing, Peter worked on testNegate.


from add_magnitudes

	if (sum < a->data[0] || sum < b->data[0]) { // case that addition of uint64_t values caused overflow
		uint64_t * data = malloc(2 * sizeof(uint64_t));
		data[0] = sum;
		data[1] = 1UL; // will always be 000...0001
		ApInt apint = {2U, 0U, data};
		*sumApInt = apint;
	} else { // cast that there was no overflow
		uint64_t * data = malloc(sizeof(uint64_t));
		data[0] = sum;
		ApInt apint = {1U, 0U, data};
		
	}

notes on create_from_hex

	//check if size is 0 
	//check for negative in get size
	// run a loop based on number of hex chars
	//set variable to track cur index , start from len - 1
	//every 16 hex char - decrease index by 1
	//char convert to int 
	//bitwise OR for left shifting by 4

from get_valid_size
	if (!*p) { // is this necessary? this is checking for null terminator
		return 0;
	}

from create_from_hex

		if (c == -1) {  // need to free the pointers first!
			free(data);
			free(ptr);
			return NULL;
		}