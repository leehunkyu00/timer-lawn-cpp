#include "test_timer.h"

int main() {

	UnitTest::TestTimer test;

	// test 1 set
	test.addData();
	test.waitEmpty();

	// test 1 set
	test.addData();
	test.waitEmpty();
	return 0;
}
