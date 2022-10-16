#include "DxLib.h"

static int time;

void time_init() {
	time = GetNowCount();
}
void time_culc() {
	time = (60000 - (GetNowCount() - time)) / 1000;
}