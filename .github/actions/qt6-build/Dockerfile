FROM ghcr.io/maplibre/linux-builder:centos8-gcc11

USER 1001

# Copy and set the entry point
COPY entrypoint.sh /entrypoint.sh
ENTRYPOINT ["/entrypoint.sh"]
