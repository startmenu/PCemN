static int opFSTSW_AX(uint32_t fetchdat)
{
        FP_ENTER();
        pc++;
        if (fplog) pclog("FSTSW\n");
        AX = npxs;
        CLOCK_CYCLES(3);
        return 0;
}



static int opFNOP(uint32_t fetchdat)
{
        FP_ENTER();
        pc++;
        CLOCK_CYCLES(4);
        return 0;
}

static int opFCLEX(uint32_t fetchdat)
{
        FP_ENTER();
        pc++;
        npxs &= 0xff00;
        CLOCK_CYCLES(4);
        return 0;
}

static int opFINIT(uint32_t fetchdat)
{
        FP_ENTER();
        pc++;
        npxc = 0x37F;
        npxs = 0;
        tag = 0xFFFF;
        TOP = 0;
        CLOCK_CYCLES(17);
        return 0;
}


static int opFFREE(uint32_t fetchdat)
{
        FP_ENTER();
        pc++;
        if (fplog) pclog("FFREE\n");
        tag |= (3 << (((TOP + fetchdat) & 7) << 1));
        CLOCK_CYCLES(3);
        return 0;
}

static int opFST(uint32_t fetchdat)
{
        int temp;
        FP_ENTER();
        pc++;
        if (fplog) pclog("FST\n");
        ST(fetchdat & 7) = ST(0);
        temp = (tag >> ((TOP & 7) << 1)) & 3;
        tag &= ~(3 << (((TOP + fetchdat) & 7) << 1));
        tag |= (temp << (((TOP + fetchdat) & 7) << 1));
        CLOCK_CYCLES(3);
        return 0;
}

static int opFSTP(uint32_t fetchdat)
{
        int temp;
        FP_ENTER();
        pc++;
        if (fplog) pclog("FSTP\n");
        ST(fetchdat & 7) = ST(0);
        temp = (tag >> ((TOP & 7) << 1)) & 3;
        tag &= ~(3 << (((TOP + fetchdat) & 7) << 1));
        tag |= (temp << (((TOP + fetchdat) & 7) << 1));
        x87_pop();
        CLOCK_CYCLES(3);
        return 0;
}




static int FSTOR()
{
        switch ((cr0 & 1) | (op32 & 0x100))
        {
                case 0x000: /*16-bit real mode*/
                case 0x001: /*16-bit protected mode*/
                npxc = readmemw(easeg, eaaddr);
                npxs = readmemw(easeg, eaaddr+2);
                tag = readmemw(easeg, eaaddr+4);
                TOP = (npxs >> 11) & 7;
                eaaddr += 14;
                break;
                case 0x100: /*32-bit real mode*/
                case 0x101: /*32-bit protected mode*/
                npxc = readmemw(easeg, eaaddr);
                npxs = readmemw(easeg, eaaddr+4);
                tag = readmemw(easeg, eaaddr+8);
                TOP = (npxs >> 11) & 7;
                eaaddr += 28;
                break;
        }
        x87_ldmmx(&MM[0]); ST(0)=x87_ld80(); eaaddr += 10;
        x87_ldmmx(&MM[1]); ST(1)=x87_ld80(); eaaddr += 10;
        x87_ldmmx(&MM[2]); ST(2)=x87_ld80(); eaaddr += 10;
        x87_ldmmx(&MM[3]); ST(3)=x87_ld80(); eaaddr += 10;
        x87_ldmmx(&MM[4]); ST(4)=x87_ld80(); eaaddr += 10;
        x87_ldmmx(&MM[5]); ST(5)=x87_ld80(); eaaddr += 10;
        x87_ldmmx(&MM[6]); ST(6)=x87_ld80(); eaaddr += 10;
        x87_ldmmx(&MM[7]); ST(7)=x87_ld80();
        ismmx = 0;
        /*Horrible hack, but as PCem doesn't keep the FPU stack in 80-bit precision at all times
          something like this is needed*/
        if (MM[0].w[4] == 0xffff && MM[1].w[4] == 0xffff && MM[2].w[4] == 0xffff && MM[3].w[4] == 0xffff &&
            MM[4].w[4] == 0xffff && MM[5].w[4] == 0xffff && MM[6].w[4] == 0xffff && MM[7].w[4] == 0xffff &&
            !TOP && !tag)
        ismmx = 1;

        CLOCK_CYCLES((cr0 & 1) ? 34 : 44);
        if (fplog) pclog("FRSTOR %08X:%08X %i %i %04X\n", easeg, eaaddr, ismmx, TOP, tag);
        return abrt;
}
static int opFSTOR_a16(uint32_t fetchdat)
{
        FP_ENTER();
        fetch_ea_16(fetchdat);
        FSTOR();
        return abrt;
}
static int opFSTOR_a32(uint32_t fetchdat)
{
        FP_ENTER();
        fetch_ea_32(fetchdat);
        FSTOR();
        return abrt;
}

