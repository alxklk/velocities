#include <stdint.h>
#include <stdio.h>
#include <vector>
#include <chrono>

#define COP_LIST(ITEM, VALUE)\
    ITEM(DST) VALUE(=0),\
    ITEM(SR0) VALUE(),\
    ITEM(SR1) VALUE(=CMD_SR0+1),\
    ITEM(ADD) VALUE(),\
    ITEM(JMP) VALUE() 


#undef ENITEM
#define ENITEM(x) CMD_##x
#undef ENVALUE
#define ENVALUE(...) __VA_ARGS__

enum ECOM : uint32_t
{
	COP_LIST(ENITEM, ENVALUE)
};

struct SCMD
{
    ECOM c;
    uint32_t d;
};

//#define CNT cnt++

#ifndef CNT
#define CNT
int cnt=2100000000;
#else
int cnt=0;
#endif

class Interpret
{
public:
    int ip;
    std::vector<SCMD>cmd;
    std::vector<int>mem;
    int dst;
    int src0;
    int src1;

    inline void Step()
    {
#undef ARLITEM
#define ARLITEM(x) &&l_##x
#undef ARLVALUE
#define ARLVALUE(...)
		static const void* sts[5] = {
				COP_LIST(ARLITEM, ARLVALUE)
			};
		SCMD* pc=&cmd[ip];
		goto *sts[pc->c];

		l_DST: CNT; dst =pc->d;                    goto *sts[(++pc)->c];
		l_SR0: CNT; src0=pc->d;                    goto *sts[(++pc)->c];
		l_SR1: CNT; src1=pc->d;                    goto *sts[(++pc)->c];
		l_ADD: CNT; mem[dst]=mem[src0]+mem[src1];  goto *sts[(++pc)->c];
		l_JMP: CNT;                                ip=pc->d;return;
    }

    inline void Step0()
    {
        while(true)
        {
            SCMD& c=cmd[ip];
            switch(c.c)
            {
                case CMD_DST:dst =c.d;                    ip++;break;
                case CMD_SR0:src0=c.d;                    ip++;break;
                case CMD_SR1:src1=c.d;                    ip++;break;
                case CMD_ADD:mem[dst]=mem[src0]+mem[src1];ip++;break;
                case CMD_JMP:                             ip=c.d;return;
            }
            CNT;
        }
    }

};


int main()
{
    Interpret inp;
    inp.ip=0;
    
    inp.cmd.emplace_back(SCMD{CMD_DST, 0} );
    inp.cmd.emplace_back(SCMD{CMD_SR0, 0} );
    inp.cmd.emplace_back(SCMD{CMD_SR1, 2} );
    inp.cmd.emplace_back(SCMD{CMD_ADD}    );
    inp.cmd.emplace_back(SCMD{CMD_DST, 0} );
    inp.cmd.emplace_back(SCMD{CMD_SR0, 0} );
    inp.cmd.emplace_back(SCMD{CMD_SR1, 1} );
    inp.cmd.emplace_back(SCMD{CMD_ADD}    );
    inp.cmd.emplace_back(SCMD{CMD_DST, 0} );
    inp.cmd.emplace_back(SCMD{CMD_SR0, 0} );
    inp.cmd.emplace_back(SCMD{CMD_SR1, 2} );
    inp.cmd.emplace_back(SCMD{CMD_ADD}    );
    inp.cmd.emplace_back(SCMD{CMD_DST, 0} );
    inp.cmd.emplace_back(SCMD{CMD_SR0, 0} );
    inp.cmd.emplace_back(SCMD{CMD_SR1, 1} );
    inp.cmd.emplace_back(SCMD{CMD_ADD}    );
    inp.cmd.emplace_back(SCMD{CMD_DST, 0} );
    inp.cmd.emplace_back(SCMD{CMD_SR0, 0} );
    inp.cmd.emplace_back(SCMD{CMD_SR1, 2} );
    inp.cmd.emplace_back(SCMD{CMD_ADD}    );
    inp.cmd.emplace_back(SCMD{CMD_JMP,0}  );

    {
        inp.mem.clear();
        inp.mem.push_back(0);
        inp.mem.push_back(1);
        inp.mem.push_back(1);

        std::chrono::steady_clock clk;
        auto time0=clk.now();

        for(int i=0;i<100000000;i++)
        {
            inp.Step();
        }

        auto delta=std::chrono::duration<double>(clk.now()-time0);

        printf("result:%i\ncount: %i\n", inp.mem[0], cnt);
        printf("time %f\n", delta.count());
        float persec=cnt/delta.count();
        printf("persec %f\n", persec);
        printf("tick/cop %f\n", 4800000000/persec);
    }
    {
        inp.mem.clear();
        inp.mem.push_back(0);
        inp.mem.push_back(1);
        inp.mem.push_back(1);

        std::chrono::steady_clock clk;
        auto time0=clk.now();

        for(int i=0;i<100000000;i++)
        {
            inp.Step0();
        }

        auto delta=std::chrono::duration<double>(clk.now()-time0);

        printf("result:%i\ncount: %i\n", inp.mem[0], cnt);
        printf("time %f\n", delta.count());
        float persec=cnt/delta.count();
        printf("persec %f\n", persec);
        printf("tick/cop %f\n", 4800000000/persec);
    }
	
    return 0;
}