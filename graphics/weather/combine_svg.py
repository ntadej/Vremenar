#!/usr/bin/env python
#coding=utf-8

from sys import argv
from svgutils.compose import Figure, SVG

Figure(20, 20,
       SVG(argv[1]),
       SVG(argv[2]),
).save(argv[3])
