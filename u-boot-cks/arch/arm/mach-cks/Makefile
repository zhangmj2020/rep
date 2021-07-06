# SPDX-License-Identifier: GPL-2.0+
#
# Copyright (c) 2014 Google, Inc


obj-$(CONFIG_CKS_A53T28) += a53t28/
obj-$(CONFIG_CKS_SMARTNIC) += smartnic/
obj-$(CONFIG_CKS_CKS6Q64) += cks6q64/
obj-$(CONFIG_CKS_CKS6Q32) += cks6q32/

# Now add SPL/TPL objects back into the main build
obj-$(CONFIG_SPL_BUILD) += $(obj-spl-y)
obj-$(CONFIG_TPL_BUILD) += $(obj-tpl-y)
