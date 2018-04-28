This is an attempt at an emulator for a belt machine -based CPU. It is modelled heavily on the Mill Architecture, though many differences exist. These differences exist because A.) they make emulation easier, and B.) not all features of the Mill architecture have been unveiled yet.

---

This CPU is designed to function similarly to the Mill-Gold core, though with a variety of differences.

There are:
  * 8 Input units
  * 8 ALU/FPUs
  * 8 Call Units
  * 4 Pick Units
  * 4 Output Units
  * 16 Retire Stations
  * 256B SIMD
  * 512B Scratchpad

This core can execute 32 instructions per cycle.
