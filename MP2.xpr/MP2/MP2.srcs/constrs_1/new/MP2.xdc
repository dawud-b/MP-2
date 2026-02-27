########################
# Physical Constraints #
########################

# ----------------------------------------------------------------------------
# HDMI Output - Bank 33
# ---------------------------------------------------------------------------- 
set_property PACKAGE_PIN W18  [get_ports {hdmi_clk}];  # "HD-CLK"
set_property PACKAGE_PIN Y13  [get_ports {hdmi_data[0]}];  # "HD-D0"
set_property PACKAGE_PIN AA13 [get_ports {hdmi_data[1]}];  # "HD-D1"
set_property PACKAGE_PIN W13  [get_ports {hdmi_data[10]}];  # "HD-D10"
set_property PACKAGE_PIN W15  [get_ports {hdmi_data[11]}];  # "HD-D11"
set_property PACKAGE_PIN V15  [get_ports {hdmi_data[12]}];  # "HD-D12"
set_property PACKAGE_PIN U17  [get_ports {hdmi_data[13]}];  # "HD-D13"
set_property PACKAGE_PIN V14  [get_ports {hdmi_data[14]}];  # "HD-D14"
set_property PACKAGE_PIN V13  [get_ports {hdmi_data[15]}];  # "HD-D15"
set_property PACKAGE_PIN AA14 [get_ports {hdmi_data[2]}];  # "HD-D2"
set_property PACKAGE_PIN Y14  [get_ports {hdmi_data[3]}];  # "HD-D3"
set_property PACKAGE_PIN AB15 [get_ports {hdmi_data[4]}];  # "HD-D4"
set_property PACKAGE_PIN AB16 [get_ports {hdmi_data[5]}];  # "HD-D5"
set_property PACKAGE_PIN AA16 [get_ports {hdmi_data[6]}];  # "HD-D6"
set_property PACKAGE_PIN AB17 [get_ports {hdmi_data[7]}];  # "HD-D7"
set_property PACKAGE_PIN AA17 [get_ports {hdmi_data[8]}];  # "HD-D8"
set_property PACKAGE_PIN Y15  [get_ports {hdmi_data[9]}];  # "HD-D9"
set_property PACKAGE_PIN U16  [get_ports {hdmi_de}];  # "HD-DE"
set_property PACKAGE_PIN V17  [get_ports {hdmi_hsync}];  # "HD-HSYNC"
# phjones: NOT USED  set_property PACKAGE_PIN W16  [get_ports {HD_INT}];  # "HD-INT"
set_property PACKAGE_PIN AA18 [get_ports {hdmi_iic_scl_io}];  # "HD-SCL"
set_property PACKAGE_PIN Y16  [get_ports {hdmi_iic_sda_io}];  # "HD-SDA"
# phjones: NOT USED  set_property PACKAGE_PIN U15  [get_ports {HD_SPDIF}];  # "HD-SPDIF"
# phjones: NOT USED  set_property PACKAGE_PIN Y18  [get_ports {HD_SPDIFO}];  # "HD-SPDIFO"
set_property PACKAGE_PIN W17  [get_ports {hdmi_vsync}];  # "HD-VSYNC"


# ----------------------------------------------------------------------------
# FMC Expansion Connector - Bank 13
# ---------------------------------------------------------------------------- 
set_property -dict {PACKAGE_PIN R7 IOSTANDARD LVCMOS33} [get_ports {cam_iic_scl_io}];  # "FMC-SCL"
set_property -dict {PACKAGE_PIN U7 IOSTANDARD LVCMOS33} [get_ports {cam_iic_sda_io}];  # "FMC-SDA"


# ----------------------------------------------------------------------------
# FMC Expansion Connector - Bank 33
# ---------------------------------------------------------------------------- 
# phjones: NOT USED  set_property PACKAGE_PIN AB14 [get_ports {cam_pwup_tri_io[1]}];  # "FMC-PRSNT"
set_property -dict {PACKAGE_PIN AB14 IOSTANDARD LVCMOS33} [get_ports {cam_pwup_tri_io[1]}];  # "FMC-LA12_N"


# ----------------------------------------------------------------------------
# FMC Expansion Connector - Bank 34
# ---------------------------------------------------------------------------- 
set_property -dict {PACKAGE_PIN T16 IOSTANDARD LVCMOS25 DRIVE 4} [get_ports {cam_pwup_tri_io[0]}];  # "FMC-LA07_P"


set_property -dict {PACKAGE_PIN N20 IOSTANDARD LVDS_25 DIFF_TERM true} [get_ports {MIPI_DPHY_clk_hs_n}];  # "FMC-LA01_CC_N"
set_property -dict {PACKAGE_PIN N19 IOSTANDARD LVDS_25 DIFF_TERM true} [get_ports {MIPI_DPHY_clk_hs_p}];  # "FMC-LA01_CC_P" - corrected 6/6/16 GE
set_property -dict {PACKAGE_PIN J22 IOSTANDARD LVCMOS25} [get_ports {MIPI_DPHY_clk_lp_n}];  # "FMC-LA08_N"
set_property -dict {PACKAGE_PIN J21 IOSTANDARD LVCMOS25} [get_ports {MIPI_DPHY_clk_lp_p}];  # "FMC-LA08_P"