static int FSAVE()
{
        if (fplog) pclog("FSAVE %08X:%08X %i\n", easeg, eaaddr, ismmx);
        npxs = (npxs & ~(7 << 11)) | (TOP << 11);

        switch ((cr0&1)|(op32&0x100))
        {
                case 0x000: /*16-bit real mode*/
                writememw(easeg,eaaddr,npxc);
                writememw(easeg,eaaddr+2,npxs);
                writememw(easeg,eaaddr+4,tag);
                writememw(easeg,eaaddr+6,x87_pc_off);
                writememw(easeg,eaaddr+10,x87_op_off);
                eaaddr+=14;
                if (ismmx)
                {
                        x87_stmmx(MM[0]); eaaddr+=10;
                        x87_stmmx(MM[1]); eaaddr+=10;
                        x87_stmmx(MM[2]); eaaddr+=10;
                        x87_stmmx(MM[3]); eaaddr+=10;
                        x87_stmmx(MM[4]); eaaddr+=10;
                        x87_stmmx(MM[5]); eaaddr+=10;
                        x87_stmmx(MM[6]); eaaddr+=10;
                        x87_stmmx(MM[7]);
                }
                else
                {
                        x87_st80(ST(0)); eaaddr+=10;
                        x87_st80(ST(1)); eaaddr+=10;
                        x87_st80(ST(2)); eaaddr+=10;
                        x87_st80(ST(3)); eaaddr+=10;
                        x87_st80(ST(4)); eaaddr+=10;
                        x87_st80(ST(5)); eaaddr+=10;
                        x87_st80(ST(6)); eaaddr+=10;
                        x87_st80(ST(7));
                }
                break;
                case 0x001: /*16-bit protected mode*/
                writememw(easeg,eaaddr,npxc);
                writememw(easeg,eaaddr+2,npxs);
                writememw(easeg,eaaddr+4,tag);
                writememw(easeg,eaaddr+6,x87_pc_off);
                writememw(easeg,eaaddr+8,x87_pc_seg);
                writememw(easeg,eaaddr+10,x87_op_off);
                writememw(easeg,eaaddr+12,x87_op_seg);
                eaaddr+=14;
                if (ismmx)
                {
                        x87_stmmx(MM[0]); eaaddr+=10;
                        x87_stmmx(MM[1]); eaaddr+=10;
                        x87_stmmx(MM[2]); eaaddr+=10;
                        x87_stmmx(MM[3]); eaaddr+=10;
                        x87_stmmx(MM[4]); eaaddr+=10;
                        x87_stmmx(MM[5]); eaaddr+=10;
                        x87_stmmx(MM[6]); eaaddr+=10;
                        x87_stmmx(MM[7]);
                }
                else
                {
                        x87_st80(ST(0)); eaaddr+=10;
                        x87_st80(ST(1)); eaaddr+=10;
                        x87_st80(ST(2)); eaaddr+=10;
                        x87_st80(ST(3)); eaaddr+=10;
                        x87_st80(ST(4)); eaaddr+=10;
                        x87_st80(ST(5)); eaaddr+=10;
                        x87_st80(ST(6)); eaaddr+=10;
                        x87_st80(ST(7));
                }
                break;
                case 0x100: /*32-bit real mode*/
                writememw(easeg,eaaddr,npxc);
                writememw(easeg,eaaddr+4,npxs);
                writememw(easeg,eaaddr+8,tag);
                writememw(easeg,eaaddr+12,x87_pc_off);
                writememw(easeg,eaaddr+20,x87_op_off);
                writememl(easeg,eaaddr+24,(x87_op_off>>16)<<12);
                eaaddr+=28;
                if (ismmx)
                {
                        x87_stmmx(MM[0]); eaaddr+=10;
                        x87_stmmx(MM[1]); eaaddr+=10;
                        x87_stmmx(MM[2]); eaaddr+=10;
                        x87_stmmx(MM[3]); eaaddr+=10;
                        x87_stmmx(MM[4]); eaaddr+=10;
                        x87_stmmx(MM[5]); eaaddr+=10;
                        x87_stmmx(MM[6]); eaaddr+=10;
                        x87_stmmx(MM[7]);
                }
                else
                {
                        x87_st80(ST(0)); eaaddr+=10;
                        x87_st80(ST(1)); eaaddr+=10;
                        x87_st80(ST(2)); eaaddr+=10;
                        x87_st80(ST(3)); eaaddr+=10;
                        x87_st80(ST(4)); eaaddr+=10;
                        x87_st80(ST(5)); eaaddr+=10;
                        x87_st80(ST(6)); eaaddr+=10;
                        x87_st80(ST(7));
                }
                break;
                case 0x101: /*32-bit protected mode*/
                writememw(easeg,eaaddr,npxc);
                writememw(easeg,eaaddr+4,npxs);
                writememw(easeg,eaaddr+8,tag);
                writememl(easeg,eaaddr+12,x87_pc_off);
                writememl(easeg,eaaddr+16,x87_pc_seg);
                writememl(easeg,eaaddr+20,x87_op_off);
                writememl(easeg,eaaddr+24,x87_op_seg);
                eaaddr+=28;
                if (ismmx)
                {
                        x87_stmmx(MM[0]); eaaddr+=10;
                        x87_stmmx(MM[1]); eaaddr+=10;
                        x87_stmmx(MM[2]); eaaddr+=10;
                        x87_stmmx(MM[3]); eaaddr+=10;
                        x87_stmmx(MM[4]); eaaddr+=10;
                        x87_stmmx(MM[5]); eaaddr+=10;
                        x87_stmmx(MM[6]); eaaddr+=10;
                        x87_stmmx(MM[7]);
                }
                else
                {
                        x87_st80(ST(0)); eaaddr+=10;
                        x87_st80(ST(1)); eaaddr+=10;
                        x87_st80(ST(2)); eaaddr+=10;
                        x87_st80(ST(3)); eaaddr+=10;
                        x87_st80(ST(4)); eaaddr+=10;
                        x87_st80(ST(5)); eaaddr+=10;
                        x87_st80(ST(6)); eaaddr+=10;
                        x87_st80(ST(7));
                }
                break;
        }
        CLOCK_CYCLES((cr0 & 1) ? 56 : 67);
        return abrt;
}
static int opFSAVE_a16(uint32_t fetchdat)
{
        FP_ENTER();
        fetch_ea_16(fetchdat);
        FSAVE();
        return abrt;
}
static int opFSAVE_a32(uint32_t fetchdat)
{
        FP_ENTER();
        fetch_ea_32(fetchdat);
        FSAVE();
        return abrt;
}

