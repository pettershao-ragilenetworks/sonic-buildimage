# libgcovpreload package

GCOV_PRELOAD_VERSION = 0.0.1
GCOV_PRELOAD_VERSION_FULL = $(GCOV_PRELOAD_VERSION)-1

export GCOV_PRELOAD_VERSION GCOV_PRELOAD_VERSION_FULL

LIBGCOV_PRELOAD = libgcovpreload_$(GCOV_PRELOAD_VERSION_FULL)_$(CONFIGURED_ARCH).deb
$(LIBGCOV_PRELOAD)_SRC_PATH = $(SRC_PATH)/preload

SONIC_MAKE_DEBS += $(LIBGCOV_PRELOAD)
