// Author: William Selby

#include <stdio.h>

//Define constants for the memory size and port size
#define MEM_SIZE 256
#define PORT_SIZE 8

//Define 8-bit registers (accumulator and program counter)
unsigned char ACC;
unsigned char PC;

//Define 8-bit memory array and 8-bit port array
unsigned char mem[MEM_SIZE];
unsigned char port[PORT_SIZE];

//Define flags
unsigned int carryFlag, zeroFlag;

int main()
{
	//Initialize registers and flags
	ACC = 0;
	PC = 0;
	carryFlag = 0;
	zeroFlag = 0;
	
	//Initialize memory and port
	int i;
	for (i = 0; i < MEM_SIZE; i++)
		mem[i] = 0;
		
	for (i = 0; i < PORT_SIZE; i++)
		port[i] = 0;
		
	//Main loop
	while (1)
	{
		//Fetch current instruction
		unsigned char instruction = mem[PC];
		
		//Decode instruction
		switch (instruction)
		{
			//ADD instruction
			case 0x01:
			{
				unsigned char operand = mem[PC + 1];
				unsigned int sum = ACC + operand;
				
				//Set carry flag
				carryFlag = (sum > 255) ? 1 : 0;
				
				//Set accumulator
				ACC = (unsigned char) sum;
				
				//Update program counter
				PC += 2;
				
				break;
			}
			
			//SUB instruction
			case 0x02:
			{
				unsigned char operand = mem[PC + 1];
				unsigned int difference = ACC - operand;
				
				//Set carry flag
				carryFlag = (difference < 0) ? 1 : 0;
				
				//Set accumulator
				ACC = (unsigned char) difference;
				
				//Update program counter
				PC += 2;
				
				break;
			}
			
			//OUT instruction
			case 0x03:
			{
				unsigned char portNumber = mem[PC + 1];
				port[portNumber] = ACC;
				
				//Update program counter
				PC += 2;
				
				break;
			}
			
			//IN instruction
			case 0x04:
			{
				unsigned char portNumber = mem[PC + 1];
				ACC = port[portNumber];
				
				//Update program counter
				PC += 2;
				
				break;
			}
			
			//JZ instruction
			case 0x05:
			{
				if (zeroFlag == 1)
				{
					unsigned char address = mem[PC + 1];
					PC = address;
				}
				else
				{
					PC += 2;
				}
				
				break;
			}
			
			//JC instruction
			case 0x06:
			{
				if (carryFlag == 1)
				{
					unsigned char address = mem[PC + 1];
					PC = address;
				}
				else
				{
					PC += 2;
				}
				
				break;
			}
			
			//JMP instruction
			case 0x07:
			{
				unsigned char address = mem[PC + 1];
				PC = address;
				
				break;
			}
			
			//NOP instruction
			case 0x00:
				PC += 1;
				break;
			
			//Halt instruction
			case 0xFF:
				return 0;
			
			//Invalid instruction
			default:
				printf("Error: Invalid instruction 0x%02X at 0x%04X\n", instruction, PC);
				return 1;
		}
	}
	
	return 0;
}
