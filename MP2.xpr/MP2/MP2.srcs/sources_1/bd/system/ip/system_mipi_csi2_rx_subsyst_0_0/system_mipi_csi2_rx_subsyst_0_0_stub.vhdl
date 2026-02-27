-- Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2020.1 (win64) Build 2902540 Wed May 27 19:54:49 MDT 2020
-- Date        : Fri Feb 27 10:33:42 2026
-- Host        : CO2041-03 running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode synth_stub
--               c:/Users/zfsalti/488/MP-2/MP2.xpr/MP2/MP2.srcs/sources_1/bd/system/ip/system_mipi_csi2_rx_subsyst_0_0/system_mipi_csi2_rx_subsyst_0_0_stub.vhdl
-- Design      : system_mipi_csi2_rx_subsyst_0_0
-- Purpose     : Stub declaration of top-level module interface
-- Device      : xc7z020clg484-1
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity system_mipi_csi2_rx_subsyst_0_0 is
  Port ( 
    lite_aclk : in STD_LOGIC;
    lite_aresetn : in STD_LOGIC;
    dphy_clk_200M : in STD_LOGIC;
    rxbyteclkhs : out STD_LOGIC;
    system_rst_out : out STD_LOGIC;
    csirxss_csi_irq : out STD_LOGIC;
    video_aclk : in STD_LOGIC;
    video_aresetn : in STD_LOGIC;
    csirxss_s_axi_awaddr : in STD_LOGIC_VECTOR ( 12 downto 0 );
    csirxss_s_axi_awprot : in STD_LOGIC_VECTOR ( 2 downto 0 );
    csirxss_s_axi_awvalid : in STD_LOGIC_VECTOR ( 0 to 0 );
    csirxss_s_axi_awready : out STD_LOGIC_VECTOR ( 0 to 0 );
    csirxss_s_axi_wdata : in STD_LOGIC_VECTOR ( 31 downto 0 );
    csirxss_s_axi_wstrb : in STD_LOGIC_VECTOR ( 3 downto 0 );
    csirxss_s_axi_wvalid : in STD_LOGIC_VECTOR ( 0 to 0 );
    csirxss_s_axi_wready : out STD_LOGIC_VECTOR ( 0 to 0 );
    csirxss_s_axi_bresp : out STD_LOGIC_VECTOR ( 1 downto 0 );
    csirxss_s_axi_bvalid : out STD_LOGIC_VECTOR ( 0 to 0 );
    csirxss_s_axi_bready : in STD_LOGIC_VECTOR ( 0 to 0 );
    csirxss_s_axi_araddr : in STD_LOGIC_VECTOR ( 12 downto 0 );
    csirxss_s_axi_arprot : in STD_LOGIC_VECTOR ( 2 downto 0 );
    csirxss_s_axi_arvalid : in STD_LOGIC_VECTOR ( 0 to 0 );
    csirxss_s_axi_arready : out STD_LOGIC_VECTOR ( 0 to 0 );
    csirxss_s_axi_rdata : out STD_LOGIC_VECTOR ( 31 downto 0 );
    csirxss_s_axi_rresp : out STD_LOGIC_VECTOR ( 1 downto 0 );
    csirxss_s_axi_rvalid : out STD_LOGIC_VECTOR ( 0 to 0 );
    csirxss_s_axi_rready : in STD_LOGIC_VECTOR ( 0 to 0 );
    video_out_tdata : out STD_LOGIC_VECTOR ( 15 downto 0 );
    video_out_tdest : out STD_LOGIC_VECTOR ( 9 downto 0 );
    video_out_tlast : out STD_LOGIC;
    video_out_tready : in STD_LOGIC;
    video_out_tuser : out STD_LOGIC_VECTOR ( 0 to 0 );
    video_out_tvalid : out STD_LOGIC;
    mipi_phy_if_clk_hs_n : in STD_LOGIC;
    mipi_phy_if_clk_hs_p : in STD_LOGIC;
    mipi_phy_if_clk_lp_n : in STD_LOGIC;
    mipi_phy_if_clk_lp_p : in STD_LOGIC;
    mipi_phy_if_data_hs_n : in STD_LOGIC_VECTOR ( 1 downto 0 );
    mipi_phy_if_data_hs_p : in STD_LOGIC_VECTOR ( 1 downto 0 );
    mipi_phy_if_data_lp_n : in STD_LOGIC_VECTOR ( 1 downto 0 );
    mipi_phy_if_data_lp_p : in STD_LOGIC_VECTOR ( 1 downto 0 )
  );

end system_mipi_csi2_rx_subsyst_0_0;

architecture stub of system_mipi_csi2_rx_subsyst_0_0 is
attribute syn_black_box : boolean;
attribute black_box_pad_pin : string;
attribute syn_black_box of stub : architecture is true;
attribute black_box_pad_pin of stub : architecture is "lite_aclk,lite_aresetn,dphy_clk_200M,rxbyteclkhs,system_rst_out,csirxss_csi_irq,video_aclk,video_aresetn,csirxss_s_axi_awaddr[12:0],csirxss_s_axi_awprot[2:0],csirxss_s_axi_awvalid[0:0],csirxss_s_axi_awready[0:0],csirxss_s_axi_wdata[31:0],csirxss_s_axi_wstrb[3:0],csirxss_s_axi_wvalid[0:0],csirxss_s_axi_wready[0:0],csirxss_s_axi_bresp[1:0],csirxss_s_axi_bvalid[0:0],csirxss_s_axi_bready[0:0],csirxss_s_axi_araddr[12:0],csirxss_s_axi_arprot[2:0],csirxss_s_axi_arvalid[0:0],csirxss_s_axi_arready[0:0],csirxss_s_axi_rdata[31:0],csirxss_s_axi_rresp[1:0],csirxss_s_axi_rvalid[0:0],csirxss_s_axi_rready[0:0],video_out_tdata[15:0],video_out_tdest[9:0],video_out_tlast,video_out_tready,video_out_tuser[0:0],video_out_tvalid,mipi_phy_if_clk_hs_n,mipi_phy_if_clk_hs_p,mipi_phy_if_clk_lp_n,mipi_phy_if_clk_lp_p,mipi_phy_if_data_hs_n[1:0],mipi_phy_if_data_hs_p[1:0],mipi_phy_if_data_lp_n[1:0],mipi_phy_if_data_lp_p[1:0]";
attribute x_core_info : string;
attribute x_core_info of stub : architecture is "bd_22c6,Vivado 2020.1";
begin
end;