set_property -dict {PACKAGE_PIN T19 IOSTANDARD LVDS_25 DIFF_TERM true} [get_ports {MIPI_DPHY_data_hs_n[0]}];  # "FMC-LA10_N"
set_property -dict {PACKAGE_PIN L22 IOSTANDARD LVDS_25 DIFF_TERM true} [get_ports {MIPI_DPHY_data_hs_n[1]}];  # "FMC-LA06_N"
set_property -dict {PACKAGE_PIN R19 IOSTANDARD LVDS_25 DIFF_TERM true} [get_ports {MIPI_DPHY_data_hs_p[0]}];  # "FMC-LA10_P"
set_property -dict {PACKAGE_PIN L21 IOSTANDARD LVDS_25 DIFF_TERM true} [get_ports {MIPI_DPHY_data_hs_p[1]}];  # "FMC-LA06_P"

set_property -dict {PACKAGE_PIN P22 IOSTANDARD LVCMOS25} [get_ports {MIPI_DPHY_data_lp_n[0]}];  # "FMC-LA03_N"
set_property -dict {PACKAGE_PIN P21 IOSTANDARD LVCMOS25} [get_ports {MIPI_DPHY_data_lp_n[1]}];  # "FMC-LA12_N"
set_property -dict {PACKAGE_PIN N22 IOSTANDARD LVCMOS25} [get_ports {MIPI_DPHY_data_lp_p[0]}];  # "FMC-LA03_P"
set_property -dict {PACKAGE_PIN P20 IOSTANDARD LVCMOS25} [get_ports {MIPI_DPHY_data_lp_p[1]}];  # "FMC-LA12_P"


# ----------------------------------------------------------------------------
# IOSTANDARD Constraints
# ---------------------------------------------------------------------------- 

# Note that the bank voltage for IO Bank 33 is fixed to 3.3V on ZedBoard. 
set_property IOSTANDARD LVCMOS33 [get_ports -of_objects [get_iobanks 33]];


set_property -dict { PACKAGE_PIN J17   IOSTANDARD LVCMOS25} [get_ports { cam_gpio_dir[0] }]; #IO_L8P_T1_34 Sch=jb_p[1]
set_property -dict { PACKAGE_PIN K19   IOSTANDARD LVCMOS25} [get_ports { cam_gpio_oen[0] }]; #IO_L8P_T1_34 Sch=jb_p[1]


set_property -dict { PACKAGE_PIN T17   IOSTANDARD LVCMOS25 PULLUP true} [get_ports { cama_gpio_tri_io[0] }]; #IO_L8P_T1_34 Sch=jb_p[1]
set_property -dict { PACKAGE_PIN N17   IOSTANDARD LVCMOS25 PULLUP true} [get_ports { cama_gpio_tri_io[1] }]; #IO_L8P_T1_34 Sch=jb_p[1]
set_property -dict { PACKAGE_PIN N18   IOSTANDARD LVCMOS25 PULLUP true} [get_ports { cama_gpio_tri_io[2] }]; #IO_L8P_T1_34 Sch=jb_p[1]
set_property -dict { PACKAGE_PIN J16   IOSTANDARD LVCMOS25 PULLUP true} [get_ports { cama_gpio_tri_io[3] }]; #IO_L8P_T1_34 Sch=jb_p[1]


set_property -dict { PACKAGE_PIN J20   IOSTANDARD LVCMOS25 } [get_ports { cama_bta_tri_io[0] }]; #IO_L8P_T1_34 Sch=jb_p[1]
set_property -dict { PACKAGE_PIN K21   IOSTANDARD LVCMOS25 } [get_ports { cama_bta_tri_io[1] }]; #IO_L8P_T1_34 Sch=jb_p[1]
set_property -dict { PACKAGE_PIN C17   IOSTANDARD LVCMOS25 } [get_ports { cama_bta_tri_io[2] }]; #IO_L8P_T1_34 Sch=jb_p[1]
set_property -dict { PACKAGE_PIN C18   IOSTANDARD LVCMOS25 } [get_ports { cama_bta_tri_io[3] }]; #IO_L8P_T1_34 Sch=jb_p[1]

# ----------------------------------------------------------------------------
# Timing Constraints
# ---------------------------------------------------------------------------- 

# Pixel clock tree underconstrained to 120 MHz to avoid pulse width errors on BUFIO/BUFR/OSERDESE2
# The MMCM outputs 5x this frequency for DVI serial clock, and is divided back by a BUFR.
# Period = 1/(5*120MHz) = 1.667 ns
create_clock -period 1.667 -name video_dynclk [get_pins -regexp .*video_dynclk/.*/mmcm_adv_inst/CLKOUT0 -hierarchical]

# Pixel clock constrained to 148.5 MHz on the output of BUFR
# Works because the clock path delay is not necessary to be analyzed all the way from the source clock of the MMCM, since there is no
# phase requirement between the source clock and the pixel clock
create_clock -period 6.734 -name pixel_dynclk [get_pins -regexp .*DVIClocking_0/U0/PixelClkBuffer/O -hierarchical]

# MIPI D-PHY data rate 420Mbps/lane = 210 MHz HS_Clk
create_clock -period 4.761 -name dphy_hs_clock_p -waveform {0.000 2.380} [get_ports MIPI_DPHY_clk_hs_p]

