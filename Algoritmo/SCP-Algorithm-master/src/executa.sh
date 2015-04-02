#!/bin/bash

luajit -b main.lua main.out
luajit -O3 main.out $1
