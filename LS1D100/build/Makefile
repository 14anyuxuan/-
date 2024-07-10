# **********************************************
# ls1x project
# **********************************************
# Name of application
#ROOT_DIR = $(shell pwd)
ROOT_DIR  = $(PWD)
# Name of application
IMAGENAME = WaterMeterLA

# **********************************************
# Tools
# **********************************************
CROSS_COMPILE = loongarch32-linux-gnusf-
#CROSS_COMPILE = loongarch32-linux-gnu-
CC        = $(CROSS_COMPILE)gcc
LD        = $(CROSS_COMPILE)ld
OBJCOPY   = $(CROSS_COMPILE)objcopy
OBJDUMP   = $(CROSS_COMPILE)objdump 
STRIP     = $(CROSS_COMPILE)strip
SIZE		= $(CROSS_COMPILE)size
CP	      = cp 
#CC        = mips-linux-gnu-gcc
#LD        = mips-linux-gnu-ld
#OBJCOPY   = mips-linux-gnu-objcopy
#OBJDUMP   = mips-linux-gnu-objdump #-mmips:4000 -S
#STRIP     = mips-linux-gnu-strip
#SIZE	  = mips-linux-gnu-size
#COPY      = copy
# **********************************************
# Directories
# **********************************************
BUILD_DIR	= $(ROOT_DIR)/build
DRIVER		= $(ROOT_DIR)/driver
TASK		= $(ROOT_DIR)/task
TARGET		= $(ROOT_DIR)/target
DRIVER		+= $(ROOT_DIR)/UserSrc
SRCDIR      = $(DRIVER) $(TASK) $(TARGET) 

VPATH       = $(SRCDIR)
DEBUG	= -g
# **********************************************
# Image file names and map file
# **********************************************
IMAGE_ELF = $(IMAGENAME).elf
IMAGE_BIN = $(IMAGENAME).bin
IMAGE_MAP = $(IMAGENAME).map

# **********************************************
# Compiler and linker options
# **********************************************
INCLUDE	+= -I$(ROOT_DIR)/include -I$(ROOT_DIR)/UserInc

#AFLAGS = -G 0 -fno-pic -mno-abicalls -mips2 -Wa,--trap -pipe  
#CFLAGS = -G 0 -O2 -mabi=32 -mhard-float -mfp32 -msingle-float -fno-pic -mno-abicalls -mips2 -Wa,--trap -pipe -g

FLAGS   = -std=gnu99 -O2 -ffunction-sections -fdata-sections -fno-builtin -msingle-float -w
#FLAGS   = -std=gnu99 -O2   -fno-builtin -msingle-float  -g
CC_OPTS	= $(DEBUG) $(FLAGS) $(INCLUDE) 
CC_COPTS	= $(DEBUG) $(FLAGS) $(INCLUDE) 

LD_SCRIPT = ld.script
LD_OPTS   = -G 0 -static -T $(LD_SCRIPT) -Ttext 0x1C000000 -Map $(IMAGE_MAP) -o $(IMAGE_ELF) --gc-sections

# **********************************************
# Files to be compiled
# **********************************************

SRC_C  = $(foreach dir, $(SRCDIR), $(wildcard $(dir)/*.c))
SRC_S  = $(foreach dir, $(SRCDIR), $(wildcard $(dir)/*.S))
SRC    = $(SRC_C) $(SRC_S)
#OBJ_S  = $(notdir $(patsubst %.S, %.o, $(SRC_S)))
OBJ_C  = $(notdir $(patsubst %.c, %.o, $(SRC_C)))
OBJ_S  = start.o $(filter-out start.o, $(notdir $(patsubst %.S, %.o, $(SRC_S))))
LS1D6_OBJ = $(OBJ_S) $(OBJ_C)

# **********************************************
# Rules
# **********************************************
.PHONY : all
all : $(IMAGE_BIN) 
$(IMAGE_BIN):$(LS1D6_OBJ)
	 
	#$(LD) $(LD_OPTS) $(LS1D6_OBJ) -T ld.script -e _start -o $(IMAGE_ELF) -Map $(IMAGE_MAP)
	##$(OBJCOPY) -O binary -R .data  $(IMAGE_ELF) $(IMAGE_BIN)
	##$(LD) $(LD_OPTS) -T ld.script -e _start -o $(IMAGE_ELF) $^ -Map $(IMAGE_MAP)
	#$(OBJCOPY) -O binary $(IMAGE_ELF) $(IMAGE_BIN)
	#$(SIZE) $(IMAGE_ELF)
	#$(OBJDUMP) -Slz $(IMAGE_ELF) >1.txt
	#$(STRIP) -g -S --strip-debug $(IMAGE_ELF)
	#cp -rf $(BUILD_DIR)/$(IMAGE_BIN) /home/tftpboot/1c100_finger.bin
	$(LD) $(LD_OPTS) -o $(IMAGE_ELF) $^ -Map $(IMAGE_MAP)
	$(OBJCOPY) -O binary $(IMAGE_ELF) $(IMAGE_BIN)
	$(SIZE) $(IMAGE_ELF)
	$(OBJDUMP) -alDS $(IMAGE_ELF) > $(IMAGENAME).s
	#$(STRIP) -g -S --strip-debug $(IMAGE_ELF)
	#cp -rf $(BUILD_DIR)/$(IMAGE_BIN) ..
	cp -rf $(BUILD_DIR)/$(IMAGE_BIN) /home/tftpboot/watermeter.bin

$(OBJ_C) : %.o : %.c 
	$(CC) $(CC_COPTS) -c -o $@ $^
$(OBJ_S) : %.o : %.S
	$(CC) $(CC_OPTS) -c -o $@ $^
	

#lixin------------------------------------------------
#$(IMAGENAME) : $(LS1D6_OBJ)
#	$(LD) $(LD_OPTS) $(LS1D6_OBJ) -o $@
#	$(OBJCOPY) -O binary -j .data $@ $(IMAGENAME).data
#	$(OBJCOPY) -O binary -R .data $@ $(IMAGENAME).bin
#	$(OBJDUMP) -ald $(IMAGENAME) > $(IMAGENAME).txt
#	$(OBJDUMP) -x $(IMAGENAME) > $(IMAGENAME).seg.txt
#	cp $(IMAGENAME).bin /home/tftpboot/
	
#lixinls
#$(IMAGE_ELF) : $(LS1D6_OBJ)
#	$(LD) $(LD_OPTS) $(LS1D6_OBJ) 

#$(OBJ_C) : %.o : %.c 
#	$(CC) $(CC_COPTS) -c $< -o $@ 
#$(OBJ_S) : %.o : %.S
#	$(CC) $(CC_OPTS) -c $< -o $@ 
##-----------------------------------------------------------	

.PHONY : clean 
clean :
	rm -rf *.o *.map *.bin 
	rm -rf *.elf *.txt *.s *.a 
