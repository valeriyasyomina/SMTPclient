CLIENT_PATH := src
UNIT_TESTS_PATH := tests/UnitTests

all: client logger tests report

client: 
	make -C $(CLIENT_PATH)

logger:
	make -C $(CLIENT_PATH) logger

tests: unit_tests system_tests

unit_tests: 
	make -C $(UNIT_TESTS_PATH)

system_tests: 
	echo 'run system tests, coming soon'

report:
	echo 'coming soon'


clean:
	make -C $(CLIENT_PATH) clean
	make -C $(UNIT_TESTS_PATH) clean
	
.PHONY: all client tests unit_tests system_tests
