#include<stdint.h>
#include<stdio.h>
#include"process.h"


int32_t imm_sign_ext(uint16_t imm){
    int32_t ext_imm =(int16_t)imm;
    return ext_imm;
};

uint32_t imm_usign_ext(uint16_t imm){
    uint32_t ext_imm=(uint32_t)imm;
    return ext_imm;   
};

int32_t byte_sign_ext(uint8_t byte){
    int32_t signed_byte = (int8_t)byte;
    uint32_t ext_byte =(uint32_t)signed_byte;
    return ext_byte;
}

uint32_t byte_usign_ext(uint8_t byte){
    uint32_t ext_byte= (uint32_t)byte;
    return ext_byte;
}

//J instruction
void j(uint32_t imm){
    NEXT_STATE.PC = (CURRENT_STATE.PC & 0xf0000000) | (imm << 2);
};

void jal(uint32_t imm){
    NEXT_STATE.REGS[31] = CURRENT_STATE.PC + 4;
    NEXT_STATE.PC = (CURRENT_STATE.PC & 0xf0000000) | (imm << 2);
};


//I instructions

void beq(uint8_t rs,uint8_t rt, uint16_t imm){
    int32_t offset=imm_sign_ext(imm)<<2;
    if(CURRENT_STATE.REGS[rs]==CURRENT_STATE.REGS[rt]){
        NEXT_STATE.PC = CURRENT_STATE.PC + offset + 4;
    }
    else{
        NEXT_STATE.PC = CURRENT_STATE.PC+ 4;
    }
};

void bne(uint8_t rs,uint8_t rt, uint16_t imm){
    int32_t offset=imm_sign_ext(imm)<<2;
    if(CURRENT_STATE.REGS[rs]!=CURRENT_STATE.REGS[rt]){
        NEXT_STATE.PC = CURRENT_STATE.PC + offset + 4;
    }
    else{
        NEXT_STATE.PC = CURRENT_STATE.PC+ 4;
    }
};

void blez(uint8_t rs,uint8_t rt, uint16_t imm){
    int32_t offset=imm_sign_ext(imm)<<2;
    if(rt==0){
        if(CURRENT_STATE.REGS[rs]==0||(CURRENT_STATE.REGS[rs]&0x80000000)!=0){
            NEXT_STATE.PC=CURRENT_STATE.PC+offset+4;
        }
        else{
            NEXT_STATE.PC=CURRENT_STATE.PC+4;
        }
    }
    else{
        printf("exception!");
    }
};

void bgtz(uint8_t rs,uint8_t rd, uint16_t imm){
        int32_t offset=imm_sign_ext(imm)<<2;
    if(rd==0){
        if(CURRENT_STATE.REGS[rs]!=0&&(CURRENT_STATE.REGS[rs]&0x80000000)==0){
            NEXT_STATE.PC=CURRENT_STATE.PC+offset+4;
        }
        else{
            NEXT_STATE.PC=CURRENT_STATE.PC+4;
        }
    }
    else{
        printf("exception!");
    }
};



void addi(uint8_t rs,uint8_t rd, uint16_t imm){
    int32_t ext_imm=imm_sign_ext(imm);
    NEXT_STATE.REGS[rd]=CURRENT_STATE.REGS[rs]+ext_imm;
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;

};

void addiu(uint8_t rs,uint8_t rd, uint16_t imm){
    uint32_t ext_imm=imm_usign_ext(imm);
    NEXT_STATE.REGS[rd]=CURRENT_STATE.REGS[rs]+ext_imm;
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
};

void slti(uint8_t rs,uint8_t rd, uint16_t imm){
    int32_t ext_imm=imm_sign_ext(imm);
    int32_t rs_imm=(int32_t)CURRENT_STATE.REGS[rs];
    if(rs_imm<ext_imm){
        NEXT_STATE.REGS[rd]=1;
    }
    else{
        NEXT_STATE.REGS[rd]=0;
    }
    NEXT_STATE.PC=CURRENT_STATE.PC+4;
};

void sltiu(uint8_t rs,uint8_t rd, uint16_t imm){
    uint32_t ext_imm=imm_usign_ext(imm);
    if (CURRENT_STATE.REGS[rs]<ext_imm)
    {
        NEXT_STATE.REGS[rd]=1;
    }
    else{
        NEXT_STATE.REGS[rd]=0;
    }
    NEXT_STATE.PC=CURRENT_STATE.PC+4;
};

