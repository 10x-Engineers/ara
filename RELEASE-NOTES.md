<h1>ARA July-15 Release Notes</h1>

The purpose of this document is to record all the changes made for July 15 ARA RVV-1.0 compliant release. It includes the details of the RTL modifications/additions, tests added, CI checks enabled for keeping the PRs clean and the regression results.

<h2>1. RTL</h2>

The base-line ARA branch used for making all the changes was [10x-Engineers/ara/rc1_1.0](https://github.com/10x-Engineers/ara/tree/rc1_1.0) and the latest commit on it was from 17th May, 2022 by suehtamacv with hash: da92dee72b615c95e561b3836012cb27036203a1 which later on was rebased to hash: f350c49a8f61e0cac20a2b3e0430abd5390ee14e from 13th July, 2022. The PRs which were cherry-picked and the additional RTL changes made for the July 15 release are as follows.

* Renamed `vpopc.m` to `vcpop.m` for consistency with scalar instruction. Kept the old assembler name as an alias. The corresponding PR used for this purpose is [PR-117](https://github.com/pulp-platform/ara/pull/117) from [pulp-platform/ara/hotfix/masku](https://github.com/pulp-platform/ara/tree/hotfix/masku) (Dropped for August 15 release)
* The fixed point saturation flag is in bit-0 of the `vxsat` csr and the upper bits should be written as zeros. In order to implement the functionality of `vxsat`, [PR-106](https://github.com/pulp-platform/ara/pull/106) from the [pulp-platform/ara/main](https://github.com/pulp-platform/ara) is incorporated
* The fixed point rounding mode field is in the lower two bits of the `vxrm` csr and the upper bits should be written as zeros. In order to implement the functionality of `vxrm`, [PR-106](https://github.com/pulp-platform/ara/pull/106) from the [pulp-platform/ara/main](https://github.com/pulp-platform/ara) is used
* The functionality of the 5 vector fixed-point instructions is implemented by incorporating [PR-106](https://github.com/pulp-platform/ara/pull/106) from [pulp-platform/ara/main](https://github.com/pulp-platform/ara)
* Fixed the RTL for `vasub` and `vasubu` instructions in `simd_alu` file from `ara/hardware/src/lane` directory
* Renamed `vmornot` to `vmorn` to be consistent with the equivalent scalar instructions. The old `vmornot` mnemonics will be retained as aliases in assembler
* Renamed `vmandnot` to `vmandn` to be consistent with the equivalent scalar instructions. The old `vmandnot`  mnemonics will be retained as aliases in assembler
* In order to add support for the interaction of `mstatus.VS` and `mstatus.SD` fields, `csr_regfile` from the cva6 (cloned as a submodule in ARA) is modified
* The hash of the cva6 submodule was updated in order to clone the cva6 with modified `csr_regfile` as a submodule
* Following table lists down all the PRs made on [10x-Engineers/ara/rc1_1.0](https://github.com/10x-Engineers/ara/tree/rc1_1.0) branch with their status:

<table>
  <tr>
   <td>
<strong>PR#</strong>
   </td>
   <td><strong>Description</strong>
   </td>
   <td><strong>Status</strong>
   </td>
  </tr>
  <tr>
   <td><a href="https://github.com/10x-Engineers/ara/pull/1">1</a>
   </td>
   <td>Changes <b>vpopc_m</b> mnemonic to <b>vcpop</b> to make it consistent with scalar instruction and adds new test with <b>vcpop</b> mnemonic
   </td>
   <td>Dropped (for August 15 release)
   </td>
  </tr>
  <tr>
   <td><a href="https://github.com/10x-Engineers/ara/pull/2">2</a>
   </td>
   <td>Changes <b>vmandnot</b> and <b>vmornot</b> mnemonics to <b>vmandn</b> and <b>vmorn</b> respectively to make it consistent with scalar instructions
   </td>
   <td>Merged
   </td>
  </tr>
  <tr>
   <td><a href="https://github.com/10x-Engineers/ara/pull/3">3</a>
   </td>
   <td>Adds <b>vxrm.c</b> and <b>vxsat.c</b> tests to test rounding mode and saturation bit respectively
   </td>
   <td>Merged
   </td>
  </tr>
  <tr>
   <td><a href="https://github.com/10x-Engineers/ara/pull/5">5</a>
   </td>
   <td>Adds <b>misa.c</b> and <b>mstatus_vs_sd.c</b> tests and adds support for interaction of <b>mstatus.VS</b> and <b>mstatus.SD</b> field
   </td>
   <td>Merged
   </td>
  </tr>
  <tr>
   <td><a href="https://github.com/10x-Engineers/ara/pull/6">6</a>
   </td>
   <td>Fixes the integer declaration in <b>vmerge.c</b> and <b>vmv.c</b> tests
   </td>
   <td>Merged
   </td>
  </tr>
  <tr>
   <td><a href="https://github.com/10x-Engineers/ara/pull/7">7</a>
   </td>
   <td>Renames <b>misa_v.c</b> and <b>mstatus_vs.c</b> tests and adds them to regression
   </td>
   <td>Merged
   </td>
  </tr>
</table>

<h3>NOTE:</h3>

The changes made in [PR#1](https://github.com/10x-Engineers/ara/pull/1) have been dropped for the August-15 release ( these changes were incorporated from [PR-117](https://github.com/pulp-platform/ara/pull/117) on [pulp-platform/ara/hotfix/masku](https://github.com/pulp-platform/ara/tree/hotfix/masku) and were causing some bugs. [PR-117](https://github.com/pulp-platform/ara/pull/117) has also been closed on [pulp-platform/ara/main](https://github.com/pulp-platform/ara) that’s why it’s been kept on hold for now).

<h2>2. Tests</h2>

The tests needed for all the RTL changes mentioned above are as follows:

<table>
  <tr>
   <td><strong>Sr#</strong>
   </td>
   <td><strong>Test</strong>
   </td>
   <td><strong>Changes Made</strong>
   </td>
   <td><strong>Status</strong>
   </td>
  </tr>
  <tr>
   <td>1
   </td>
   <td>mstatus_vs.c
   </td>
   <td>New Test Added
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td>2
   </td>
   <td>ld_st_exp.c
   </td>
   <td>New Test Added
   </td>
   <td>Dropped for August 15
   </td>
  </tr>
  <tr>
   <td>3
   </td>
   <td>whole_reg_ld_st.c
   </td>
   <td>Already Present in Ara
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td>4
   </td>
   <td>misa_v.c
   </td>
   <td>New Test Added
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td>5
   </td>
   <td>vcpop.m
   </td>
   <td>New Test Added by changing mnemonics of the “vpopc.m” test
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td>6
   </td>
   <td>vxsat.c
   </td>
   <td>New Test Added
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td>7
   </td>
   <td>vxrm.c
   </td>
   <td>New Test Added
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td>8
   </td>
   <td>vmorn.c
   </td>
   <td>New Test Added by changing mnemonics of the “vmornot.c” test
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td>9
   </td>
   <td>vmandn.c
   </td>
   <td>New Test Added by changing mnemonics of the “vmandnot.c” test
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td>10
   </td>
   <td>vaadd.c
   </td>
   <td>N/A
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td>11
   </td>
   <td>vaaddu.c
   </td>
   <td>N/A
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td>12
   </td>
   <td>vsadd.c
   </td>
   <td>N/A
   </td>
   <td>Dropped for August 15
   </td>
  </tr>
  <tr>
   <td>13
   </td>
   <td>vsaddu.c
   </td>
   <td>N/A
   </td>
   <td>Dropped for August 15
   </td>
  </tr>
  <tr>
   <td>14
   </td>
   <td>vasub.c
   </td>
   <td>Test Macros Changed
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td>15
   </td>
   <td>vasubu.c
   </td>
   <td>Test Macros Changed
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td>16
   </td>
   <td>vssub.c
   </td>
   <td>Expected values in the test changed
   </td>
   <td>Dropped for August 15
   </td>
  </tr>
  <tr>
   <td>17
   </td>
   <td>vssubu.c
   </td>
   <td>N/A
   </td>
   <td>Pass
   </td>
  </tr>
</table>

<h3>NOTE:</h3>

* `ld_st_exp.c` test has been dropped for the August-15 release as ARA hangs while running this test due to outdated mechanism of dependencies checks/scoreboard issues for vector instructions which need to be re-structured
* `vsadd.c` and `vsaddu.c` tests are failing on 2-lanes and need to be debugged (They were initally planned to be released with 15th August release, so they're dropped for now)
* `vssub.c` test is failing on both RTL and Spike and needs to be debugged (It was also planned to be released with 15th August release, so it is dropped for now)



<h2>3. CI Checks</h2>
<h3>CI-Check for PR-2, PR-3, PR-5, PR-6 and PR-7</h3>

The following table shows all the CI checks (for all the PR which are merged to the [base-line](https://github.com/10x-Engineers/ara/tree/rc1_1.0) branch of 10xEngineers/ara).

<table>
  <tr>
   <td colspan="2" >
<strong>CI Check</strong>
   </td>
   <td><strong>Status</strong>
   </td>
  </tr>
  <tr>
   <td colspan="2" >tc-llvm
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td colspan="2" >tc-isa-sim
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td colspan="2" >tc-verilator
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td colspan="2" >tc-gcc
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td colspan="2" >check-license
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td colspan="2" >check-trailing-whitespaces and tabs
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td rowspan="4" >Matrix: compile-apps
   </td>
   <td>compile-apps (16_lanes)
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td>compile-apps (8_lanes)
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td>compile-apps (4_lanes)
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td>compile-apps (2_lanes)
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td colspan="2" >check-clang-format
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td rowspan="4" >Matrix: compile-ara
   </td>
   <td>compile-ara (16_lanes)
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td>compile-ara (8_lanes)
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td>compile-ara (4_lanes)
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td>compile-ara (2_lanes)
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td rowspan="4" >Matrix: compile-riscv-tests
   </td>
   <td>compile-riscv-tests (16_lanes)
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td>compile-riscv-tests (8_lanes)
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td>compile-riscv-tests (4_lanes)
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td>compile-riscv-tests (2_lanes)
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td rowspan="24" >Matrix: simulate
   </td>
   <td>simulate (fconv2d, 16_lanes)
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td>simulate (fconv2d, 8_lanes)
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td>simulate (fconv2d, 4_lanes)
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td>simulate (fconv2d, 2_lanes)
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td>simulate (fconv3d, 16_lanes)
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td>simulate (fconv3d, 8_lanes)
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td>simulate (fconv3d, 4_lanes)
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td>simulate (fconv3d, 2_lanes)
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td>simulate (fmatmul, 16_lanes)
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td>simulate (fmatmul, 8_lanes)
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td>simulate (fmatmul, 4_lanes)
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td>simulate (fmatmul, 2_lanes)
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td>simulate (hello_world, 16_lanes)
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td>simulate (hello_world, 8_lanes)
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td>simulate (hello_world, 4_lanes)
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td>simulate (hello_world, 2_lanes)
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td>simulate (iconv2d, 16_lanes)
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td>simulate (iconv2d, 8_lanes)
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td>simulate (iconv2d, 4_lanes)
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td>simulate (iconv2d, 2_lanes)
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td>simulate (imatmul, 16_lanes)
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td>simulate (imatmul, 8_lanes)
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td>simulate (imatmul, 4_lanes)
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td>simulate (imatmul, 2_lanes)
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td rowspan="4" >Matrix: benchmark
   </td>
   <td>benchmark (16_lanes)
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td>benchmark (8_lanes)
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td>benchmark (4_lanes)
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td>benchmark (2_lanes)
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td rowspan="4" >Matrix: riscv-tests-simv
   </td>
   <td>riscv-tests-simv (16_lanes)
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td>riscv-tests-simv (8_lanes)
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td>riscv-tests-simv (4_lanes)
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td>riscv-tests-simv (2_lanes)
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td colspan="2" >riscv-tests-spike
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td colspan="2" >roofline
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td colspan="2" >clean-up
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td rowspan="4" >Matrix: clean-up-compile-runs
   </td>
   <td>clean-up-compile-runs (16_lanes)
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td>clean-up-compile-runs (8_lanes)
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td>clean-up-compile-runs (4_lanes)
   </td>
   <td>Pass
   </td>
  </tr>
  <tr>
   <td>clean-up-compile-runs (2_lanes)
   </td>
   <td>Pass
   </td>
  </tr>
</table>

All CI Checks were successfully passing before merging in the PR's.

<h2>4. Regression</h2>

The log of the regression run after making all the RTL changes is given as follows:


<table>
  <tr>
   <td>
<strong>Date</strong>
   </td>
   <td><strong>Count</strong>
   </td>
   <td><strong>Passed</strong>
   </td>
   <td><strong>Pass Ratio</strong>
   </td>
   <td><strong>Failed</strong>
   </td>
   <td><strong>Branch</strong>
   </td>
  </tr>
  <tr>
   <td>July-04
   </td>
   <td>136
   </td>
   <td>132
   </td>
   <td>97.06 %
   </td>
   <td>- vmv - vmerge - vmvnrr - vssub
   </td>
   <td><a href="https://github.com/10x-Engineers/ara/tree/rc1_1.0">rc1_1.0</a>
   </td>
  </tr>
  <tr>
   <td>July-15
   </td>
   <td>231
   </td>
   <td>231
   </td>
   <td>100 %
   </td>
   <td>N/A
   </td>
   <td><a href="https://github.com/10x-Engineers/ara/tree/rc1_1.0">rc1_1.0</a>
   </td>
  </tr>
</table>

<h3>NOTE:</h3>

Both vector and scalar tests are run by cherry-picking the aforementioned PRs in the [rc1_1.0](https://github.com/10x-Engineers/ara/tree/rc1_1.0) branch and making any additional changes where required.
