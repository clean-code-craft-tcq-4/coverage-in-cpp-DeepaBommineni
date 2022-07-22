#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("Check the breach if its with in limits") {
	REQUIRE(inferBreach(12, 20, 40) == TOO_LOW);
	REQUIRE(inferBreach(50, 20, 40) == TOO_HIGH);
	REQUIRE(inferBreach(25, 20, 40) == NORMAL);
}

TEST_CASE("Divide and cover the temperature breach") {
	REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, -5) == TOO_LOW);
	REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 40) == TOO_HIGH);
	REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 10) == NORMAL);

	REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, -5) == TOO_LOW);
	REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 50) == TOO_HIGH);
	REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 10) == NORMAL);

	REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, -5) == TOO_LOW);
	REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 50) == TOO_HIGH);
	REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 10) == NORMAL);
}

TEST_CASE("Check alert and message to Controller") {
	BatteryCharacter batteryChar {PASSIVE_COOLING,"ELBattery"};
	checkAndAlert(TO_CONTROLLER, batteryChar, -5) ;
	checkAndAlert(TO_CONTROLLER, batteryChar, 40) ;
	checkAndAlert(TO_CONTROLLER, batteryChar, 10) ;
}
TEST_CASE("Check Alert and message of To Email") {
	BatteryCharacter batteryChar {PASSIVE_COOLING,"ELBattery"};
	checkAndAlert(TO_EMAIL, batteryChar, -5) ;
	checkAndAlert(TO_EMAIL, batteryChar, 40) ;
	checkAndAlert(TO_EMAIL, batteryChar, 10) ;
}
TEST_CASE("Check alert for default input") {
	BatteryCharacter batteryChar {PASSIVE_COOLING,"ELBattery"};
	checkAndAlert(TO_DEFAULT, batteryChar, -5);
}