# 2024-02-12T16:56:15.658163
import vitis

client = vitis.create_client()
client.set_workspace(path="/home/yzwu/Desktop/soc_test")

status = client.set_preference(level = "WORKSPACE", device = "Versal", key = "Sysroot", value = "/opt/petalinux/2023.2/sysroots/cortexa72-cortexa53-xilinx-linux")

status = client.set_preference(level = "WORKSPACE", device = "Versal", key = "KernelImage", value = "/opt/xilinx/platforms/Image")

status = client.set_preference(level = "WORKSPACE", device = "Versal", key = "RootFS", value = "/opt/xilinx/platforms/rootfs.ext4")

comp = client.get_component(name="matrix_plio_vec")
comp.build(target="hw")

comp = client.get_component(name="matrix_plio")
comp.build(target="hw")

client.delete_component(name="matrix_plio_vec")

comp.build(target="hw")

comp.build(target="hw")

comp.build(target="hw")

comp.build(target="x86sim")

comp.build(target="hw")

comp.build(target="x86sim")

client.delete_component(name="matrix_blo")

vitis.dispose()

