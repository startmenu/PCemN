static int opIMUL_w_iw_a16(uint32_t fetchdat)
{
        int32_t templ;
        int16_t tempw, tempw2; 
        
        fetch_ea_16(fetchdat);
                        
        tempw = geteaw();               if (abrt) return 1;
        tempw2 = getword();             if (abrt) return 1;
        
        templ = ((int)tempw) * ((int)tempw2);
        flags_rebuild();
        if ((templ >> 15) != 0 && (templ >> 15) != -1) flags |=   C_FLAG | V_FLAG;
        else                                           flags &= ~(C_FLAG | V_FLAG);
        regs[reg].w = templ & 0xffff;

        CLOCK_CYCLES((mod == 3) ? 14 : 17);
        return 0;
}
static int opIMUL_w_iw_a32(uint32_t fetchdat)
{
        int32_t templ;
        int16_t tempw, tempw2;
        
        fetch_ea_32(fetchdat);
                        
        tempw = geteaw();               if (abrt) return 1;
        tempw2 = getword();             if (abrt) return 1;
        
        templ = ((int)tempw) * ((int)tempw2);
        flags_rebuild();
        if ((templ >> 15) != 0 && (templ >> 15) != -1) flags |=   C_FLAG | V_FLAG;
        else                                           flags &= ~(C_FLAG | V_FLAG);
        regs[reg].w = templ & 0xffff;

        CLOCK_CYCLES((mod == 3) ? 14 : 17);
        return 0;
}

static int opIMUL_l_il_a16(uint32_t fetchdat)
{
        int64_t temp64;
        int32_t templ, templ2;
        
        fetch_ea_16(fetchdat);
        
        templ = geteal();               if (abrt) return 1;
        templ2 = getlong();             if (abrt) return 1;
        
        temp64 = ((int64_t)templ) * ((int64_t)templ2);
        flags_rebuild();
        if ((temp64 >> 31) != 0 && (temp64 >> 31) != -1) flags |=   C_FLAG | V_FLAG;
        else                                             flags &= ~(C_FLAG | V_FLAG);
        regs[reg].l = temp64 & 0xffffffff;
        
        CLOCK_CYCLES(25);
        return 0;
}
static int opIMUL_l_il_a32(uint32_t fetchdat)
{
        int64_t temp64;
        int32_t templ, templ2;
        
        fetch_ea_32(fetchdat);
        
        templ = geteal();               if (abrt) return 1;
        templ2 = getlong();             if (abrt) return 1;
        
        temp64 = ((int64_t)templ) * ((int64_t)templ2);
        flags_rebuild();
        if ((temp64 >> 31) != 0 && (temp64 >> 31) != -1) flags |=   C_FLAG | V_FLAG;
        else                                             flags &= ~(C_FLAG | V_FLAG);
        regs[reg].l = temp64 & 0xffffffff;
        
        CLOCK_CYCLES(25);
        return 0;
}

static int opIMUL_w_ib_a16(uint32_t fetchdat)
{
        int32_t templ;
        int16_t tempw, tempw2;
        
        fetch_ea_16(fetchdat);
        
        tempw = geteaw();               if (abrt) return 1;
        tempw2 = getbyte();             if (abrt) return 1;
        if (tempw2 & 0x80) tempw2 |= 0xff00;
        
        templ = ((int)tempw) * ((int)tempw2);
        flags_rebuild();
        if ((templ >> 15) != 0 && (templ >> 15) != -1) flags |=   C_FLAG | V_FLAG;
        else                                           flags &= ~(C_FLAG | V_FLAG);
        regs[reg].w = templ & 0xffff;
        
        CLOCK_CYCLES((mod == 3) ? 14 : 17);
        return 0;
}
static int opIMUL_w_ib_a32(uint32_t fetchdat)
{
        int32_t templ;
        int16_t tempw, tempw2;
        
        fetch_ea_32(fetchdat);
        
        tempw = geteaw();               if (abrt) return 1;
        tempw2 = getbyte();             if (abrt) return 1;
        if (tempw2 & 0x80) tempw2 |= 0xff00;
        
        templ = ((int)tempw) * ((int)tempw2);
        flags_rebuild();
        if ((templ >> 15) != 0 && (templ >> 15) != -1) flags |=   C_FLAG | V_FLAG;
        else                                           flags &= ~(C_FLAG | V_FLAG);
        regs[reg].w = templ & 0xffff;
        
        CLOCK_CYCLES((mod == 3) ? 14 : 17);
        return 0;
}

