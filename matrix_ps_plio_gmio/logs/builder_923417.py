# 2024-02-08T15:09:43.951890
import vitis

client = vitis.create_client()
client.set_workspace(path="/home/yzwu/Desktop/soc_test")

status = client.set_preference(level = "WORKSPACE", device = "Versal", key = "Sysroot", value = "/opt/petalinux/2023.2/sysroots/cortexa72-cortexa53-xilinx-linux")

status = client.set_preference(level = "WORKSPACE", device = "Versal", key = "KernelImage", value = "/opt/xilinx/platforms/Image")

status = client.set_preference(level = "WORKSPACE", device = "Versal", key = "RootFS", value = "/opt/xilinx/platforms/rootfs.ext4")

status = client.add_platform_repos(platform=["/opt/xilinx/xrt"])

platform = client.create_platform_component(name = "platform",platform_xpfm_path = "/tools/Xilinx/Vitis/2023.2/base_platforms/xilinx_vck190_base_202320_1/xilinx_vck190_base_202320_1.xpfm")

platform = client.get_platform_component(name="platform")
status = platform.build()

domain = platform.add_domain(cpu = "psv_cortexa72_1",os = "standalone",name = "hello",display_name = "hello",support_app = "hello_world")

comp = client.create_app_component(name="hello_world",platform = "/home/yzwu/Desktop/soc_test/platform/export/platform/platform.xpfm",domain = "hello",template = "hello_world")

vitis.dispose()

