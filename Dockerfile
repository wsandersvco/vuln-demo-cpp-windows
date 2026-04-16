# Use specific version tag for reproducibility
FROM --platform=linux/amd64 gcc:13.2.0

RUN dpkg --add-architecture arm64

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        openjdk-17-jdk \
        curl \
        ca-certificates \
        make \
        zip \ 
        crossbuild-essential-arm64 \
        g++-aarch64-linux-gnu \
        gcc-aarch64-linux-gnu \
        binutils-aarch64-linux-gnu \
        libkrb5-dev:arm64 \
        libgssapi-krb5-2:arm64 \
        libk5crypto3:arm64 \
        libkrb5support0:arm64 \
        libcom-err2:arm64 \
        libkeyutils1:arm64 \
        libkrb5-dev \
        libgssapi-krb5-2 \
        libk5crypto3 \
        libkrb5support0 \
        libcom-err2 \
        libkeyutils1 && \
    curl -fsS https://tools.veracode.com/veracode-cli/install | sh && \
    curl -sSL https://sca-downloads.veracode.com/install | sh && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

WORKDIR /app

CMD ["bash"]