void andi(uint8_t rs,uint8_t rd, uint16_t imm){
    uint32_t ext_imm=imm_usign_ext(imm);
    NEXT_STATE.REGS[rd]=CURRENT_STATE.REGS[rs]&ext_imm;
    NEXT_STATE.PC=CURRENT_STATE.PC+4;
};


void ori(uint8_t rs,uint8_t rd, uint16_t imm){
    uint32_t ext_imm=imm_usign_ext(imm);
    NEXT_STATE.REGS[rd]=CURRENT_STATE.REGS[rs]|ext_imm;
    NEXT_STATE.PC=CURRENT_STATE.PC+4;
};

void xori(uint8_t rs,uint8_t rd, uint16_t imm){
    uint32_t ext_imm=imm_usign_ext(imm);
    NEXT_STATE.REGS[rd]=CURRENT_STATE.REGS[rs]^ext_imm;
    NEXT_STATE.PC=CURRENT_STATE.PC+4;
};

void lui(uint8_t rs,uint8_t rd, uint16_t imm){
    uint32_t ext_imm=imm_usign_ext(imm)<<16;
    if(rs==0){
        NEXT_STATE.REGS[rd]=ext_imm;
    }
    else{
        printf("exception!");
    }
    NEXT_STATE.PC=CURRENT_STATE.PC+4;
};

void lb(uint8_t rs,uint8_t rd, uint16_t imm){

    uint32_t addr = imm_sign_ext(imm) + CURRENT_STATE.REGS[rs];
    uint8_t byte = mem_read_32(addr) & 0xff;
    int32_t ext_byte=byte_sign_ext(byte);
    NEXT_STATE.REGS[rd] = ext_byte;
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
};

void lh(uint8_t rs,uint8_t rd, uint16_t imm){
    uint32_t addr = imm_sign_ext(imm) + CURRENT_STATE.REGS[rs];
    if(addr&0x1!=0){
        printf("exception!");
    }
    else{
    uint16_t halfbyte = mem_read_32(addr) & 0xffff;
    NEXT_STATE.REGS[rd] = imm_sign_ext(halfbyte);
    }
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
};

void lw(uint8_t rs,uint8_t rd, uint16_t imm){
    uint32_t addr = imm_sign_ext(imm) + CURRENT_STATE.REGS[rs];
    if(addr&0x3!=0){
        printf("exception!");
    }
    else{
        int32_t word = mem_read_32(addr) & 0xffffffff;
        NEXT_STATE.REGS[rd] =word;
    }
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
};

void lbu(uint8_t rs,uint8_t rd, uint16_t imm){
    uint32_t addr = imm_sign_ext(imm) + CURRENT_STATE.REGS[rs];
    uint8_t byte = mem_read_32(addr) & 0xff;
    uint32_t ext_byte=byte_usign_ext(byte);
    NEXT_STATE.REGS[rd] = ext_byte;
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
};

void lhu(uint8_t rs,uint8_t rd, uint16_t imm){
    uint32_t addr = imm_sign_ext(imm) + CURRENT_STATE.REGS[rs];
    if(addr&0x1!=0){
        printf("exception!");
    }
    else{
    uint16_t halfbyte = mem_read_32(addr) & 0xffff;
    NEXT_STATE.REGS[rd] = imm_usign_ext(halfbyte);
    }
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
};

void sb(uint8_t rs,uint8_t rd, uint16_t imm){
    uint32_t addr = imm_sign_ext(imm) + CURRENT_STATE.REGS[rs];
    uint32_t val = (mem_read_32(addr) & 0xffffff00) |(CURRENT_STATE.REGS[rd] & 0xff);
    mem_write_32(addr, val);
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
};

void sh(uint8_t rs,uint8_t rd, uint16_t imm){
    uint32_t addr = imm_sign_ext(imm) + CURRENT_STATE.REGS[rs];
    uint32_t val = (mem_read_32(addr) & 0xffff0000) |(CURRENT_STATE.REGS[rd] & 0xffff);
    mem_write_32(addr, val);
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
};

