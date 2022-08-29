"""
Templates.
"""

MAKEFRAG_TEMPLATE = """
#=======================================================================
# Makefrag for rv64uv tests
#-----------------------------------------------------------------------

rv64uv_sc_tests = \\
{data}

rv64uv_p_tests = $(addprefix rv64uv-p-, $(rv64uv_sc_tests))
rv64uv_v_tests = $(addprefix rv64uv-v-, $(rv64uv_sc_tests))
"""


TEMPLATE_HEADER = """
# See LICENSE for license details.

# This file is automatically generated. Do not edit.

#*****************************************************************************
# {filename}
#-----------------------------------------------------------------------------
#
# Test {inst_name} instructions.
# {extras}
#

#include "riscv_test.h"
#include "test_macros.h"

RVTEST_RV64UV
"""

MASK_CODE = """
  li t0, -1
  vsetvli t1, t0, e8,m1,ta,ma
  la a3, mask
  vle8.v v0, (a3)
"""

VLRE_TEMPLATE = """
RVTEST_CODE_BEGIN

  li t0, -1
  vsetvli t1, t0, e{eew},m{nf}
  la a2, tdat
  mv s1, a2
  addi a2, a2, 8
  vle{eew}.v v0, (a2)

  vl{nf}re{eew}.v v0, (s1)

  li t0, -1
  vsetvli t1, t0, e{eew},m{nf}
  la a1, res
  vse{eew}.v v0, (a1)

{test_cases}

  TEST_PASSFAIL

RVTEST_CODE_END

  .data
RVTEST_DATA_BEGIN

res:
  .zero {nbytes}

tdat:
{test_data_str}

RVTEST_DATA_END
"""


VLE_CODE_TEMPLATE = """
  li t0, -1
  vsetvli t1, t0, e{eew},m{lmul},ta,ma
  la a2, tdat
  mv s1, a2
  addi a2, a2, 8
  vle{eew}.v v{lmul}, (a2)

  {mask_code}
  li t0, {vl}
  vsetvli t1, t0, e{eew},m{lmul},{vta},{vma}
  vle{eew}.v v{lmul}, (s1){v0t}

  li t0, -1
  vsetvli t1, t0, e{eew},m{lmul},ta,ma
  la a1, res
  vse{eew}.v v{lmul}, (a1)"""


VSE_CODE_TEMPLATE = """
  li t0, -1
  vsetvli t1, t0, e{eew},m{lmul},ta,ma
  la a2, tdat
  mv s1, a2
  addi a2, a2, 8
  vle{eew}.v v{lmul}, (a2)
  la a1, res
  vse{eew}.v v{lmul}, (a1)
  vle{eew}.v v{lmul}, (s1)

  {mask_code}
  li t0, {vl}
  vsetvli t1, t0, e{eew},m{lmul},{vta},{vma}
  vse{eew}.v v{lmul}, (a1){v0t}"""


VLSE_TEMPLATE = """
RVTEST_CODE_BEGIN

{code_vm0_ta_ma}
{test_cases_vm0_ta_ma}

{code_vm1_ta_ma}
{test_cases_vm1_ta_ma}

{code_vm0_tu_ma}
{test_cases_vm0_tu_ma}

{code_vm1_ta_mu}
{test_cases_vm1_ta_mu}

  TEST_PASSFAIL

RVTEST_CODE_END

  .data
RVTEST_DATA_BEGIN

res:
  .zero {nbytes}

tdat:
{test_data_str}

mask:
  .quad 0x5555555555555555
  .quad 0x5555555555555555
  .quad 0x5555555555555555
  .quad 0x5555555555555555

RVTEST_DATA_END
"""

ARITH_VV_CODE_TEMPLATE = """
  li t0, -1
  vsetvli t1, t0, e{sew},m{lmul},ta,ma
  la a2, tdat
  vle{sew}.v v{vs1}, (a2)
  vle{sew}.v v{vd}, (a2)
  la a2, tdat+8
  vle{sew}.v v{vs2}, (a2)

  {mask_code}
  li t0, {vl}
  vsetvli t1, t0, e{sew},m{lmul},{vta},{vma}
  {op} v{vd}, v{vs1}, v{vs2}{v0t}

  li t0, -1
  vsetvli t1, t0, e{sew},m{lmul},ta,ma
  la a1, res
  vse{sew}.v v{vd}, (a1)
  la a2, sres
"""

ARITH_VI_CODE_TEMPLATE = """
  li t0, -1
  vsetvli t1, t0, e{sew},m{lmul},ta,ma
  la a2, tdat
  vle{sew}.v v{vs1}, (a2)
  vle{sew}.v v{vd}, (a2)

  {mask_code}
  li t0, {vl}
  vsetvli t1, t0, e{sew},m{lmul},{vta},{vma}
  {op} v{vd}, v{vs1}, {imm}{v0t}

  li t0, -1
  vsetvli t1, t0, e{sew},m{lmul},ta,ma
  la a1, res
  vse{sew}.v v{vd}, (a1)
  la a2, sres
"""

ARITH_VX_CODE_TEMPLATE = """
  li t0, -1
  vsetvli t1, t0, e{sew},m{lmul},ta,ma
  la a2, tdat
  vle{sew}.v v{vs1}, (a2)
  vle{sew}.v v{vd}, (a2)

  {mask_code}
  li t0, {vl}
  vsetvli t1, t0, e{sew},m{lmul},{vta},{vma}
  li t2, {imm}
  {op} v{vd}, v{vs1}, t2{v0t}

  li t0, -1
  vsetvli t1, t0, e{sew},m{lmul},ta,ma
  la a1, res
  vse{sew}.v v{vd}, (a1)
  la a2, sres
"""

ARITH_VF_CODE_TEMPLATE = """
  li t0, -1
  vsetvli t1, t0, e{sew},m{lmul},ta,ma
  la a2, tdat
  vle{sew}.v v{vs1}, (a2)
  vle{sew}.v v{vd}, (a2)

  {mask_code}
  li t0, {vl}
  vsetvli t1, t0, e{sew},m{lmul},{vta},{vma}
  li t2, {imm}
  fmv.{fmv_unit}.x f2, t2
  {op} v{vd}, v{vs1}, f2{v0t}

  li t0, -1
  vsetvli t1, t0, e{sew},m{lmul},ta,ma
  la a1, res
  vse{sew}.v v{vd}, (a1)
  la a2, sres
"""

ARITH_TEMPLATE = """
RVTEST_CODE_BEGIN

{scalar_code}

{code_vm0_ta_ma}
{test_cases_vm0_ta_ma}
{code_vm1_ta_ma}
{test_cases_vm1_ta_ma}
{code_vm0_tu_ma}
{test_cases_vm0_tu_ma}
{code_vm1_ta_mu}
{test_cases_vm1_ta_mu}

  TEST_PASSFAIL

RVTEST_CODE_END

  .data
RVTEST_DATA_BEGIN

res:
  .zero {nbytes}

sres:
  .zero {nbytes}

tdat:
{test_data}

mask:
  .quad 0x5555555555555555
  .quad 0x5555555555555555
  .quad 0x5555555555555555
  .quad 0x5555555555555555

RVTEST_DATA_END
"""