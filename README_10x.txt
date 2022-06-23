Download toolchain from https://github.com/riscv-collab/riscv-gnu-toolchain/releases/download/2022.06.10/riscv64-elf-ubuntu-20.04-nightly-2022.06.10-nightly.tar.gz 
Go to ara top directory and follow the steps below:
- update the submodules recursively
- mkdir install && cd install
- extract the downloaded toolchain here and rename the folder to riscv-gcc
- cd riscv-gcc (you should see bin/ include/ and other folders)
- go back to ara top directory
- cd apps && make riscv_tests
- cd ../hardware && make apply-patches && make verilate (if you get an error here, go to hardware/cva6 and update the submodules recursively again)
- make simv app=rv64uv-ara-vadd
