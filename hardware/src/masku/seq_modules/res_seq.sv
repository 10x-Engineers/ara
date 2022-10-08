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
    // Interface with the masku
    input  logic [3:0]                                 vsew,
    input  logic [NrLanes*DataWidth-1:0]               alu_result,
    output logic [NrLanes*DataWidth-1:0]               alu_result_seq
  );

  generate
    case (NrLanes)
      2 : always_comb begin case (vsew)
          EW8 : alu_result_seq = {alu_result[127:120], alu_result[63:56], alu_result[95:88], alu_result[31:24], alu_result[111:104], alu_result[47:40] ,alu_result[79:72], alu_result[15:8],
                                        alu_result[119:112], alu_result[55:48], alu_result[87:80], alu_result[23:16], alu_result[103: 96], alu_result[39:32], alu_result[71:64], alu_result[7 :0]};
          EW16: alu_result_seq = {alu_result[127:112], alu_result[63:48], alu_result[95:80], alu_result[31:16],
                                        alu_result[111: 96], alu_result[47:32], alu_result[79:64], alu_result[15: 0]};
          EW32: alu_result_seq = {alu_result[127: 96], alu_result[63:32],
                                        alu_result[95 : 64], alu_result[31: 0]};
          EW64: alu_result_seq = {alu_result[127: 64],
                                        alu_result[63 :  0]};
        endcase
      end
      4 : always_comb begin case (vsew)
          EW8 : alu_result_seq = {alu_result[255:248], alu_result[191:184], alu_result[127:120], alu_result[63:56], alu_result[223:216], alu_result[159:152], alu_result[95:88], alu_result[31:24],
                                        alu_result[247:240], alu_result[183:176], alu_result[119:112], alu_result[55:48], alu_result[215:208], alu_result[151:144] ,alu_result[87:80], alu_result[23:16],
                                        alu_result[239:232], alu_result[175:168], alu_result[111:104], alu_result[47:40], alu_result[207:200], alu_result[143:136], alu_result[79:72], alu_result[15: 8],
                                        alu_result[231:224], alu_result[167:160], alu_result[103: 96], alu_result[39:32], alu_result[199:192], alu_result[135:128], alu_result[71:64], alu_result[7 : 0]};
          EW16: alu_result_seq = {alu_result[255:240], alu_result[191:176], alu_result[127:112], alu_result[63:48],
                                        alu_result[223:208], alu_result[159:144], alu_result[95 : 80], alu_result[31:16],
                                        alu_result[239:224], alu_result[175:160], alu_result[111: 96], alu_result[47:32],
                                        alu_result[207:192], alu_result[143:128], alu_result[79 : 64], alu_result[15: 0]};
          EW32: alu_result_seq = {alu_result[255:224], alu_result[191:160],
                                        alu_result[127: 96], alu_result[63 : 32],
                                        alu_result[223:192], alu_result[159:128],
                                        alu_result[95 : 64], alu_result[31 :  0]};
          EW64: alu_result_seq = {alu_result[255:192],
                                        alu_result[191:128],
                                        alu_result[127: 64],
                                        alu_result[63 :  0]};
        endcase
      end
      8 : always_comb begin case (vsew)
          EW8 : alu_result_seq = {alu_result[511:504], alu_result[447:440], alu_result[383:376], alu_result[319:312], alu_result[255:248], alu_result[191:184], alu_result[127:120], alu_result[63:56],
                                        alu_result[503:496], alu_result[439:432], alu_result[375:368], alu_result[311:304], alu_result[247:240], alu_result[183:176], alu_result[119:112], alu_result[55:48],
                                        alu_result[495:488], alu_result[431:424], alu_result[367:360], alu_result[303:296], alu_result[239:232], alu_result[175:168], alu_result[111:104], alu_result[47:40],
                                        alu_result[487:480], alu_result[423:416], alu_result[359:352], alu_result[295:288], alu_result[231:224], alu_result[167:160], alu_result[103: 96], alu_result[39:32],
                                        alu_result[479:472], alu_result[415:408], alu_result[351:344], alu_result[287:280], alu_result[223:216], alu_result[159:152], alu_result[95 : 88], alu_result[31:24],
                                        alu_result[471:464], alu_result[407:400], alu_result[343:336], alu_result[279:272], alu_result[215:208], alu_result[151:144], alu_result[87 : 80], alu_result[23:16],
                                        alu_result[463:456], alu_result[399:392], alu_result[335:328], alu_result[271:264], alu_result[207:200], alu_result[143:136], alu_result[79 : 72], alu_result[15: 8],
                                        alu_result[455:448], alu_result[391:384], alu_result[327:320], alu_result[263:256], alu_result[199:192], alu_result[135:128], alu_result[71 : 64], alu_result[7 : 0]};
          EW16: alu_result_seq = {alu_result[511:496], alu_result[447:432], alu_result[383:368], alu_result[319:304],
                                        alu_result[255:240], alu_result[191:176], alu_result[127:112], alu_result[63 : 48],
                                        alu_result[479:464], alu_result[415:400], alu_result[351:336], alu_result[287:272],
                                        alu_result[223:208], alu_result[159:144], alu_result[95 : 80], alu_result[31 : 16],
                                        alu_result[495:480], alu_result[431:416], alu_result[367:352], alu_result[303:288],
                                        alu_result[239:224], alu_result[175:160], alu_result[111: 96], alu_result[47 : 32],
                                        alu_result[463:448], alu_result[399:384], alu_result[335:320], alu_result[271:256],
                                        alu_result[207:192], alu_result[143:128], alu_result[79 : 64], alu_result[15 :  0]};
          EW32: alu_result_seq = {alu_result[511:480], alu_result[447:416],
                                        alu_result[383:352], alu_result[319:288],
                                        alu_result[255:224], alu_result[191:160],
                                        alu_result[127: 96], alu_result[63 : 32],
                                        alu_result[479:448], alu_result[415:384],
                                        alu_result[351:320], alu_result[287:256],
                                        alu_result[223:192], alu_result[159:128],
                                        alu_result[95 : 64], alu_result[31 :  0]};
          EW64: alu_result_seq = {alu_result[511:448],
                                        alu_result[447:384],
                                        alu_result[383:320],
                                        alu_result[319:256],
                                        alu_result[255:192],
                                        alu_result[191:128],
                                        alu_result[127: 64],
                                        alu_result[63 :  0]};
        endcase
      end
      16 : always_comb begin case (vsew)
          EW8 : alu_result_seq = {alu_result[1023:1016], alu_result[959:952], alu_result[895:888], alu_result[831:824], alu_result[767:760], alu_result[703:696], alu_result[639:632], alu_result[575:568],
                                        alu_result[1015:1008], alu_result[951:944], alu_result[887:880], alu_result[823:816], alu_result[759:752], alu_result[695:688], alu_result[631:624], alu_result[567:560],
                                        alu_result[1007:1000], alu_result[943:936], alu_result[879:872], alu_result[815:808], alu_result[751:744], alu_result[687:680], alu_result[623:616], alu_result[559:552],
                                        alu_result[999 : 992], alu_result[935:928], alu_result[871:864], alu_result[807:800], alu_result[743:736], alu_result[679:672], alu_result[615:608], alu_result[551:544],
                                        alu_result[991 : 984], alu_result[927:920], alu_result[863:856], alu_result[799:792], alu_result[735:728], alu_result[671:664], alu_result[607:600], alu_result[543:536],
                                        alu_result[983 : 976], alu_result[919:912], alu_result[855:848], alu_result[791:784], alu_result[727:720], alu_result[663:656], alu_result[599:592], alu_result[535:528],
                                        alu_result[975 : 968], alu_result[911:904], alu_result[847:840], alu_result[783:776], alu_result[719:712], alu_result[655:648], alu_result[591:584], alu_result[527:520],
                                        alu_result[967 : 960], alu_result[903:896], alu_result[839:832], alu_result[775:768], alu_result[711:704], alu_result[647:640], alu_result[583:576], alu_result[519:512],
                                        alu_result[511 : 504], alu_result[447:440], alu_result[383:376], alu_result[319:312], alu_result[255:248], alu_result[191:184], alu_result[127:120], alu_result[63 : 56],
                                        alu_result[503 : 496], alu_result[439:432], alu_result[375:368], alu_result[311:304], alu_result[247:240], alu_result[183:176], alu_result[119:112], alu_result[55 : 48],
                                        alu_result[495 : 488], alu_result[431:424], alu_result[367:360], alu_result[303:296], alu_result[239:232], alu_result[175:168], alu_result[111:104], alu_result[47 : 40],
                                        alu_result[487 : 480], alu_result[423:416], alu_result[359:352], alu_result[295:288], alu_result[231:224], alu_result[167:160], alu_result[103: 96], alu_result[39 : 32],
                                        alu_result[479 : 472], alu_result[415:408], alu_result[351:344], alu_result[287:280], alu_result[223:216], alu_result[159:152], alu_result[95 : 88], alu_result[31 : 24],
                                        alu_result[471 : 464], alu_result[407:400], alu_result[343:336], alu_result[279:272], alu_result[215:208], alu_result[151:144], alu_result[87 : 80], alu_result[23 : 16],
                                        alu_result[463 : 456], alu_result[399:392], alu_result[335:328], alu_result[271:264], alu_result[207:200], alu_result[143:136], alu_result[79 : 72], alu_result[15 :  8],
                                        alu_result[455 : 448], alu_result[391:384], alu_result[327:320], alu_result[263:256], alu_result[199:192], alu_result[135:128], alu_result[71 : 64], alu_result[7  :  0]};
          EW16: alu_result_seq = {alu_result[1023:1008], alu_result[959:944], alu_result[895:880], alu_result[831:816],
                                        alu_result[767 : 752], alu_result[703:688], alu_result[639:624], alu_result[575:560],
                                        alu_result[511 : 496], alu_result[447:432], alu_result[383:368], alu_result[319:304],
                                        alu_result[255 : 240], alu_result[191:176], alu_result[127:112], alu_result[63 : 48],
                                        alu_result[991 : 976], alu_result[927:912], alu_result[863:848], alu_result[799:784],
                                        alu_result[735 : 720], alu_result[671:656], alu_result[607:592], alu_result[543:528],
                                        alu_result[479 : 464], alu_result[415:400], alu_result[351:336], alu_result[287:272],
                                        alu_result[223 : 208], alu_result[159:144], alu_result[95 : 80], alu_result[31 : 16],
                                        alu_result[1007: 992], alu_result[943:928], alu_result[879:864], alu_result[815:800],
                                        alu_result[751 : 736], alu_result[687:672], alu_result[623:608], alu_result[559:544],
                                        alu_result[495 : 480], alu_result[431:416], alu_result[367:352], alu_result[303:288],
                                        alu_result[239 : 224], alu_result[175:160], alu_result[111: 96], alu_result[47 : 32],
                                        alu_result[975 : 960], alu_result[911:896], alu_result[847:832], alu_result[783:768],
                                        alu_result[719 : 704], alu_result[655:640], alu_result[591:576], alu_result[527:512],
                                        alu_result[463 : 448], alu_result[399:384], alu_result[335:320], alu_result[271:256],
                                        alu_result[207 : 192], alu_result[143:128], alu_result[79 : 64], alu_result[15 :  0]};
          EW32: alu_result_seq = {alu_result[1023: 992], alu_result[959:928],
                                        alu_result[895 : 864], alu_result[831:800],
                                        alu_result[767 : 736], alu_result[703:672],
                                        alu_result[639 : 608], alu_result[575:544],
                                        alu_result[511 : 480], alu_result[447:416],
                                        alu_result[383 : 352], alu_result[319:288],
                                        alu_result[255 : 224], alu_result[191:160],
                                        alu_result[127 :  96], alu_result[63 : 32],
                                        alu_result[991 : 960], alu_result[927:896],
                                        alu_result[863 : 832], alu_result[799:768],
                                        alu_result[735 : 704], alu_result[671:640],
                                        alu_result[607 : 576], alu_result[543:512],
                                        alu_result[479 : 448], alu_result[415:384],
                                        alu_result[351 : 320], alu_result[287:256],
                                        alu_result[223 : 192], alu_result[159:128],
                                        alu_result[95  :  64], alu_result[31 :  0]};
          EW64: alu_result_seq = {alu_result[1023: 960],
                                        alu_result[959 : 896],
                                        alu_result[895 : 832],
                                        alu_result[831 : 768],
                                        alu_result[767 : 704],
                                        alu_result[703 : 640],
                                        alu_result[639 : 576],
                                        alu_result[575 : 512],
                                        alu_result[511 : 448],
                                        alu_result[447 : 384],
                                        alu_result[383 : 320],
                                        alu_result[319 : 256],
                                        alu_result[255 : 192],
                                        alu_result[191 : 128],
                                        alu_result[127 :  64],
                                        alu_result[63  :   0]};
        endcase
      end
    endcase
  endgenerate

endmodule : res_seq