static int opFSTSW_a16(uint32_t fetchdat)
{
        FP_ENTER();
        fetch_ea_16(fetchdat);
        if (fplog) pclog("FSTSW %08X:%08X\n", easeg, eaaddr);
        seteaw((npxs & 0xC7FF) | (TOP << 11));
        CLOCK_CYCLES(3);
        return abrt;
}
static int opFSTSW_a32(uint32_t fetchdat)
{
        FP_ENTER();
        fetch_ea_32(fetchdat);
        if (fplog) pclog("FSTSW %08X:%08X\n", easeg, eaaddr);
        seteaw((npxs & 0xC7FF) | (TOP << 11));
        CLOCK_CYCLES(3);
        return abrt;
}


static int opFLD(uint32_t fetchdat)
{
        FP_ENTER();
        pc++;
        if (fplog) pclog("FLD %f\n", ST(fetchdat & 7));
        x87_push(ST(fetchdat&7));
        CLOCK_CYCLES(4);
        return 0;
}

static int opFXCH(uint32_t fetchdat)
{
        double td;
        FP_ENTER();
        pc++;
        if (fplog) pclog("FXCH\n");
        td = ST(0);
        ST(0) = ST(fetchdat&7);
        ST(fetchdat&7) = td;
        CLOCK_CYCLES(4);
        return 0;
}

