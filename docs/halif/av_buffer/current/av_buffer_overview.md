# Overview: AV Buffer HAL

The **AV Buffer HAL** manages both secure and non-secure memory heaps and pools for the media pipeline and related A/V HAL components.

- An **AV buffer** typically stores audio or video data, which may be in either encrypted or clear form.
- **Secure memory buffers** handle decrypted data when DRM, conditional access, or other secure decryption mechanisms are used.
- **Non-secure memory** is allocated for encrypted data from a media player source until it is decrypted into a secure memory buffer.
- If a media player processes only clear (unencrypted) audio or video data, **non-secure memory buffers** can be used throughout from source to decoder.
- AV memory buffers are referenced by **handles** as they move through the media pipeline and across HAL interfaces.

