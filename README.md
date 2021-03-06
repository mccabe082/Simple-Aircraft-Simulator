[![Join the team using Discord: https://discord.gg/6zMa4Tp](https://img.shields.io/badge/Discord-collaborate-brightgreen.svg)](https://discord.gg/6zMa4Tp)
[![Build status](https://ci.appveyor.com/api/projects/status/07276mey39n8kaob?svg=true)](https://ci.appveyor.com/project/DavidMcCabe/simpleircraftsimulator)


# F16-Simulation

Numerical simulation of an F16 aircraft.This non-linear statespace model is a port of an old Matlab project I wrote ages ago.  The model originally came from the book:
[Aircraft Control and Simulation](https://www.google.com/search?q=Aircraft+Control+and+Simulation&source=lnms&tbm=isch&sa=X&ved=2ahUKEwjbz6vpkNfoAhVCi1wKHYkKBSIQ_AUoAXoECBsQAw&biw=1506&bih=712#imgrc=0XpnQJDE3oj5dM)
- [dynamic_simulation_of_aircraft](docs/dynamic_simulation_of_aircraft.md)

> **Note: This project currently requires [Boost 1.71.0](https://www.boost.org/users/history/version_1_71_0.html)**


## Bilinear Lookup Table
```xml
<LookupTable2D description="e^(-(x^2)-(y^2))">
  <Column description="x"> -1, -0.8, -0.6 <Column>
  <Row description="y">  0, 0.2, 0.4, 0.6, 0.8, 1 <Row>
  <Values>
    <Row> 0.367879441 0.527292424 0.697676326 </Row>
    <Row> 0.353454682 0.506616992 0.670320046 </Row>
    <Row> 0.313486181 0.449328964 0.594520548 </Row>
    <Row> 0.256660777 0.367879441 0.486752256 </Row>
    <Row> 0.193980042 0.2780373   0.367879441 </Row>
    <Row> 0.135335283 0.193980042 0.256660777 </Row>
  </Values>
</LookupTable2D>
```
