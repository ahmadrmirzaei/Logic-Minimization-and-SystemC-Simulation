CC := g++ -std=c++11
BUILD_DIR := build
PARSER_DIR := parser
SYSC_DIR := sysc
OUT_FILE := app.out
INCLUDE_PATH := -I. -I./$(PARSER_DIR) -L.

CC_SRC := $(wildcard *.cc)
CC_SRC_PRS := $(wildcard $(PARSER_DIR)/*.cc)
CC_SRC_SYSC := $(wildcard $(SYSC_DIR)/*.cc)
OBJ_SRC := $(foreach OBJ,$(patsubst %.cc,%.o,$(CC_SRC)),$(BUILD_DIR)/$(OBJ)) $(BUILD_DIR)/parser.o $(BUILD_DIR)/scanner.o

all: $(BUILD_DIR) $(PARSER_DIR) $(SYSC_DIR) $(OUT_FILE)
	./$(OUT_FILE) > $(SYSC_DIR)/sysc.hh

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
$(PARSER_DIR):
	mkdir -p $(PARSER_DIR)
$(SYSC_DIR):
	mkdir -p $(SYSC_DIR)

$(OUT_FILE): $(OBJ_SRC)
	$(CC) $(OBJ_SRC) -o $@ $(INCLUDE_PATH)

$(BUILD_DIR)/parser.o: $(PARSER_DIR)/parser.hh
$(BUILD_DIR)/scanner.o: $(BUILD_DIR)/driver.o $(PARSER_DIR)/parser.cc
$(BUILD_DIR)/%.o: $(PARSER_DIR)/%.cc
	$(CC) -c $< -o $@ $(INCLUDE_PATH)

$(BUILD_DIR)/driver.o: $(BUILD_DIR)/parser.o
$(BUILD_DIR)/%.o: %.cc %.hh
	$(CC) -c $< -o $@ $(INCLUDE_PATH)

$(BUILD_DIR)/main.o: main.cc $(BUILD_DIR)/driver.o
	$(CC) -c $< -o $@ $(INCLUDE_PATH)

$(PARSER_DIR)/location.hh:
$(PARSER_DIR)/parser.hh:
$(PARSER_DIR)/%.hh: scanner.l parser.y
	flex -o$(PARSER_DIR)/scanner.cc scanner.l
	bison -o$(PARSER_DIR)/parser.cc parser.y

$(PARSER_DIR)/parser.cc:
$(PARSER_DIR)/scanner.cc:
$(PARSER_DIR)/%.cc: scanner.l parser.y
	flex -o$(PARSER_DIR)/scanner.cc scanner.l
	bison -o$(PARSER_DIR)/parser.cc parser.y

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(PARSER_DIR) *.o *.out &> /dev/null
	rm -rf $(SYSC_DIR)/sysc.hh

vcd:
	$(CC) $(CC_SRC_SYSC) -o $(SYSC_DIR)/vcd.out $(INCLUDE_PATH)