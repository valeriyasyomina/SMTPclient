CLIENT_PATH := src
UNIT_TESTS_PATH := tests/UnitTests
SYSTEM_TESTS_PATH := tests/SystemTests
REPORT_PATH := report

all: client logger unit_tests report

client: 
	make -C $(CLIENT_PATH)

logger:
	make -C $(CLIENT_PATH) logger

tests: unit_tests system_tests

unit_tests: 
	make -C $(UNIT_TESTS_PATH)

.ONESHELL:
system_tests: 
	cd $(SYSTEM_TESTS_PATH)
	./run_test.sh

report:
	make -C $(REPORT_PATH)


clean:
	make -C $(CLIENT_PATH) clean
	make -C $(UNIT_TESTS_PATH) clean
	make -C $(SYSTEM_TESTS_PATH) clean
	make -C $(REPORT_PATH) clean
	
.PHONY: all client tests unit_tests system_tests report
