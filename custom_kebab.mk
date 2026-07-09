#
# Copyright (C) 2018 The LineageOS Project
#
# SPDX-License-Identifier: Apache-2.0
#

# Inherit from those products. Most specific first.
$(call inherit-product, $(SRC_TARGET_DIR)/product/core_64_bit.mk)
TARGET_SUPPORTS_OMX_SERVICE := false
$(call inherit-product, $(SRC_TARGET_DIR)/product/full_base_telephony.mk)

# Inherit from kebab device
$(call inherit-product, device/oneplus/kebab/device.mk)

# Inherit some common PixelOS stuff.
$(call inherit-product, vendor/custom/config/common_full_phone.mk)

PRODUCT_NAME := custom_kebab
PRODUCT_DEVICE := kebab
PRODUCT_MANUFACTURER := OnePlus
PRODUCT_BRAND := OnePlus
PRODUCT_MODEL := KB2005

PRODUCT_GMS_CLIENTID_BASE := android-oneplus

PRODUCT_MODEL_FOR_ATTESTATION := KB2005
PRODUCT_BRAND_FOR_ATTESTATION := OnePlus
PRODUCT_NAME_FOR_ATTESTATION := OnePlus8T
PRODUCT_DEVICE_FOR_ATTESTATION := OnePlus8T
PRODUCT_MANUFACTURER_FOR_ATTESTATION := OnePlus

BUILD_FINGERPRINT := OnePlus/OnePlus8T/OnePlus8T:16/BP4A.251205.006/R.1a46c89-1_1:user/release-keys
PRODUCT_BUILD_PROP_OVERRIDES += \
    BuildDesc="qssi-user 16 BP4A.251205.006 R.1a46c89-1_1 release-keys" \
    BuildFingerprint=OnePlus/OnePlus8T/OnePlus8T:16/BP4A.251205.006/R.1a46c89-1_1:user/release-keys \
    DeviceName=OnePlus8T \
    DeviceProduct=OnePlus8T

-include vendor/lineage-priv/keys/keys.mk
