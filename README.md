# Make Linux mainline driver for friendlyelec Edp Panel

- If you use NanopcT4,please enable overlay follow this:
https://github.com/EricaLinaG/armbian-boot-edp-overlay

- How install ?
```
make install
```

- The K116E drm_display_mode 's clock not to 60Hz, reason unknown, if clock is 60Hz, panel will blank.
- Now only support K116E
