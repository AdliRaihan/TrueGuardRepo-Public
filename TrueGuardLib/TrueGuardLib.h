// TrueGuardLib.h : Include file for standard system include files,
// or project specific include files.

#pragma once
#define DLLEXPORT __declspec(dllexport)


#include <iostream>

#pragma warning(push)
#include <RE/Skyrim.h>
#include <REL/Relocation.h>
#include <SKSE/SKSE.h>
#include <SKSE/Interfaces.h>

/* Utilities */
namespace logger = SKSE::log;

