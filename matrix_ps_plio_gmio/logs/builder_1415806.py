# 2024-02-12T14:34:21.443053
import vitis

client = vitis.create_client()
client.set_workspace(path="/home/yzwu/Desktop/soc_test")

status = client.set_preference(level = "WORKSPACE", device = "Versal", key = "Sysroot", value = "/opt/petalinux/2023.2/sysroots/cortexa72-cortexa53-xilinx-linux")

status = client.set_preference(level = "WORKSPACE", device = "Versal", key = "KernelImage", value = "/opt/xilinx/platforms/Image")

status = client.set_preference(level = "WORKSPACE", device = "Versal", key = "RootFS", value = "/opt/xilinx/platforms/rootfs.ext4")

comp = client.get_component(name="matrix_plio_vec")
comp.build(target="x86sim")

comp.build(target="x86sim")

comp.build(target="x86sim")

comp.build(target="x86sim")

comp.build(target="x86sim")

comp.build(target="x86sim")

comp.build(target="hw")

comp.build(target="x86sim")

comp = client.get_component(name="aie_component")
comp.build(target="x86sim")

client.delete_component(name="matrix_plio_vec")

comp = client.create_aie_component(name="matrix_plio_vec", platform = "/tools/Xilinx/Vitis/2023.2/base_platforms/xilinx_vck190_base_202320_1/xilinx_vck190_base_202320_1.xpfm", template = "empty_aie_component")

comp = client.get_component(name="matrix_plio_vec")
status = comp.update_top_level_file(top_level_file="src/project.cpp")

comp.build(target="x86sim")

comp.build(target="x86sim")

comp.build(target="x86sim")

comp.build(target="x86sim")

comp.build(target="x86sim")

comp.build(target="x86sim")

comp.build(target="hw")

comp.build(target="x86sim")

comp.build(target="x86sim")

comp.build(target="x86sim")

comp.build(target="x86sim")

comp.build(target="hw")

comp.build(target="hw")

comp.build(target="x86sim")

comp.build(target="x86sim")

comp.build(target="x86sim")

comp.build(target="hw")

comp.build(target="x86sim")

comp.build(target="hw")

comp.build(target="x86sim")

comp.build(target="hw")

comp.build(target="x86sim")

comp.build(target="hw")

comp.build(target="hw")

comp = client.get_component(name="matrix_plio")
comp.build(target="hw")

vitis.dispose()

