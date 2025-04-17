#  Chaos Encoder/Decoder – Mandelbrot Key Generator (C++)
coded by J.-P. Champeaux
jpc@irsamc.ups-tlse.fr

free to use for academic / non commercial purpose - please refere to author if use.

> A chaotic, Mandelbrot-based encoding/decoding tool written in modern C++.  
> Inspired by mathematical beauty and cryptographic fun.

![C++](https://img.shields.io/badge/C%2B%2B-17-blue) ![Status](https://img.shields.io/badge/status-stable-green) ![Version](https://img.shields.io/badge/version-1.0.0-blueviolet)

---
This project is a **proof of concept** showing how to use chaotic systems (specifically, the Mandelbrot set) to generate iteration keys for **robust encoding/decoding** of data like text or any encryption protocol.  
The core idea is to use a randomly generated 512-bit hexadecimal key to derive points in the Mandelbrot set, use those for iteration counts, and apply them to encode characters in a non-reversible way (without the correct key).

---

## 🔍 Features

- ✅ 512-bit random key generation (hexadecimal)
- ✅ Mandelbrot-based key derivation
- ✅ Positionally-aware encoding/decoding
- ✅ Base64 export/import for iteration keys
- ✅ Corruption detection (wrong key = garbled result)
- ✅ Colored console output (with `Cout_color.h`)
- ✅ Embedded version info (`version.h`)

---

## 🧬 How it works

1. **Key Generation**  
   A 512-bit (128 hex characters) random key is generated using `std::mt19937` and `chrono`.

2. **Mandelbrot Mapping**  
   The hex key is used to generate coordinates in the complex plane.  
   Each coordinate is iterated through the Mandelbrot equation `z = z² + c`.  
   The number of iterations before divergence is stored as a key.

3. **Text Encoding**  
   Each character is shifted by a combination of:
   - Its position
   - A custom pattern (`i + (i % 5)`)
   - The Mandelbrot iteration count

4. **Text Decoding**  
   The same key is used in reverse to retrieve the original message.

---

## 🧪 Example

```bash
Original Text:
Bonjour, ceci est un test a encoder 12

Encoded (Base64):
JkvtwcKRr8q6rrOcscm8u6Cjrc+rrcifrsqMtrSTw8CAw8Gc

Decoded with Correct Key:
Bonjour, ceci est un test a encoder 12

Decoded with Wrong Key:
⟪ÇqÅæ`Àúêc«$]¨'æóºÖ³¼D
