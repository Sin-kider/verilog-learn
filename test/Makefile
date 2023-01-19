TOPNAME = top
NXDC_FILES = constr/top.nxdc
INC_PATH ?=

VERILATOR = verilator
VERILATOR_CFLAGS += -MMD --build -cc  \
				-O3 --x-assign fast --x-initial fast --noassert

BUILD_DIR = ./build
NVBOARD_BUILD_DIR = ./nvboard_build
OBJ_DIR = $(BUILD_DIR)/obj_dir
BIN = $(BUILD_DIR)/$(TOPNAME)
NVBOARD_BIN = $(NVBOARD_BUILD_DIR)/$(TOPNAME)
VCD_DIR = $(shell find $(abspath $(BUILD_DIR)) -name "*.vcd")
default: $(BIN)

$(shell mkdir -p $(BUILD_DIR))

# constraint file
SRC_AUTO_BIND = $(abspath $(BUILD_DIR)/auto_bind.cpp)
$(SRC_AUTO_BIND): $(NXDC_FILES)
	python3 $(NVBOARD_HOME)/scripts/auto_pin_bind.py $^ $@

# project source
VSRCS = $(shell find $(abspath ./vsrc) -name "*.v")
CSRCS = $(shell find $(abspath ./csrc) -name "*.c" -or -name "*.cc" -or -name "*.cpp")
NVBOARD_CSRCS = $(CSRCS) $(SRC_AUTO_BIND)

# rules for NVBoard
include $(NVBOARD_HOME)/scripts/nvboard.mk

# rules for verilator
INCFLAGS = $(addprefix -I, $(INC_PATH))
CFLAGS += $(INCFLAGS) -DTOP_NAME="\"V$(TOPNAME)\""
NVBOARD_CFLAGS = $(CFLAGS) -DNVBOARD
LDFLAGS += -lSDL2 -lSDL2_image


$(NVBOARD_BIN): $(VSRCS) $(NVBOARD_CSRCS) $(NVBOARD_ARCHIVE)
	@rm -rf $(OBJ_DIR)
	@echo "******************************************************************"
	$(VERILATOR) $(VERILATOR_CFLAGS) \
		--top-module $(TOPNAME) $^ \
		$(addprefix -CFLAGS , $(NVBOARD_CFLAGS)) $(addprefix -LDFLAGS , $(LDFLAGS)) \
		--Mdir $(OBJ_DIR) --exe -o $(abspath $(NVBOARD_BIN))

$(BIN): $(VSRCS) $(CSRCS)
	@rm -rf $(OBJ_DIR)
	@echo "-------------------------------------------------------------------"
	$(VERILATOR) $(VERILATOR_CFLAGS) \
		--top-module $(TOPNAME) $^ \
		$(addprefix -CFLAGS , $(CFLAGS)) \
		--Mdir $(OBJ_DIR) --trace --exe -o $(abspath $(BIN))

all: default

run_nvboard: $(NVBOARD_BIN)
	@$^

run: $(BIN)
	cd $(BUILD_DIR) && ./$(TOPNAME)
	echo "已生成波形文件"
	echo $(VCD_DIR)

sim: run
	@gtkwave $(VCD_DIR)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: default all clean run
