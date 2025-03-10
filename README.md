# Library that encompasses multiple sensors as a simple interface.

Link this library by adding it as subdirectort and linking your application with `msensor_library`

## Scan files

Scan files are generates using protobuf. The convention is that the number of bytes to follow come before the serialized data.

### Systemd examples and embedded deployment
Useful hints for systemd installation for services.
Place them onto /etc/system/system/<name>.service

## udev dependant example (optional)
- Find device info: `udevadm info --name=/dev/ttyUSB0`
- Collect "idVendor", "idProduct" information.
- Write `SUBSYSTEM=="tty", ATTRS{idVendor}=="10c4", ATTRS{idProduct}=="ea60", SYMLINK+="my_usb_device", MODE="0666`
- Use `my_usb_device` as udev event.
- Debug with `udevadm control --reload-rules` and `udevadm trigger`

```
[Unit]
Description=RPLidar publisher
Requires=dev-ttyUSB0.device
After=dev-ttyUSB0.device

[Service]
Type=simple
ExecStart=/usr/local/bin/rplidar_publisher /dev/ttyUSB0

[Install]
WantedBy=multi-user.target
```

## Common example.
```
[Unit]
Description=GL Proxy Service
After=network.target

[Service]
Type=simple
ExecStart=/usr/local/bin/gl_proxy localhost:50051 192.168.1.50:50051

[Install]
WantedBy=multi-user.target
```

