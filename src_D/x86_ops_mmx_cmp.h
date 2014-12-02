static int opPCMPEQB_a16(uint32_t fetchdat)
{
        MMX_REG src;
        
        MMX_ENTER();
        
        fetch_ea_16(fetchdat);
        MMX_GETSRC();

        MM[reg].b[0] = (MM[reg].b[0] == src.b[0]) ? 0xff : 0;
        MM[reg].b[1] = (MM[reg].b[1] == src.b[1]) ? 0xff : 0;
        MM[reg].b[2] = (MM[reg].b[2] == src.b[2]) ? 0xff : 0;
        MM[reg].b[3] = (MM[reg].b[3] == src.b[3]) ? 0xff : 0;
        MM[reg].b[4] = (MM[reg].b[4] == src.b[4]) ? 0xff : 0;
        MM[reg].b[5] = (MM[reg].b[5] == src.b[5]) ? 0xff : 0;
        MM[reg].b[6] = (MM[reg].b[6] == src.b[6]) ? 0xff : 0;
        MM[reg].b[7] = (MM[reg].b[7] == src.b[7]) ? 0xff : 0;
        
        return 0;
}
static int opPCMPEQB_a32(uint32_t fetchdat)
{
        MMX_REG src;
        
        MMX_ENTER();
        
        fetch_ea_32(fetchdat);
        MMX_GETSRC();

        MM[reg].b[0] = (MM[reg].b[0] == src.b[0]) ? 0xff : 0;
        MM[reg].b[1] = (MM[reg].b[1] == src.b[1]) ? 0xff : 0;
        MM[reg].b[2] = (MM[reg].b[2] == src.b[2]) ? 0xff : 0;
        MM[reg].b[3] = (MM[reg].b[3] == src.b[3]) ? 0xff : 0;
        MM[reg].b[4] = (MM[reg].b[4] == src.b[4]) ? 0xff : 0;
        MM[reg].b[5] = (MM[reg].b[5] == src.b[5]) ? 0xff : 0;
        MM[reg].b[6] = (MM[reg].b[6] == src.b[6]) ? 0xff : 0;
        MM[reg].b[7] = (MM[reg].b[7] == src.b[7]) ? 0xff : 0;
        
        return 0;
}

static int opPCMPGTB_a16(uint32_t fetchdat)
{
        MMX_REG src;
        
        MMX_ENTER();
        
        fetch_ea_16(fetchdat);
        MMX_GETSRC();

        MM[reg].b[0] = (MM[reg].sb[0] > src.sb[0]) ? 0xff : 0;
        MM[reg].b[1] = (MM[reg].sb[1] > src.sb[1]) ? 0xff : 0;
        MM[reg].b[2] = (MM[reg].sb[2] > src.sb[2]) ? 0xff : 0;
        MM[reg].b[3] = (MM[reg].sb[3] > src.sb[3]) ? 0xff : 0;
        MM[reg].b[4] = (MM[reg].sb[4] > src.sb[4]) ? 0xff : 0;
        MM[reg].b[5] = (MM[reg].sb[5] > src.sb[5]) ? 0xff : 0;
        MM[reg].b[6] = (MM[reg].sb[6] > src.sb[6]) ? 0xff : 0;
        MM[reg].b[7] = (MM[reg].sb[7] > src.sb[7]) ? 0xff : 0;
        
        return 0;
}
static int opPCMPGTB_a32(uint32_t fetchdat)
{
        MMX_REG src;
        
        MMX_ENTER();
        
        fetch_ea_32(fetchdat);
        MMX_GETSRC();

        MM[reg].b[0] = (MM[reg].sb[0] > src.sb[0]) ? 0xff : 0;
        MM[reg].b[1] = (MM[reg].sb[1] > src.sb[1]) ? 0xff : 0;
        MM[reg].b[2] = (MM[reg].sb[2] > src.sb[2]) ? 0xff : 0;
        MM[reg].b[3] = (MM[reg].sb[3] > src.sb[3]) ? 0xff : 0;
        MM[reg].b[4] = (MM[reg].sb[4] > src.sb[4]) ? 0xff : 0;
        MM[reg].b[5] = (MM[reg].sb[5] > src.sb[5]) ? 0xff : 0;
        MM[reg].b[6] = (MM[reg].sb[6] > src.sb[6]) ? 0xff : 0;
        MM[reg].b[7] = (MM[reg].sb[7] > src.sb[7]) ? 0xff : 0;
        
        return 0;
}

