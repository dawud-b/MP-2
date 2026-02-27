connect -url tcp:127.0.0.1:3121
source D:/repos/Incercare2019/repo2018/ZedBoard-FMC-Pcam-Adapter-DEMO/proj/ZedBoard-FMC-Pcam-Adapter-DEMO.sdk/system_wrapper_hw_platform_0/ps7_init.tcl
targets -set -nocase -filter {name =~"APU*" && jtag_cable_name =~ "Digilent Zed 210248AA3C0E"} -index 0
loadhw -hw D:/repos/Incercare2019/repo2018/ZedBoard-FMC-Pcam-Adapter-DEMO/proj/ZedBoard-FMC-Pcam-Adapter-DEMO.sdk/system_wrapper_hw_platform_0/system.hdf -mem-ranges [list {0x40000000 0xbfffffff}]
configparams force-mem-access 1
targets -set -nocase -filter {name =~"APU*" && jtag_cable_name =~ "Digilent Zed 210248AA3C0E"} -index 0
stop
ps7_init
ps7_post_config
targets -set -nocase -filter {name =~ "ARM*#0" && jtag_cable_name =~ "Digilent Zed 210248AA3C0E"} -index 0
rst -processor
targets -set -nocase -filter {name =~ "ARM*#0" && jtag_cable_name =~ "Digilent Zed 210248AA3C0E"} -index 0
dow D:/repos/Incercare2019/repo2018/ZedBoard-FMC-Pcam-Adapter-DEMO/proj/ZedBoard-FMC-Pcam-Adapter-DEMO.sdk/ZedBoard_FMC_Pcam_Adapter_DEMO/Debug/ZedBoard_FMC_Pcam_Adapter_DEMO.elf
configparams force-mem-access 0
targets -set -nocase -filter {name =~ "ARM*#0" && jtag_cable_name =~ "Digilent Zed 210248AA3C0E"} -index 0
con
