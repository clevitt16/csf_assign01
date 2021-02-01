This file should contain the names of the team members, and
should briefly summarize each team member's contributions to the
code.

Notes:

On add_magnitudes:

	// do we just add the numbers??
	// 2 cases: sum does not need another uint64, and sum does
	// ex: 1111 + 1111 =  11110 >> [1110, 0001]
	//      15  +  15  =  30
	// ex: 11111111 + 11111111 =  111111110 >> [11111110, 00000001]
	//      255  +  255  =  610
	// so even if both values are maxed out, the max new place value will be a 1 in the next bit
	// assumes that lengths of both are 1 (use assert!)


Adding logic:

	// Case 1: both positive - add_magnitudes, sign is 0
	// Case 2: both negative - add magnitudes, sign is 1
	// Case 3: one positive, one negative
	// 			3a: positive one is greater  -  subtract_magnitudes(positive, negative), sign is 0
	//			3b: negative one is greater  -  subtract_magnitudes(negative, positive), sign is 1