static int opFCHS(uint32_t fetchdat)
{
        FP_ENTER();
        pc++;
        if (fplog) pclog("FCHS\n");
        ST(0) = -ST(0);
        CLOCK_CYCLES(6);
        return 0;
}

static int opFABS(uint32_t fetchdat)
{
        FP_ENTER();
        pc++;
        if (fplog) pclog("FABS %f\n", ST(0));
        ST(0) = fabs(ST(0));
        CLOCK_CYCLES(3);
        return 0;
}

static int opFTST(uint32_t fetchdat)
{
        FP_ENTER();
        pc++;
        if (fplog) pclog("FTST\n");
        npxs &= ~(C0|C2|C3);
        if (ST(0) == 0.0)     npxs |= C3;
        else if (ST(0) < 0.0) npxs |= C0;
        CLOCK_CYCLES(4);
        return 0;
}

static int opFXAM(uint32_t fetchdat)
{
        FP_ENTER();
        pc++;
        if (fplog) pclog("FXAM %i %f\n", ((tag>>((TOP&7)<<1))&3), ST(0));
        npxs &= ~(C0|C2|C3);
        if (((tag>>((TOP&7)<<1))&3)==3) npxs |= (C0|C3);
        else if (ST(0) == 0.0)          npxs |= C3;
        else                            npxs |= C2;
        if (ST(0) < 0.0)                npxs |= C1;
        CLOCK_CYCLES(8);
        return 0;
}

static int opFLD1(uint32_t fetchdat)
{
        FP_ENTER();
        pc++;
        if (fplog) pclog("FLD1\n");
        x87_push(1.0);
        CLOCK_CYCLES(4);
        return 0;
}

static int opFLDL2T(uint32_t fetchdat)
{
        FP_ENTER();
        pc++;
        if (fplog) pclog("FLDL2T\n");
        x87_push(3.3219280948873623);
        CLOCK_CYCLES(8);
        return 0;
}

static int opFLDL2E(uint32_t fetchdat)
{
        FP_ENTER();
        pc++;
        if (fplog) pclog("FLDL2E\n");
        x87_push(1.4426950408889634);
        CLOCK_CYCLES(8);
        return 0;
}

static int opFLDPI(uint32_t fetchdat)
{
        FP_ENTER();
        pc++;
        if (fplog) pclog("FLDPI\n");
        x87_push(3.141592653589793);
        CLOCK_CYCLES(8);
        return 0;
}

static int opFLDEG2(uint32_t fetchdat)
{
        FP_ENTER();
        pc++;
        if (fplog) pclog("FLDEG2\n");
        x87_push(0.3010299956639812);
        CLOCK_CYCLES(8);
        return 0;
}

static int opFLDLN2(uint32_t fetchdat)
{
        FP_ENTER();
        pc++;
        if (fplog) pclog("FLDLN2\n");
        x87_push(0.693147180559945);
        CLOCK_CYCLES(8);
        return 0;
}
 
static int opFLDZ(uint32_t fetchdat)
{
        FP_ENTER();
        pc++;
        if (fplog) pclog("FLDZ\n");
        x87_push(0.0);
        tag |= (1<<((TOP&7)<<1));
        CLOCK_CYCLES(4);
        return 0;
}

static int opF2XM1(uint32_t fetchdat)
{
        FP_ENTER();
        pc++;
        if (fplog) pclog("F2XM1\n");
        ST(0) = pow(2.0, ST(0)) - 1.0;
        CLOCK_CYCLES(200);
        return 0;
}

static int opFYL2X(uint32_t fetchdat)
{
        FP_ENTER();
        pc++;
        if (fplog) pclog("FYL2X\n");
        ST(1) = ST(1) * (log(ST(0)) / log(2.0));
        x87_pop();
        CLOCK_CYCLES(250);
        return 0;
}

static int opFPTAN(uint32_t fetchdat)
{
        FP_ENTER();
        pc++;
        if (fplog) pclog("FPTAN\n");
        ST(0) = tan(ST(0));
        x87_push(1.0);
        npxs &= ~C2;
        CLOCK_CYCLES(235);
        return 0;
}

