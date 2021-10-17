FROM centos:7

# Update the base system
RUN yum -y update \
 && yum install -y centos-release-scl epel-release \
 && yum -y update \
 && yum clean all

# Install build tools
RUN yum -y install ccache cmake3 fuse-sshfs gcc gcc-c++ make ninja-build wget \
 && yum clean all

# Enable FUSE
RUN usermod -aG fuse root

# Install dependencies
RUN yum -y install libxcb-devel libxkbcommon-x11-devel mesa-libGL-devel zlib-devel \
 && yum clean all

# Install ICU
RUN mkdir /icu && cd /icu \
 && wget https://github.com/unicode-org/icu/releases/download/release-56-2/icu4c-56_2-src.tgz \
 && tar xf icu4c-56_2-src.tgz \
 && ls && cd icu \
 && ./source/runConfigureICU Linux \
 && make -j \
 && make install \
 && cd / && rm -r /icu 

# Install devtoolset-8 and git
RUN yum -y install devtoolset-8-toolchain rh-git218 \
 && yum clean all

# Copy and set the entry point
COPY entrypoint.sh /entrypoint.sh
ENTRYPOINT ["/entrypoint.sh"]
