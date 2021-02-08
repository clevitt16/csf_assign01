Casey Levitt and Peter Novello
clevitt1@jhu.edu and pnovell1@jhu.edu

Casey:

Worked on apint_create_from_u64, apint_is_zero, apint_get_bits, 
apint_highest_bit_set, apint_format_as_hex, apint_negate, apint_add, 
apint_compare, add_magnitudes, and compare_magnitudes functions. For the unit testing, 
Casey worked on testApintGetBits, testApintIsZero, testApintIsNegative, testAdd, testAddSingle 
testSub, and testSubSingle

Peter:

Worked on apint_destroy, apint_is_negative, apint_highest_bit_set, 
apint_negate, apint_add, apint_sub, subtract_magnitudes, apint_create_from_hex,
getVal, getValidSize, and getFullSize.
For the unit testing, Peter worked on testNegate and testCreateFromHex


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

			//000AFCB5    AFCB5
	//size = 8    5
	//  8 - 5 = 3, which is index of the first non-zero hex char


from compare 

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




 Assume we have uint4_t values
            val1: 1011 0111
			val2: 1001 1111
      need to add 1011 + 1001 first, and then if there's overflow, we add 0001 + 0111 + 1111

      1011
	  1001



          1111
		  0011
	 	 10010 
   assuming we have both positive or both negative values of the same length
   for each array element:
         add using add_magnitudes, place sum (the single uint16_t in corresponding value in new ApInt)
         if the previous sum had overflow, add 0000...01 to the next place
    if there was overflow on the last sum, add another array element of 0000...01


    assuming we have both positive or both negative values of different lengths:
      compare lengths
      for each array element in smaller-length ApInt
        add using add_magnitudes, place sum (the single uint16_t in corresponding value in new ApInt)
          if the previous sum had overflow, add 0000...01 to the next place
      for each remaining array value in longer ApInt
          append to new array
          *make sure to check if there's overflow from the last actual addition
   Assume we have uint4_t values
            val1: 1011 1111   11 + 240 = 251  
			val2: 1101 0111   13 + 112 = 125       difference should be 126      need to subtract 1011 - 1001 

         0*11        ****
         1101        0111
         1110        0111        =     14 + 112 = 126

    assuming we have a larger positive value (A) and a smaller negative (B) value of the same length
      for each array element
            check which uint64_t value is greater
                if the value from A is greater, call subtract magnitudes, put that difference in the new ApInt, continue
                  if the value from B is greater, subtract A value from B value, add most significant bit

				  1101
				  0111
				  0110
