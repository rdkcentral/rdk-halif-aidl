# QEMU Emulator and vDevice Installation Manual

## Document Version

|Version|Date|Author|
|-------|----|-------|
|1.0|2025-06-13| vDevice Development Team|

## Introduction

The **QEMU emulator** is an essential tool for virtual device development, enabling flexible, cost-effective software testing without physical hardware.

**Benefits:**

* **Testing & Debugging:** Emulate diverse hardware architectures.
* **Flexibility:** Switch easily between device configurations.
* **Cost-Effective:** No need for physical prototypes.

By using QEMU, we can efficiently develop, test, and validate the vDevice backend and HAL components.

---

## Setup with QEMU Emulator

### Required Repositories

#### Poky (Yocto Project Reference Distribution)

```xml
<project name="poky.git"
  remote="yoctoproject"
  revision="kirkstone"
  clone-depth="1"
  path="poky" />
```

#### Meta-OpenEmbedded

```xml
<project name="meta-openembedded.git"
  remote="openembedded"
  revision="kirkstone"
  clone-depth="1"
  path="meta-openembedded" />
```

#### Meta-GStreamer1.0

```xml
<project name="OSSystems/meta-gstreamer1.0.git"
  remote="github"
  revision="master"
  clone-depth="1"
  path="meta-gstreamer1.0" />
```

---

## Yocto Build Environment

### Key Components

* **Poky Kirkstone**

  * Linux Kernel: 5.15

* **GStreamer 1.20.7**

  * Command: `gst-launch-1.0 --version`

* **XFCE4 Desktop Environment**

* **ALSA**

  * Packages: alsa-lib, alsa-plugins, alsa-state, alsa-utils, alsa-utils-scripts

### Build Steps

#### SSH Configuration

To avoid conflicts between organization GitHub and RDK Central GitHub:

```bash
Host github.code.rdkcentral.com
    IdentityFile <GitHub SSH key>
```

Refer to: [https://docs.github.com/en/authentication/connecting-to-github-with-ssh/adding-a-new-ssh-key-to-your-github-account](https://docs.github.com/en/authentication/connecting-to-github-with-ssh/adding-a-new-ssh-key-to-your-github-account)

#### Clone Repository

```bash
repo init -b develop -m vdevice.xml -u ssh://git@github.code.rdkcentral.com/rdkcentral/vdevice-manifest.git -q
repo sync -cd -j 16 --no-repo-verify -q
```

#### Environment Setup

```bash
export AIDL_BIN_DIR=/home/user/local/bin
```

Build AIDL compiler using docker:

```bash
sc docker run rdk-kirkstone /bin/bash
export AIDL_BIN_DIR=/home/user/local/bin
```

#### Yocto Environment

```bash
MACHINE=vdevice_x86-64 source scripts/setup-environment
```

#### Windows Support (MSYS2 UCRT64)

1. Download MSYS2 installer.
2. Run installer, update packages:

```bash
pacman -Syuu
```

3. Install additional tools:

```bash
pacman -S mingw-w64-ucrt-x86_64-gcc
```

---

## Running QEMU Emulator

### Copying the Rootfs and Kernel Image

```bash
mkdir -p /home/shm62/qemu
cp /path/to/core-image-vdevice-xfce-vdevice_x86-64-<timestamp>.rootfs.ext4 /home/shm62/qemu/
cp /path/to/bzImage--5.15.179+git0+<hash>.bin /home/shm62/qemu/
```

### Running QEMU

```bash
cd /home/shm62/qemu

qemu-system-x86_64.exe \
  -accel whpx \
  -cpu IvyBridge \
  -machine q35 \
  -kernel bzImage--5.15.179+git0+<hash>.bin \
  -append "video=1280x720 console=ttyS0 root=/dev/sda" \
  -drive if=none,id=hd,file=core-image-vdevice-xfce-vdevice_x86-64-<timestamp>.rootfs.ext4,format=raw \
  -device virtio-scsi-pci,id=scsi \
  -device scsi-hd,drive=hd \
  -serial mon:stdio \
  -smp 8 \
  -m 4096 \
  -display sdl,gl=on -vga none -device virtio-gpu-gl,max_outputs=1 \
  -device usb-tablet \
  -netdev user,id=network0 \
  -device virtio-net,netdev=network0 \
  -usb -device usb-host,vendorid=0x0bb4,productid=0x0a5f \
  -audiodev id=snd0,driver=sdl \
  -device ich9-intel-hda \
  -device hda-duplex,audiodev=snd0 \
  -nic user,ipv6=off,model=e1000,id=network_0,net=10.0.8.0/24,hostfwd=tcp:127.0.0.1:5522-:22
```

---

## Software Versions

| Component                   | Version                 |
| --------------------------- | ----------------------- |
| QEMU                        | Custom Build            |
| Kernel                      | 5.15.178-yocto-standard |
| GStreamer                   | 1.22.5                  |
| FFmpeg                      | 5.0.1                   |
| SDL2                        | 2.0.18                  |
| ALSA                        | 1.2.6                   |
| rdk-media-hal               | 0.4                     |
| rdk-gstreamer-media-plugins | 0.4                     |
| Android Binder              | Android 13.0.0\_r74     |

---

## Requirements

* vDevice image built using Yocto (aligned with RDK-E build practices)
* Vendor HAL buildable via Yocto (optional)
* VTS (Vendor Test Suites) independent of Yocto
* AIDL interfaces must generate source code independent of Yocto

---

## vDevice Yocto PoC

Repository: [https://github.com/rdkcentral/vdevice-manifest](https://github.com/rdkcentral/vdevice-manifest) (branch: kirkstone)

**Additional Repositories:**

* `meta-rdk-vendor-test-utils` (AIDL example)
* `meta-binder` (libbinder, liblog)
* `meta-vdevice` (customizations)

**Custom Work:**

* Kernel configuration to enable binder
* Kernel patch to disable binder security context checking
* Patches to meta-binder and meta-rdk-vendor-test-utils
* Build setup script

**TODO:**

* Remove manual patches from meta-binder and meta-rdk-vendor-test-utils
* Integrate AIDL compiler natively
* Create RDK-E version of vDevice manifest

---

## QEMU vDevice Productization Goals

* Create full-featured TV vDevice RDK-E Yocto product layer
* Use same OSS libraries and kernel as A4K
* Support 32-bit user space
* Operational AIDL & Binder
* Full Polaris AV HALs + VTS tests
* Full Polaris GStreamer components

---

## ALSA Configuration for QEMU

Edit `/etc/asound.conf`:

```plaintext
pcm.!default {
    type hw
    card 0
}

ctl.!default {
    type hw
    card 0
}

pcm.!default {
    type plug
    slave.pcm "hw:0,0"
}
```

---

## Testing Multimedia Playback

### Download Sample Video

```bash
wget https://test-videos.co.uk/vids/bigbuckbunny/mp4/h264/720/Big_Buck_Bunny_720_10s_2MB.mp4
```

### GStreamer Pipelines

#### Video + Audio Playback

```bash
gst-launch-1.0 filesrc location=Big_Buck_Bunny_720_10s_2MB.mp4 ! qtdemux name=demuxer \
  demuxer.video_0 ! queue ! rdkviddec ! rdkvidsink
```

#### Audio Test

```bash
GST_DEBUG=2 gst-launch-1.0 audiotestsrc freq=432 ! avenc_ac3 ! ac3parse ! rdkauddec ! rdkaudsink
```