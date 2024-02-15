# 2024-02-09T17:45:06.464316
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

vitis.dispose()

