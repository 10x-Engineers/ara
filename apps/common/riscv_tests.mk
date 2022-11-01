#=======================================================================
# Makefrag for instructions employed in CVA6
#-----------------------------------------------------------------------

include $(TESTS_DIR)/rv64uv/Makefrag

rv64uv_ara_tests := $(addprefix rv64uv-ara-, $(rv64uv_sc_tests))

cva6_tests := 

# Atomics are messy, since there is currently no memory region capable of handling them
#							$(rv64ua_ara_tests) \

ara_tests := $(rv64uv_ara_tests)
