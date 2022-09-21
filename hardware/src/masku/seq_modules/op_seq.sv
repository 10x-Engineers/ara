// Copyright 2021 ETH Zurich and University of Bologna.
// Solderpad Hardware License, Version 0.51, see LICENSE for details.
// SPDX-License-Identifier: SHL-0.51
//
// Author: Muhammad Ijaz
// Description:
// This is Ara's operand sequencer module, which is responsible for sequencing the operand recieved from lane_sequencer


module op_seq import ara_pkg::*; import rvv_pkg::*; #(
    parameter  int  unsigned NrLanes = 0,
    // Dependant parameters. DO NOT CHANGE!
    localparam int  unsigned DataWidth = $bits(elen_t) // Width of the lane datapath
  ) (
    // Interface with the masku
    input  logic [3:0]                                 vsew,
    input  logic [NrLanes*DataWidth-1:0]               alu_operand,
    output logic [NrLanes*DataWidth-1:0]               alu_operand_seq
  );

  generate
    case (NrLanes)
      2 : always_comb begin case (vsew)
          EW8 : alu_operand_seq = {alu_operand[127:120], alu_operand[63:56], alu_operand[111:104], alu_operand[47:40], alu_operand[95 :88], alu_operand[31:24] ,alu_operand[79:72], alu_operand[15:8],
                                   alu_operand[119:112], alu_operand[55:48], alu_operand[87 : 80], alu_operand[23:16], alu_operand[103:96], alu_operand[39:32], alu_operand[71:64], alu_operand[7 :0]};
          EW16: alu_operand_seq = {alu_operand[127:112], alu_operand[63:48], alu_operand[95 : 80], alu_operand[31:16],
                                   alu_operand[111: 96], alu_operand[47:32], alu_operand[79 : 64], alu_operand[15: 0]};
          EW32: alu_operand_seq = {alu_operand[127: 96], alu_operand[63:32],
                                   alu_operand[95 : 64], alu_operand[31: 0]};
          EW64: alu_operand_seq = {alu_operand[127: 64],
                                   alu_operand[63 :  0]};
        endcase
      end
      4 : always_comb begin case (vsew)
          EW8 : alu_operand_seq = {alu_operand[255:248], alu_operand[191:184], alu_operand[127:120], alu_operand[63:56], alu_operand[223:216], alu_operand[159:152], alu_operand[95:88], alu_operand[31:24],
                                   alu_operand[239:232], alu_operand[175:168], alu_operand[111:104], alu_operand[47:40], alu_operand[207:200], alu_operand[143:136], alu_operand[79:72], alu_operand[15: 8],
                                   alu_operand[247:240], alu_operand[183:176], alu_operand[119:112], alu_operand[55:48], alu_operand[215:208], alu_operand[151:144] ,alu_operand[87:80], alu_operand[23:16],
                                   alu_operand[231:224], alu_operand[167:160], alu_operand[103: 96], alu_operand[39:32], alu_operand[199:192], alu_operand[135:128], alu_operand[71:64], alu_operand[7 : 0]};
          EW16: alu_operand_seq = {alu_operand[255:240], alu_operand[191:176], alu_operand[127:112], alu_operand[63:48],
                                   alu_operand[223:208], alu_operand[159:144], alu_operand[95 : 80], alu_operand[31:16],
                                   alu_operand[239:224], alu_operand[175:160], alu_operand[111: 96], alu_operand[47:32],
                                   alu_operand[207:192], alu_operand[143:128], alu_operand[79 : 64], alu_operand[15: 0]};
          EW32: alu_operand_seq = {alu_operand[255:224], alu_operand[191:160],
                                   alu_operand[127: 96], alu_operand[63 : 32],
                                   alu_operand[223:192], alu_operand[159:128],
                                   alu_operand[95 : 64], alu_operand[31 :  0]};
          EW64: alu_operand_seq = {alu_operand[255:192],
                                   alu_operand[191:128],
                                   alu_operand[127: 64],
                                   alu_operand[63 :  0]};
        endcase
      end
      8 : always_comb begin case (vsew)
          EW8 : alu_operand_seq = {alu_operand[511:504], alu_operand[447:440], alu_operand[383:376], alu_operand[319:312], alu_operand[255:248], alu_operand[191:184], alu_operand[127:120], alu_operand[63:56],
                                   alu_operand[479:472], alu_operand[415:408], alu_operand[351:344], alu_operand[287:280], alu_operand[223:216], alu_operand[159:152], alu_operand[95 : 88], alu_operand[31:24],
                                   alu_operand[495:488], alu_operand[431:424], alu_operand[367:360], alu_operand[303:296], alu_operand[239:232], alu_operand[175:168], alu_operand[111:104], alu_operand[47:40],
                                   alu_operand[463:456], alu_operand[399:392], alu_operand[335:328], alu_operand[271:264], alu_operand[207:200], alu_operand[143:136], alu_operand[79 : 72], alu_operand[15: 8],
                                   alu_operand[503:496], alu_operand[439:432], alu_operand[375:368], alu_operand[311:304], alu_operand[247:240], alu_operand[183:176], alu_operand[119:112], alu_operand[55:48],
                                   alu_operand[471:464], alu_operand[407:400], alu_operand[343:336], alu_operand[279:272], alu_operand[215:208], alu_operand[151:144], alu_operand[87 : 80], alu_operand[23:16],
                                   alu_operand[487:480], alu_operand[423:416], alu_operand[359:352], alu_operand[295:288], alu_operand[231:224], alu_operand[167:160], alu_operand[103: 96], alu_operand[39:32],
                                   alu_operand[455:448], alu_operand[391:384], alu_operand[327:320], alu_operand[263:256], alu_operand[199:192], alu_operand[135:128], alu_operand[71 : 64], alu_operand[7 : 0]};
          EW16: alu_operand_seq = {alu_operand[511:496], alu_operand[447:432], alu_operand[383:368], alu_operand[319:304],
                                   alu_operand[255:240], alu_operand[191:176], alu_operand[127:112], alu_operand[63 : 48],
                                   alu_operand[479:464], alu_operand[415:400], alu_operand[351:336], alu_operand[287:272],
                                   alu_operand[223:208], alu_operand[159:144], alu_operand[95 : 80], alu_operand[31 : 16],
                                   alu_operand[495:480], alu_operand[431:416], alu_operand[367:352], alu_operand[303:288],
                                   alu_operand[239:224], alu_operand[175:160], alu_operand[111: 96], alu_operand[47 : 32],
                                   alu_operand[463:448], alu_operand[399:384], alu_operand[335:320], alu_operand[271:256],
                                   alu_operand[207:192], alu_operand[143:128], alu_operand[79 : 64], alu_operand[15 :  0]};
          EW32: alu_operand_seq = {alu_operand[511:480], alu_operand[447:416],
                                   alu_operand[383:352], alu_operand[319:288],
                                   alu_operand[255:224], alu_operand[191:160],
                                   alu_operand[127: 96], alu_operand[63 : 32],
                                   alu_operand[479:448], alu_operand[415:384],
                                   alu_operand[351:320], alu_operand[287:256],
                                   alu_operand[223:192], alu_operand[159:128],
                                   alu_operand[95 : 64], alu_operand[31 :  0]};
          EW64: alu_operand_seq = {alu_operand[511:448],
                                   alu_operand[447:384],
                                   alu_operand[383:320],
                                   alu_operand[319:256],
                                   alu_operand[255:192],
                                   alu_operand[191:128],
                                   alu_operand[127: 64],
                                   alu_operand[63 :  0]};
        endcase
      end
      16 : always_comb begin case (vsew)
          EW8 : alu_operand_seq = {alu_operand[1023:1016], alu_operand[959:952], alu_operand[895:888], alu_operand[831:824], alu_operand[767:760], alu_operand[703:696], alu_operand[639:632], alu_operand[575:568],
                                   alu_operand[511 : 504], alu_operand[447:440], alu_operand[383:376], alu_operand[319:312], alu_operand[255:248], alu_operand[191:184], alu_operand[127:120], alu_operand[63 : 56],
                                   alu_operand[991 : 984], alu_operand[927:920], alu_operand[863:856], alu_operand[799:792], alu_operand[735:728], alu_operand[671:664], alu_operand[607:600], alu_operand[543:536],
                                   alu_operand[479 : 472], alu_operand[415:408], alu_operand[351:344], alu_operand[287:280], alu_operand[223:216], alu_operand[159:152], alu_operand[95 : 88], alu_operand[31 : 24],
                                   alu_operand[1007:1000], alu_operand[943:936], alu_operand[879:872], alu_operand[815:808], alu_operand[751:744], alu_operand[687:680], alu_operand[623:616], alu_operand[559:552],
                                   alu_operand[495 : 488], alu_operand[431:424], alu_operand[367:360], alu_operand[303:296], alu_operand[239:232], alu_operand[175:168], alu_operand[111:104], alu_operand[47 : 40],
                                   alu_operand[975 : 968], alu_operand[911:904], alu_operand[847:840], alu_operand[783:776], alu_operand[719:712], alu_operand[655:648], alu_operand[591:584], alu_operand[527:520],
                                   alu_operand[463 : 456], alu_operand[399:392], alu_operand[335:328], alu_operand[271:264], alu_operand[207:200], alu_operand[143:136], alu_operand[79 : 72], alu_operand[15 :  8],
                                   alu_operand[1015:1008], alu_operand[951:944], alu_operand[887:880], alu_operand[823:816], alu_operand[759:752], alu_operand[695:688], alu_operand[631:624], alu_operand[567:560],
                                   alu_operand[503 : 496], alu_operand[439:432], alu_operand[375:368], alu_operand[311:304], alu_operand[247:240], alu_operand[183:176], alu_operand[119:112], alu_operand[55 : 48],
                                   alu_operand[983 : 976], alu_operand[919:912], alu_operand[855:848], alu_operand[791:784], alu_operand[727:720], alu_operand[663:656], alu_operand[599:592], alu_operand[535:528],
                                   alu_operand[471 : 464], alu_operand[407:400], alu_operand[343:336], alu_operand[279:272], alu_operand[215:208], alu_operand[151:144], alu_operand[87 : 80], alu_operand[23 : 16],
                                   alu_operand[999 : 992], alu_operand[935:928], alu_operand[871:864], alu_operand[807:800], alu_operand[743:736], alu_operand[679:672], alu_operand[615:608], alu_operand[551:544],
                                   alu_operand[487 : 480], alu_operand[423:416], alu_operand[359:352], alu_operand[295:288], alu_operand[231:224], alu_operand[167:160], alu_operand[103: 96], alu_operand[39 : 32],
                                   alu_operand[967 : 960], alu_operand[903:896], alu_operand[839:832], alu_operand[775:768], alu_operand[711:704], alu_operand[647:640], alu_operand[583:576], alu_operand[519:512],
                                   alu_operand[455 : 448], alu_operand[391:384], alu_operand[327:320], alu_operand[263:256], alu_operand[199:192], alu_operand[135:128], alu_operand[71 : 64], alu_operand[7  :  0]};
          EW16: alu_operand_seq = {alu_operand[1023:1008], alu_operand[959:944], alu_operand[895:880], alu_operand[831:816],
                                   alu_operand[767 : 752], alu_operand[703:688], alu_operand[639:624], alu_operand[575:560],
                                   alu_operand[511 : 496], alu_operand[447:432], alu_operand[383:368], alu_operand[319:304],
                                   alu_operand[255 : 240], alu_operand[191:176], alu_operand[127:112], alu_operand[63 : 48],
                                   alu_operand[991 : 976], alu_operand[927:912], alu_operand[863:848], alu_operand[799:784],
                                   alu_operand[735 : 720], alu_operand[671:656], alu_operand[607:592], alu_operand[543:528],
                                   alu_operand[479 : 464], alu_operand[415:400], alu_operand[351:336], alu_operand[287:272],
                                   alu_operand[223 : 208], alu_operand[159:144], alu_operand[95 : 80], alu_operand[31 : 16],
                                   alu_operand[1007: 992], alu_operand[943:928], alu_operand[879:864], alu_operand[815:800],
                                   alu_operand[751 : 736], alu_operand[687:672], alu_operand[623:608], alu_operand[559:544],
                                   alu_operand[495 : 480], alu_operand[431:416], alu_operand[367:352], alu_operand[303:288],
                                   alu_operand[239 : 224], alu_operand[175:160], alu_operand[111: 96], alu_operand[47 : 32],
                                   alu_operand[975 : 960], alu_operand[911:896], alu_operand[847:832], alu_operand[783:768],
                                   alu_operand[719 : 704], alu_operand[655:640], alu_operand[591:576], alu_operand[527:512],
                                   alu_operand[463 : 448], alu_operand[399:384], alu_operand[335:320], alu_operand[271:256],
                                   alu_operand[207 : 192], alu_operand[143:128], alu_operand[79 : 64], alu_operand[15 :  0]};
          EW32: alu_operand_seq = {alu_operand[1023: 992], alu_operand[959:928],
                                   alu_operand[895 : 864], alu_operand[831:800],
                                   alu_operand[767 : 736], alu_operand[703:672],
                                   alu_operand[639 : 608], alu_operand[575:544],
                                   alu_operand[511 : 480], alu_operand[447:416],
                                   alu_operand[383 : 352], alu_operand[319:288],
                                   alu_operand[255 : 224], alu_operand[191:160],
                                   alu_operand[127 :  96], alu_operand[63 : 32],
                                   alu_operand[991 : 960], alu_operand[927:896],
                                   alu_operand[863 : 832], alu_operand[799:768],
                                   alu_operand[735 : 704], alu_operand[671:640],
                                   alu_operand[607 : 576], alu_operand[543:512],
                                   alu_operand[479 : 448], alu_operand[415:384],
                                   alu_operand[351 : 320], alu_operand[287:256],
                                   alu_operand[223 : 192], alu_operand[159:128],
                                   alu_operand[95  :  64], alu_operand[31 :  0]};
          EW64: alu_operand_seq = {alu_operand[1023: 960],
                                   alu_operand[959 : 896],
                                   alu_operand[895 : 832],
                                   alu_operand[831 : 768],
                                   alu_operand[767 : 704],
                                   alu_operand[703 : 640],
                                   alu_operand[639 : 576],
                                   alu_operand[575 : 512],
                                   alu_operand[511 : 448],
                                   alu_operand[447 : 384],
                                   alu_operand[383 : 320],
                                   alu_operand[319 : 256],
                                   alu_operand[255 : 192],
                                   alu_operand[191 : 128],
                                   alu_operand[127 :  64],
                                   alu_operand[63  :   0]};
        endcase
      end
    endcase
  endgenerate

endmodule : op_seq

