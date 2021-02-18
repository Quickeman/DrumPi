#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE SequencerTest
#include <boost/test/unit_test.hpp>
#include <sequencer.hpp>

using namespace sequencer;

int numSteps = 8;

BOOST_AUTO_TEST_CASE(constructors) {
	Sequencer seq1(numSteps);
	Sequencer seq2(numSteps);

	// Check for non-null objects (pointers)
	BOOST_CHECK(&seq1);
	BOOST_CHECK(&seq2);
}

BOOST_AUTO_TEST_CASE(stepping) {
	Sequencer seq(numSteps);

	// Should be on step 0
	BOOST_CHECK(seq.getStepNum() == 0);

	// Advance by one, should be on step 1
	seq.step();
	BOOST_CHECK(seq.getStepNum() == 1);

	// Advance by 2, should be on step 3
	seq.step(2);
	BOOST_CHECK(seq.getStepNum() == 3);
}