void sw(uint8_t rs,uint8_t rd, uint16_t imm)
{
    uint32_t addr = imm_sign_ext(imm) + CURRENT_STATE.REGS[rs];
    uint32_t val = CURRENT_STATE.REGS[rd] & 0xffffffff;
    mem_write_32(addr, val);
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
};

void bltz(uint8_t rs,uint16_t imm){
    if(CURRENT_STATE.REGS[rs]&0x80000000!=0){
        uint32_t offset=imm_sign_ext(imm)<<2;
        NEXT_STATE.PC=CURRENT_STATE.PC+4+offset;
    }
    else{
        NEXT_STATE.PC=CURRENT_STATE.PC+4;
    }
};

void bgez(uint8_t rs,uint16_t imm){
    if(CURRENT_STATE.REGS[rs]&0x80000000==0){
        uint32_t offset=imm_sign_ext(imm)<<4;
        NEXT_STATE.PC=CURRENT_STATE.PC+4+offset;
    }
    else{
        NEXT_STATE.PC=CURRENT_STATE.PC+4;
    }
};

void bltzal(uint8_t rs,uint16_t imm){
    if(rs!=31){
        uint32_t offset=imm_sign_ext(imm)<<4;
        if(CURRENT_STATE.REGS[rs]&0x80000000!=0){
            NEXT_STATE.REGS[31]=CURRENT_STATE.PC+4;
            NEXT_STATE.PC=CURRENT_STATE.PC+4+offset;
        }
        else{
            NEXT_STATE.PC=CURRENT_STATE.PC+4;
        }
    }
    else{
        printf("exception!");
        NEXT_STATE.PC=CURRENT_STATE.PC+4;
    }
};


void bgezal(uint8_t rs, uint16_t imm){
    if(rs!=31){
        uint32_t offset=imm_sign_ext(imm)<<4;
        if(CURRENT_STATE.REGS[rs]&0x80000000==0){
            NEXT_STATE.REGS[31]=CURRENT_STATE.PC+4;
            NEXT_STATE.PC=CURRENT_STATE.PC+4+offset;
        }
        else{
            NEXT_STATE.PC=CURRENT_STATE.PC+4;
        }
    }
    else{
        printf("exception!");
        NEXT_STATE.PC=CURRENT_STATE.PC+4;
    }
};

//R instructions
void sll(uint8_t shamt,uint8_t rt, uint8_t rd){
    NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rt] << shamt;
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
};

void srl(uint8_t shamt,uint8_t rt, uint8_t rd){
    NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rt] >> shamt;
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
};

void sra(uint8_t shamt,uint8_t rt, uint8_t rd){
    int32_t val = (int32_t)CURRENT_STATE.REGS[rt];
    val = val >> shamt;
    NEXT_STATE.REGS[rd] = val;
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
};

void sllv(uint8_t rs,uint8_t rt, uint8_t rd){
    uint32_t shamt = CURRENT_STATE.REGS[rs] & 0x1f;
    NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rt] << shamt;
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
};

void srlv(uint8_t rs,uint8_t rt, uint8_t rd){
    uint32_t shamt = CURRENT_STATE.REGS[rs] & 0x1f;
    NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rt] >> shamt;
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
};

void srav(uint8_t rs,uint8_t rt, uint8_t rd){
    int32_t val = (int32_t)CURRENT_STATE.REGS[rt];
    uint32_t shamt = CURRENT_STATE.REGS[rs] & 0x1f;
    val = val >> shamt;
    NEXT_STATE.REGS[rd] = val;
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
};

void jr(uint8_t rs){
    NEXT_STATE.PC = CURRENT_STATE.REGS[rs];
};

void jalr(uint8_t rs, uint8_t rd){
    NEXT_STATE.REGS[rd] = CURRENT_STATE.PC + 4;
    NEXT_STATE.PC = CURRENT_STATE.REGS[rs];
};

void add(uint8_t rs,uint8_t rt, uint8_t rd){
    NEXT_STATE.REGS[rd] =CURRENT_STATE.REGS[rs] + CURRENT_STATE.REGS[rt];
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
};

void addu(uint8_t rs,uint8_t rt, uint8_t rd){
    add(rs,rt,rd);    
};

void sub(uint8_t rs,uint8_t rt, uint8_t rd){
    NEXT_STATE.REGS[rd] =CURRENT_STATE.REGS[rs] - CURRENT_STATE.REGS[rt];
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
};

