#include <stdio.h>
#include "shell.h"
#include"process.h"


uint8_t get_op(uint32_t inst){ return inst >> 26;}

uint8_t get_rs(uint32_t inst){ return (inst >> 21) & 0x1f;}

uint8_t get_rt(uint32_t inst){ return (inst >> 16) & 0x1f; }

uint8_t get_rd(uint32_t inst) { return (inst >> 11) & 0x1f; }

uint32_t get_target(uint32_t inst) { return inst & 0x3ffffff;}

uint16_t get_imm(uint32_t inst) { return inst & 0xffff; }

uint8_t get_shamt(uint32_t inst) { return (inst >> 6) & 0x1f;}

uint8_t get_funct(uint32_t inst) { return inst & 0x3f; }


void process_instruction()
{
    /* execute one instruction here. You should use CURRENT_STATE and modify
     * values in NEXT_STATE. You can call mem_read_32() and mem_write_32() to
     * access memory. */

    uint32_t inst = mem_read_32(CURRENT_STATE.PC);

    uint8_t op = get_op(inst);
    uint8_t rs = get_rs(inst);
    uint8_t rt = get_rt(inst);
    uint16_t imm = get_imm(inst);
    uint8_t rd = get_rd(inst);
    uint8_t shamt = get_shamt(inst);
    uint8_t funct = get_funct(inst);
    uint32_t target = get_target(inst);


    switch(op){
        case 0:{
            switch(funct){
                case 0x0:sll(shamt,rt,rd);
                break;
                case 0x2:srl(shamt,rt,rd);
                break;
                case 0x3:sra(shamt,rt,rd);
                break;
                case 0x4:sllv(rs,rt,rd);
                break;
                case 0x6:srlv(rs,rt,rd);
                break;
                case 0x7:srav(rs,rt,rd);
                break;
                case 0x8:jr(rs);
                break;
                case 0x9:jalr(rs,rd);
                break;
                case 0xc:syscall();
                break;
                case 0x10:mfhi(rd);
                break;
                case 0x11:mthi(rs);
                break;
                case 0x12:mflo(rd);
                break;
                case 0x13:mtlo(rs);
                break;
                case 0x18:mult(rs,rt);
                break;
                case 0x19:multu(rs,rt);
                break;
                case 0x1a:div(rs,rt);
                break;
                case 0x1b:divu(rs,rt);
                break;
                case 0x20:add(rs,rt,rd);
                break;
                case 0x21:addu(rs,rt,rd);
                break;
                case 0x22:sub(rs,rt,rd);
                break;
                case 0x23:subu(rs,rt,rd);
                break;
                case 0x24:And(rs,rt,rd);
                break;
                case 0x25:Or(rs,rt,rd);
                break;
                case 0x26:Xor(rs,rt,rd);
                break;
                case 0x27:Nor(rs,rt,rd);
                break;
                case 0x2a:slt(rs,rt,rd);
                break;
                case 0x2b:sltu(rs,rt,rd);
                break;
            }
        }
        break;
        case 0x1:{
            switch(rt){
                case 0x0:bltz(rs,imm);
                break;
                case 0x1:bgez(rs,imm);
                break;
                case 0x10:bltzal(rs,imm);
                break;
                case 0x11:bgezal(rs,imm);
                break;
            }
        }
        break;
        case 0x2:j(target);
        break;
        case 0x3:jal(target);
        break;
        case 0x4:beq(rs,rt,imm);
        break;
        case 0x5:bne(rs,rt,imm);
        break;
        case 0x6:blez(rs,rt,imm);
        break;
        case 0x7:bgtz(rs,rt,imm);
        break;
        case 0x8:addi(rs,rt,imm);
        break;
        case 0x9:addiu(rs,rt,imm);
        break;
        case 0xa:slti(rs,rt,imm);
        break;
        case 0xb:sltiu(rs,rt,imm);
        break;
        case 0xc:andi(rs,rt,imm);
        break;
        case 0xd:ori(rs,rt,imm);
        break;
        case 0xe:xori(rs,rt,imm);
        break;
        case 0xf:lui(rs,rt,imm);
        break;
        case 0x20:lb(rs,rt,imm);
        break;
        case 0x21:lh(rs,rt,imm);
        break;
        case 0x23:lw(rs,rt,imm);
        break;
        case 0x24:lbu(rs,rt,imm);
        break;
        case 0x25:lhu(rs,rt,imm);
        break;
        case 0x28:sb(rs,rt,imm);
        break;
        case 0x29:sh(rs,rt,imm);
        break;
        case 0x2b:sw(rs,rt,imm);
        break;
    }


}