static int opIMUL_l_ib_a16(uint32_t fetchdat)
{
        int64_t temp64;
        int32_t templ, templ2;

        fetch_ea_16(fetchdat);
        templ = geteal();               if (abrt) return 1;
        templ2 = getbyte();             if (abrt) return 1;
        if (templ2 & 0x80) templ2 |= 0xffffff00;
        
        temp64 = ((int64_t)templ)*((int64_t)templ2);
        flags_rebuild();
        if ((temp64 >> 31) != 0 && (temp64 >> 31) != -1) flags |=   C_FLAG | V_FLAG;
        else                                             flags &= ~(C_FLAG | V_FLAG);
        regs[reg].l = temp64 & 0xffffffff;
        
        CLOCK_CYCLES(20);
        return 0;
}
static int opIMUL_l_ib_a32(uint32_t fetchdat)
{
        int64_t temp64;
        int32_t templ, templ2;

        fetch_ea_32(fetchdat);
        templ = geteal();               if (abrt) return 1;
        templ2 = getbyte();             if (abrt) return 1;
        if (templ2 & 0x80) templ2 |= 0xffffff00;
        
        temp64 = ((int64_t)templ)*((int64_t)templ2);
        flags_rebuild();
        if ((temp64 >> 31) != 0 && (temp64 >> 31) != -1) flags |=   C_FLAG | V_FLAG;
        else                                             flags &= ~(C_FLAG | V_FLAG);
        regs[reg].l = temp64 & 0xffffffff;
        
        CLOCK_CYCLES(20);
        return 0;
}



static int opIMUL_w_w_a16(uint32_t fetchdat)
{
        int32_t templ;
        
        fetch_ea_16(fetchdat);
        templ = (int32_t)(int16_t)regs[reg].w * (int32_t)(int16_t)geteaw();
        if (abrt) return 1;
        regs[reg].w = templ & 0xFFFF;
        flags_rebuild();
        if ((templ >> 15) != 0 && (templ >> 15) != -1) flags |=   C_FLAG | V_FLAG;
        else                                           flags &= ~(C_FLAG | V_FLAG);
        
        CLOCK_CYCLES(18);
        return 0;
}
static int opIMUL_w_w_a32(uint32_t fetchdat)
{
        int32_t templ;
        
        fetch_ea_32(fetchdat);
        templ = (int32_t)(int16_t)regs[reg].w * (int32_t)(int16_t)geteaw();
        if (abrt) return 1;
        regs[reg].w = templ & 0xFFFF;
        flags_rebuild();
        if ((templ >> 15) != 0 && (templ >> 15) != -1) flags |=   C_FLAG | V_FLAG;
        else                                           flags &= ~(C_FLAG | V_FLAG);
        
        CLOCK_CYCLES(18);
        return 0;
}

static int opIMUL_l_l_a16(uint32_t fetchdat)
{
        int64_t temp64;

        fetch_ea_16(fetchdat);
        temp64 = (int64_t)(int32_t)regs[reg].l * (int64_t)(int32_t)geteal();
        if (abrt) return 1;
        regs[reg].l = temp64 & 0xFFFFFFFF;
        flags_rebuild();
        if ((temp64 >> 31) != 0 && (temp64 >> 31) != -1) flags |=   C_FLAG | V_FLAG;
        else                                             flags &= ~(C_FLAG | V_FLAG);
        
        CLOCK_CYCLES(30);
        return 0;
}
static int opIMUL_l_l_a32(uint32_t fetchdat)
{
        int64_t temp64;

        fetch_ea_32(fetchdat);
        temp64 = (int64_t)(int32_t)regs[reg].l * (int64_t)(int32_t)geteal();
        if (abrt) return 1;
        regs[reg].l = temp64 & 0xFFFFFFFF;
        flags_rebuild();
        if ((temp64 >> 31) != 0 && (temp64 >> 31) != -1) flags |=   C_FLAG | V_FLAG;
        else                                             flags &= ~(C_FLAG | V_FLAG);
        
        CLOCK_CYCLES(30);
        return 0;
}

