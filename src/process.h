#include<stdint.h>
#include"shell.h"

int32_t imm_sign_ext(uint16_t imm);

uint32_t imm_usign_ext(uint16_t imm);

//J instruction
void j(uint32_t imm);

void jal(uint32_t imm);


//I instructions

void beq(uint8_t rs,uint8_t rt, uint16_t imm);

void bne(uint8_t rs,uint8_t rt, uint16_t imm);

void blez(uint8_t rs,uint8_t rt, uint16_t imm);

void bgtz(uint8_t rs,uint8_t rt, uint16_t imm);

void addi(uint8_t rs,uint8_t rt, uint16_t imm);

void addiu(uint8_t rs,uint8_t rt, uint16_t imm);

void slti(uint8_t rs,uint8_t rt, uint16_t imm);

void sltiu(uint8_t rs,uint8_t rt, uint16_t imm);

void andi(uint8_t rs,uint8_t rt, uint16_t imm);

void ori(uint8_t rs,uint8_t rt, uint16_t imm);

void xori(uint8_t rs,uint8_t rt, uint16_t imm);

void lui(uint8_t rs,uint8_t rt, uint16_t imm);

void lb(uint8_t rs,uint8_t rt, uint16_t imm);

void lh(uint8_t rs,uint8_t rt, uint16_t imm);

void lw(uint8_t rs,uint8_t rt, uint16_t imm);

void lbu(uint8_t rs,uint8_t rt, uint16_t imm);

void lhu(uint8_t rs,uint8_t rt, uint16_t imm);

void sb(uint8_t rs,uint8_t rt, uint16_t imm);

void sh(uint8_t rs,uint8_t rt, uint16_t imm);

void sw(uint8_t rs,uint8_t rt, uint16_t imm);

void bltz(uint8_t rs, uint16_t imm);

void bgez(uint8_t rs, uint16_t imm);

void bltzal(uint8_t rs, uint16_t imm);

void bgezal(uint8_t rs, uint16_t imm);

//R instructions
void sll(uint8_t shamt,uint8_t rt, uint8_t rd);

void srl(uint8_t shamt,uint8_t rt, uint8_t rd);

void sra(uint8_t shamt,uint8_t rt, uint8_t rd);

void sllv(uint8_t rs,uint8_t rt, uint8_t rd);

void srlv(uint8_t rs,uint8_t rt, uint8_t rd);

void srav(uint8_t rs,uint8_t rt, uint8_t rd);

void jr(uint8_t rs);

void jalr(uint8_t rs, uint8_t rd);

void add(uint8_t rs,uint8_t rt, uint8_t rd);

void addu(uint8_t rs,uint8_t rt, uint8_t rd);

void sub(uint8_t rs,uint8_t rt, uint8_t rd);

void subu(uint8_t rs,uint8_t rt, uint8_t rd);

void And(uint8_t rs,uint8_t rt, uint8_t rd);

void Or(uint8_t rs,uint8_t rt, uint8_t rd);

void Xor(uint8_t rs,uint8_t rt, uint8_t rd);

void Nor(uint8_t rs,uint8_t rt, uint8_t rd);

void slt(uint8_t rs,uint8_t rt, uint8_t rd);

void sltu(uint8_t rs,uint8_t rt, uint8_t rd);

void mult(uint8_t rs,uint8_t rt);

void mfhi(uint8_t rd);

void mflo(uint8_t rd);

void mthi(uint8_t rs);

void mtlo(uint8_t rs);

void multu(uint8_t rs,uint8_t rt);

void div(uint8_t rs,uint8_t rt);

void divu(uint8_t rs,uint8_t rt);

void syscall();