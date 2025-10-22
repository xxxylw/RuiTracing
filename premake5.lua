-- premake5.lua
workspace "RuiTracing"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "RuiTracing"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
include "Walnut/WalnutExternal.lua"

include "RuiTracing"