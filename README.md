# IEEE 754 Float Converter (CS211)

This project implements binary ↔ decimal conversion, and decimal ↔ IEEE 754 encoding and decoding using C.  
It was developed as part of **CS211: Computer Architecture** at Rutgers University (Spring 2025).

---

##  Features

###  Integer Conversions

- Binary to unsigned decimal
- Binary to signed magnitude / one’s complement / two’s complement
- Decimal to binary (unsigned & signed formats)

###  IEEE 754 Floating-Point Support

- Convert IEEE 754 binary → decimal (`ieee754_to_decimal`)
- Convert decimal → IEEE 754 binary (`decimal_to_ieee754_binary`)
- Customizable bit-widths: exponent & mantissa bits
- Handles special values: 0, Infinity, NaN, Denormals
- Supports rounding modes:
  - `ROUNDUP` (0)
  - `ROUNDDOWN` (1)
  - `ROUNDTOEVEN` (2)

---

##  Files

- `pa2.c`: All conversion logic (no external libraries used except stdlib/math)
- `README.md`: Project overview

---

##  Compilation & Usage

```bash
gcc pa2.c -o converter -lm
./converter