void subu(uint8_t rs,uint8_t rt, uint8_t rd){
    sub(rs,rt,rd);
};

void And(uint8_t rs,uint8_t rt, uint8_t rd){
    NEXT_STATE.REGS[rd] =CURRENT_STATE.REGS[rs] & CURRENT_STATE.REGS[rt];
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;

};

void Or(uint8_t rs,uint8_t rt, uint8_t rd){
    NEXT_STATE.REGS[rd] =CURRENT_STATE.REGS[rs] | CURRENT_STATE.REGS[rt];
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
};

void Xor(uint8_t rs,uint8_t rt, uint8_t rd){
    NEXT_STATE.REGS[rd] =CURRENT_STATE.REGS[rs] ^ CURRENT_STATE.REGS[rt];
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
};

void Nor(uint8_t rs,uint8_t rt, uint8_t rd){
    NEXT_STATE.REGS[rd] =~(CURRENT_STATE.REGS[rs] | CURRENT_STATE.REGS[rt]);
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
};

void slt(uint8_t rs,uint8_t rt, uint8_t rd){
    int32_t lhs = (int32_t)CURRENT_STATE.REGS[rs];
    int32_t rhs = (int32_t)CURRENT_STATE.REGS[rt];
    NEXT_STATE.REGS[rd] = (lhs < rhs) ? 1 : 0;
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
};

void sltu(uint8_t rs,uint8_t rt, uint8_t rd){
    uint32_t lhs = (int32_t)CURRENT_STATE.REGS[rs];
    uint32_t rhs = (int32_t)CURRENT_STATE.REGS[rt];
    NEXT_STATE.REGS[rd] = (lhs < rhs) ? 1 : 0;
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
};

void mult(uint8_t rs,uint8_t rt){
    int64_t lhs = (int32_t)CURRENT_STATE.REGS[rs];
    int64_t rhs = (int32_t)CURRENT_STATE.REGS[rt];
    int64_t product = lhs * rhs;
    uint64_t uint_product = (uint32_t)product;
    NEXT_STATE.HI =(uint32_t)((uint_product >> 32) & 0xffffffff);
    NEXT_STATE.LO = (uint32_t)(uint_product & 0xffffffff);
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
};

void mfhi(uint8_t rd){
    NEXT_STATE.REGS[rd] = CURRENT_STATE.HI;
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
};

void mflo(uint8_t rd){
    NEXT_STATE.REGS[rd] = CURRENT_STATE.LO;
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
};

void mthi(uint8_t rs){
    NEXT_STATE.LO = CURRENT_STATE.REGS[rs];
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
};

void mtlo(uint8_t rs){
    NEXT_STATE.LO = CURRENT_STATE.REGS[rs];
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
};

void multu(uint8_t rs,uint8_t rt){
    uint64_t lhs = (uint32_t)CURRENT_STATE.REGS[rs];
    uint64_t rhs = (uint32_t)CURRENT_STATE.REGS[rt];
    uint64_t product = lhs * rhs;
    uint64_t uint_product = (uint32_t)product;
    NEXT_STATE.HI =(uint32_t)((uint_product >> 32) & 0xffffffff);
    NEXT_STATE.LO = (uint32_t)(uint_product & 0xffffffff);
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
};

void div(uint8_t rs,uint8_t rt){
    int32_t lhs =(int32_t)CURRENT_STATE.REGS[rs];
    int32_t rhs = (int32_t)CURRENT_STATE.REGS[rt];
    NEXT_STATE.LO = lhs / rhs;
    NEXT_STATE.HI = lhs % rhs;
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
};

void divu(uint8_t rs,uint8_t rt){
    uint32_t lhs =(uint32_t)CURRENT_STATE.REGS[rs];
    uint32_t rhs = (uint32_t)CURRENT_STATE.REGS[rt];
    NEXT_STATE.LO = lhs / rhs;
    NEXT_STATE.HI = lhs % rhs;
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
};

void syscall(){
    if (CURRENT_STATE.REGS[2] == 0x0a) {
        RUN_BIT = FALSE;
    } 
    else{
        NEXT_STATE.PC = CURRENT_STATE.PC + 4;
    }
};