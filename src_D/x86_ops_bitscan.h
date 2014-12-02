#define BS_common(start, end, dir, dest, time)                                  \
        flags_rebuild();                                                        \
        if (temp)                                                               \
        {                                                                       \
                int c;                                                          \
                flags &= ~Z_FLAG;                                               \
                for (c = start; c != end; c += dir)                             \
                {                                                               \
                        CLOCK_CYCLES(time);                                     \
                        if (temp & (1 << c))                                    \
                        {                                                       \
                                dest = c;                                       \
                                break;                                          \
                        }                                                       \
                }                                                               \
        }                                                                       \
        else                                                                    \
                flags |= Z_FLAG;

static int opBSF_w_a16(uint32_t fetchdat)
{
        uint16_t temp;
        
        fetch_ea_16(fetchdat);
        temp = geteaw();                        if (abrt) return 1;
        
        BS_common(0, 16, 1, regs[reg].w, (is486) ? 1 : 3);
        
        CLOCK_CYCLES((is486) ? 6 : 10);
        return 0;
}
static int opBSF_w_a32(uint32_t fetchdat)
{
        uint16_t temp;
        
        fetch_ea_32(fetchdat);
        temp = geteaw();                        if (abrt) return 1;
        
        BS_common(0, 16, 1, regs[reg].w, (is486) ? 1 : 3);
        
        CLOCK_CYCLES((is486) ? 6 : 10);
        return 0;
}
static int opBSF_l_a16(uint32_t fetchdat)
{
        uint32_t temp;
        
        fetch_ea_16(fetchdat);
        temp = geteal();                        if (abrt) return 1;
        
        BS_common(0, 32, 1, regs[reg].l, (is486) ? 1 : 3);
        
        CLOCK_CYCLES((is486) ? 6 : 10);
        return 0;
}
static int opBSF_l_a32(uint32_t fetchdat)
{
        uint32_t temp;
        
        fetch_ea_32(fetchdat);
        temp = geteal();                        if (abrt) return 1;
        
        BS_common(0, 32, 1, regs[reg].l, (is486) ? 1 : 3);
        
        CLOCK_CYCLES((is486) ? 6 : 10);
        return 0;
}

static int opBSR_w_a16(uint32_t fetchdat)
{
        uint16_t temp;
        
        fetch_ea_16(fetchdat);
        temp = geteaw();                        if (abrt) return 1;
        
        BS_common(15, -1, -1, regs[reg].w, 3);
        
        CLOCK_CYCLES((is486) ? 6 : 10);
        return 0;
}
static int opBSR_w_a32(uint32_t fetchdat)
{
        uint16_t temp;
        
        fetch_ea_32(fetchdat);
        temp = geteaw();                        if (abrt) return 1;
        
        BS_common(15, -1, -1, regs[reg].w, 3);
        
        CLOCK_CYCLES((is486) ? 6 : 10);
        return 0;
}
static int opBSR_l_a16(uint32_t fetchdat)
{
        uint32_t temp;
        
        fetch_ea_16(fetchdat);
        temp = geteal();                        if (abrt) return 1;
        
        BS_common(31, -1, -1, regs[reg].l, 3);
        
        CLOCK_CYCLES((is486) ? 6 : 10);
        return 0;
}
static int opBSR_l_a32(uint32_t fetchdat)
{
        uint32_t temp;
        
        fetch_ea_32(fetchdat);
        temp = geteal();                        if (abrt) return 1;
        
        BS_common(31, -1, -1, regs[reg].l, 3);
        
        CLOCK_CYCLES((is486) ? 6 : 10);
        return 0;
}

