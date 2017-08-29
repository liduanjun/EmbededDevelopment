Security extensions[edit]
TrustZone (for Cortex-A profile)[edit]
The Security Extensions, marketed as TrustZone Technology, is in ARMv6KZ and later application profile architectures. It provides a low-cost alternative to adding another dedicated security core to an SoC, by providing two virtual processors backed by hardware based access control. This lets the application core switch between two states, referred to as worlds (to reduce confusion with other names for capability domains), in order to prevent information from leaking from the more trusted world to the less trusted world. This world switch is generally orthogonal to all other capabilities of the processor, thus each world can operate independently of the other while using the same core. Memory and peripherals are then made aware of the operating world of the core and may use this to provide access control to secrets and code on the device.[85]

Typically, a rich operating system is run in the less trusted world, with smaller security-specialized code in the more trusted world, aiming to reduce the attack surface. Typical applications include DRM functionality for controlling the use of media on ARM-based devices,[86] and preventing any unapproved use of the device.

One option for the more trusted world is TrustZone Software, a TrustZone optimised version of the Trusted Foundations Software developed by Trusted Logic Mobility. Trusted Foundations Software was acquired by Gemalto. Giesecke & Devrient developed a rival implementation named Mobicore. In April 2012 ARM Gemalto and Giesecke & Devrient combined their TrustZone portfolios into a joint venture Trustonic.[87][88]

In practice, since the specific implementation details of proprietary TrustZone implementations have not been publicly disclosed for review, it is unclear what level of assurance is provided for a given threat model, but they are not immune from attack.[89][90]

Open Virtualization[91] and T6[92] are open source implementations of the trusted world architecture for TrustZone.

AMD has licensed and incorprorated TrustZone technology into its Secure Processor Technology.[93] Enabled in some but not all products, AMD's APUs include a Cortex-A5 processor for handling secure processing.[94][95][96] In fact, the Cortex-A5 TrustZone core had been included in earlier AMD products, but was not enabled due to time constraints.[95]

Samsung Knox uses TrustZone for purposes such as detecting modifications to the kernel.[97]