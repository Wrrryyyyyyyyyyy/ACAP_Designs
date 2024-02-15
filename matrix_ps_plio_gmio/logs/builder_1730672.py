# 2024-02-13T11:11:40.324871
import vitis

client = vitis.create_client()
client.set_workspace(path="/home/yzwu/Desktop/soc_test")

status = client.set_preference(level = "WORKSPACE", device = "Versal", key = "Sysroot", value = "/opt/petalinux/2023.2/sysroots/cortexa72-cortexa53-xilinx-linux")

status = client.set_preference(level = "WORKSPACE", device = "Versal", key = "KernelImage", value = "/opt/xilinx/platforms/Image")

status = client.set_preference(level = "WORKSPACE", device = "Versal", key = "RootFS", value = "/opt/xilinx/platforms/rootfs.ext4")

vitis.dispose()