static int opFPATAN(uint32_t fetchdat)
{
        FP_ENTER();
        pc++;
        if (fplog) pclog("FPATAN\n");
        ST(1) = atan2(ST(1), ST(0));
        x87_pop();
        CLOCK_CYCLES(250);
        return 0;
}

static int opFDECSTP(uint32_t fetchdat)
{
        FP_ENTER();
        pc++;
        if (fplog) pclog("FDECSTP\n");
        TOP = (TOP - 1) & 7;
        CLOCK_CYCLES(4);
        return 0;
}

static int opFINCSTP(uint32_t fetchdat)
{
        FP_ENTER();
        pc++;
        if (fplog) pclog("FDECSTP\n");
        TOP = (TOP + 1) & 7;
        CLOCK_CYCLES(4);
        return 0;
}

static int opFPREM(uint32_t fetchdat)
{
        int64_t temp64;
        FP_ENTER();
        pc++;
        if (fplog) pclog("FPREM %f %f  ", ST(0), ST(1));
        temp64 = (int64_t)(ST(0) / ST(1));
        ST(0) = ST(0) - (ST(1) * (double)temp64);
        if (fplog) pclog("%f\n", ST(0));
        npxs &= ~(C0|C1|C2|C3);
        if (temp64 & 4) npxs|=C0;
        if (temp64 & 2) npxs|=C3;
        if (temp64 & 1) npxs|=C1;
        CLOCK_CYCLES(100);
        return 0;
}

static int opFSQRT(uint32_t fetchdat)
{
        FP_ENTER();
        pc++;
        if (fplog) pclog("FSQRT\n");
        ST(0) = sqrt(ST(0));
        CLOCK_CYCLES(83);
        return 0;
}

static int opFSINCOS(uint32_t fetchdat)
{
        double td;
        FP_ENTER();
        pc++;
        if (fplog) pclog("FSINCOS\n");
        td = ST(0);
        ST(0) = sin(td);
        x87_push(cos(td));
        npxs &= ~C2;
        CLOCK_CYCLES(330);
        return 0;
}

static int opFRNDINT(uint32_t fetchdat)
{
        FP_ENTER();
        pc++;
        if (fplog) pclog("FRNDINT %g ", ST(0));
        ST(0) = (double)x87_fround(ST(0));
        if (fplog) pclog("%g\n", ST(0));
        CLOCK_CYCLES(21);
        return 0;
}

static int opFSCALE(uint32_t fetchdat)
{
        int64_t temp64;
        FP_ENTER();
        pc++;
        if (fplog) pclog("FSCALE\n");
        temp64 = (int64_t)ST(1);
        ST(0) = ST(0) * pow(2.0, (double)temp64);
        CLOCK_CYCLES(30);
        return 0;
}

static int opFSIN(uint32_t fetchdat)
{
        FP_ENTER();
        pc++;
        if (fplog) pclog("FSIN\n");
        ST(0) = sin(ST(0));
        npxs &= ~C2;
        CLOCK_CYCLES(300);
        return 0;
}

static int opFCOS(uint32_t fetchdat)
{
        FP_ENTER();
        pc++;
        if (fplog) pclog("FCOS\n");
        ST(0) = cos(ST(0));
        npxs &= ~C2;
        CLOCK_CYCLES(300);
        return 0;
}


static int FLDENV()
{
        if (fplog) pclog("FLDENV %08X:%08X\n", easeg, eaaddr);
        switch ((cr0 & 1) | (op32 & 0x100))
        {
                case 0x000: /*16-bit real mode*/
                case 0x001: /*16-bit protected mode*/
                npxc = readmemw(easeg, eaaddr);
                npxs = readmemw(easeg, eaaddr+2);
                tag = readmemw(easeg, eaaddr+4);
                TOP = (npxs >> 11) & 7;
                break;
                case 0x100: /*32-bit real mode*/
                case 0x101: /*32-bit protected mode*/
                npxc = readmemw(easeg, eaaddr);
                npxs = readmemw(easeg, eaaddr+4);
                tag = readmemw(easeg, eaaddr+8);
                TOP = (npxs >> 11) & 7;
                break;
        }
        CLOCK_CYCLES((cr0 & 1) ? 34 : 44);
        return abrt;
}

