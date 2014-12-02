typedef int (*OpFn)(uint32_t fetchdat);

#ifdef DYNAREC
void x86_setopcodes(OpFn *opcodes, OpFn *opcodes_0f, OpFn *dynarec_opcodes, OpFn *dynarec_opcodes_0f);

extern OpFn *x86_dynarec_opcodes;
extern OpFn *x86_dynarec_opcodes_0f;
extern OpFn *x86_dynarec_opcodes_d8_a16;
extern OpFn *x86_dynarec_opcodes_d8_a32;
extern OpFn *x86_dynarec_opcodes_d9_a16;
extern OpFn *x86_dynarec_opcodes_d9_a32;
extern OpFn *x86_dynarec_opcodes_da_a16;
extern OpFn *x86_dynarec_opcodes_da_a32;
extern OpFn *x86_dynarec_opcodes_db_a16;
extern OpFn *x86_dynarec_opcodes_db_a32;
extern OpFn *x86_dynarec_opcodes_dc_a16;
extern OpFn *x86_dynarec_opcodes_dc_a32;
extern OpFn *x86_dynarec_opcodes_dd_a16;
extern OpFn *x86_dynarec_opcodes_dd_a32;
extern OpFn *x86_dynarec_opcodes_de_a16;
extern OpFn *x86_dynarec_opcodes_de_a32;
extern OpFn *x86_dynarec_opcodes_df_a16;
extern OpFn *x86_dynarec_opcodes_df_a32;

extern OpFn dynarec_ops_286[1024];
extern OpFn dynarec_ops_286_0f[1024];

extern OpFn dynarec_ops_386[1024];
extern OpFn dynarec_ops_386_0f[1024];

extern OpFn dynarec_ops_winchip_0f[1024];

extern OpFn dynarec_ops_pentium_0f[1024];
extern OpFn dynarec_ops_pentiummmx_0f[1024];

extern OpFn dynarec_ops_fpu_d8_a16[32];
extern OpFn dynarec_ops_fpu_d8_a32[32];
extern OpFn dynarec_ops_fpu_d9_a16[256];
extern OpFn dynarec_ops_fpu_d9_a32[256];
extern OpFn dynarec_ops_fpu_da_a16[256];
extern OpFn dynarec_ops_fpu_da_a32[256];
extern OpFn dynarec_ops_fpu_db_a16[256];
extern OpFn dynarec_ops_fpu_db_a32[256];
extern OpFn dynarec_ops_fpu_dc_a16[32];
extern OpFn dynarec_ops_fpu_dc_a32[32];
extern OpFn dynarec_ops_fpu_dd_a16[256];
extern OpFn dynarec_ops_fpu_dd_a32[256];
extern OpFn dynarec_ops_fpu_de_a16[256];
extern OpFn dynarec_ops_fpu_de_a32[256];
extern OpFn dynarec_ops_fpu_df_a16[256];
extern OpFn dynarec_ops_fpu_df_a32[256];
extern OpFn dynarec_ops_nofpu_a16[256];
extern OpFn dynarec_ops_nofpu_a32[256];
#else
void x86_setopcodes(OpFn *opcodes, OpFn *opcodes_0f);
#endif

extern OpFn *x86_opcodes;
extern OpFn *x86_opcodes_0f;
extern OpFn *x86_opcodes_d8_a16;
extern OpFn *x86_opcodes_d8_a32;
extern OpFn *x86_opcodes_d9_a16;
extern OpFn *x86_opcodes_d9_a32;
extern OpFn *x86_opcodes_da_a16;
extern OpFn *x86_opcodes_da_a32;
extern OpFn *x86_opcodes_db_a16;
extern OpFn *x86_opcodes_db_a32;
extern OpFn *x86_opcodes_dc_a16;
extern OpFn *x86_opcodes_dc_a32;
extern OpFn *x86_opcodes_dd_a16;
extern OpFn *x86_opcodes_dd_a32;
extern OpFn *x86_opcodes_de_a16;
extern OpFn *x86_opcodes_de_a32;
extern OpFn *x86_opcodes_df_a16;
extern OpFn *x86_opcodes_df_a32;

extern OpFn ops_286[1024];
extern OpFn ops_286_0f[1024];

extern OpFn ops_386[1024];
extern OpFn ops_386_0f[1024];

extern OpFn ops_winchip_0f[1024];

extern OpFn ops_pentium_0f[1024];
extern OpFn ops_pentiummmx_0f[1024];

extern OpFn ops_fpu_d8_a16[32];
extern OpFn ops_fpu_d8_a32[32];
extern OpFn ops_fpu_d9_a16[256];
extern OpFn ops_fpu_d9_a32[256];
extern OpFn ops_fpu_da_a16[256];
extern OpFn ops_fpu_da_a32[256];
extern OpFn ops_fpu_db_a16[256];
extern OpFn ops_fpu_db_a32[256];
extern OpFn ops_fpu_dc_a16[32];
extern OpFn ops_fpu_dc_a32[32];
extern OpFn ops_fpu_dd_a16[256];
extern OpFn ops_fpu_dd_a32[256];
extern OpFn ops_fpu_de_a16[256];
extern OpFn ops_fpu_de_a32[256];
extern OpFn ops_fpu_df_a16[256];
extern OpFn ops_fpu_df_a32[256];
extern OpFn ops_nofpu_a16[256];
extern OpFn ops_nofpu_a32[256];
