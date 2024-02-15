# 2024-02-09T22:01:07.220200
import vitis

client = vitis.create_client()
client.set_workspace(path="/home/yzwu/Desktop/soc_test")

status = client.set_preference(level = "WORKSPACE", device = "Versal", key = "Sysroot", value = "/opt/petalinux/2023.2/sysroots/cortexa72-cortexa53-xilinx-linux")

status = client.set_preference(level = "WORKSPACE", device = "Versal", key = "KernelImage", value = "/opt/xilinx/platforms/Image")

status = client.set_preference(level = "WORKSPACE", device = "Versal", key = "RootFS", value = "/opt/xilinx/platforms/rootfs.ext4")

comp = client.get_component(name="aie_component")
comp.build(target="x86sim")

comp.build(target="x86sim")

comp.build(target="x86sim")

comp.build(target="x86sim")

comp.build(target="x86sim")

comp.build(target="x86sim")

comp.build(target="x86sim")

comp.build(target="x86sim")

comp.build(target="x86sim")

comp.build(target="x86sim")

comp.build(target="x86sim")

comp.build(target="x86sim")

comp.build(target="x86sim")

comp.build(target="x86sim")

comp.build(target="x86sim")

comp.build(target="x86sim")

comp.build(target="x86sim")

comp.build(target="x86sim")

comp.build(target="x86sim")

comp.build(target="x86sim")

comp.build(target="x86sim")

comp.build(target="x86sim")

comp.build(target="x86sim")

proj = client.get_sys_project(name="vadd")

proj.build(target="sw_emu")

comp = client.clone_component(name="aie_component",new_name="matrix_plio")

comp = client.get_component(name="matrix_plio")
comp.build(target="x86sim")

comp.build(target="x86sim")

comp.build(target="hw")

comp.build(target="hw")

comp = client.get_component(name="aie_component")
comp.build(target="hw")

comp.build(target="hw")

comp.build(target="hw")

comp.build(target="hw")

comp.build(target="x86sim")

comp = client.get_component(name="matrix_plio")
comp.build(target="x86sim")

comp.build(target="hw")

comp.build(target="hw")

comp.build(target="x86sim")

comp = client.clone_component(name="matrix_plio",new_name="matrix_block")

comp = client.get_component(name="matrix_block")
comp.build(target="x86sim")

comp.build(target="x86sim")

comp.build(target="x86sim")

comp.build(target="x86sim")

comp.build(target="x86sim")

comp.build(target="x86sim")

comp.build(target="x86sim")

comp.build(target="x86sim")

comp.build(target="x86sim")

comp.build(target="x86sim")

comp.build(target="x86sim")

comp.build(target="x86sim")

comp.build(target="x86sim")

comp.build(target="x86sim")

status = comp.clean(target="x86sim")

comp.build(target="x86sim")

comp.build(target="x86sim")

comp.build(target="x86sim")

comp.build(target="x86sim")

comp.build(target="x86sim")

comp.build(target="x86sim")

comp.build(target="x86sim")

comp.build(target="x86sim")

comp.build(target="hw")

comp.build(target="hw")

status = comp.remove_cfg_files(cfg_files=["aiecompiler.cfg", "aiecompiler.cfg", "aiecompiler.cfg"])

comp.build(target="hw")

comp.build(target="hw")

comp.build(target="x86sim")

status = comp.clean(target="x86sim")

status = comp.clean(target="hw")

comp = client.create_aie_component(name="matrix_blo", platform = "/tools/Xilinx/Vitis/2023.2/base_platforms/xilinx_vck190_base_202320_1/xilinx_vck190_base_202320_1.xpfm", template = "empty_aie_component")

comp = client.get_component(name="matrix_blo")
status = comp.update_top_level_file(top_level_file="src/project.cpp")

comp.build(target="x86sim")

comp.build(target="hw")

client.delete_component(name="matrix_blo")

comp = client.create_aie_component(name="matrix_blo", platform = "/tools/Xilinx/Vitis/2023.2/base_platforms/xilinx_vck190_base_202320_1/xilinx_vck190_base_202320_1.xpfm", template = "empty_aie_component")

status = comp.update_top_level_file(top_level_file="src/project.cpp")

client.delete_component(name="matrix_block")

comp.build(target="hw")

comp.build(target="hw")

comp.build(target="x86sim")

vitis.dispose()

