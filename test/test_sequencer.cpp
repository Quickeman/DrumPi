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

	// Check wrapping around
	// Wrap around and then step again
	for (int i = 0; i < 6; i++) seq.step();
	BOOST_CHECK(seq.getStepNum() == 1);
}

BOOST_AUTO_TEST_CASE(addRemoveDrums) {
	Sequencer seq(numSteps);
	int d1 = 3;
	int d2 = 5;

	seq.step();
	// Add d1 to current step (1)
	seq.addToStep(d1);
	// Add d1 and d2 to step 2
	seq.addToStep(d1, 2);
	seq.addToStep(d2, 2);

	BOOST_CHECK(seq.isActive(d1));
	BOOST_CHECK(seq.isActive(d1, 2));
	BOOST_CHECK(seq.isActive(d2, 2));
	BOOST_CHECK(!seq.isActive(d2)); // d2 not active in current step

	std::vector<int> active = seq.getActive();
	BOOST_CHECK(active.size() == 1);
	BOOST_CHECK(active[0] == d1);

	seq.removeFromStep(d1);
	active = seq.getActive();
	BOOST_CHECK(active.empty());

	// Check step 2
	seq.step();
	active = seq.getActive();
	BOOST_CHECK(active.size() == 2);
	BOOST_CHECK(active[0] == d1);
	BOOST_CHECK(active[1] == d2);
}

BOOST_AUTO_TEST_CASE(sequence) {
	Sequencer seq(numSteps);

	std::vector<std::vector<bool>> s;

	s.resize(numSteps);
	for (int i = 0; i < s.size(); i++) { // For each step...
		s[i].resize(NUM_DRUMS);
		for (int j = 0; j < s[i].size(); j++) { // For each drum...
			s[i][j] = static_cast<bool>(rand() % 2);
			if (s[i][j]) seq.addToStep(j, i);
		}
	}

	std::vector<std::vector<bool>> active = seq.getSequence();

	bool error = false;
	for (int i = 0; i < s.size(); i++) {
		for (int j = 0; j < s[i].size(); j++) {
			error = error or (active[i][j] != s[i][j]);
		}
	}

	BOOST_CHECK(!error);
}

BOOST_AUTO_TEST_CASE(resetting) {
	Sequencer seq(numSteps);

	std::vector<std::vector<bool>> s;

	s.resize(numSteps);
	for (int i = 0; i < s.size(); i++) { // For each step...
		s[i].resize(NUM_DRUMS);
		for (int j = 0; j < s[i].size(); j++) { // For each drum...
			s[i][j] = static_cast<bool>(rand() % 2);
			if (s[i][j]) seq.addToStep(j, i);
		}
	}

	seq.step();
	seq.reset();

	std::vector<std::vector<bool>> active = seq.getSequence();

	bool error = false;
	for (int i = 0; i < s.size(); i++) {
		for (int j = 0; j < s[i].size(); j++) {
			error = error or active[i][j];
		}
	}

	BOOST_CHECK(!error);
	BOOST_CHECK(seq.getStepNum() == 0);
}