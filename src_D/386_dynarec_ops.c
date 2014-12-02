#ifdef DYNAREC
#include "ibm.h"
#include "cpu.h"
#include "x86.h"
#include "x86_ops.h"
#include "x87.h"
#include "x86_flags.h"
#include "codegen.h"

#define CPU_BLOCK_END() cpu_block_end = 1

#include "386_common.h"


extern uint16_t *mod1add[2][8];
extern uint32_t *mod1seg[8];

/*Copy-and-pasted from 386_dynarec.c, is not in a header file because it will
  eventually be different for the dynarec ops*/
static inline void fetch_ea_32_long(uint32_t rmdat)
{
        eal_r = eal_w = NULL;
        easeg = ea_seg->base;
        ea_rseg = ea_seg->seg;
        if (easeg != 0xFFFFFFFF && ((easeg + eaaddr) & 0xFFF) <= 0xFFC)
        {
                if ( readlookup2[(easeg + eaaddr) >> 12] != -1)
                   eal_r = (uint32_t *)(readlookup2[(easeg + eaaddr) >> 12] + easeg + eaaddr);
                if (writelookup2[(easeg + eaaddr) >> 12] != -1)
                   eal_w = (uint32_t *)(writelookup2[(easeg + eaaddr) >> 12] + easeg + eaaddr);
        }
}

static inline void fetch_ea_16_long(uint32_t rmdat)
{
        eal_r = eal_w = NULL;
        easeg = ea_seg->base;
        ea_rseg = ea_seg->seg;
        if (easeg != 0xFFFFFFFF && ((easeg + eaaddr) & 0xFFF) <= 0xFFC)
        {
                if ( readlookup2[(easeg + eaaddr) >> 12] != -1)
                   eal_r = (uint32_t *)(readlookup2[(easeg + eaaddr) >> 12] + easeg + eaaddr);
                if (writelookup2[(easeg + eaaddr) >> 12] != -1)
                   eal_w = (uint32_t *)(writelookup2[(easeg + eaaddr) >> 12] + easeg + eaaddr);
        }
}

#define fetch_ea_16(rmdat)              pc++; if (mod != 3) fetch_ea_16_long(rmdat); 
#define fetch_ea_32(rmdat)              pc++; if (mod != 3) fetch_ea_32_long(rmdat); 

#define OP_TABLE(name) dynarec_ops_ ## name
#define CLOCK_CYCLES(c) 
#define CLOCK_CYCLES_ALWAYS(c) cycles -= (c)

#include "386_ops.h"
#endif
