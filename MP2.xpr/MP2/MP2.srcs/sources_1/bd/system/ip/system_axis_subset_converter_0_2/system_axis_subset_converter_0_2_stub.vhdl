-- Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2020.1 (win64) Build 2902540 Wed May 27 19:54:49 MDT 2020
-- Date        : Wed Apr  8 12:51:39 2026
-- Host        : CO2041-15 running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode synth_stub
--               c:/Users/zfsalti/488/MP-2/MP2.xpr/MP2/MP2.srcs/sources_1/bd/system/ip/system_axis_subset_converter_0_2/system_axis_subset_converter_0_2_stub.vhdl
-- Design      : system_axis_subset_converter_0_2
-- Purpose     : Stub declaration of top-level module interface
-- Device      : xc7z020clg484-1
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity system_axis_subset_converter_0_2 is
  Port ( 
    aclk : in STD_LOGIC;
    aresetn : in STD_LOGIC;
    s_axis_tvalid : in STD_LOGIC;
    s_axis_tready : out STD_LOGIC;
    s_axis_tdata : in STD_LOGIC_VECTOR ( 15 downto 0 );
    s_axis_tlast : in STD_LOGIC;
    s_axis_tdest : in STD_LOGIC_VECTOR ( 9 downto 0 );
    s_axis_tuser : in STD_LOGIC_VECTOR ( 0 to 0 );
    m_axis_tvalid : out STD_LOGIC;
    m_axis_tready : in STD_LOGIC;
    m_axis_tdata : out STD_LOGIC_VECTOR ( 15 downto 0 );
    m_axis_tlast : out STD_LOGIC;
    m_axis_tdest : out STD_LOGIC_VECTOR ( 9 downto 0 );
    m_axis_tuser : out STD_LOGIC_VECTOR ( 0 to 0 )
  );

end system_axis_subset_converter_0_2;

architecture stub of system_axis_subset_converter_0_2 is
attribute syn_black_box : boolean;
attribute black_box_pad_pin : string;
attribute syn_black_box of stub : architecture is true;
attribute black_box_pad_pin of stub : architecture is "aclk,aresetn,s_axis_tvalid,s_axis_tready,s_axis_tdata[15:0],s_axis_tlast,s_axis_tdest[9:0],s_axis_tuser[0:0],m_axis_tvalid,m_axis_tready,m_axis_tdata[15:0],m_axis_tlast,m_axis_tdest[9:0],m_axis_tuser[0:0]";
attribute X_CORE_INFO : string;
attribute X_CORE_INFO of stub : architecture is "top_system_axis_subset_converter_0_2,Vivado 2020.1";
begin
end;
