set_property SRC_FILE_INFO {cfile:c:/Users/zfsalti/488/MP-2/MP2.xpr/MP2/MP2.srcs/sources_1/bd/system/ip/system_clk_wiz_0_0/system_clk_wiz_0_0/system_clk_wiz_0_0_in_context.xdc rfile:../../../MP2.srcs/sources_1/bd/system/ip/system_clk_wiz_0_0/system_clk_wiz_0_0/system_clk_wiz_0_0_in_context.xdc id:1 order:EARLY scoped_inst:system_i/clk_wiz_0} [current_design]
set_property SRC_FILE_INFO {cfile:c:/Users/zfsalti/488/MP-2/MP2.xpr/MP2/MP2.srcs/sources_1/bd/system/ip/system_processing_system7_0_0/system_processing_system7_0_0/system_processing_system7_0_0_in_context.xdc rfile:../../../MP2.srcs/sources_1/bd/system/ip/system_processing_system7_0_0/system_processing_system7_0_0/system_processing_system7_0_0_in_context.xdc id:2 order:EARLY scoped_inst:system_i/processing_system7_0} [current_design]
set_property SRC_FILE_INFO {cfile:c:/Users/zfsalti/488/MP-2/MP2.xpr/MP2/MP2.srcs/sources_1/bd/system/ip/system_video_dynclk_0/system_video_dynclk_0/system_video_dynclk_0_in_context.xdc rfile:../../../MP2.srcs/sources_1/bd/system/ip/system_video_dynclk_0/system_video_dynclk_0/system_video_dynclk_0_in_context.xdc id:3 order:EARLY scoped_inst:system_i/video_dynclk} [current_design]
set_property SRC_FILE_INFO {cfile:c:/Users/zfsalti/488/MP-2/MP2.xpr/MP2/MP2.srcs/sources_1/bd/system/ip/system_mipi_csi2_rx_subsyst_0_0/system_mipi_csi2_rx_subsyst_0_0/system_mipi_csi2_rx_subsyst_0_0_in_context.xdc rfile:../../../MP2.srcs/sources_1/bd/system/ip/system_mipi_csi2_rx_subsyst_0_0/system_mipi_csi2_rx_subsyst_0_0/system_mipi_csi2_rx_subsyst_0_0_in_context.xdc id:4 order:EARLY scoped_inst:system_i/mipi_csi2_rx_subsyst_0} [current_design]
set_property SRC_FILE_INFO {cfile:C:/Users/zfsalti/488/MP-2/MP2.xpr/MP2/MP2.srcs/constrs_1/new/MP2.xdc rfile:../../../MP2.srcs/constrs_1/new/MP2.xdc id:5} [current_design]
current_instance system_i/clk_wiz_0
set_property src_info {type:SCOPED_XDC file:1 line:2 export:INPUT save:INPUT read:READ} [current_design]
create_generated_clock -source [get_ports clk_in1] -edges {1 2 3} -edge_shift {0.000 -1.667 -3.333} [get_ports {}]
set_property src_info {type:SCOPED_XDC file:1 line:4 export:INPUT save:INPUT read:READ} [current_design]
create_generated_clock -source [get_ports clk_in1] -edges {1 2 3} -edge_shift {0.000 5.000 10.000} [get_ports {}]
set_property src_info {type:SCOPED_XDC file:1 line:6 export:INPUT save:INPUT read:READ} [current_design]
create_generated_clock -source [get_ports clk_in1] -edges {1 2 3} -edge_shift {0.000 -2.500 -5.000} [get_ports {}]
current_instance
current_instance system_i/processing_system7_0
set_property src_info {type:SCOPED_XDC file:2 line:2 export:INPUT save:INPUT read:READ} [current_design]
create_clock -period 10.000 [get_ports {}]
current_instance
current_instance system_i/video_dynclk
set_property src_info {type:SCOPED_XDC file:3 line:2 export:INPUT save:INPUT read:READ} [current_design]
create_generated_clock -source [get_ports clk_in1] -edges {1 2 3} -edge_shift {0.000 -4.327 -8.653} [get_ports {}]
current_instance
current_instance system_i/mipi_csi2_rx_subsyst_0
set_property src_info {type:SCOPED_XDC file:4 line:2 export:INPUT save:INPUT read:READ} [current_design]
create_clock -period 19.048 [get_ports {}]
set_property src_info {type:SCOPED_XDC file:4 line:4 export:INPUT save:INPUT read:READ} [current_design]
create_clock -period 6.666 [get_ports {}]
set_property src_info {type:SCOPED_XDC file:4 line:6 export:INPUT save:INPUT read:READ} [current_design]
create_clock -period 10.000 [get_ports {}]
current_instance
set_property src_info {type:XDC file:5 line:8 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN W18  [get_ports {hdmi_clk}];  # "HD-CLK"
set_property src_info {type:XDC file:5 line:9 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN Y13  [get_ports {hdmi_data[0]}];  # "HD-D0"
set_property src_info {type:XDC file:5 line:10 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN AA13 [get_ports {hdmi_data[1]}];  # "HD-D1"
set_property src_info {type:XDC file:5 line:11 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN W13  [get_ports {hdmi_data[10]}];  # "HD-D10"
set_property src_info {type:XDC file:5 line:12 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN W15  [get_ports {hdmi_data[11]}];  # "HD-D11"
set_property src_info {type:XDC file:5 line:13 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN V15  [get_ports {hdmi_data[12]}];  # "HD-D12"
set_property src_info {type:XDC file:5 line:14 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN U17  [get_ports {hdmi_data[13]}];  # "HD-D13"
set_property src_info {type:XDC file:5 line:15 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN V14  [get_ports {hdmi_data[14]}];  # "HD-D14"
set_property src_info {type:XDC file:5 line:16 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN V13  [get_ports {hdmi_data[15]}];  # "HD-D15"
set_property src_info {type:XDC file:5 line:17 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN AA14 [get_ports {hdmi_data[2]}];  # "HD-D2"
set_property src_info {type:XDC file:5 line:18 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN Y14  [get_ports {hdmi_data[3]}];  # "HD-D3"
set_property src_info {type:XDC file:5 line:19 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN AB15 [get_ports {hdmi_data[4]}];  # "HD-D4"
set_property src_info {type:XDC file:5 line:20 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN AB16 [get_ports {hdmi_data[5]}];  # "HD-D5"
set_property src_info {type:XDC file:5 line:21 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN AA16 [get_ports {hdmi_data[6]}];  # "HD-D6"
set_property src_info {type:XDC file:5 line:22 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN AB17 [get_ports {hdmi_data[7]}];  # "HD-D7"
set_property src_info {type:XDC file:5 line:23 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN AA17 [get_ports {hdmi_data[8]}];  # "HD-D8"
set_property src_info {type:XDC file:5 line:24 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN Y15  [get_ports {hdmi_data[9]}];  # "HD-D9"
set_property src_info {type:XDC file:5 line:25 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN U16  [get_ports {hdmi_de}];  # "HD-DE"
set_property src_info {type:XDC file:5 line:26 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN V17  [get_ports {hdmi_hsync}];  # "HD-HSYNC"
set_property src_info {type:XDC file:5 line:28 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN AA18 [get_ports {hdmi_iic_scl_io}];  # "HD-SCL"
set_property src_info {type:XDC file:5 line:29 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN Y16  [get_ports {hdmi_iic_sda_io}];  # "HD-SDA"
set_property src_info {type:XDC file:5 line:32 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN W17  [get_ports {hdmi_vsync}];  # "HD-VSYNC"
set_property src_info {type:XDC file:5 line:38 export:INPUT save:INPUT read:READ} [current_design]
set_property -dict {PACKAGE_PIN R7 IOSTANDARD LVCMOS33} [get_ports {cam_iic_scl_io}];  # "FMC-SCL"
set_property src_info {type:XDC file:5 line:39 export:INPUT save:INPUT read:READ} [current_design]
set_property -dict {PACKAGE_PIN U7 IOSTANDARD LVCMOS33} [get_ports {cam_iic_sda_io}];  # "FMC-SDA"
set_property src_info {type:XDC file:5 line:46 export:INPUT save:INPUT read:READ} [current_design]
set_property -dict {PACKAGE_PIN AB14 IOSTANDARD LVCMOS33} [get_ports {cam_pwup_tri_io[1]}];  # "FMC-LA12_N"
set_property src_info {type:XDC file:5 line:52 export:INPUT save:INPUT read:READ} [current_design]
set_property -dict {PACKAGE_PIN T16 IOSTANDARD LVCMOS25 DRIVE 4} [get_ports {cam_pwup_tri_io[0]}];  # "FMC-LA07_P"
set_property src_info {type:XDC file:5 line:55 export:INPUT save:INPUT read:READ} [current_design]
set_property -dict {PACKAGE_PIN N20 IOSTANDARD LVDS_25 DIFF_TERM true} [get_ports {MIPI_DPHY_clk_hs_n}];  # "FMC-LA01_CC_N"
set_property src_info {type:XDC file:5 line:56 export:INPUT save:INPUT read:READ} [current_design]
set_property -dict {PACKAGE_PIN N19 IOSTANDARD LVDS_25 DIFF_TERM true} [get_ports {MIPI_DPHY_clk_hs_p}];  # "FMC-LA01_CC_P" - corrected 6/6/16 GE
set_property src_info {type:XDC file:5 line:57 export:INPUT save:INPUT read:READ} [current_design]
set_property -dict {PACKAGE_PIN J22 IOSTANDARD LVCMOS25} [get_ports {MIPI_DPHY_clk_lp_n}];  # "FMC-LA08_N"
set_property src_info {type:XDC file:5 line:58 export:INPUT save:INPUT read:READ} [current_design]
set_property -dict {PACKAGE_PIN J21 IOSTANDARD LVCMOS25} [get_ports {MIPI_DPHY_clk_lp_p}];  # "FMC-LA08_P"
set_property src_info {type:XDC file:5 line:60 export:INPUT save:INPUT read:READ} [current_design]
set_property -dict {PACKAGE_PIN T19 IOSTANDARD LVDS_25 DIFF_TERM true} [get_ports {MIPI_DPHY_data_hs_n[0]}];  # "FMC-LA10_N"
set_property src_info {type:XDC file:5 line:61 export:INPUT save:INPUT read:READ} [current_design]
set_property -dict {PACKAGE_PIN L22 IOSTANDARD LVDS_25 DIFF_TERM true} [get_ports {MIPI_DPHY_data_hs_n[1]}];  # "FMC-LA06_N"
set_property src_info {type:XDC file:5 line:62 export:INPUT save:INPUT read:READ} [current_design]
set_property -dict {PACKAGE_PIN R19 IOSTANDARD LVDS_25 DIFF_TERM true} [get_ports {MIPI_DPHY_data_hs_p[0]}];  # "FMC-LA10_P"
set_property src_info {type:XDC file:5 line:63 export:INPUT save:INPUT read:READ} [current_design]
set_property -dict {PACKAGE_PIN L21 IOSTANDARD LVDS_25 DIFF_TERM true} [get_ports {MIPI_DPHY_data_hs_p[1]}];  # "FMC-LA06_P"
set_property src_info {type:XDC file:5 line:65 export:INPUT save:INPUT read:READ} [current_design]
set_property -dict {PACKAGE_PIN P22 IOSTANDARD LVCMOS25} [get_ports {MIPI_DPHY_data_lp_n[0]}];  # "FMC-LA03_N"
set_property src_info {type:XDC file:5 line:66 export:INPUT save:INPUT read:READ} [current_design]
set_property -dict {PACKAGE_PIN P21 IOSTANDARD LVCMOS25} [get_ports {MIPI_DPHY_data_lp_n[1]}];  # "FMC-LA12_N"
set_property src_info {type:XDC file:5 line:67 export:INPUT save:INPUT read:READ} [current_design]
set_property -dict {PACKAGE_PIN N22 IOSTANDARD LVCMOS25} [get_ports {MIPI_DPHY_data_lp_p[0]}];  # "FMC-LA03_P"
set_property src_info {type:XDC file:5 line:68 export:INPUT save:INPUT read:READ} [current_design]
set_property -dict {PACKAGE_PIN P20 IOSTANDARD LVCMOS25} [get_ports {MIPI_DPHY_data_lp_p[1]}];  # "FMC-LA12_P"
set_property src_info {type:XDC file:5 line:76 export:INPUT save:INPUT read:READ} [current_design]
set_property IOSTANDARD LVCMOS33 [get_ports -of_objects [get_iobanks 33]];
set_property src_info {type:XDC file:5 line:79 export:INPUT save:INPUT read:READ} [current_design]
set_property -dict { PACKAGE_PIN J17   IOSTANDARD LVCMOS25} [get_ports { cam_gpio_dir[0] }]; #IO_L8P_T1_34 Sch=jb_p[1]
set_property src_info {type:XDC file:5 line:80 export:INPUT save:INPUT read:READ} [current_design]
set_property -dict { PACKAGE_PIN K19   IOSTANDARD LVCMOS25} [get_ports { cam_gpio_oen[0] }]; #IO_L8P_T1_34 Sch=jb_p[1]
set_property src_info {type:XDC file:5 line:83 export:INPUT save:INPUT read:READ} [current_design]
set_property -dict { PACKAGE_PIN T17   IOSTANDARD LVCMOS25 PULLUP true} [get_ports { cama_gpio_tri_io[0] }]; #IO_L8P_T1_34 Sch=jb_p[1]
set_property src_info {type:XDC file:5 line:84 export:INPUT save:INPUT read:READ} [current_design]
set_property -dict { PACKAGE_PIN N17   IOSTANDARD LVCMOS25 PULLUP true} [get_ports { cama_gpio_tri_io[1] }]; #IO_L8P_T1_34 Sch=jb_p[1]
set_property src_info {type:XDC file:5 line:85 export:INPUT save:INPUT read:READ} [current_design]
set_property -dict { PACKAGE_PIN N18   IOSTANDARD LVCMOS25 PULLUP true} [get_ports { cama_gpio_tri_io[2] }]; #IO_L8P_T1_34 Sch=jb_p[1]
set_property src_info {type:XDC file:5 line:86 export:INPUT save:INPUT read:READ} [current_design]
set_property -dict { PACKAGE_PIN J16   IOSTANDARD LVCMOS25 PULLUP true} [get_ports { cama_gpio_tri_io[3] }]; #IO_L8P_T1_34 Sch=jb_p[1]
set_property src_info {type:XDC file:5 line:89 export:INPUT save:INPUT read:READ} [current_design]
set_property -dict { PACKAGE_PIN J20   IOSTANDARD LVCMOS25 } [get_ports { cama_bta_tri_io[0] }]; #IO_L8P_T1_34 Sch=jb_p[1]
set_property src_info {type:XDC file:5 line:90 export:INPUT save:INPUT read:READ} [current_design]
set_property -dict { PACKAGE_PIN K21   IOSTANDARD LVCMOS25 } [get_ports { cama_bta_tri_io[1] }]; #IO_L8P_T1_34 Sch=jb_p[1]
set_property src_info {type:XDC file:5 line:91 export:INPUT save:INPUT read:READ} [current_design]
set_property -dict { PACKAGE_PIN C17   IOSTANDARD LVCMOS25 } [get_ports { cama_bta_tri_io[2] }]; #IO_L8P_T1_34 Sch=jb_p[1]
set_property src_info {type:XDC file:5 line:92 export:INPUT save:INPUT read:READ} [current_design]
set_property -dict { PACKAGE_PIN C18   IOSTANDARD LVCMOS25 } [get_ports { cama_bta_tri_io[3] }]; #IO_L8P_T1_34 Sch=jb_p[1]
set_property src_info {type:XDC file:5 line:101 export:INPUT save:INPUT read:READ} [current_design]
create_clock -period 1.667 -name video_dynclk [get_pins -regexp .*video_dynclk/.*/mmcm_adv_inst/CLKOUT0 -hierarchical]
set_property src_info {type:XDC file:5 line:106 export:INPUT save:INPUT read:READ} [current_design]
create_clock -period 6.734 -name pixel_dynclk [get_pins -regexp .*DVIClocking_0/U0/PixelClkBuffer/O -hierarchical]
