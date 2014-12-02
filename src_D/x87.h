uint32_t x87_pc_off,x87_op_off;
uint16_t x87_pc_seg,x87_op_seg;
extern uint32_t op32;
extern int TOP;
extern uint16_t npxs, npxc, tag;
extern int ismmx;
extern double ST[8];

typedef union MMX_REG
{
        uint64_t q;
        int64_t  sq;
        uint32_t l[2];
        int32_t  sl[2];
        uint16_t w[5];
        int16_t  sw[4];
        uint8_t  b[8];
        int8_t   sb[8];
} MMX_REG;

extern MMX_REG MM[8];

static inline void x87_set_mmx();
static inline void x87_emms();