static int opPCMPEQW_a16(uint32_t fetchdat)
{
        MMX_REG src;
        
        MMX_ENTER();
        
        fetch_ea_16(fetchdat);
        MMX_GETSRC();

        MM[reg].w[0] = (MM[reg].w[0] == src.w[0]) ? 0xffff : 0;
        MM[reg].w[1] = (MM[reg].w[1] == src.w[1]) ? 0xffff : 0;
        MM[reg].w[2] = (MM[reg].w[2] == src.w[2]) ? 0xffff : 0;
        MM[reg].w[3] = (MM[reg].w[3] == src.w[3]) ? 0xffff : 0;
        
        return 0;
}
static int opPCMPEQW_a32(uint32_t fetchdat)
{
        MMX_REG src;
        
        MMX_ENTER();
        
        fetch_ea_32(fetchdat);
        MMX_GETSRC();

        MM[reg].w[0] = (MM[reg].w[0] == src.w[0]) ? 0xffff : 0;
        MM[reg].w[1] = (MM[reg].w[1] == src.w[1]) ? 0xffff : 0;
        MM[reg].w[2] = (MM[reg].w[2] == src.w[2]) ? 0xffff : 0;
        MM[reg].w[3] = (MM[reg].w[3] == src.w[3]) ? 0xffff : 0;
        
        return 0;
}

static int opPCMPGTW_a16(uint32_t fetchdat)
{
        MMX_REG src;
        
        MMX_ENTER();
        
        fetch_ea_16(fetchdat);
        MMX_GETSRC();

        MM[reg].w[0] = (MM[reg].sw[0] > src.sw[0]) ? 0xffff : 0;
        MM[reg].w[1] = (MM[reg].sw[1] > src.sw[1]) ? 0xffff : 0;
        MM[reg].w[2] = (MM[reg].sw[2] > src.sw[2]) ? 0xffff : 0;
        MM[reg].w[3] = (MM[reg].sw[3] > src.sw[3]) ? 0xffff : 0;
        
        return 0;
}
static int opPCMPGTW_a32(uint32_t fetchdat)
{
        MMX_REG src;
        
        MMX_ENTER();
        
        fetch_ea_32(fetchdat);
        MMX_GETSRC();

        MM[reg].w[0] = (MM[reg].sw[0] > src.sw[0]) ? 0xffff : 0;
        MM[reg].w[1] = (MM[reg].sw[1] > src.sw[1]) ? 0xffff : 0;
        MM[reg].w[2] = (MM[reg].sw[2] > src.sw[2]) ? 0xffff : 0;
        MM[reg].w[3] = (MM[reg].sw[3] > src.sw[3]) ? 0xffff : 0;
        
        return 0;
}

static int opPCMPEQD_a16(uint32_t fetchdat)
{
        MMX_REG src;
        
        MMX_ENTER();
        
        fetch_ea_16(fetchdat);
        MMX_GETSRC();

        MM[reg].l[0] = (MM[reg].l[0] == src.l[0]) ? 0xffffffff : 0;
        MM[reg].l[1] = (MM[reg].l[1] == src.l[1]) ? 0xffffffff : 0;
        
        return 0;
}
static int opPCMPEQD_a32(uint32_t fetchdat)
{
        MMX_REG src;
        
        MMX_ENTER();
        
        fetch_ea_16(fetchdat);
        MMX_GETSRC();

        MM[reg].l[0] = (MM[reg].l[0] == src.l[0]) ? 0xffffffff : 0;
        MM[reg].l[1] = (MM[reg].l[1] == src.l[1]) ? 0xffffffff : 0;
        
        return 0;
}

static int opPCMPGTD_a16(uint32_t fetchdat)
{
        MMX_REG src;
        
        MMX_ENTER();
        
        fetch_ea_16(fetchdat);
        MMX_GETSRC();

        MM[reg].l[0] = (MM[reg].sl[0] > src.sl[0]) ? 0xffffffff : 0;
        MM[reg].l[1] = (MM[reg].sl[1] > src.sl[1]) ? 0xffffffff : 0;
        
        return 0;
}
static int opPCMPGTD_a32(uint32_t fetchdat)
{
        MMX_REG src;
        
        MMX_ENTER();
        
        fetch_ea_16(fetchdat);
        MMX_GETSRC();

        MM[reg].l[0] = (MM[reg].sl[0] > src.sl[0]) ? 0xffffffff : 0;
        MM[reg].l[1] = (MM[reg].sl[1] > src.sl[1]) ? 0xffffffff : 0;
        
        return 0;
}
