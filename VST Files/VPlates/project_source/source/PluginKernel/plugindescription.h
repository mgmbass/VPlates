// --- CMAKE generated variables for your plugin

#include "pluginstructures.h"

#ifndef _plugindescription_h
#define _plugindescription_h

#define QUOTE(name) #name
#define STR(macro) QUOTE(macro)
#define AU_COCOA_VIEWFACTORY_STRING STR(AU_COCOA_VIEWFACTORY_NAME)
#define AU_COCOA_VIEW_STRING STR(AU_COCOA_VIEW_NAME)

// --- AU Plugin Cocoa View Names (flat namespace) 
#define AU_COCOA_VIEWFACTORY_NAME AUCocoaViewFactory_F165720072C43239B0CC2165A0CE33D6
#define AU_COCOA_VIEW_NAME AUCocoaView_F165720072C43239B0CC2165A0CE33D6

// --- BUNDLE IDs (MacOS Only) 
const char* kAAXBundleID = "developer.aax.vplates.bundleID";
const char* kAUBundleID = "developer.au.vplates.bundleID";
const char* kVST3BundleID = "developer.vst3.vplates.bundleID";

// --- Plugin Names 
const char* kPluginName = "Plate Verb";
const char* kShortPluginName = "Plate Verb";
const char* kAUBundleName = "VPlates";

// --- Plugin Type 
const pluginType kPluginType = pluginType::kFXPlugin;

// --- VST3 UUID 
const char* kVSTFUID = "{f1657200-72c4-3239-b0cc-2165a0ce33d6}";

// --- 4-char codes 
const int32_t kFourCharCode = 'asdf';
const int32_t kAAXProductID = 'asdf';
const int32_t kManufacturerID = 'VNDR';

// --- Vendor information 
const char* kVendorName = "RackAFX User";
const char* kVendorURL = "www.yourcompany.com";
const char* kVendorEmail = "help@yourcompany.com";

// --- Plugin Options 
const bool kWantSidechain = false;
const uint32_t kLatencyInSamples = 0;
const double kTailTimeMsec = 0.000000;
const bool kVSTInfiniteTail = false;
const bool kVSTSAA = false;
const uint32_t kVST3SAAGranularity = 1;
const uint32_t kAAXCategory = aaxPlugInCategory_None;

#endif
