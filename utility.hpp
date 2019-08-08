#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <cstdlib>
#include <ctime>

void utility_init() {
	srand(time(0));
	// srand(19260817);
}

int get_election_timeout() {
	// 150 ~ 300
	return rand() % 151 + 150;
}

int get_heartbeat_timeout() {
	// 30 ~ 60
	return rand() % 31 + 30;
}

#endif
