# Project

Windows natively utilizes many HID controls, exposing hardware integration-points to enhance user-experience.  While HID is a well-understood industry standard, the great flexibility of HID Report descriptors introduces complexity for the consumer (e.g. Applications, Hosts) to parse and support, so only a subset of what HIDs can describe may be supported (with great variance amongst consumers).  The inevitability of errors/deviations in shipped device/consumer implementations from the HID-spec and the need to maintain backwards compatibility, further reduce what can be usefully described.

This project provides reference-implementations of HIDs that Windows natively consumes as hardware integration-points (e.g. Shell-interaction, Application-WindowMessages, UserMode APIs).  (*Note: 3rd-Party applications are naturally not limited to only what Windows natively consumes*).  References document (inline) any Windows expectations/limitations/work-arounds, and generally why things are the way they are.

> References are intended to be used as a starting-point for 3rd-Party HID vendors, and to be consumed as-is by hobbyists.

> This project is available as a library via the [Arduino Package Manager](https://reference.arduino.cc/reference/en/libraries/microsoft_hidforwindows/).  Search for `Microsoft_HidForWindows`.

See also the [Waratah project](https://github.com/microsoft/hidtools) for HID Descriptor composition.

## Supported Devices

> Additional devices will be continually added over the coming months.  To make suggestions for the next device-type, please file an issue.

- Consumer Control  (see `Microsoft_HidConsumerControl.h`)
- LampArray (see `Microsoft_HidLampArray.h`)
  - New support in Windows as part of [Dynamic Lighting](https://blogs.windows.com/windows-insider/2023/06/07/announcing-windows-11-insider-preview-build-23475/)
- System Control (see `Microsoft_HidSystemControl.h`)
- Telephony Headset (see `Microsoft_HidTelephonyHeadset.h`)
- Wireless Radio Control (see `Microsoft_HidWirelessRadioControl.h`)

## Caveats
- Untested on non-Windows systems (e.g. macOS, Linux, etc…)
- Comprehension/simplicity was always chosen over efficiency  (e.g. multiple Reports used, where one would be sufficient).  See [HID-spec](https://usb.org/document-library/device-class-definition-hid-111) and [Waratah](https://github.com/microsoft/hidtools) for rolling-your-own Report Descriptor.
- A subset of HID Report Descriptor variations within the HID-spec are naturally supported, but likely not all.
- Documented expectations/work-arounds may change at any time, and do not guarantee compatibility.
  - Last Validated on Windows 11 (22621.1702) (`22621.1.amd64fre.ni_release.220506-1250`)

## Contributing

This project welcomes contributions and suggestions.  Most contributions require you to agree to a
Contributor License Agreement (CLA) declaring that you have the right to, and actually do, grant us
the rights to use your contribution. For details, visit https://cla.opensource.microsoft.com.

When you submit a pull request, a CLA bot will automatically determine whether you need to provide
a CLA and decorate the PR appropriately (e.g., status check, comment). Simply follow the instructions
provided by the bot. You will only need to do this once across all repos using our CLA.

This project has adopted the [Microsoft Open Source Code of Conduct](https://opensource.microsoft.com/codeofconduct/).
For more information see the [Code of Conduct FAQ](https://opensource.microsoft.com/codeofconduct/faq/) or
contact [opencode@microsoft.com](mailto:opencode@microsoft.com) with any additional questions or comments.

## Trademarks

This project may contain trademarks or logos for projects, products, or services. Authorized use of Microsoft 
trademarks or logos is subject to and must follow 
[Microsoft's Trademark & Brand Guidelines](https://www.microsoft.com/en-us/legal/intellectualproperty/trademarks/usage/general).
Use of Microsoft trademarks or logos in modified versions of this project must not cause confusion or imply Microsoft sponsorship.
Any use of third-party trademarks or logos are subject to those third-party's policies.
