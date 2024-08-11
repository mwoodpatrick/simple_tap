# simple_tap

Experiments with tap devices

Install needed tools:

* sudo apt install openvpn
* sudo apt install tshark

When installing wireshark:

On Debian and Debian derivatives such as Ubuntu, if you have installed Wireshark from a package, try running

    sudo dpkg-reconfigure wireshark-common

selecting "<Yes>" in response to the question

    Should non-superusers be able to capture packets?

adding yourself to the "wireshark" group by running

    sudo usermod -a -G wireshark {your username}

and then logging out and logging back in again.

# Build

Build the app:

    gcc -o tap_access tap_access.c

# Basic Steps

1. sudo ip tuntap add name tapint mode tap
1. sudo ip link set tapint up
1. sudo ip addr add 10.0.0.1/24 dev tapint
1. tshark -i tapint

In a seperate session:

1. tap_access

In a seperate session:

1. ping 10.0.0.1

## References

1. [Tun/Tap interface tutorial](https://backreference.org/2010/03/26/tuntap-interface-tutorial/index.html)
1. [Universal TUN/TAP device driver](https://www.kernel.org/doc/html/latest/networking/tuntap.html)
1. [Linux TUN/TAP virtual interfaces TAP Interface - Sample Access Episode 2](https://thelinuxchannel.org/2023/10/linux-tun-tap-virtual-network-interfaces-tap-interface-sample-access-via-c-code/)
1. [TUN/TAP devices in 5 Minute](https://amitniz.github.io/posts/understanding_tuntap/)
1. [Guide to Linux ip Command With Examples](https://www.baeldung.com/linux/ip-command-tutorial)
1. [Creating TUN/TAP interfaces in Linux](https://john-millikin.com/creating-tun-tap-interfaces-in-linux)
1. [TAP interfaces in WSL-2 #11912](https://github.com/microsoft/WSL/discussions/11912)

