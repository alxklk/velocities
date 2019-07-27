#include <vector>

struct COP
{
    unsigned char cop;
    unsigned char dss;
    unsigned char s0s;
    unsigned char s1s;
    unsigned char dsp;
    unsigned char s0p;
    unsigned char s1p;
    unsigned int dst;
    unsigned int sr0;
    unsigned int sr1;
};

enum OPS
{
    NOP,
    ADD,
    SUB,
    MUL,
    DIV,
    JMP,
    OUT,
    INP,
    BRK
};

extern float In();
extern void Out(float);
extern void Log(const char*);

struct SI
{
    std::vector<COP>ops;
    std::vector<float>mem;
    int ip;
    bool Step()
    {
        bool brk=false;
        COP op=ops[ip];
        switch(op.cop)
        {
            case NOP: ip++;break;
            case ADD: mem[op.dst]=mem[op.sr0]+mem[op.sr1];ip++;break;
            case SUB: mem[op.dst]=mem[op.sr0]-mem[op.sr1];ip++;break;
            case MUL: mem[op.dst]=mem[op.sr0]*mem[op.sr1];ip++;break;
            case DIV: mem[op.dst]=mem[op.sr0]/mem[op.sr1];ip++;break;
            case JMP: ip=op.dst;break;
            case OUT: Out(mem[op.dst]);ip++;break;
            case INP: mem[op.dst]=In();ip++;break;
            case BRK: brk=true;ip++;break;
            defalut: ip++;Log("Unknown");break;
        }
        return brk;
    }
};

void test(SI& si)
{
    while(true)
    {
        if(si.Step())
            break;
    }
}
