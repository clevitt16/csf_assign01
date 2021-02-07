/*
 * Unit tests for arbitrary-precision integer data type
 *
 * These tests are by no means comprehensive.  You will need to
 * add more tests of your own!  In particular, make sure that
 * you have tests for more challenging situations, such as
 *
 * - large values
 * - adding/subtracting/comparing values with different lengths
 * - special cases (carries when adding, borrows when subtracting, etc.)
 * - etc.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "apint.h"
#include "tctest.h"

typedef struct {
	ApInt *ap0;
	ApInt *ap1;
	ApInt *ap110660361;
	ApInt *max1;
	ApInt *minus1;
	// ApInts multi-array representing positive numbers , increasing magnitude
	ApInt *hex1;
	ApInt *hex2;
	ApInt *hex3;
	ApInt *hex4;
	ApInt *hex5;

	ApInt *hex6;
	ApInt *hex7;
	ApInt *hex8;
	ApInt *hex9;
	ApInt *hex10;

	// ApInts multi-array representing negative numbers , increasing magnitude
	ApInt *nhex1;
	ApInt *nhex2;
	ApInt *nhex3;
	ApInt *nhex4;
	ApInt *nhex5;

	ApInt *nhex6;
	ApInt *nhex7;
	ApInt *nhex8;
	ApInt *nhex9;
	ApInt *nhex10;
} TestObjs;

TestObjs *setup(void);
void cleanup(TestObjs *objs);

void testCreateFromU64(TestObjs *objs);
void testCreateFromHex(TestObjs *objs);
void testApintIsZero(TestObjs *objs);
void testApintIsNegative(TestObjs *objs);
void testApintGetBits(TestObjs *objs);
void testHighestBitSet(TestObjs *objs);
void testFormatAsHex(TestObjs *objs);
void testNegate(TestObjs *objs);
void testAddSingle(TestObjs *objs);
void testSubSingle(TestObjs *objs);
void testCompareSingle(TestObjs *objs);
/* TODO: add more test function prototypes */

int main(int argc, char **argv) {
	TEST_INIT();

	if (argc > 1) {
		/*
		 * name of specific test case to execute was provided
		 * as a command line argument
		 */
		tctest_testname_to_execute = argv[1];
	}
/*
	TEST(testCreateFromU64);
	TEST(testCreateFromHex);
	TEST(testApintIsZero);
	TEST(testApintIsNegative);
	TEST(testApintGetBits);
	TEST(testHighestBitSet);
	TEST(testFormatAsHex);
	TEST(testNegate);
	TEST(testAddSingle);
	TEST(testSubSingle);
	TEST(testCompareSingle); */
	/* TODO: use TEST macro to execute more test functions */

	TEST_FINI();
}

TestObjs *setup(void) {
	TestObjs *objs = malloc(sizeof(TestObjs));
	objs->ap0 = apint_create_from_u64(0UL);
	objs->ap1 = apint_create_from_u64(1UL);
	objs->ap110660361 = apint_create_from_u64(110660361UL);
	objs->max1 = apint_create_from_u64(0xFFFFFFFFFFFFFFFFUL);
	objs->minus1 = apint_negate(objs->ap1);

	char * h1 = "10000000000000000";
	char * h2 = "a410000002200004500";
	char * h3 = "000222bac888a410024da0022037804500";
	char * h4 = "1234567899b4b3ca410024da0022037804501";
	char * h5 = "100000000066cccfff8999b4b3ca410024da0022037804501";
	objs->hex1 = apint_create_from_hex(h1);
	objs->hex2 = apint_create_from_hex(h2);
	objs->hex3 = apint_create_from_hex(h3);
	objs->hex4 = apint_create_from_hex(h4);
	objs->hex5 = apint_create_from_hex(h5);

	char * h6 = "0000ff";
	char * h7 = "00000000";
	char * h8 = "001ABF00";
	char * h9 = "000007fb";
	char * h10 = "1357def";
	objs->hex6 = apint_create_from_hex(h6);
	objs->hex7 = apint_create_from_hex(h7);
	objs->hex8 = apint_create_from_hex(h8);
	objs->hex9 = apint_create_from_hex(h9);
	objs->hex10 = apint_create_from_hex(h10);


	char * n1 = "-10000000000000000";
	char * n2 = "-a410000002200004500";
	char * n3 = "-000222bac888a410024da0022037804500";
	char * n4 = "-1234567899b4b3ca410024da0022037804501";
	char * n5 = "-100000000066cccfff8999b4b3ca410024da0022037804501";
	objs->nhex1 = apint_create_from_hex(n1);
	objs->nhex2 = apint_create_from_hex(n2);
	objs->nhex3 = apint_create_from_hex(n3);
	objs->nhex4 = apint_create_from_hex(n4);
	objs->nhex5 = apint_create_from_hex(n5);


	char * n6 = "-0000ff";
	char * n7 = "-00000000";
	char * n8 = "-001ABF00";
	char * n9 = "-000007fb";
	char * n10 = "-1357def";
	objs->nhex6 = apint_create_from_hex(n6);
	objs->nhex7 = apint_create_from_hex(n7);
	objs->nhex8 = apint_create_from_hex(n8);
	objs->nhex9 = apint_create_from_hex(n9);
	objs->nhex10 = apint_create_from_hex(n10);

	return objs;
}

