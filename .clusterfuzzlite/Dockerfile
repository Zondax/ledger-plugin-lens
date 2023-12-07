FROM ghcr.io/ledgerhq/ledger-app-builder/ledger-app-builder-lite:latest AS LITE_BUILDER

# Base image with clang toolchain
FROM gcr.io/oss-fuzz-base/base-builder:v1

# Copy the project's source code.
COPY . $SRC/ledger-plugin-lens
COPY --from=LITE_BUILDER /opt/nanox-secure-sdk $SRC/ledger-plugin-lens/BOLOS_SDK

# Working directory for build.sh
WORKDIR $SRC/ledger-plugin-lens

# Copy build.sh into $SRC dir.
COPY ./.clusterfuzzlite/build.sh $SRC/
