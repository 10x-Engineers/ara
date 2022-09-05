// Copyright 2021 ETH Zurich and University of Bologna.
// Solderpad Hardware License, Version 0.51, see LICENSE for details.
// SPDX-License-Identifier: SHL-0.51
//
// Author: Muhammad Ijaz
// Description:
// This is Ara's operand sequencer module, which is responsible for sequencing the operand recieved from lane_sequencer


module res_seq import ara_pkg::*; import rvv_pkg::*; #(
    parameter  int  unsigned NrLanes = 0,
    // Dependant parameters. DO NOT CHANGE!
    localparam int  unsigned DataWidth = $bits(elen_t) // Width of the lane datapath
  ) (
    input  logic                                       clk_i,
    input  logic                                       rst_ni,
    // Interface with the masku
    input  pe_req_t                                    vinsn_issue_i,
    input  logic [NrLanes*DataWidth-1:0]               alu_result_viota_masked,
    output logic [NrLanes*DataWidth-1:0]               alu_result_viota_seq
  );

  generate
    case (NrLanes)
      2 : always_comb begin case (vinsn_issue_i.vtype.vsew)
          EW8 : alu_result_viota_seq = {alu_result_viota_masked[127:120], alu_result_viota_masked[63:56], alu_result_viota_masked[95:88], alu_result_viota_masked[31:24], alu_result_viota_masked[111:104], alu_result_viota_masked[47:40] ,alu_result_viota_masked[79:72], alu_result_viota_masked[15:8],
                                        alu_result_viota_masked[119:112], alu_result_viota_masked[55:48], alu_result_viota_masked[87:80], alu_result_viota_masked[23:16], alu_result_viota_masked[103: 96], alu_result_viota_masked[39:32], alu_result_viota_masked[71:64], alu_result_viota_masked[7 :0]};
          EW16: alu_result_viota_seq = {alu_result_viota_masked[127:112], alu_result_viota_masked[63:48], alu_result_viota_masked[95:80], alu_result_viota_masked[31:16],
                                        alu_result_viota_masked[111: 96], alu_result_viota_masked[47:32], alu_result_viota_masked[79:64], alu_result_viota_masked[15: 0]};
          EW32: alu_result_viota_seq = {alu_result_viota_masked[127: 96], alu_result_viota_masked[63:32],
                                        alu_result_viota_masked[95 : 64], alu_result_viota_masked[31: 0]};
          EW64: alu_result_viota_seq = {alu_result_viota_masked[127: 64],
                                        alu_result_viota_masked[63 :  0]};
        endcase
      end
      4 : always_comb begin case (vinsn_issue_i.vtype.vsew)
          EW8 : alu_result_viota_seq = {alu_result_viota_masked[255:248], alu_result_viota_masked[191:184], alu_result_viota_masked[127:120], alu_result_viota_masked[63:56], alu_result_viota_masked[223:216], alu_result_viota_masked[159:152], alu_result_viota_masked[95:88], alu_result_viota_masked[31:24],
                                        alu_result_viota_masked[247:240], alu_result_viota_masked[183:176], alu_result_viota_masked[119:112], alu_result_viota_masked[55:48], alu_result_viota_masked[215:208], alu_result_viota_masked[151:144] ,alu_result_viota_masked[87:80], alu_result_viota_masked[23:16],
                                        alu_result_viota_masked[239:232], alu_result_viota_masked[175:168], alu_result_viota_masked[111:104], alu_result_viota_masked[47:40], alu_result_viota_masked[207:200], alu_result_viota_masked[143:136], alu_result_viota_masked[79:72], alu_result_viota_masked[15: 8],
                                        alu_result_viota_masked[231:224], alu_result_viota_masked[167:160], alu_result_viota_masked[103: 96], alu_result_viota_masked[39:32], alu_result_viota_masked[199:192], alu_result_viota_masked[135:128], alu_result_viota_masked[71:64], alu_result_viota_masked[7 : 0]};
          EW16: alu_result_viota_seq = {alu_result_viota_masked[255:240], alu_result_viota_masked[191:176], alu_result_viota_masked[127:112], alu_result_viota_masked[63:48],
                                        alu_result_viota_masked[223:208], alu_result_viota_masked[159:144], alu_result_viota_masked[95 : 80], alu_result_viota_masked[31:16],
                                        alu_result_viota_masked[239:224], alu_result_viota_masked[175:160], alu_result_viota_masked[111: 96], alu_result_viota_masked[47:32],
                                        alu_result_viota_masked[207:192], alu_result_viota_masked[143:128], alu_result_viota_masked[79 : 64], alu_result_viota_masked[15: 0]};
          EW32: alu_result_viota_seq = {alu_result_viota_masked[255:224], alu_result_viota_masked[191:160],
                                        alu_result_viota_masked[127: 96], alu_result_viota_masked[63 : 32],
                                        alu_result_viota_masked[223:192], alu_result_viota_masked[159:128],
                                        alu_result_viota_masked[95 : 64], alu_result_viota_masked[31 :  0]};
          EW64: alu_result_viota_seq = {alu_result_viota_masked[255:192],
                                        alu_result_viota_masked[191:128],
                                        alu_result_viota_masked[127: 64],
                                        alu_result_viota_masked[63 :  0]};
        endcase
      end
      8 : always_comb begin case (vinsn_issue_i.vtype.vsew)
          EW8 : alu_result_viota_seq = {alu_result_viota_masked[511:504], alu_result_viota_masked[447:440], alu_result_viota_masked[383:376], alu_result_viota_masked[319:312], alu_result_viota_masked[255:248], alu_result_viota_masked[191:184], alu_result_viota_masked[127:120], alu_result_viota_masked[63:56],
                                        alu_result_viota_masked[503:496], alu_result_viota_masked[439:432], alu_result_viota_masked[375:368], alu_result_viota_masked[311:304], alu_result_viota_masked[247:240], alu_result_viota_masked[183:176], alu_result_viota_masked[119:112], alu_result_viota_masked[55:48],
                                        alu_result_viota_masked[495:488], alu_result_viota_masked[431:424], alu_result_viota_masked[367:360], alu_result_viota_masked[303:296], alu_result_viota_masked[239:232], alu_result_viota_masked[175:168], alu_result_viota_masked[111:104], alu_result_viota_masked[47:40],
                                        alu_result_viota_masked[487:480], alu_result_viota_masked[423:416], alu_result_viota_masked[359:352], alu_result_viota_masked[295:288], alu_result_viota_masked[231:224], alu_result_viota_masked[167:160], alu_result_viota_masked[103: 96], alu_result_viota_masked[39:32],
                                        alu_result_viota_masked[479:472], alu_result_viota_masked[415:408], alu_result_viota_masked[351:344], alu_result_viota_masked[287:280], alu_result_viota_masked[223:216], alu_result_viota_masked[159:152], alu_result_viota_masked[95 : 88], alu_result_viota_masked[31:24],
                                        alu_result_viota_masked[471:464], alu_result_viota_masked[407:400], alu_result_viota_masked[343:336], alu_result_viota_masked[279:272], alu_result_viota_masked[215:208], alu_result_viota_masked[151:144], alu_result_viota_masked[87 : 80], alu_result_viota_masked[23:16],
                                        alu_result_viota_masked[463:456], alu_result_viota_masked[399:392], alu_result_viota_masked[335:328], alu_result_viota_masked[271:264], alu_result_viota_masked[207:200], alu_result_viota_masked[143:136], alu_result_viota_masked[79 : 72], alu_result_viota_masked[15: 8],
                                        alu_result_viota_masked[455:448], alu_result_viota_masked[391:384], alu_result_viota_masked[327:320], alu_result_viota_masked[263:256], alu_result_viota_masked[199:192], alu_result_viota_masked[135:128], alu_result_viota_masked[71 : 64], alu_result_viota_masked[7 : 0]};
          EW16: alu_result_viota_seq = {alu_result_viota_masked[511:496], alu_result_viota_masked[447:432], alu_result_viota_masked[383:368], alu_result_viota_masked[319:304],
                                        alu_result_viota_masked[255:240], alu_result_viota_masked[191:176], alu_result_viota_masked[127:112], alu_result_viota_masked[63 : 48],
                                        alu_result_viota_masked[479:464], alu_result_viota_masked[415:400], alu_result_viota_masked[351:336], alu_result_viota_masked[287:272],
                                        alu_result_viota_masked[223:208], alu_result_viota_masked[159:144], alu_result_viota_masked[95 : 80], alu_result_viota_masked[31 : 16],
                                        alu_result_viota_masked[495:480], alu_result_viota_masked[431:416], alu_result_viota_masked[367:352], alu_result_viota_masked[303:288],
                                        alu_result_viota_masked[239:224], alu_result_viota_masked[175:160], alu_result_viota_masked[111: 96], alu_result_viota_masked[47 : 32],
                                        alu_result_viota_masked[463:448], alu_result_viota_masked[399:384], alu_result_viota_masked[335:320], alu_result_viota_masked[271:256],
                                        alu_result_viota_masked[207:192], alu_result_viota_masked[143:128], alu_result_viota_masked[79 : 64], alu_result_viota_masked[15 :  0]};
          EW32: alu_result_viota_seq = {alu_result_viota_masked[511:480], alu_result_viota_masked[447:416],
                                        alu_result_viota_masked[383:352], alu_result_viota_masked[319:288],
                                        alu_result_viota_masked[255:224], alu_result_viota_masked[191:160],
                                        alu_result_viota_masked[127: 96], alu_result_viota_masked[63 : 32],
                                        alu_result_viota_masked[479:448], alu_result_viota_masked[415:384],
                                        alu_result_viota_masked[351:320], alu_result_viota_masked[287:256],
                                        alu_result_viota_masked[223:192], alu_result_viota_masked[159:128],
                                        alu_result_viota_masked[95 : 64], alu_result_viota_masked[31 :  0]};
          EW64: alu_result_viota_seq = {alu_result_viota_masked[511:448],
                                        alu_result_viota_masked[447:384],
                                        alu_result_viota_masked[383:320],
                                        alu_result_viota_masked[319:256],
                                        alu_result_viota_masked[255:192],
                                        alu_result_viota_masked[191:128],
                                        alu_result_viota_masked[127: 64],
                                        alu_result_viota_masked[63 :  0]};
        endcase
      end
      16 : always_comb begin case (vinsn_issue_i.vtype.vsew)
          EW8 : alu_result_viota_seq = {alu_result_viota_masked[1023:1016], alu_result_viota_masked[959:952], alu_result_viota_masked[895:888], alu_result_viota_masked[831:824], alu_result_viota_masked[767:760], alu_result_viota_masked[703:696], alu_result_viota_masked[639:632], alu_result_viota_masked[575:568],
                                        alu_result_viota_masked[1015:1008], alu_result_viota_masked[951:944], alu_result_viota_masked[887:880], alu_result_viota_masked[823:816], alu_result_viota_masked[759:752], alu_result_viota_masked[695:688], alu_result_viota_masked[631:624], alu_result_viota_masked[567:560],
                                        alu_result_viota_masked[1007:1000], alu_result_viota_masked[943:936], alu_result_viota_masked[879:872], alu_result_viota_masked[815:808], alu_result_viota_masked[751:744], alu_result_viota_masked[687:680], alu_result_viota_masked[623:616], alu_result_viota_masked[559:552],
                                        alu_result_viota_masked[999 : 992], alu_result_viota_masked[935:928], alu_result_viota_masked[871:864], alu_result_viota_masked[807:800], alu_result_viota_masked[743:736], alu_result_viota_masked[679:672], alu_result_viota_masked[615:608], alu_result_viota_masked[551:544],
                                        alu_result_viota_masked[991 : 984], alu_result_viota_masked[927:920], alu_result_viota_masked[863:856], alu_result_viota_masked[799:792], alu_result_viota_masked[735:728], alu_result_viota_masked[671:664], alu_result_viota_masked[607:600], alu_result_viota_masked[543:536],
                                        alu_result_viota_masked[983 : 976], alu_result_viota_masked[919:912], alu_result_viota_masked[855:848], alu_result_viota_masked[791:784], alu_result_viota_masked[727:720], alu_result_viota_masked[663:656], alu_result_viota_masked[599:592], alu_result_viota_masked[535:528],
                                        alu_result_viota_masked[975 : 968], alu_result_viota_masked[911:904], alu_result_viota_masked[847:840], alu_result_viota_masked[783:776], alu_result_viota_masked[719:712], alu_result_viota_masked[655:648], alu_result_viota_masked[591:584], alu_result_viota_masked[527:520],
                                        alu_result_viota_masked[967 : 960], alu_result_viota_masked[903:896], alu_result_viota_masked[839:832], alu_result_viota_masked[775:768], alu_result_viota_masked[711:704], alu_result_viota_masked[647:640], alu_result_viota_masked[583:576], alu_result_viota_masked[519:512],
                                        alu_result_viota_masked[511 : 504], alu_result_viota_masked[447:440], alu_result_viota_masked[383:376], alu_result_viota_masked[319:312], alu_result_viota_masked[255:248], alu_result_viota_masked[191:184], alu_result_viota_masked[127:120], alu_result_viota_masked[63 : 56],
                                        alu_result_viota_masked[503 : 496], alu_result_viota_masked[439:432], alu_result_viota_masked[375:368], alu_result_viota_masked[311:304], alu_result_viota_masked[247:240], alu_result_viota_masked[183:176], alu_result_viota_masked[119:112], alu_result_viota_masked[55 : 48],
                                        alu_result_viota_masked[495 : 488], alu_result_viota_masked[431:424], alu_result_viota_masked[367:360], alu_result_viota_masked[303:296], alu_result_viota_masked[239:232], alu_result_viota_masked[175:168], alu_result_viota_masked[111:104], alu_result_viota_masked[47 : 40],
                                        alu_result_viota_masked[487 : 480], alu_result_viota_masked[423:416], alu_result_viota_masked[359:352], alu_result_viota_masked[295:288], alu_result_viota_masked[231:224], alu_result_viota_masked[167:160], alu_result_viota_masked[103: 96], alu_result_viota_masked[39 : 32],
                                        alu_result_viota_masked[479 : 472], alu_result_viota_masked[415:408], alu_result_viota_masked[351:344], alu_result_viota_masked[287:280], alu_result_viota_masked[223:216], alu_result_viota_masked[159:152], alu_result_viota_masked[95 : 88], alu_result_viota_masked[31 : 24],
                                        alu_result_viota_masked[471 : 464], alu_result_viota_masked[407:400], alu_result_viota_masked[343:336], alu_result_viota_masked[279:272], alu_result_viota_masked[215:208], alu_result_viota_masked[151:144], alu_result_viota_masked[87 : 80], alu_result_viota_masked[23 : 16],
                                        alu_result_viota_masked[463 : 456], alu_result_viota_masked[399:392], alu_result_viota_masked[335:328], alu_result_viota_masked[271:264], alu_result_viota_masked[207:200], alu_result_viota_masked[143:136], alu_result_viota_masked[79 : 72], alu_result_viota_masked[15 :  8],
                                        alu_result_viota_masked[455 : 448], alu_result_viota_masked[391:384], alu_result_viota_masked[327:320], alu_result_viota_masked[263:256], alu_result_viota_masked[199:192], alu_result_viota_masked[135:128], alu_result_viota_masked[71 : 64], alu_result_viota_masked[7  :  0]};
          EW16: alu_result_viota_seq = {alu_result_viota_masked[1023:1008], alu_result_viota_masked[959:944], alu_result_viota_masked[895:880], alu_result_viota_masked[831:816],
                                        alu_result_viota_masked[767 : 752], alu_result_viota_masked[703:688], alu_result_viota_masked[639:624], alu_result_viota_masked[575:560],
                                        alu_result_viota_masked[511 : 496], alu_result_viota_masked[447:432], alu_result_viota_masked[383:368], alu_result_viota_masked[319:304],
                                        alu_result_viota_masked[255 : 240], alu_result_viota_masked[191:176], alu_result_viota_masked[127:112], alu_result_viota_masked[63 : 48],
                                        alu_result_viota_masked[991 : 976], alu_result_viota_masked[927:912], alu_result_viota_masked[863:848], alu_result_viota_masked[799:784],
                                        alu_result_viota_masked[735 : 720], alu_result_viota_masked[671:656], alu_result_viota_masked[607:592], alu_result_viota_masked[543:528],
                                        alu_result_viota_masked[479 : 464], alu_result_viota_masked[415:400], alu_result_viota_masked[351:336], alu_result_viota_masked[287:272],
                                        alu_result_viota_masked[223 : 208], alu_result_viota_masked[159:144], alu_result_viota_masked[95 : 80], alu_result_viota_masked[31 : 16],
                                        alu_result_viota_masked[1007: 992], alu_result_viota_masked[943:928], alu_result_viota_masked[879:864], alu_result_viota_masked[815:800],
                                        alu_result_viota_masked[751 : 736], alu_result_viota_masked[687:672], alu_result_viota_masked[623:608], alu_result_viota_masked[559:544],
                                        alu_result_viota_masked[495 : 480], alu_result_viota_masked[431:416], alu_result_viota_masked[367:352], alu_result_viota_masked[303:288],
                                        alu_result_viota_masked[239 : 224], alu_result_viota_masked[175:160], alu_result_viota_masked[111: 96], alu_result_viota_masked[47 : 32],
                                        alu_result_viota_masked[975 : 960], alu_result_viota_masked[911:896], alu_result_viota_masked[847:832], alu_result_viota_masked[783:768],
                                        alu_result_viota_masked[719 : 704], alu_result_viota_masked[655:640], alu_result_viota_masked[591:576], alu_result_viota_masked[527:512],
                                        alu_result_viota_masked[463 : 448], alu_result_viota_masked[399:384], alu_result_viota_masked[335:320], alu_result_viota_masked[271:256],
                                        alu_result_viota_masked[207 : 192], alu_result_viota_masked[143:128], alu_result_viota_masked[79 : 64], alu_result_viota_masked[15 :  0]};
          EW32: alu_result_viota_seq = {alu_result_viota_masked[1023: 992], alu_result_viota_masked[959:928],
                                        alu_result_viota_masked[895 : 864], alu_result_viota_masked[831:800],
                                        alu_result_viota_masked[767 : 736], alu_result_viota_masked[703:672],
                                        alu_result_viota_masked[639 : 608], alu_result_viota_masked[575:544],
                                        alu_result_viota_masked[511 : 480], alu_result_viota_masked[447:416],
                                        alu_result_viota_masked[383 : 352], alu_result_viota_masked[319:288],
                                        alu_result_viota_masked[255 : 224], alu_result_viota_masked[191:160],
                                        alu_result_viota_masked[127 :  96], alu_result_viota_masked[63 : 32],
                                        alu_result_viota_masked[991 : 960], alu_result_viota_masked[927:896],
                                        alu_result_viota_masked[863 : 832], alu_result_viota_masked[799:768],
                                        alu_result_viota_masked[735 : 704], alu_result_viota_masked[671:640],
                                        alu_result_viota_masked[607 : 576], alu_result_viota_masked[543:512],
                                        alu_result_viota_masked[479 : 448], alu_result_viota_masked[415:384],
                                        alu_result_viota_masked[351 : 320], alu_result_viota_masked[287:256],
                                        alu_result_viota_masked[223 : 192], alu_result_viota_masked[159:128],
                                        alu_result_viota_masked[95  :  64], alu_result_viota_masked[31 :  0]};
          EW64: alu_result_viota_seq = {alu_result_viota_masked[1023: 960],
                                        alu_result_viota_masked[959 : 896],
                                        alu_result_viota_masked[895 : 832],
                                        alu_result_viota_masked[831 : 768],
                                        alu_result_viota_masked[767 : 704],
                                        alu_result_viota_masked[703 : 640],
                                        alu_result_viota_masked[639 : 576],
                                        alu_result_viota_masked[575 : 512],
                                        alu_result_viota_masked[511 : 448],
                                        alu_result_viota_masked[447 : 384],
                                        alu_result_viota_masked[383 : 320],
                                        alu_result_viota_masked[319 : 256],
                                        alu_result_viota_masked[255 : 192],
                                        alu_result_viota_masked[191 : 128],
                                        alu_result_viota_masked[127 :  64],
                                        alu_result_viota_masked[63  :   0]};
        endcase
      end
    endcase
  endgenerate

endmodule : res_seq