void cleanup(TestObjs *objs) {
	apint_destroy(objs->ap0);
	apint_destroy(objs->ap1);
	apint_destroy(objs->ap110660361);
	apint_destroy(objs->max1);
	apint_destroy(objs->minus1);
	/* TODO: destroy additional members of test fixture */
	apint_destroy(objs->hex1);
	apint_destroy(objs->hex2);
	apint_destroy(objs->hex3);
	apint_destroy(objs->hex4);
	apint_destroy(objs->hex5);
	apint_destroy(objs->hex6);
	apint_destroy(objs->hex7);
	apint_destroy(objs->hex8);
	apint_destroy(objs->hex9);
	apint_destroy(objs->hex10);
	apint_destroy(objs->nhex1);
	apint_destroy(objs->nhex2);
	apint_destroy(objs->nhex3);
	apint_destroy(objs->nhex4);
	apint_destroy(objs->nhex5);
	apint_destroy(objs->nhex6);
	apint_destroy(objs->nhex7);
	apint_destroy(objs->nhex8);
	apint_destroy(objs->nhex9);
	apint_destroy(objs->nhex10);
	free(objs);
}

void testCreateFromU64(TestObjs *objs) {
	ASSERT(0UL == apint_get_bits(objs->ap0, 0));
	ASSERT(1UL == apint_get_bits(objs->ap1, 0));
	ASSERT(110660361UL == apint_get_bits(objs->ap110660361, 0));
	ASSERT(0xFFFFFFFFFFFFFFFFUL == apint_get_bits(objs->max1, 0));
}

void testCreateFromHex(TestObjs *objs) {

	ASSERT(0x0000ffUL == apint_get_bits(objs->hex6, 0));
	ASSERT(0UL == apint_get_bits(objs->hex7, 0));
	ASSERT(0x001ABF00UL == apint_get_bits(objs->hex8, 0));
	ASSERT(0x000007fbUL == apint_get_bits(objs->hex9, 0));
	ASSERT(0x1357defUL == apint_get_bits(objs->hex10, 0));
	ASSERT(0x0000ffUL == apint_get_bits(objs->nhex6, 0));
	ASSERT(0UL == apint_get_bits(objs->nhex7, 0));
	ASSERT(0x001ABF00UL == apint_get_bits(objs->nhex8, 0));
	ASSERT(0x000007fbUL == apint_get_bits(objs->nhex9, 0));
	ASSERT(0x1357defUL == apint_get_bits(objs->nhex10, 0));


	char * test;
	//TODO: May run into issues with ignoring leading zeroes in create from hex
	ASSERT(0 == strcmp("10000000000000000", (test = apint_format_as_hex(objs->hex1))));
	free(test);
	
	ASSERT(0 == strcmp("a410000002200004500", (test = apint_format_as_hex(objs->hex2))));
	free(test);

	ASSERT(0 == strcmp("222bac888a410024da0022037804500", (test = apint_format_as_hex(objs->hex3))));
	free(test);

	ASSERT(0 == strcmp("1234567899b4b3ca410024da0022037804501", (test = apint_format_as_hex(objs->hex4))));
	free(test);

	ASSERT(0 == strcmp("100000000066cccfff8999b4b3ca410024da0022037804501", (test = apint_format_as_hex(objs->hex5))));
	free(test);


	ASSERT(0 == strcmp("ff", (test = apint_format_as_hex(objs->hex6))));
	free(test);

	ASSERT(0 == strcmp("0", (test = apint_format_as_hex(objs->hex7))));
	free(test);

	ASSERT(0 == strcmp("1ABF00", (test = apint_format_as_hex(objs->hex8))));
	free(test);

	ASSERT(0 == strcmp("7fb", (test = apint_format_as_hex(objs->hex9))));
	free(test);

	ASSERT(0 == strcmp("1357def", (test = apint_format_as_hex(objs->hex10))));
	free(test);
}

