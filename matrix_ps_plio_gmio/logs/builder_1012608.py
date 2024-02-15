# 2024-02-08T16:10:51.753252
import vitis

client = vitis.create_client()
client.set_workspace(path="/home/yzwu/Desktop/soc_test")

status = client.set_preference(level = "WORKSPACE", device = "Versal", key = "Sysroot", value = "/opt/petalinux/2023.2/sysroots/cortexa72-cortexa53-xilinx-linux")

status = client.set_preference(level = "WORKSPACE", device = "Versal", key = "KernelImage", value = "/opt/xilinx/platforms/Image")

status = client.set_preference(level = "WORKSPACE", device = "Versal", key = "RootFS", value = "/opt/xilinx/platforms/rootfs.ext4")

platform = client.get_platform_component(name="platform")
status = platform.build()

comp = client.get_component(name="hello_world")
comp.build()

comp = client.create_app_component(name="linux_hello_world",platform = "/tools/Xilinx/Vitis/2023.2/base_platforms/xilinx_vck190_base_202320_1/xilinx_vck190_base_202320_1.xpfm",domain = "xrt",template = "linux_hello_world")

comp = client.get_component("linux_hello_world")

status = comp.set_sysroot(sysroot="/opt/petalinux/2023.2/sysroots/cortexa72-cortexa53-xilinx-linux")

client.delete_component(name="hello_world")

client.delete_platform_component(name="platform")

comp = client.get_component(name="linux_hello_world")
comp.build()

comp.build()

client.delete_component(name="linux_hello_world")

proj = client.create_sys_project(name="vadd", platform="/tools/Xilinx/Vitis/2023.2/base_platforms/xilinx_vck190_base_202320_1/xilinx_vck190_base_202320_1.xpfm", template="installed_examples/vadd")

proj = client.get_sys_project(name="vadd")

proj.build(target="sw_emu")

proj.build(target="sw_emu")

proj.build(target="sw_emu")

proj.build(target="sw_emu")

proj.build(target="sw_emu")

proj.build(target="sw_emu")

proj.build(target="sw_emu")

proj.build(target="sw_emu")

comp = client.get_component(name="vadd_host")
comp.build(target="x86sim")

proj.build(target="sw_emu")

proj.build(target="sw_emu")

comp = client.create_aie_component(name="aie_component", platform = "/tools/Xilinx/Vitis/2023.2/base_platforms/xilinx_vck190_base_202320_1/xilinx_vck190_base_202320_1.xpfm", template = "empty_aie_component")

comp = client.get_component(name="aie_component")
status = comp.update_top_level_file(top_level_file="src/project.cpp")

status = comp.import_files(from_loc="/home/yzwu/Desktop/training_lab/design_with_aie_1/aie_tool_flow/completed/single_node_graph", files=["src", "data"])

vitis.dispose()

