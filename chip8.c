#include "chip8.h"

void load_rom(chip8 *ch8, char const* filename) 
{
	uint8_t *buffer;
	long rom_len;
	FILE *file = fopen(filename, "rb");
	if (file != NULL)
	{
		fseek(file, 0, SEEK_END);
		rom_len = ftell(file);
		rewind(file);

		buffer = (uint8_t*)malloc(sizeof(uint8_t) *rom_len);

		if (buffer == NULL)
		{
			printf("ERROR: out of memory\n");
			exit(EXIT_FAILURE);
		}

		fread(buffer, sizeof(uint8_t), rom_len, file);

		if ((PROGRAM_END_ADDR - PROGRAM_START_ADDR) >= rom_len) {
			for(int i = 0; i < rom_len; i++) {
				chip8->ram[i + 0x200] = buffer[i];
			}
			else {
				printf("ERROR: rom file too large\n");
				exit(EXIT_FAILURE);
			}
		}
		else {
			printf("ERROR: rom file doesn't exist\n");
			exit(EXIT_FAILURE);
		}

		fclose(file);
		free(buffer);
	}
}

int get_rand() 
{
	return rand() % 255;
}

chip8 *chip8_new(void)
{
	chip8 *chip = malloc(sizeof(chip8_new));
	chip->pc = 0x200; // pc startx at 0x200
	chip->opcode = 0; // reset opcode
	chip->index = 0;  // reset curr index
	chip->sp = 0;     // reset stack pointer

	memset(chip->video_mem, 0, 64 * 32); //clear display
	memset(chip->stack, 0, 16 * sizeof(uint16_t)); //clear stack 
	memset(chip->registers, 0, 16); //clear registers 
	memset(chip->memory, 0, 4096); //clear the memory

	for(int i = 0; i < FONTSET_SIZE; i++) {
		chip->ram[FONTSET_START_ADDRESS + i] = fontset[i];
	}
}

void CLS()
{

}

/*
void init_chip8(chip8 *chip)
{
	srand(time(NULL))
	chip->pc = CHIP8_RAM_START_ADDR;
	for(int i = 0; i < FONTSET_SIZE; i++) {
		chip->ram[FONTSET_START_ADDRESS + i] = fontset[i];
	}
}
*/