void testApintIsZero(TestObjs *objs) {
	ASSERT(apint_is_zero(objs->ap0));
	ASSERT(!apint_is_zero(objs->ap1));
	ASSERT(!apint_is_zero(objs->minus1));
	ASSERT(!apint_is_zero(objs->max1));
}

void testApintIsNegative(TestObjs *objs) {
	ASSERT(apint_is_negative(objs->minus1));
	ASSERT(!apint_is_negative(objs->ap0));
	ASSERT(!apint_is_negative(objs->ap1));
	ASSERT(!apint_is_negative(objs->max1));
	ASSERT(!apint_is_negative(objs->hex1));
	ASSERT(!apint_is_negative(objs->hex2));
	ASSERT(!apint_is_negative(objs->hex3));
	ASSERT(!apint_is_negative(objs->hex4));
	ASSERT(!apint_is_negative(objs->hex5));
	ASSERT(apint_is_negative(objs->nhex1));
	ASSERT(apint_is_negative(objs->nhex2));
	ASSERT(apint_is_negative(objs->nhex3));
	ASSERT(apint_is_negative(objs->nhex4));
	ASSERT(apint_is_negative(objs->nhex5));
	ASSERT(apint_is_negative(objs->nhex6));
	ASSERT(apint_is_negative(objs->nhex7));
	ASSERT(apint_is_negative(objs->nhex8));
	ASSERT(apint_is_negative(objs->nhex9));
	ASSERT(apint_is_negative(objs->nhex10));

}

void testApintGetBits(TestObjs *objs) {
	ASSERT(0UL == apint_get_bits(objs->ap0, 1));
	ASSERT(0UL == apint_get_bits(objs->ap110660361, 2));
	ASSERT(0UL == apint_get_bits(objs->max1, 1));
	ASSERT(0UL == apint_get_bits(objs->ap0, 0));
	ASSERT(1UL == apint_get_bits(objs->ap1, 0));
	ASSERT(1UL == apint_get_bits(objs->minus1, 0));
	ASSERT(110660361UL == apint_get_bits(objs->ap110660361, 0));
}


void testHighestBitSet(TestObjs *objs) {
	ASSERT(-1 == apint_highest_bit_set(objs->ap0));
	ASSERT(0 == apint_highest_bit_set(objs->ap1));
	ASSERT(26 == apint_highest_bit_set(objs->ap110660361));
	ASSERT(63 == apint_highest_bit_set(objs->max1));
}

void testFormatAsHex(TestObjs *objs) {
	char *s;
	
	ASSERT(0 == strcmp("0", (s = apint_format_as_hex(objs->ap0))));
	free(s);

	ASSERT(0 == strcmp("1", (s = apint_format_as_hex(objs->ap1))));
	free(s);

	ASSERT(0 == strcmp("6988b09", (s = apint_format_as_hex(objs->ap110660361))));
	free(s);

	ASSERT(0 == strcmp("ffffffffffffffff", (s = apint_format_as_hex(objs->max1))));
	free(s);
}


void testNegate(TestObjs *objs) {
	ApInt *result;
	
	result = apint_negate(objs->ap0);
	ASSERT(0 == result->data[0]);
	apint_destroy(result);

	result = apint_negate(objs->ap1);
	ASSERT(1 == result->data[0]);
	ASSERT(result->flags == 1);
	apint_destroy(result);

	result = apint_negate(objs->minus1);
	ASSERT(1 == result->data[0]);
	ASSERT(result->flags == 0);
	apint_destroy(result);


	result = apint_negate(objs->ap110660361);
	ASSERT(110660361UL == result->data[0]);
	ASSERT(result->flags == 1);
	apint_destroy(result);
}

