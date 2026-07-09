/*
 * Copyright (C) 2026 The PixelOS Project
 * SPDX-License-Identifier: Apache-2.0
 */

#include <cstdlib>
#include <string.h>
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>
#include <android-base/properties.h>

#include "property_service.h"
#include "vendor_init.h"

using android::base::GetProperty;

void property_override(const char* prop, const char* value) {
    auto pi = (prop_info*)__system_property_find(prop);
    if (pi != nullptr)
        __system_property_update(pi, value, strlen(value));
    else
        __system_property_add(prop, strlen(prop), value, strlen(value));
}

void vendor_load_properties() {
    if (access("/system/bin/recovery", F_OK) == 0 ||
        GetProperty("ro.bootmode", "") == "charger")
        return;

    // Regional variant from rf_version (stock pattern)
    auto rf_version = std::stoi(GetProperty("ro.boot.rf_version", "0"));
    const char* model = "KB2005";
    const char* name  = "OnePlus8T";
    switch (rf_version) {
        case 11: model = "KB2000";                 break; // CN
        case 12: model = "KB2007"; name = "OnePlus8T_TMO"; break; // TMO
        case 13: model = "KB2001";                 break; // IN
        case 14: model = "KB2003"; name = "OnePlus8T_EEA"; break; // EU
        default: model = "KB2005";                 break; // NA
    }

    // Brand / manufacturer
    property_override("ro.product.brand", "OnePlus");
    property_override("ro.product.manufacturer", "OnePlus");

    // Attestation model — align with regional model (stock has empty, but
    // build-time hardcodes KB2005; override to match runtime model)
    property_override("ro.product.model_for_attestation", model);

    // Regional model
    property_override("ro.product.model", model);
    property_override("ro.product.name", name);
    property_override("ro.product.device", "OnePlus8T");

    // Build flavor / product — aligned with stock OxygenOS
    // Stock: ro.build.flavor=qssi-user, ro.build.product=<model_number>
    property_override("ro.build.flavor", "qssi-user");
    property_override("ro.build.product", model);

    // System partition identity (GSI/GKI — stock my_manifest overrides these
    // to OnePlus values, but build-time origin is qssi/ossi/oplus)
    property_override("ro.product.system.brand", "OnePlus");
    property_override("ro.product.system.device", "OnePlus8T");
    property_override("ro.product.system.manufacturer", "OnePlus");
    property_override("ro.product.system.model", model);
    property_override("ro.product.system.name", name);

    // System_ext partition (Qualcomm BSP layer — stock overrides to OnePlus)
    property_override("ro.product.system_ext.brand", "OnePlus");
    property_override("ro.product.system_ext.device", "OnePlus8T");
    property_override("ro.product.system_ext.manufacturer", "OnePlus");
    property_override("ro.product.system_ext.model", model);
    property_override("ro.product.system_ext.name", name);

    // Product partition identity
    property_override("ro.product.product.brand", "OnePlus");
    property_override("ro.product.product.device", "OnePlus8T");
    property_override("ro.product.product.manufacturer", "OnePlus");
    property_override("ro.product.product.model", model);
    property_override("ro.product.product.name", name);

    // Vendor partition identity
    property_override("ro.product.vendor.brand", "OnePlus");
    property_override("ro.product.vendor.device", "OnePlus8T");
    property_override("ro.product.vendor.manufacturer", "OnePlus");
    property_override("ro.product.vendor.model", model);
    property_override("ro.product.vendor.name", name);

    // ODM partition identity
    property_override("ro.product.odm.brand", "OnePlus");
    property_override("ro.product.odm.device", "OnePlus8T");
    property_override("ro.product.odm.manufacturer", "OnePlus");
    property_override("ro.product.odm.model", model);
    property_override("ro.product.odm.name", name);

    // Vendor_dlkm partition identity
    property_override("ro.product.vendor_dlkm.brand", "OnePlus");
    property_override("ro.product.vendor_dlkm.device", "OnePlus8T");
    property_override("ro.product.vendor_dlkm.manufacturer", "OnePlus");
    property_override("ro.product.vendor_dlkm.model", model);
    property_override("ro.product.vendor_dlkm.name", name);

    // Vendor SDK version (stock value from OxygenOS 14 vendor)
    property_override("ro.vendor.build.version.sdk", "30");
}