static int opFLDENV_a16(uint32_t fetchdat)
{
        FP_ENTER();
        fetch_ea_16(fetchdat);
        FLDENV();
        return abrt;
}
static int opFLDENV_a32(uint32_t fetchdat)
{
        FP_ENTER();
        fetch_ea_32(fetchdat);
        FLDENV();
        return abrt;
}

static int opFLDCW_a16(uint32_t fetchdat)
{
        uint16_t tempw;
        FP_ENTER();
        fetch_ea_16(fetchdat);
        if (fplog) pclog("FLDCW %08X:%08X\n", easeg, eaaddr);                        
        tempw = geteaw();
        if (abrt) return 1;
        npxc = tempw;
        CLOCK_CYCLES(4);
        return 0;
}
static int opFLDCW_a32(uint32_t fetchdat)
{
        uint16_t tempw;
        FP_ENTER();
        fetch_ea_32(fetchdat);
        if (fplog) pclog("FLDCW %08X:%08X\n", easeg, eaaddr);                        
        tempw = geteaw();
        if (abrt) return 1;
        npxc = tempw;
        CLOCK_CYCLES(4);
        return 0;
}

static int FSTENV()
{
        if (fplog) pclog("FSTENV %08X:%08X\n", easeg, eaaddr);
        switch ((cr0 & 1) | (op32 & 0x100))
        {
                case 0x000: /*16-bit real mode*/
                writememw(easeg,eaaddr,npxc);
                writememw(easeg,eaaddr+2,npxs);
                writememw(easeg,eaaddr+4,tag);
                writememw(easeg,eaaddr+6,x87_pc_off);
                writememw(easeg,eaaddr+10,x87_op_off);
                break;
                case 0x001: /*16-bit protected mode*/
                writememw(easeg,eaaddr,npxc);
                writememw(easeg,eaaddr+2,npxs);
                writememw(easeg,eaaddr+4,tag);
                writememw(easeg,eaaddr+6,x87_pc_off);
                writememw(easeg,eaaddr+8,x87_pc_seg);
                writememw(easeg,eaaddr+10,x87_op_off);
                writememw(easeg,eaaddr+12,x87_op_seg);
                break;
                case 0x100: /*32-bit real mode*/
                writememw(easeg,eaaddr,npxc);
                writememw(easeg,eaaddr+4,npxs);
                writememw(easeg,eaaddr+8,tag);
                writememw(easeg,eaaddr+12,x87_pc_off);
                writememw(easeg,eaaddr+20,x87_op_off);
                writememl(easeg,eaaddr+24,(x87_op_off>>16)<<12);
                break;
                case 0x101: /*32-bit protected mode*/
                writememw(easeg,eaaddr,npxc);
                writememw(easeg,eaaddr+4,npxs);
                writememw(easeg,eaaddr+8,tag);
                writememl(easeg,eaaddr+12,x87_pc_off);
                writememl(easeg,eaaddr+16,x87_pc_seg);
                writememl(easeg,eaaddr+20,x87_op_off);
                writememl(easeg,eaaddr+24,x87_op_seg);
                break;
        }
        CLOCK_CYCLES((cr0 & 1) ? 56 : 67);
        return abrt;
}

static int opFSTENV_a16(uint32_t fetchdat)
{
        FP_ENTER();
        fetch_ea_16(fetchdat);
        FSTENV();
        return abrt;
}
static int opFSTENV_a32(uint32_t fetchdat)
{
        FP_ENTER();
        fetch_ea_32(fetchdat);
        FSTENV();
        return abrt;
}

static int opFSTCW_a16(uint32_t fetchdat)
{
        FP_ENTER();
        fetch_ea_16(fetchdat);
        if (fplog) pclog("FSTCW %08X:%08X\n", easeg, eaaddr);
        seteaw(npxc);
        CLOCK_CYCLES(3);
        return abrt;
}
static int opFSTCW_a32(uint32_t fetchdat)
{
        FP_ENTER();
        fetch_ea_32(fetchdat);
        if (fplog) pclog("FSTCW %08X:%08X\n", easeg, eaaddr);
        seteaw(npxc);
        CLOCK_CYCLES(3);
        return abrt;
}
