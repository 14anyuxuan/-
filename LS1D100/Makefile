all:
	@echo "***************************************************************************"
	@echo "*"
	@echo "*	Welcome loongson ls1d100"
	@echo "*	You will get one file in /home/tftpboot or ./ ."
	@echo "*	This is 1d100_demo.bin."
	@echo "*"
	@echo "***************************************************************************"
	make -C build all
clean:
	rm -rf *.bin  *.pro* *.elf
	rm -rf /home/tftpboot/*.bin
	make -C build clean

.PHONY: all
.PHONY: clean
