TrueGuard

A lightweight SKSE plugin experiment for Skyrim SE/AE that draws a minimalist guard-duty HUD (DX11 + ImGui).
This repo is based on a CommonLibSSE

Status

Development discontinued. The project hit AV false-positive issues (e.g., Microsoft Defender / VirusTotal) specifically in Release due to the inline detour pattern used for D3D11 hooking. The code remains public for reference/learning.

Features (intended)
* DX11 overlay path compatible with ENB (Present/ResizeBuffers hook).
* Simple right-aligned UI panel (ImGui) intended to show:
* Guard status (On/Off duty)
* Opinion/Reputation
* Time left on duty
* Modern C++ / CMake layout.
* Source-first dependencies via submodules.
(Some items are prototypes; see code for current state.)