void testAddSingle(TestObjs *objs) {
	ApInt *sum;
	char *s;

	/* 0 + 0 = 0 */
	sum = apint_add(objs->ap0, objs->ap0);
	ASSERT(0 == strcmp("0", (s = apint_format_as_hex(sum))));
	apint_destroy(sum);
	free(s);

	/* 1 + 0 = 1 */
	sum = apint_add(objs->ap1, objs->ap0);
	ASSERT(0 == strcmp("1", (s = apint_format_as_hex(sum))));
	apint_destroy(sum);
	free(s);

	/* 1 + 1 = 2 */
	sum = apint_add(objs->ap1, objs->ap1);
	ASSERT(0 == strcmp("2", (s = apint_format_as_hex(sum))));
	apint_destroy(sum);
	free(s);

	/* 110660361 + 1 = 110660362 */
	sum = apint_add(objs->ap110660361, objs->ap1);
	ASSERT(0 == strcmp("6988b0a", (s = apint_format_as_hex(sum))));
	apint_destroy(sum);
	free(s);

	/* FFFFFFFFFFFFFFFF + 1 = 10000000000000000 */
	sum = apint_add(objs->max1, objs->ap1);
	ASSERT(0 == strcmp("10000000000000000", (s = apint_format_as_hex(sum))));
	apint_destroy(sum);
	free(s);
}

void testSubSingle(TestObjs *objs) {
	ApInt *diff;
	char *s;

	/* subtracting 1 from ffffffffffffffff is fffffffffffffffe */
	diff = apint_sub(objs->max1, objs->ap1);
	ASSERT(0 == strcmp("fffffffffffffffe", (s = apint_format_as_hex(diff))));
	apint_destroy(diff);
	free(s);

	/* subtracting 0 from 1 is 1 */
	diff = apint_sub(objs->ap1, objs->ap0);
	ASSERT(0 == strcmp("1", (s = apint_format_as_hex(diff))));
	ASSERT(0 == apint_compare(diff, objs->ap1));
	apint_destroy(diff);
	free(s);

	/* subtracting 1 from 1 is 0 */
	diff = apint_sub(objs->ap1, objs->ap1);
	ASSERT(0 == strcmp("0", (s = apint_format_as_hex(diff))));
	ASSERT(0 == apint_compare(diff, objs->ap0));
	apint_destroy(diff);
	free(s);

	/* subtracting 1 from 0 is -1 */
	diff = apint_sub(objs->ap0, objs->ap1);
	ASSERT(0 == (strcmp("-1", (s = apint_format_as_hex(diff)))));
	ASSERT(0 == apint_compare(diff, objs->minus1));
	apint_destroy(diff);
	free(s);

	
	// test involving larger values 
	ApInt * a = apint_create_from_hex("7e35207519b6b06429378631ca460905c19537644f31dc50114e9dc90bb4e4ebc43cfebe6b86d");
	ApInt * b = apint_create_from_hex("9fa0fb165441ade7cb8b17c3ab3653465e09e8078e09631ec8f6fe3a5b301dc");
	diff = apint_sub(a, b);
	ASSERT(0 == strcmp("7e35207519b6afc4883c6fdd8898213a367d73b918de95f20766963b0251c622cd3ec4633b691",
		(s = apint_format_as_hex(diff))));
	apint_destroy(diff);
	apint_destroy(b);
	apint_destroy(a);
	free(s);

	// test involving larger values (with a negative difference) 
	a = apint_create_from_hex("9fa0fb165441ade7cb8b17c3ab3653465e09e8078e09631ec8f6fe3a5b301dc");
	b = apint_create_from_hex("7e35207519b6b06429378631ca460905c19537644f31dc50114e9dc90bb4e4ebc43cfebe6b86d");
	diff = apint_sub(a, b);
	ASSERT(0 == strcmp("-7e35207519b6afc4883c6fdd8898213a367d73b918de95f20766963b0251c622cd3ec4633b691",
		(s = apint_format_as_hex(diff))));
	apint_destroy(diff);
	apint_destroy(b);
	apint_destroy(a);
	free(s);
	
}

void testCompareSingle(TestObjs *objs) {
	/* 1 > 0 */
	ASSERT(apint_compare(objs->ap1, objs->ap0) > 0);
	/* 0 < 1 */
	ASSERT(apint_compare(objs->ap0, objs->ap1) < 0);
	/* 110660361 > 0 */
	ASSERT(apint_compare(objs->ap110660361, objs->ap0) > 0);
	/* 110660361 > 1 */
	ASSERT(apint_compare(objs->ap110660361, objs->ap1) > 0);
	/* 0 < 110660361 */
	ASSERT(apint_compare(objs->ap0, objs->ap110660361) < 0);
	/* 1 < 110660361 */
	ASSERT(apint_compare(objs->ap1, objs->ap110660361) < 0);
}

/* TODO: add more test functions */
